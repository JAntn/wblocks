#include "FW/UI/ui_main_window.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    C_UiMainWindow w;
    w.show();

    return a.exec();
}
