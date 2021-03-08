//
// Created by Oleg Evseev on 05.03.2021.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>

#include "DealPresenter.h"
#include "DealView.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr, const Qt::WindowFlags &flags = Qt::WindowFlags());

public slots:
    void setDeal();

private:
    DealPresenter *dealPresenter;
    DealView *dealView;
};


#endif //MAINWINDOW_H
