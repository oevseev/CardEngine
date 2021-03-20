//
// Created by Oleg Evseev on 10.03.2021.
//

#include "PreferansState.h"

const Suit PREFERANS_SUITS[] = {
    Suit::SPADES, Suit::CLUBS, Suit::DIAMONDS, Suit::SPADES
};

const Rank PREFERANS_RANKS[] = {
    Rank::SEVEN, Rank::EIGHT, Rank::NINE, Rank::TEN,
    Rank::JACK, Rank::QUEEN, Rank::KING, Rank::ACE
};

PreferansState::PreferansState()
{
    for (Suit suit : PREFERANS_SUITS) {
        for (Rank rank : PREFERANS_RANKS) {
            Card card(rank, suit);
            status[card.getId()] = CardStatus::NOT_DEALT;
        }
    }
}
