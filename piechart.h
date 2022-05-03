#ifndef PIECHART_H
#define PIECHART_H

#include "chart.h"
#include <QtCharts/QPieSeries>
#include <QStringList>

class PieChart final : public Chart {
private:
    qreal pieSize;
    QtCharts::QPieSlice* slice;
    QStringList v;
    std::vector<QtCharts::QPieSeries*> pieVector;
public:
    PieChart(Values*);
    QtCharts::QPieSeries* GetSeries(int) const;
    virtual int getTypeChart() const override;
    ~PieChart();
};

#endif // PIECHART_H
