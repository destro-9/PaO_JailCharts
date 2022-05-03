#ifndef TABLE_H
#define TABLE_H

#include <QTableWidget>
#include <QComboBox>
#include <QSpinBox>
#include "values.h"

class Controller;

class Table : public QTableWidget {
private:
    Values val;
    Controller* controller;
public:
    explicit Table(QWidget* =nullptr);
    Controller* getTableController() const;
    Values* getVal();
    void setController(Controller*);
    void Update();
    void DisableRows() const;
    void EnableRows() const;
    void InsertNew(int);
    void DeleteRow(int);
    void DeleteAll();
    ~Table();
};

#endif // TABLE_H
