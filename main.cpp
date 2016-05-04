#include <QApplication>
#include "form.h"

int main(int argc,char *argv[])
{
    QApplication app(argc,argv);
    Form w;
    w.resize(800,600);
    w.show();
    return app.exec();
}
