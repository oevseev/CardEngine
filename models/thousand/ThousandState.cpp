//
// Created by Oleg Evseev on 08.03.2021.
//

#include "ThousandState.h"

const int cardOrder[] = {0, 6, 0, 0, 0, 0, 0, 0, 0, 1, 5, 2, 3, 4};

const int cardValues[] = {0, 11, 0, 0, 0, 0, 0, 0, 0, 0, 10, 2, 3, 4};

const int marriageValues[] = {0, 60, 80, 100, 40};

inline bool beats(Card card1, Card card2, Suit trump)
{
    if (card2 == Card{}) {
        return true;
    }
    if (card1.suit == card2.suit) {
        return cardOrder[static_cast<int>(card1.rank)] > cardOrder[static_cast<int>(card2.rank)];
    }
    if (card1.suit == trump && card2.suit != trump) {
        return true;
    }

    return false;
}

std::vector<std::pair<ThousandState, int>> ThousandState::transitions() const
{
    std::vector<std::pair<ThousandState, int>> result;

    int cardsInTrick = 0;
    for (int i = 1; i <= NUM_CARDS; i++) {
        if (status[i] == CardStatus::IN_TRICK) {
            cardsInTrick++;
        }
    }

    if (cardsInTrick == THOUSAND_PLAYER_COUNT) {
        ThousandState nextState(*this);
        nextState.leadSuit = Suit::NONE;

        Card winningCard{};
        int winner = 0;
        int trickValue = 0;

        for (int i = 1; i <= NUM_CARDS; i++) {
            if (status[i] != CardStatus::IN_TRICK) {
                continue;
            }
            Card card(i);
            if ((card.suit == leadSuit || card.suit == trump) && beats(card, winningCard, trump)) {
                winningCard = card;
                winner = owner[i];
            }
            trickValue += cardValues[static_cast<int>(card.rank)];
            nextState.status[i] = CardStatus::PLAYED;
        }

        nextState.currentPlayer = winner;

        if (winner == 1) {
            result.emplace_back(nextState, trickValue);
        }
        else {
            result.emplace_back(nextState, 0);
        }

        return result;
    }

    int nextPlayer = currentPlayer % THOUSAND_PLAYER_COUNT + 1;

    int cardsInHand = 0;
    bool hasTrumps = false, hasLeadSuit = false;
    for (int i = 1; i <= NUM_CARDS; i++) {
        if (status[i] != CardStatus::IN_HAND || owner[i] != currentPlayer) {
            continue;
        }
        Card card(i);
        cardsInHand++;
        hasTrumps |= card.suit == trump;
        hasLeadSuit |= card.suit == leadSuit;
    }

    for (int i = 1; i <= NUM_CARDS; i++) {
        if (status[i] != CardStatus::IN_HAND || owner[i] != currentPlayer) {
            continue;
        }

        Card card(i);

        if (leadSuit == Suit::NONE) {
            if (hasLeadSuit && card.suit != leadSuit) {
                continue;
            }
            if (!hasLeadSuit && hasTrumps && card.suit != trump) {
                continue;
            }
        }

        ThousandState nextState(*this);
        nextState.status[i] = CardStatus::IN_TRICK;
        nextState.currentPlayer = nextPlayer;
        if (leadSuit == Suit::NONE) {
            nextState.leadSuit = card.suit;
        }

        result.emplace_back(nextState, 0);

        if (leadSuit == Suit::NONE && cardsInHand < 8) {
            bool marriage = false;
            if (card.rank == Rank::QUEEN) {
                Card king(Rank::KING, card.suit);
                int kingId = king.getId();
                marriage |= status[kingId] == CardStatus::IN_HAND && owner[kingId] == currentPlayer;
            }
            else if (card.rank == Rank::KING) {
                Card queen(Rank::QUEEN, card.suit);
                int queenId = queen.getId();
                marriage |= status[queenId] == CardStatus::IN_HAND && owner[queenId] == currentPlayer;
            }

            if (marriage) {
                ThousandState marriageState(nextState);

                marriageState.trump = card.suit;

                if (currentPlayer == 1) {
                    result.emplace_back(marriageState, marriageValues[static_cast<int>(marriageState.trump)]);
                }
                else {
                    result.emplace_back(marriageState, 0);
                }
            }
        }
    }

    return result;
}
