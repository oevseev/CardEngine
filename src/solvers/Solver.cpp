//
// Created by Oleg Evseev on 19.03.2021.
//

#include "Solver.h"

std::pair<int, std::vector<PreferansState>> Solver::evaluate(const PreferansDeal &deal, const PreferansState &state)
{
    throw std::runtime_error("preferans deals not supported by solver");
}

std::pair<int, std::vector<ThousandState>> Solver::evaluate(const ThousandDeal &deal, const ThousandState &state)
{
    throw std::runtime_error("thousand deals not supported by solver");
}
