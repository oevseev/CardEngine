//
// Created by Oleg Evseev on 08.03.2021.
//

#ifndef THOUSANDDEAL_H
#define THOUSANDDEAL_H

#include "../DealImpl.h"
#include "ThousandState.h"

class ThousandDeal : public DealImpl<ThousandState>
{
public:
    ThousandDeal();

    [[nodiscard]] int getPlayerCount() const override;
    [[nodiscard]] Suit getTrump() const override;

    std::pair<int, std::vector<ThousandState>> evaluateState(Solver &solver, const ThousandState &state) const override;
    [[nodiscard]] bool canPlayCard(const ThousandState &state, Card card) const override;
    [[nodiscard]] std::pair<ThousandState, int> playCard(const ThousandState &state, Card card, int player) const override;
};

#endif //THOUSANDDEAL_H
