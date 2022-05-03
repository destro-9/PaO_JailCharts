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
    void SetController(Controller*);
    bool BlanksCheck() const;
    bool YearCheck() const;
    int getInputRowsNum() const;
    Data* getData(int) const;
    ~InputForm();
};

#endif // INPUTFORM_H
