//
// Created by Oleg Evseev on 08.03.2021.
//

#ifndef SETDEALDIALOG_H
#define SETDEALDIALOG_H

#include <QDialog>
#include <QLineEdit>

#include "../models/Card.h"
#include "../models/Deal.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
class SetDealDialog;
}
QT_END_NAMESPACE

class SetDealDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SetDealDialog(QWidget *parent = nullptr);
    ~SetDealDialog() override;

    [[nodiscard]] std::shared_ptr<Deal> makeDeal() const;

private:
    void setCards(Deal &deal, QLineEdit *lineEdit, int playerIndex, Suit suit) const;

    Ui::SetDealDialog *ui;
};

#endif //SETDEALDIALOG_H
