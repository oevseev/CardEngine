//
// Created by Oleg Evseev on 19.03.2021.
//

#ifndef ALPHABETASOLVER_H
#define ALPHABETASOLVER_H

#include "Solver.h"

#include <unordered_map>

#include "../models/Deal.h"
#include "../models/State.h"

class AlphaBetaSolver : public Solver
{
public:
    std::pair<int, std::vector<PreferansState>> evaluate(
        const PreferansDeal &deal,
        const PreferansState &state) override;
    std::pair<int, std::vector<ThousandState>> evaluate(
        const ThousandDeal &deal,
        const ThousandState &state) override;

private:
    template<typename DealT, typename StateT>
    int evaluateAlphaBeta(
        const DealT &deal,
        const StateT &state,
        int alpha = std::numeric_limits<int>::min(),
        int beta = std::numeric_limits<int>::max());

    int maximizingPlayer = 1;
    std::unordered_map<State, int> score;
    const Deal *lastDeal;
};

#endif //ALPHABETASOLVER_H
