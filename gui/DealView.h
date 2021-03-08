//
// Created by Oleg Evseev on 07.03.2021.
//

#ifndef DEALVIEW_H
#define DEALVIEW_H


#include <QWidget>

#include "../models/State.h"
#include "DealPresenter.h"
#include "HandView.h"

class DealView : public QWidget
{
    Q_OBJECT

public:
    explicit DealView(QWidget *parent = nullptr);

    [[nodiscard]] DealPresenter *getPresenter() const;
    void setPresenter(DealPresenter *presenter);

public slots:
    void setCards(int playerIndex, const QVector<Card> &cards);
    void setPlayerCount(int playerCount);

private:
    DealPresenter *presenter = nullptr;

    HandView *southView;
    HandView *westView;
    HandView *northView;
    HandView *eastView;

    QMap<int, HandView *> handMapping;
};


#endif //DEALVIEW_H
