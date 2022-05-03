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

void Model::CreateTypeChart(int i){

    //QString t = chart->getTitle();
    //QString d = chart->getDescription();

    /*
    if(chart && i>0 && i<=5)
        delete chart;   //PROBABILE ERRORE!
    */
    switch(i){
    case 1:
        chart = new BarChart(val);
        //chart->setTitle(t);
        //chart->setDescription(d);
        //dynamic_cast<BarChart*>(chart)->setTitle(t);
        //I dynamic non son necessari con molta probabilita`
        //Tenuti per "compatibilita`"
        break;
    case 2:
        chart = new LineChart(val);
        //chart->setTitle(t);
        //chart->setDescription(d);
        //dynamic_cast<LineChart*>(chart)->setTitle(t);
        break;
    case 3:
        chart = new ScatterChart(val);
        //chart->setTitle(t);
        //chart->setDescription(d);
        //dynamic_cast<ScatterChart*>(chart)->setTitle(t);
        break;
    case 4:
        chart = new AreaChart(val);
        //chart->setTitle(t);
        //chart->setDescription(d);
        //dynamic_cast<AreaChart*>(chart)->setTitle(t);
        break;
    case 5:
        chart = new PieChart(val);
        //chart->setTitle(t);
        //chart->setDescription(d);
        //dynamic_cast<PieChart*>(chart)->setTitle(t);
        break;
    default:
        return;
    }
    qDebug()<<"CTC -> Switch eseguito";
}

Model::~Model(){}
