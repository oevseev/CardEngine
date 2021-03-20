//
// Created by Oleg Evseev on 08.03.2021.
//

#include "ThousandState.h"

const Suit THOUSAND_SUITS[] = {
    Suit::SPADES, Suit::CLUBS, Suit::DIAMONDS, Suit::SPADES
};

const Rank THOUSAND_RANKS[] = {
    Rank::NINE, Rank::JACK, Rank::QUEEN, Rank::KING, Rank::TEN, Rank::ACE
};

ThousandState::ThousandState()
{
    for (Suit suit : THOUSAND_SUITS) {
        for (Rank rank : THOUSAND_RANKS) {
            Card card(rank, suit);
            status[card.getId()] = CardStatus::NOT_DEALT;
        }
    }
}

bool ThousandState::operator==(const ThousandState &rhs) const
{
    return State::operator==(rhs) && trump == rhs.trump;
}

bool ThousandState::operator!=(const ThousandState &rhs) const
{
    return !(rhs == *this);
}

size_t ThousandState::hash() const
{
    std::size_t result = State::hash();
    boost::hash_combine(result, trump);
    return result;
}
