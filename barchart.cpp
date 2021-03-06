#include "barchart.h"

BarChart::BarChart(Values* val) : series(new QtCharts::QBarSeries()),
                                setMale(new QtCharts::QBarSet("Male")),
                                setFemale(new QtCharts::QBarSet("Female")),
                                axisX(new QtCharts::QBarCategoryAxis()),
                                axisY(new QtCharts::QValueAxis()){
    Values* sorted = GetSortedDeepCopyOfVal(val);
    for(int i=0; i < sorted->GetSize(); i++){
        *setMale << (*sorted)[i]->getMale();
        *setFemale << (*sorted)[i]->getFemale();
        categories << QString::number((*sorted)[i]->getYear());
    }
    delete sorted;
    setFemale->setColor(QColor::fromRgb(255,192,203));
    series->append(setMale);
    series->append(setFemale);
    axisX->append(categories);
    axisY->setRange(0, val->GetValMax());
    axisY->setTickCount(val->GetValMax()/10);
}

BarChart::BarChart(QString t, QString d){setTitle(t);setDescription(d);}

int BarChart::getTypeChart() const {return 1;}
QtCharts::QBarCategoryAxis* BarChart::GetAxisX() {return axisX;}
QtCharts::QValueAxis* BarChart::GetAxisY() {return axisY;}
QtCharts::QBarSeries* BarChart::GetSeries() const {return series;}
QStringList BarChart::GetCategories() const {return categories;}

BarChart::~BarChart(){
/*
    delete series;
    delete setMale;
    delete setFemale;
    delete axisX;
*/
}
