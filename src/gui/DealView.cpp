//
// Created by Oleg Evseev on 07.03.2021.
//

#include "DealView.h"

#include <QVBoxLayout>

DealView::DealView(QWidget *parent) : QWidget(parent)
{
    auto *layout = new QGridLayout(this);

    // TODO: Find a way to describe these layouts in more compact and descriptive format
    northView = new HandView(this);
    layout->addWidget(northView, 0, 1);
    westView = new HandView(this);
    layout->addWidget(westView, 1, 0);
    eastView = new HandView(this);
    layout->addWidget(eastView, 1, 2);
    southView = new HandView(this);
    layout->addWidget(southView, 2, 1);

    setLayout(layout);
}

DealPresenter *DealView::getPresenter() const
{
    return presenter;
}

void DealView::setPresenter(DealPresenter *newPresenter)
{
    if (presenter != nullptr) {
        disconnect(
            presenter, SIGNAL(playerCountChanged(int)),
            this, SLOT(setPlayerCount(int)));
        disconnect(
            presenter, SIGNAL(handChanged(int, const QVector<Card> &)),
            this, SLOT(setCards(int, const QVector<Card> &)));
        disconnect(
            presenter, SIGNAL(estimatesUpdated(const QVector<QPair<Card, int>> &)),
            this, SLOT(setEstimates(const QVector<QPair<Card, int>> &)));

        disconnect(
            northView, SIGNAL(cardClicked(Card)),
            presenter, SLOT(playCard(Card)));
        disconnect(
            westView, SIGNAL(cardClicked(Card)),
            presenter, SLOT(playCard(Card)));
        disconnect(
            eastView, SIGNAL(cardClicked(Card)),
            presenter, SLOT(playCard(Card)));
        disconnect(
            southView, SIGNAL(cardClicked(Card)),
            presenter, SLOT(playCard(Card)));
    }

    presenter = newPresenter;

    connect(
        presenter, SIGNAL(playerCountChanged(int)),
        this, SLOT(setPlayerCount(int)));
    connect(
        presenter, SIGNAL(handChanged(int, const QVector<Card> &)),
        this, SLOT(setCards(int, const QVector<Card> &)));
    connect(
        presenter, SIGNAL(estimatesUpdated(const QVector<QPair<Card, int>> &)),
        this, SLOT(setEstimates(const QVector<QPair<Card, int>> &)));

    connect(
        northView, SIGNAL(cardClicked(Card)),
        presenter, SLOT(playCard(Card)));
    connect(
        westView, SIGNAL(cardClicked(Card)),
        presenter, SLOT(playCard(Card)));
    connect(
        eastView, SIGNAL(cardClicked(Card)),
        presenter, SLOT(playCard(Card)));
    connect(
        southView, SIGNAL(cardClicked(Card)),
        presenter, SLOT(playCard(Card)));
}

void DealView::setCards(int playerIndex, const QVector<Card> &cards)
{
    if (handMapping.contains(playerIndex)) {
        handMapping[playerIndex]->setCards(cards);
    }
}

void DealView::setEstimates(const QVector<QPair<Card, int>> &estimates)
{
    // TODO: Update only the current hand view
    southView->clearEstimates();
    northView->clearEstimates();
    westView->clearEstimates();
    eastView->clearEstimates();

    for (const auto &[card, estimate] : estimates) {
        southView->setEstimate(card, estimate);
        northView->setEstimate(card, estimate);
        westView->setEstimate(card, estimate);
        eastView->setEstimate(card, estimate);
    }
}

void DealView::setPlayerCount(int playerCount)
{
    if (playerCount == 2) {
        southView->show();
        northView->show();
        westView->hide();
        eastView->hide();

        handMapping = {{1, southView}, {2, northView}};
    }
    else if (playerCount == 3) {
        southView->show();
        westView->show();
        eastView->show();
        northView->hide();

        handMapping = {{1, southView}, {2, westView}, {3, eastView}};
    }
    else if (playerCount == 4) {
        southView->show();
        westView->show();
        eastView->show();
        northView->show();

        handMapping = {{1, southView}, {2, westView}, {3, northView}, {4, eastView}};
    }
    else {
        throw std::invalid_argument("unsupported player count");
    }
}
