//
// Created by Oleg Evseev on 10.03.2021.
//

#include "PreferansDeal.h"

const int PREFERANS_PLAYER_COUNT = 3;

static const int CARD_ORDER[] = {
    0, 8, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7
};

static inline bool beats(Card card1, Card card2, Suit trump)
{
    if (card2 == Card{}) {
        return true;
    }
    if (card1.suit == card2.suit) {
        return CARD_ORDER[static_cast<int>(card1.rank)] >
            CARD_ORDER[static_cast<int>(card2.rank)];
    }
    if (card1.suit == trump && card2.suit != trump) {
        return true;
    }

    return false;
}

PreferansDeal::PreferansDeal(Suit trump) : DealImpl<PreferansState>(), trump(trump)
{}

int PreferansDeal::getPlayerCount() const
{
    return PREFERANS_PLAYER_COUNT;
}

Suit PreferansDeal::getTrump() const
{
    return trump;
}

void PreferansDeal::setTrump(Suit newTrump)
{
    trump = newTrump;
}

std::pair<int, std::vector<PreferansState>> PreferansDeal::evaluateState(Solver &solver, const PreferansState &state) const
{
    return solver.evaluate(*this, state);
}

std::pair<PreferansState, int> PreferansDeal::playCard(const PreferansState &state, Card card, int player) const
{
    PreferansState nextState(state);
    nextState.status[card.getId()] = CardStatus::IN_TRICK;
    nextState.currentPlayer = state.currentPlayer % getPlayerCount() + 1;
    if (nextState.leadSuit == Suit::NONE) {
        nextState.leadSuit = card.suit;
    }

    int cardsInTrick = 0;
    for (int i = 1; i <= NUM_CARDS; i++) {
        if (nextState.status[i] == CardStatus::IN_TRICK) {
            cardsInTrick++;
        }
    }

    int score = 0;
    if (cardsInTrick == getPlayerCount()) {
        Card winningCard{};
        int winner = 0;

        for (int i = 1; i <= NUM_CARDS; i++) {
            if (nextState.status[i] != CardStatus::IN_TRICK) {
                continue;
            }
            Card cardInTrick(i);
            if ((cardInTrick.suit == nextState.leadSuit || cardInTrick.suit == trump) &&
                beats(cardInTrick, winningCard, trump))
            {
                winningCard = cardInTrick;
                winner = nextState.owner[i];
            }
            nextState.status[i] = CardStatus::PLAYED;
        }

        nextState.leadSuit = Suit::NONE;
        nextState.currentPlayer = winner;

        if (winner == player) {
            score++;
        }
    }

    return {nextState, score};
}
