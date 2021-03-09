//
// Created by Oleg Evseev on 07.03.2021.
//

#ifndef DEALPRESENTER_H
#define DEALPRESENTER_H


#include <QObject>

#include "../models/Deal.h"

class DealPresenter : public QObject
{
    Q_OBJECT

public:
    explicit DealPresenter(QObject *parent = nullptr);

    [[nodiscard]] std::shared_ptr<Deal> getDeal() const;
    void setDeal(std::shared_ptr<Deal> deal);

signals:
    void handChanged(int playerIndex, const QVector<Card> &cards);
    void playerCountChanged(int playerCount);
    void estimatesUpdated(const QVector<QPair<Card, int>> &estimates);

public slots:
    void nextState();
    void previousState();
    void evaluateCurrentState();

    void playCard(Card card);

private:
    void updateAll();

    std::shared_ptr<Deal> deal = nullptr;
};


#endif //DEALPRESENTER_H
