//
// Created by Oleg Evseev on 06.03.2021.
//

#include "Deal.h"

void Deal::nextState()
{
    if (std::distance(currentState, states.end()) != 1) {
        currentState++;
    }
}

void Deal::previousState()
{
    if (currentState != states.begin()) {
        currentState--;
    }
}

State &Deal::getCurrentState() const
{
    return *currentState;
}

void Deal::advance()
{
    states.erase(std::next(currentState), states.end());
    currentState = states.insert(currentState, *currentState);
    ++currentState;
}

void Deal::playCard(Card card)
{
    if (card == Card{}) {
        return;
    }
    advance();
    currentState->status[card.getId()] = CardStatus::IN_TRICK;
}
