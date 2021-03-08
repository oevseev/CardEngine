//
// Created by Oleg Evseev on 08.03.2021.
//

#include "ThousandDeal.h"

const Card thousandDeck[] = {
    {Rank::NINE, Suit::SPADES},
    {Rank::JACK, Suit::SPADES},
    {Rank::QUEEN, Suit::SPADES},
    {Rank::KING, Suit::SPADES},
    {Rank::TEN, Suit::SPADES},
    {Rank::ACE, Suit::SPADES},
    {Rank::NINE, Suit::CLUBS},
    {Rank::JACK, Suit::CLUBS},
    {Rank::QUEEN, Suit::CLUBS},
    {Rank::KING, Suit::CLUBS},
    {Rank::TEN, Suit::CLUBS},
    {Rank::ACE, Suit::CLUBS},
    {Rank::NINE, Suit::DIAMONDS},
    {Rank::JACK, Suit::DIAMONDS},
    {Rank::QUEEN, Suit::DIAMONDS},
    {Rank::KING, Suit::DIAMONDS},
    {Rank::TEN, Suit::DIAMONDS},
    {Rank::ACE, Suit::DIAMONDS},
    {Rank::NINE, Suit::HEARTS},
    {Rank::JACK, Suit::HEARTS},
    {Rank::QUEEN, Suit::HEARTS},
    {Rank::KING, Suit::HEARTS},
    {Rank::TEN, Suit::HEARTS},
    {Rank::ACE, Suit::HEARTS},
};

ThousandDeal::ThousandDeal()
{
    State state;
    for (auto card : thousandDeck) {
        state.status[card.getId()] = CardStatus::NOT_DEALT;
    }
    states.push_back(state);
    currentState = states.begin();
}

int ThousandDeal::getPlayerCount() const
{
    return 3;
}
