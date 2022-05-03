#ifndef AREACHART_H
#define AREACHART_H

#include "chart.h"
#include <QtCharts/QLineSeries>
#include <QtCharts/QAreaSeries>

class AreaChart final : public Chart {
private:
    QtCharts::QLineSeries* serieMale;
    QtCharts::QLineSeries* serieFemale;
    QtCharts::QAreaSeries* series;
public:
    AreaChart(Values*); //Necessario passare anche title e description?
    QtCharts::QAreaSeries* GetSeries() const;
    virtual int getTypeChart() const override;
    ~AreaChart();
};

#endif // AREACHART_H
