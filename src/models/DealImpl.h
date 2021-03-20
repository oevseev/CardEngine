//
// Created by Oleg Evseev on 18.03.2021.
//

#ifndef DEALIMPL_H
#define DEALIMPL_H

#include <unordered_map>

#include "Deal.h"

template<typename StateT>
class DealImpl : public Deal
{
public:
    DealImpl();

    void nextState() override;
    void previousState() override;
    [[nodiscard]] State &getCurrentState() const override;

    void playCard(Card card) override;

    std::pair<int, std::vector<State>> evaluateCurrentState(Solver &solver) const override;
    std::vector<std::pair<Card, int>> evaluatePossibleMoves(Solver &solver) const override;

    virtual std::pair<int, std::vector<StateT>> evaluateState(Solver &solver, const StateT &state) const = 0;
    [[nodiscard]] virtual bool canPlayCard(const StateT &state, Card card) const;
    virtual std::vector<Card> getValidMoves(const StateT &state) const;
    virtual std::pair<StateT, int> playCard(const StateT &state, Card card, int player) const = 0;

protected:
    std::vector<StateT> states;
    typename std::vector<StateT>::iterator currentState;
};

#endif //DEALIMPL_H
