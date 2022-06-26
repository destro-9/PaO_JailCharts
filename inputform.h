#ifndef INPUTFORM_H
#define INPUTFORM_H

#include <QDialog>
#include <QScrollArea>

#include "data.h"

class Controller;

class InputForm : public QDialog
{
private:
    Controller* controller;
    int rows;
    QList<Data*> list;
    QScrollArea* area;
    QPushButton* confirm;
    QPushButton* cancel;
public:
    explicit InputForm(int =2, QDialog* =nullptr);
    void SetController(Controller*); //Setta Controller* controller e gestisce le connect
    bool BlanksCheck() const;
    bool YearCheck() const;
    int getInputRowsNum() const; //Restituisce il numero di elementi Data
    Data* getData(int) const; //Restituisce l' i-esimo Data presente in list
    ~InputForm(); //Dealloca ogni elemento Data presente in list
};

#endif // INPUTFORM_H
