#include "linechart.h"

LineChart::LineChart(Values* val) : serieMale(new QtCharts::QLineSeries()),
                                    serieFemale(new QtCharts::QLineSeries()),
                                    axisX(new QtCharts::QCategoryAxis()),
                                    axisY(new QtCharts::QValueAxis())
{
    Values* sorted = GetSortedDeepCopyOfVal(val);
    for(int i=0; i < val->GetSize(); i++){
        int year = (*sorted)[i]->getYear();
        serieMale->append(year,(*sorted)[i]->getMale());
        serieFemale->append(year,(*sorted)[i]->getFemale());
        axisX->append(QString::number(year),year);
    }
    delete sorted;
    serieMale->setName("Male");
    serieFemale->setName("Female");
    serieFemale->setColor(QColor::fromRgb(255,20,147));
    axisY->setRange(0, val->GetValMax());
    axisY->setTickCount(val->GetValMax()/10);
}

QtCharts::QCategoryAxis* LineChart::GetAxisX() const{return axisX;}
QtCharts::QValueAxis* LineChart::GetAxisY() const{return axisY;}

QtCharts::QLineSeries* LineChart::GetSerieMale() const {
    return serieMale;
}

QtCharts::QLineSeries* LineChart::GetSerieFemale() const {
    return serieFemale;
}

int LineChart::getTypeChart() const {
    return 2;
}

LineChart::~LineChart(){
    /*
    delete serieMale;
    delete serieFemale;
    */
}
