#include "controller.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Model m;
    Controller c;
    MainWindow w;
    c.SetModel(&m);
    c.SetView(&w);
    m.setVal(w.getTable()->getVal());
    w.SetController(&c);
    w.show();

    return a.exec();
}

