#include "barchart.h"

BarChart::BarChart(Values* val) : series(new QtCharts::QBarSeries()),
                                setMale(new QtCharts::QBarSet("Male")),
                                setFemale(new QtCharts::QBarSet("Female")),
                                axisX(new QtCharts::QBarCategoryAxis()) {
    for(int i=0; i < val->GetSize(); i++){
        *setMale << (*val)[i]->getMale();
        *setFemale << (*val)[i]->getFemale();
        categories << QString::number((*val)[i]->getYear());
    }
    setFemale->setColor(QColor::fromRgb(255,192,203));
    series->append(setMale);
    series->append(setFemale);
    axisX->append(categories);
}

int BarChart::getTypeChart() const {return 1;}
QtCharts::QBarCategoryAxis* BarChart::GetAxisX() {return axisX;}
QtCharts::QBarSeries* BarChart::GetSeries() const {return series;}
QStringList BarChart::GetCategories() const {return categories;}

//Non ne sono sicuro
BarChart::~BarChart(){
    delete series;
    delete setMale;
    delete setFemale;
    delete axisX;
}
