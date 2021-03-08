//
// Created by Oleg Evseev on 08.03.2021.
//

#ifndef THOUSANDDEAL_H
#define THOUSANDDEAL_H


#include "../Deal.h"

class ThousandDeal : public Deal
{
public:
    ThousandDeal();

    [[nodiscard]] int getPlayerCount() const override;
};


#endif //THOUSANDDEAL_H
