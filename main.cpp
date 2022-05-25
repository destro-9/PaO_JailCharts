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
<<<<<<< HEAD
=======
    m.setVal(w.getTable()->getVal());
>>>>>>> release/alpha0
    w.SetController(&c);
    w.show();

    return a.exec();
}

// Problemi:
// - Quando vengono create le istanze di Data in InputForm, il genitore di Data
//      e` InputForm, ma dovrebbe essere Table, questo in futuro puo` dar
//      problemi con il passaggio del controller ???
