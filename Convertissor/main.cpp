#include <QApplication>
#include "unitconverterwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    UnitConverterWindow converterWindow;
    converterWindow.show();
    return app.exec();
}
