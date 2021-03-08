#include <QApplication>

#include "gui/MainWindow.h"

// TODO: Proper code styling and formatting

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow mainWindow{};
    mainWindow.show();

    return QApplication::exec();
}
