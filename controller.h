#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QtXml>
#include "mainwindow.h"
#include "newwindow.h"
#include "inputform.h"
#include "model.h"

class Controller : public QObject{
    Q_OBJECT
private:
    Model* model;
    MainWindow* view;
    NewWindow* neww;
    InputForm* inputw;
    QString path;
    void deleteAxis() const;
    void readXML();
    void writeXML();
public:
    explicit Controller();
    void SetModel(Model*);
    void SetView(MainWindow*);
public slots:
    void CallNewWindow();
    void CallInputForm();
    void UpdateModelChart() const;
    void UpdateViewChart() const;
    void open();
    void save();
    void Clear() const;
    void AddToTab() const;
    void RemoveFromTab() const;
    void Apply();
    void CreateBarChart() const;
    void CreateLineChart() const;
    void CreateScatterChart() const;
    void CreateAreaChart() const;
    void CreatePieChart() const;
    void InsertToVal(); // ???
    //Va implementato in modo che valga per tutte le spinbox e combobox
    void ChangedValue();
    /*
    void ChangedMaleValue();
    void ChangedFemaleValue();
    void ChangedYearValue();
    */
};

#endif // CONTROLLER_H
