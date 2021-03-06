//
// Created by Oleg Evseev on 18.03.2021.
//

#include "DealImpl.h"

#include "preferans/PreferansState.h"
#include "thousand/ThousandState.h"

template<typename StateT>
DealImpl<StateT>::DealImpl()
{
    states.emplace_back();
    currentState = states.begin();
}

template<typename StateT>
void DealImpl<StateT>::nextState()
{
    if (std::distance(currentState, states.end()) != 1) {
        currentState++;
    }
}

template<typename StateT>
void DealImpl<StateT>::previousState()
{
    if (currentState != states.begin()) {
        currentState--;
    }
}

template<typename StateT>
State &DealImpl<StateT>::getCurrentState() const
{
    return *currentState;
}

template<typename StateT>
void DealImpl<StateT>::playCard(Card card)
{
    if (!canPlayCard(*currentState, card)) {
        return;
    }
    
    states.erase(std::next(currentState), states.end());
    StateT newState = playCard(*currentState, card, 1).first;
    currentState = states.insert(states.end(), newState);
}

template<typename StateT>
std::pair<int, std::vector<State>> DealImpl<StateT>::evaluateCurrentState(Solver &solver) const
{
    std::vector<State> result;
    auto [score, states] = evaluateState(solver, *currentState);
    std::copy(states.begin(), states.end(), result.begin());
    return {score, result};
}

template<typename StateT>
std::vector<Card> DealImpl<StateT>::getValidMoves(const StateT &state) const
{
    bool hasTrumps = false, hasLeadSuit = false;
    for (int i = 1; i <= NUM_CARDS; i++) {
        if (state.status[i] != CardStatus::IN_HAND || state.owner[i] != state.currentPlayer) {
            continue;
        }
        Card cardInHand(i);
        hasTrumps |= cardInHand.suit == getTrump();
        hasLeadSuit |= cardInHand.suit == state.leadSuit;
    }

    std::vector<Card> result;
    for (int i = 1; i <= NUM_CARDS; i++) {
        Card card(i);

        if (state.status[card.getId()] != CardStatus::IN_HAND ||
            state.owner[card.getId()] != state.currentPlayer)
        {
            continue;
        }

        if (state.leadSuit != Suit::NONE) {
            if (hasLeadSuit && card.suit != state.leadSuit) {
                continue;
            }
            if (!hasLeadSuit && hasTrumps && card.suit != getTrump()) {
                continue;
            }
        }

        result.push_back(card);
    }

    return result;
}

template<typename StateT>
bool DealImpl<StateT>::canPlayCard(const StateT &state, Card card) const
{
    auto validMoves = getValidMoves(state);
    return std::any_of(validMoves.begin(), validMoves.end(), [&](const auto &c) -> decltype(auto) {
        return c == card;
    });
}

template<typename StateT>
std::vector<std::pair<Card, int>> DealImpl<StateT>::evaluatePossibleMoves(Solver &solver) const
{
    std::vector<std::pair<Card, int>> result{};
    for (int i = 1; i <= NUM_CARDS; i++) {
        Card card(i);
        if (!canPlayCard(*currentState, card)) {
            continue;
        }

        // TODO: Make player argument optional
        StateT newState = playCard(*currentState, card, 1).first;

        int score = evaluateState(solver, newState).first;
        result.emplace_back(card, score);
    }
    return result;
}

template class DealImpl<PreferansState>;
template class DealImpl<ThousandState>;
