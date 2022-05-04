#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts/QChart>
#include <QtCharts/QChartGlobal>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QToolBar>
#include <QMenu>
#include <QStatusBar>
#include <QMenuBar>
#include <QString>
#include <QCloseEvent>
#include <QAction>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>

#include "table.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Controller* controller;
    Table* table;
    QAction* NewA;
    QAction* OpenA;
    QAction* SaveA;
    QAction* CloseA;
    QAction* QuitA;
    QAction* BarChartA;
    QAction* LineChartA;
    QAction* ScatterChartA;
    QAction* AreaChartA;
    QAction* PieChartA;
    QAction* AddA;
    QAction* RemoveA;
    QAction* ConfirmA;
    QMenu* FileM;
    QMenu* EditM;
    QMenu* ViewM;
    QToolBar* FileT;
    QToolBar* ChartT;
    QToolBar* ModificaT;
    QtCharts::QChartView* chartView;
public:
    explicit MainWindow(QWidget *parent = 0);
    void SetController(Controller*);
    void Update(int);
    Table* getTable() const;
    QtCharts::QChart* getChart() const;
    void setChart();
    bool ApplyIsEnabled() const;
    void ApplyUpdate();
    void ClearUpdate();
    ~MainWindow();
public slots:
    void AddUpdate();
    void RemoveUpdate();
};

#endif // MAINWINDOW_H
