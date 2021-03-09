//
// Created by Oleg Evseev on 22.02.2021.
//

#ifndef THOUSANDSOLVER_H
#define THOUSANDSOLVER_H


#include <climits>

#include "../models/thousand/ThousandState.h"

int solve(ThousandState s, int alpha = 0, int beta = INT_MAX);


#endif //THOUSANDSOLVER_H
