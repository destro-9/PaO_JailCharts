#include "table.h"
#include "controller.h"

Table::Table(QWidget* parent) : QTableWidget(parent), controller(nullptr) {
    setColumnCount(3);
    QStringList names;
    names <<"Year"<<"Male Data"<<"Female Data";
    setHorizontalHeaderLabels(names);
    setRowCount(0);
}

Controller* Table::getTableController() const {return controller;}
Values* Table::getVal() {Values* v=&val; return v;}

void Table::Update(){
    for(int i=0; i < val.GetSize(); i++){
        insertRow(i);
        setCellWidget(i,0,val[i]->getYearWidget());
        setCellWidget(i,1,val[i]->getMaleWidget());
        setCellWidget(i,2,val[i]->getFemaleWidget());
    }
    show(); //Serve?
}

void Table::setController(Controller* c) {controller=c;}

bool Table::IsEmpty() const{
    return val.IsEmpty();
}

bool Table::YearCheck() const{
    return val.YearCheck();
}

void Table::DisableRows() const{ // Disattiva tutte le row tranne l'ultima che subira` modifiche in attesa di Controller::Apply() per essere "ufficializzata"
    for(int i=0; i < val.GetSize()-1; i++)
        val[i]->Disable();
}

void Table::EnableRows() const{
    for(int i=0; i < val.GetSize(); i++)
        val[i]->Enable();
}

void Table::InsertNew(int i){
    insertRow(i);
    Data* d = new Data();
    val.Add(d);
    setCellWidget(i,0,d->getYearWidget());
    setCellWidget(i,1,d->getMaleWidget());
    setCellWidget(i,2,d->getFemaleWidget());
    setCurrentCell(i,0);
}

void Table::InsertDataOnNewRow(Data* d, int i){
    insertRow(i);
    val.Add(d);
    setCellWidget(i,0,d->getYearWidget());
    setCellWidget(i,1,d->getMaleWidget());
    setCellWidget(i,2,d->getFemaleWidget());
    setCurrentCell(i,0);
}

void Table::DeleteRow(int i){
    val.Delete(i);
    removeRow(i);
}

void Table::DeleteAll(){
    for(int i=rowCount(); i>=0; i--)
        removeRow(i);
    val.DeleteAll();
}

Table::~Table() {DeleteAll();}
