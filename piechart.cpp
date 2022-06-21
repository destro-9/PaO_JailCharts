#include "piechart.h"

PieChart::PieChart(Values* val) {
    pieSize = 0.7 / val->GetSize();
    qreal vpos1= 0.5, vpos2, vpos3;
    qreal hPos1=0.1, hPos2=0.1, hPos3=0.1;
    if (val->GetSize() >= 4) {
        if (val->GetSize() <= 8) {
            vpos1 =0.33;
            vpos2= 0.66;
        } else {
            vpos1 =0.25;
            vpos2= 0.5;
            vpos3= 0.75;
        }
    }
    for (int i=0; i < val->GetSize(); ++i) {
        QtCharts::QPieSeries* series = new QtCharts::QPieSeries();
        v.push_back(QString::number((*val)[i]->getYear()));
        // !!! Slice e` attributo ma qui viene ridefinito localmente
        // !!! per di piu` non e` manco utilizzata se non per settare colore e visualizzare label
        slice= series->append(v[i],(*val)[i]->getMale());
        slice->setColor(QColor::fromRgb(100,149,237));
        slice->setLabelVisible();
        slice= series->append(v[i],(*val)[i]->getFemale());
        slice->setColor(QColor::fromRgb(255,192,203));
        series->setPieSize(pieSize);
        pieVector.push_back(series);
        if (val->GetSize() >= 4) { //più di 4 grafici
            if (val->GetSize() <= 8) { //ho più di 4 grafici ma al più 8
                if (i < 4) { //primi 4 grafici
                    if (i == 0) {
                        series->setHorizontalPosition(hPos1);
                        series->setVerticalPosition(vpos1);
                    } else { // i=1,2,3
                        series->setVerticalPosition(vpos1);
                        hPos1+=0.25;
                        series->setHorizontalPosition(hPos1);
                    }
                } else { //i > 4, seconda riga
                    if (i == 4) {
                        series->setVerticalPosition(vpos2);
                        series->setHorizontalPosition(hPos2);
                    } else {
                        series->setVerticalPosition(vpos2);
                        hPos2+=0.25;
                        series->setHorizontalPosition(hPos2);
                    }
                }
            } else { // ho più di 8 grafici, serve una terza riga
                if (i < 4) { //prima riga
                    if (i==0) {
                        series->setVerticalPosition(vpos1);
                        series->setHorizontalPosition(hPos1);
                    } else {
                        series->setVerticalPosition(vpos1);
                        hPos1+=0.25;
                        series->setHorizontalPosition(hPos1);
                    }
                }
                else if (i >= 4 && i < 8) { //seconda riga
                    if (i==4) {
                        series->setVerticalPosition(vpos2);
                        series->setHorizontalPosition(hPos2);
                    }
                    else {
                        series->setVerticalPosition(vpos2);
                        hPos2+=0.25;
                        series->setHorizontalPosition(hPos2);
                    }
                } else { //terza riga
                    if (i==8) {
                        series->setVerticalPosition(vpos3);
                        series->setHorizontalPosition(hPos3);
                    }
                    series->setVerticalPosition(vpos3);
                    hPos3+=0.25;
                    series->setHorizontalPosition(hPos3);
                }
            }
        } else { // ho al più 4 torte
            if (i==0) {
                if (val->GetSize() == 1) {
                    series->setVerticalPosition(vpos1); //sempre 0.5
                    hPos1+=0.4;
                    series->setHorizontalPosition(hPos1);
                } else if (val->GetSize() == 2) {
                    series->setVerticalPosition(vpos1); //sempre 0.5
                    hPos1+=0.1;
                    series->setHorizontalPosition(hPos1);
                } else {
                    series->setVerticalPosition(vpos1); //sempre 0.5
                    series->setHorizontalPosition(hPos1);
                }
            } else {
                if (val->GetSize() == 2 && i==1) {
                    series->setVerticalPosition(vpos1);
                    hPos1+=0.45;
                    series->setHorizontalPosition(hPos1);
                } else {
                    series->setVerticalPosition(vpos1);
                    hPos1+=0.25;
                    series->setHorizontalPosition(hPos1);
                }
            }
        }
    }
}

QtCharts::QPieSeries* PieChart::GetSeries(int i) const {
    return pieVector[i];
}

int PieChart::getTypeChart() const {
    return 5;
}

PieChart::~PieChart(){
    //delete slice;
}
