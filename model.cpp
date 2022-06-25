#include "model.h"

#include <QDebug>

Model::Model() {}

void Model::setVal(Values* v){
    val=v;
}

Chart* Model::getChart() {return chart;}

void Model::InitChart(QString t, QString d) {chart = new BarChart(t,d);}

void Model::CreateTypeChart(int i){
    switch(i){
    case 1:
        chart = new BarChart(val);
        break;
    case 2:
        chart = new LineChart(val);
        break;
    case 3:
        chart = new ScatterChart(val);
        break;
    case 4:
        chart = new AreaChart(val);
        break;
    case 5:
        chart = new PieChart(val);
        break;
    default:
        return;
    }
}

Model::~Model(){}
