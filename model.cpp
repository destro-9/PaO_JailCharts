#include "model.h"

#include <QDebug>

Model::Model() {}

void Model::setVal(Values* v){
    val=v;
}

int Model::ValueToIndex(int i) const {
    switch (i) {
        case 2010:
            return 0;
            break;
        case 2011:
            return 1;
            break;
        case 2012:
            return 2;
            break;
        case 2013:
            return 3;
            break;
        case 2014:
            return 4;
            break;
        case 2015:
            return 5;
            break;
        case 2016:
            return 6;
            break;
        case 2017:
            return 7;
            break;
        case 2018:
            return 8;
            break;
        case 2019:
            return 9;
            break;
        case 2020:
            return 10;
            break;
        default:
            return 0;
    }
}

Chart* Model::getChart() {return chart;}

void Model::InitChart(QString t, QString d) {chart = new BarChart(t,d);}

void Model::CreateTypeChart(int i){
    //Implementare deallocazione? Tanto arrivati a sto punto il vChart e` gia` deallocato
    //Servono distruttori virtuali
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
    qDebug()<<"CTC -> Switch eseguito";
}

void Model::ChartDeallocator(Chart* c){
    BarChart* bar;LineChart* line;ScatterChart* scatter;AreaChart* area;PieChart* pie;
    if(c == nullptr)
        return;
    bar = dynamic_cast<BarChart*>(c);
    line = dynamic_cast<LineChart*>(c);
    scatter = dynamic_cast<ScatterChart*>(c);
    area = dynamic_cast<AreaChart*>(c);
    pie = dynamic_cast<PieChart*>(c);
    if(bar){
        bar->~BarChart();
        return;
    }
    if(line){
        line->~LineChart();
        return;
    }
    if(scatter){
        scatter->~ScatterChart();
        return;
    }
    if(area){
        area->~AreaChart();
        return;
    }
    if(pie)
        pie->~PieChart();
}

Model::~Model(){}
