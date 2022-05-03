#include "scatterchart.h"

ScatterChart::ScatterChart(Values* val) : serieMale(new QtCharts::QScatterSeries()),
                             serieFemale(new QtCharts::QScatterSeries()) {
    for(int i=0; i<val->GetSize(); i++){
        serieMale->append((*val)[i]->getYear(),(*val)[i]->getMale());
        serieFemale->append((*val)[i]->getYear(),(*val)[i]->getFemale());
    }
    serieMale->setName("Male");
    serieFemale->setName("Female");
    serieMale->setMarkerShape(QtCharts::QScatterSeries::MarkerShapeCircle);
    serieFemale->setMarkerShape(QtCharts::QScatterSeries::MarkerShapeCircle);
    serieMale->setMarkerSize(20.0);
    serieFemale->setMarkerSize(20.0);
    serieFemale->setColor(QColor::fromRgb(255,20,147));
}

QtCharts::QScatterSeries* ScatterChart::GetSerieMale() const {
    return serieMale;
}

QtCharts::QScatterSeries* ScatterChart::GetSerieFemale() const {
    return serieFemale;
}

int ScatterChart::getTypeChart() const{
    return 3;
}

ScatterChart::~ScatterChart(){
    delete serieMale;
    delete serieFemale;
}
