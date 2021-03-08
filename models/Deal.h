//
// Created by Oleg Evseev on 06.03.2021.
//

#ifndef DEAL_H
#define DEAL_H


#include <vector>

#include "State.h"

class Deal
{
public:
    void nextState();
    void previousState();
    [[nodiscard]] State &getCurrentState() const;
    void playCard(Card card);

    [[nodiscard]] virtual int getPlayerCount() const = 0;

protected:
    void advance();

    std::vector<State> states;
    std::vector<State>::iterator currentState;
};


#endif //DEAL_H
