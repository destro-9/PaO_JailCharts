#ifndef MODEL_H
#define MODEL_H

#include "linechart.h"
#include "scatterchart.h"
#include "barchart.h"
#include "areachart.h"
#include "piechart.h"

class Model {
private:
    Chart* chart;
    Values* val;
public:
    explicit Model();
    void setVal(Values*);
    int ValueToIndex(int) const;
    Chart* getChart();
    void InitChart(QString,QString);
    void CreateTypeChart(int);
    static void ChartDeallocator(Chart*);
    ~Model();
};

#endif // MODEL_H
