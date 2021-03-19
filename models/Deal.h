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
    virtual void nextState() = 0;
    virtual void previousState() = 0;
    [[nodiscard]] virtual State &getCurrentState() const = 0;

    [[nodiscard]] virtual int getPlayerCount() const = 0;
    [[nodiscard]] virtual Suit getTrump() const;

    virtual void playCard(Card card) = 0;

    virtual std::pair<int, std::vector<State>> evaluateCurrentState(Solver &solver) const = 0;
    virtual std::vector<std::pair<Card, int>> evaluatePossibleMoves(Solver &solver) const = 0;
};

#endif //DEAL_H
