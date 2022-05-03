#include "linechart.h"

LineChart::LineChart(Values* val) : serieMale(new QtCharts::QLineSeries()),
                                    serieFemale(new QtCharts::QLineSeries()) {
    for(int i=0; i < val->GetSize(); i++){
        serieMale->append((*val)[i]->getYear(),(*val)[i]->getMale());
        serieFemale->append((*val)[i]->getYear(),(*val)[i]->getFemale());
    }
    serieMale->setName("Male");
    serieFemale->setName("Female");
    serieFemale->setColor(QColor::fromRgb(255,20,147));
}

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
    delete serieMale;
    delete serieFemale;
}
