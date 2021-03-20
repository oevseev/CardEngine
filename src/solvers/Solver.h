//
// Created by Oleg Evseev on 19.03.2021.
//

#ifndef SOLVER_H
#define SOLVER_H

#include <utility>
#include <vector>

class State;

class PreferansDeal;
class PreferansState;
class ThousandDeal;
class ThousandState;

class Solver
{
public:
    virtual std::pair<int, std::vector<PreferansState>> evaluate(
        const PreferansDeal &deal,
        const PreferansState &state);
    virtual std::pair<int, std::vector<ThousandState>> evaluate(
        const ThousandDeal &deal,
        const ThousandState &state);
};

#endif //SOLVER_H
