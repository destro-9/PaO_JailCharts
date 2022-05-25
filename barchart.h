#ifndef BARCHART_H
#define BARCHART_H

#include "chart.h"
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QStackedBarSeries>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>


class BarChart final : public Chart {
private:
    QtCharts::QBarSeries* series;
    QtCharts::QBarSet* setMale;
    QtCharts::QBarSet* setFemale;
    QtCharts::QBarSeries* serieMale;
    QtCharts::QBarSeries* serieFemale;
    QStringList categories;
    QtCharts::QBarCategoryAxis* axisX;
    QtCharts::QValueAxis* axisY;

public:
    BarChart(Values*);
    QtCharts::QBarCategoryAxis* GetAxisX();
    QtCharts::QValueAxis* GetAxisY();

    QtCharts::QBarSeries* GetSeries() const;
    QStringList GetCategories() const;
    virtual int getTypeChart() const override;
    ~BarChart();
};

#endif // BARCHART_H
