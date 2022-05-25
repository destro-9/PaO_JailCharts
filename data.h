#ifndef DATA_H
#define DATA_H

#include <QObject>
#include <QSpinBox>
#include <QComboBox>
#include <QString>

class Controller;

class Data : public QObject
{
    Q_OBJECT
private:
    Controller* controller;
    QSpinBox* male;
    QSpinBox* female;
    QComboBox* year;
    int ValueToIndex(int) const;
public:
    explicit Data(QObject* =nullptr);
    explicit Data(int,int,int,QObject* =nullptr);
    explicit Data(const Data&); // ex explicit Data(Data*, ...
    Data* ReassignParent(QObject*);
    void setController(Controller*);
    QSpinBox* getMaleWidget() const;
    QSpinBox* getFemaleWidget() const;
    QComboBox* getYearWidget() const;
    void setMale(int);
    void setFemale(int);
    void setYearIndex(int);
    int getMale() const;
    int getFemale() const;
    int getYear() const;
    void Disable() const;
    void Enable() const;
    bool operator>(const Data&) const;
    ~Data();
};

#endif // DATA_H
