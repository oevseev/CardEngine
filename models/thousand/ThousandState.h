//
// Created by Oleg Evseev on 08.03.2021.
//

#ifndef THOUSANDSTATE_H
#define THOUSANDSTATE_H


#include "../State.h"

const int THOUSAND_PLAYER_COUNT = 3;

class ThousandState : public State
{
public:
    [[nodiscard]] std::vector<std::pair<ThousandState, int>> transitions() const;
};

namespace std
{

template<>
struct hash<ThousandState>
{
    std::size_t operator()(ThousandState const &s) const noexcept
    {
        std::size_t result = 0;

        boost::hash_combine(result, s.trump);
        boost::hash_combine(result, s.leadSuit);
        boost::hash_combine(result, s.currentPlayer);
        for (int i = 1; i <= NUM_CARDS; i++) {
            boost::hash_combine(result, s.status[i]);
            boost::hash_combine(result, s.owner[i]);
        }

        return result;
    }
};

}


#endif //THOUSANDSTATE_H
