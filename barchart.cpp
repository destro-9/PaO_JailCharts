#include "barchart.h"
#include <QDebug>
BarChart::BarChart(Values* val) : series(new QtCharts::QBarSeries()),
                                setMale(new QtCharts::QBarSet("Male")),
                                setFemale(new QtCharts::QBarSet("Female")),
                                axisX(new QtCharts::QBarCategoryAxis()),
                                axisY(new QtCharts::QValueAxis()){
    qDebug()<<"Barchart constructor";
    for(int i=0; i < val->GetSize(); i++){
        qDebug()<<i;
        *setMale << (*val)[i]->getMale();
        *setFemale << (*val)[i]->getFemale();
        categories << QString::number((*val)[i]->getYear());
    }
    setFemale->setColor(QColor::fromRgb(255,192,203));
    series->append(setMale);
    series->append(setFemale);
    axisX->append(categories);
    qDebug()<<val->GetValMax();
    axisY->setRange(1, val->GetValMax()+1);
    axisY->setTickCount(val->GetValMax()/10);
}

int BarChart::getTypeChart() const {return 1;}
QtCharts::QBarCategoryAxis* BarChart::GetAxisX() {return axisX;}
QtCharts::QValueAxis* BarChart::GetAxisY() {return axisY;}
QtCharts::QBarSeries* BarChart::GetSeries() const {return series;}
QStringList BarChart::GetCategories() const {return categories;}

//Non ne sono sicuro
BarChart::~BarChart(){
    delete series;
    delete setMale;
    delete setFemale;
    delete axisX;
}
