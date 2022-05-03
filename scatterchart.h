#ifndef SCATTERCHART_H
#define SCATTERCHART_H

#include "chart.h"
#include <QtCharts/QScatterSeries>

class ScatterChart final : public Chart {
private:
    QtCharts::QScatterSeries* serieMale;
    QtCharts::QScatterSeries* serieFemale;
public:
    ScatterChart(Values*);
    QtCharts::QScatterSeries* GetSerieMale() const;
    QtCharts::QScatterSeries* GetSerieFemale() const;
    virtual int getTypeChart() const override;
    ~ScatterChart();
};

#endif // SCATTERCHART_H
