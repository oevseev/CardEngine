//
// Created by Oleg Evseev on 07.03.2021.
//

#ifndef CARD_H
#define CARD_H


enum class Rank {
    NONE = 0, ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING
};

const int NUM_RANKS = 13;

enum class Suit {
    NONE = 0, CLUBS, DIAMONDS, HEARTS, SPADES
};

const int NUM_SUITS = 4;

constexpr int NUM_CARDS = NUM_RANKS * NUM_SUITS;

struct Card {
    Rank rank;
    Suit suit;

    inline Card()
        : rank(Rank::NONE)
        , suit(Suit::NONE)
    {}
    inline Card(int id)
        : rank(static_cast<Rank>((id - 1) % NUM_RANKS + 1))
        , suit(static_cast<Suit>((id - 1) / NUM_RANKS + 1))
    {}
    inline Card(Rank rank, Suit suit)
        : rank(rank), suit(suit)
    {}

    inline int getId() const {
        return (static_cast<int>(suit) - 1) * NUM_RANKS + static_cast<int>(rank);
    }

    inline bool operator==(const Card &rhs) const
    {
        return rank == rhs.rank && suit == rhs.suit;
    }
    inline bool operator!=(const Card &rhs) const
    {
        return !(rhs == *this);
    }
};


#endif //CARD_H
