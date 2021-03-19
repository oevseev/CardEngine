//
// Created by Oleg Evseev on 08.03.2021.
//

#include "ThousandDeal.h"

const int THOUSAND_PLAYER_COUNT = 3;

static const int CARD_ORDER[] = {
    0, 6, 0, 0, 0, 0, 0, 0, 0, 1, 5, 2, 3, 4
};

static const int CARD_VALUES[] = {
    0, 11, 0, 0, 0, 0, 0, 0, 0, 0, 10, 2, 3, 4
};

static const int MARRIAGE_VALUES[] = {
    0, 60, 80, 100, 40
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

ThousandDeal::ThousandDeal() : DealImpl<ThousandState>()
{}

int ThousandDeal::getPlayerCount() const
{
    return THOUSAND_PLAYER_COUNT;
}

Suit ThousandDeal::getTrump() const
{
    return currentState->trump;
}

std::pair<int, std::vector<ThousandState>> ThousandDeal::evaluateState(Solver &solver, const ThousandState &state) const
{
    return solver.evaluate(*this, state);
}

std::pair<ThousandState, int> ThousandDeal::playCard(const ThousandState &state, Card card, int player) const
{
    bool marriage = false;
    if (state.leadSuit == Suit::NONE) {
        int cardsInHand = 0;
        for (int i = 1; i <= NUM_CARDS; i++) {
            if (state.status[i] != CardStatus::IN_HAND || state.owner[i] != state.currentPlayer) {
                continue;
            }
            cardsInHand++;
        }

        if (cardsInHand < 8) {
            if (card.rank == Rank::QUEEN) {
                Card king(Rank::KING, card.suit);
                int kingId = king.getId();
                if (state.status[kingId] == CardStatus::IN_HAND &&
                    state.owner[kingId] == state.currentPlayer)
                {
                    marriage = true;
                }
            }
            else if (card.rank == Rank::KING) {
                Card queen(Rank::QUEEN, card.suit);
                int queenId = queen.getId();
                if (state.status[queenId] == CardStatus::IN_HAND &&
                    state.owner[queenId] == state.currentPlayer)
                {
                    marriage = true;
                }
            }
        }
    }

    ThousandState nextState(state);
    nextState.status[card.getId()] = CardStatus::IN_TRICK;
    nextState.currentPlayer = state.currentPlayer % getPlayerCount() + 1;
    if (nextState.leadSuit == Suit::NONE) {
        nextState.leadSuit = card.suit;
    }

    int score = 0;
    if (marriage) {
        score += MARRIAGE_VALUES[static_cast<int>(card.suit)];
        nextState.trump = card.suit;
    }

    int cardsInTrick = 0;
    for (int i = 1; i <= NUM_CARDS; i++) {
        if (nextState.status[i] == CardStatus::IN_TRICK) {
            cardsInTrick++;
        }
    }

    if (cardsInTrick == getPlayerCount()) {
        Card winningCard{};
        int winner = 0;
        int trickValue = 0;

        for (int i = 1; i <= NUM_CARDS; i++) {
            if (nextState.status[i] != CardStatus::IN_TRICK) {
                continue;
            }
            Card cardInTrick(i);
            if ((cardInTrick.suit == nextState.leadSuit || cardInTrick.suit == nextState.trump) &&
                beats(cardInTrick, winningCard, nextState.trump))
            {
                winningCard = cardInTrick;
                winner = nextState.owner[i];
            }
            trickValue += CARD_VALUES[static_cast<int>(cardInTrick.rank)];
            nextState.status[i] = CardStatus::PLAYED;
        }

        nextState.leadSuit = Suit::NONE;
        nextState.currentPlayer = winner;

        if (winner == player) {
            score += trickValue;
        }
    }

    return {nextState, score};
}
