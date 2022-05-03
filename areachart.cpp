#include "areachart.h"

AreaChart::AreaChart(Values* val) : serieMale(new QtCharts::QLineSeries()),
                                    serieFemale(new QtCharts::QLineSeries()) {
    for(int i=0; i < val->GetSize(); i++){
        serieMale->append((*val)[i]->getYear(), (*val)[i]->getMale());
        serieFemale->append((*val)[i]->getYear(), (*val)[i]->getFemale());
    }
    series = new QtCharts::QAreaSeries(serieMale, serieFemale);
    series->setColor(QColor::fromRgb(65,255,50));
    series->setName("Male and female");
    QPen pen(0x059605);
    pen.setWidth(3);
    series->setPen(pen);
}

QtCharts::QAreaSeries* AreaChart::GetSeries() const {
    return series;
}

int AreaChart::getTypeChart() const{
    return 4;
}

//Non so se sia sicuro
AreaChart::~AreaChart(){
    delete series;
    delete serieMale;
    delete serieFemale;
}
