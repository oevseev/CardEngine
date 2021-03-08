//
// Created by Oleg Evseev on 08.03.2021.
//

// You may need to build the project (run Qt uic code generator) to get "ui_SetDealDialog.h" resolved

#include "SetDealDialog.h"
#include "ui_SetDealDialog.h"

const QMap<char, Rank> charToRank = {
    {'A', Rank::ACE},
    {'K', Rank::KING},
    {'Q', Rank::QUEEN},
    {'J', Rank::JACK},
    {'T', Rank::TEN},
    {'9', Rank::NINE}
};

SetDealDialog::SetDealDialog(QWidget *parent)
    :
    QDialog(parent), ui(new Ui::SetDealDialog)
{
    ui->setupUi(this);
}

SetDealDialog::~SetDealDialog()
{
    delete ui;
}

std::shared_ptr<ThousandDeal> SetDealDialog::makeDeal() const
{
    auto deal = std::make_shared<ThousandDeal>();

    setCards(*deal, ui->southSpades, 1, Suit::SPADES);
    setCards(*deal, ui->southClubs, 1, Suit::CLUBS);
    setCards(*deal, ui->southDiamonds, 1, Suit::DIAMONDS);
    setCards(*deal, ui->southHearts, 1, Suit::HEARTS);

    setCards(*deal, ui->westSpades, 2, Suit::SPADES);
    setCards(*deal, ui->westClubs, 2, Suit::CLUBS);
    setCards(*deal, ui->westDiamonds, 2, Suit::DIAMONDS);
    setCards(*deal, ui->westHearts, 2, Suit::HEARTS);

    setCards(*deal, ui->eastSpades, 3, Suit::SPADES);
    setCards(*deal, ui->eastClubs, 3, Suit::CLUBS);
    setCards(*deal, ui->eastDiamonds, 3, Suit::DIAMONDS);
    setCards(*deal, ui->eastHearts, 3, Suit::HEARTS);

    return deal;
}

void SetDealDialog::setCards(ThousandDeal &deal, QLineEdit *lineEdit, int playerIndex, Suit suit) const
{
    for (char c : lineEdit->text().toStdString()) {
        if (charToRank.contains(c)) {
            Card card(charToRank[c], suit);
            deal.getCurrentState().owner[card.getId()] = playerIndex;
            deal.getCurrentState().status[card.getId()] = CardStatus::IN_HAND;
        }
    }
}
