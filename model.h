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
    void CreateTypeChart(int);
    ~Model();
};

#endif // MODEL_H
