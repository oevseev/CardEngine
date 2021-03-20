//
// Created by Oleg Evseev on 10.03.2021.
//

#ifndef PREFERANSDEAL_H
#define PREFERANSDEAL_H

#include "../DealImpl.h"
#include "PreferansState.h"

// TODO: Misere contract
// TODO: All-pass game

class PreferansDeal : public DealImpl<PreferansState>
{
public:
    explicit PreferansDeal(Suit trump = Suit::NONE);

    [[nodiscard]] int getPlayerCount() const override;
    [[nodiscard]] Suit getTrump() const override;

    void setTrump(Suit newTrump);

    std::pair<int, std::vector<PreferansState>> evaluateState(Solver &solver, const PreferansState &state) const override;
    [[nodiscard]] std::pair<PreferansState, int> playCard(const PreferansState &state, Card card, int player) const override;

protected:
    Suit trump;
};

#endif //PREFERANSDEAL_H
