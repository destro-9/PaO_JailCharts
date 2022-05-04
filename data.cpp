#include "data.h"
#include "controller.h"

Data::Data(QObject *parent) : QObject(parent), male(new QSpinBox()),
                                female(new QSpinBox()), year(new QComboBox())
{
    for(int i=2010; i<=2020; i++)
        year->insertItem(i, QString::number(i));
    male->setRange(0,200000);
    male->setValue(0);
    male->setAccelerated(true);
    female->setRange(0,200000);
    female->setValue(0);
    female->setAccelerated(true);
    Table* t = dynamic_cast<Table*>(parent);
    if(t)
        setController(t->getTableController());
}

Data::Data(int m, int f, int y,QObject *parent) : QObject(parent), male(new QSpinBox()),
                                female(new QSpinBox()), year(new QComboBox())
{
    for(int i=2010; i<=2020; i++)
        year->insertItem(i, QString::number(i));

    // DA CANCELLARE A FINE DEBUG !!!
    if(y>12)
        qDebug()<<y<<"y richiede valori fra 0 e 11";
    // RICORDATIII

    year->setCurrentIndex(y);
    male->setRange(0,200000);
    male->setValue(m);
    male->setAccelerated(true);
    female->setRange(0,200000);
    female->setValue(f);
    female->setAccelerated(true);
    Table* t = dynamic_cast<Table*>(parent);
    if(t)
        setController(t->getTableController());
}

void Data::setController(Controller* c){
    //Se la funzione viene invocata allora parent e` di tipo Table
    controller = c;
    connect(year, SIGNAL(currentIndexChanged(int)), controller, SLOT(ChangedValue()));
    connect(male, SIGNAL(valueChanged(int)), controller, SLOT(ChangedValue()));
    connect(female, SIGNAL(valueChanged(int)), controller, SLOT(ChangedValue()));
}

QSpinBox* Data::getMaleWidget() const {return male;}
QSpinBox* Data::getFemaleWidget() const {return female;}
QComboBox* Data::getYearWidget() const {return year;}
int Data::getMale() const {return male->value();}
int Data::getFemale() const {return female->value();}
int Data::getYear() const {return year->currentText().toInt();}
void Data::setMale(int n) {male->setValue(n);}
void Data::setFemale(int n) {female->setValue(n);}
void Data::setYearIndex(int n) {year->setCurrentIndex(n);}

void Data::Disable() const{
    male->setEnabled(false);
    female->setEnabled(false);
    year->setEnabled(false);
}

void Data::Enable() const{
    male->setEnabled(true);
    female->setEnabled(true);
    year->setEnabled(true);
}

bool Data::operator>(const Data& d) const{
    return getYear() > d.getYear();
}

Data::~Data(){
    delete male;
    delete female;
    delete year;
}
