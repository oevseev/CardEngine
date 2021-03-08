//
// Created by Oleg Evseev on 05.03.2021.
//

#include "MainWindow.h"

#include <QToolBar>
#include <QMenuBar>
#include <QPushButton>

#include "SetDealDialog.h"

MainWindow::MainWindow(QWidget *parent, const Qt::WindowFlags &flags)
{
    auto *toolBar = new QToolBar("Toolbar", this);
    toolBar->setMovable(false);

    // TODO: Proper toolbar with actions instead of widgets
    auto *previousButton = new QPushButton("Previous", toolBar);
    toolBar->addWidget(previousButton);
    auto *nextButton = new QPushButton("Next", toolBar);
    toolBar->addWidget(nextButton);

    auto *menuBar = new QMenuBar(this);
    auto *fileMenu = new QMenu("File", menuBar);
    auto *setDealAction = new QAction("Set deal...", menuBar);
    connect(setDealAction, SIGNAL(triggered(bool)), this, SLOT(setDeal()));
    fileMenu->addAction(setDealAction);
    menuBar->addMenu(fileMenu);

    addToolBar(toolBar);
    setMenuBar(menuBar);
    setUnifiedTitleAndToolBarOnMac(true);

    dealPresenter = new DealPresenter(this);
    connect(previousButton, SIGNAL(clicked(bool)), dealPresenter, SLOT(previousState()));
    connect(nextButton, SIGNAL(clicked(bool)), dealPresenter, SLOT(nextState()));

    dealView = new DealView(this);
    dealView->setPresenter(dealPresenter);
    setCentralWidget(dealView);
}

void MainWindow::setDeal()
{
    SetDealDialog dialog;
    if (dialog.exec()) {
        dealPresenter->setDeal(dialog.makeDeal());
    }
}
