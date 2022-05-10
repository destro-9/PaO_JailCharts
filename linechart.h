#ifndef LINECHART_H
#define LINECHART_H

#include "chart.h"
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QCategoryAxis>

class LineChart final : public Chart
{
private:
    QtCharts::QLineSeries* serieMale;
    QtCharts::QLineSeries* serieFemale;
    QtCharts::QCategoryAxis* axisX;
    QtCharts::QValueAxis* axisY;

public:
    LineChart(Values*);
    QtCharts::QLineSeries* GetSerieMale() const;
    QtCharts::QLineSeries* GetSerieFemale() const;
    virtual int getTypeChart() const override;
    ~LineChart();
};

#endif // LINECHART_H
