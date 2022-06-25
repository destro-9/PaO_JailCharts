#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "mainwindow.h"
#include "newwindow.h"
#include "inputform.h"
#include "model.h"
#include "rename.h"

class Controller : public QObject{
    Q_OBJECT
private:
    Model* model;
    MainWindow* view;
    NewWindow* neww;
    InputForm* inputw;
    Rename* rename;
    QString path;
    void readXML();
    void writeXML();
    bool InputMode_;
    void InsertToVal();
    void CloseInputForm() const;
public:
    explicit Controller();
    void SetModel(Model*);
    void SetView(MainWindow*);
public slots:
    void InputSequence(); //Sequenza di funzioni/slot da chiamare per l'inizializzazione
    void CallNewWindow();
    void CallInputForm();
    void CallRenameWindow();
    void UpdateModelChart() const; //Private?
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
    void ChangedValue();
    void RenameSlot() const;
};

#endif // CONTROLLER_H
