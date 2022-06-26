#include "chart.h"

QString Chart::getTitle() const {return title;}
QString Chart::getDescription() const {return description;}
void Chart::setTitle(QString s) {title=s;}
void Chart::setDescription(QString s) {description=s;}

Values* Chart::GetSortedDeepCopyOfVal(Values* original) {
    Values aux;
    for(int i=0; i < original->GetSize(); i++){ //Fa una copia profonda
        Data* auxd = new Data(*((*original)[i]));
        aux.Add(auxd);
    }
    Values* v = new Values();
    int n = aux.GetSize();
    for(int i=0; i < n; i++){
        int pos = aux.GetIndexForDataMinimumYear(); //Indice del Data con anno minore
        Data* ennesimaCopiaInutile = new Data(*(aux[pos]));
        v->Add(ennesimaCopiaInutile);
        aux.Delete(pos);
    }
    return v;
}

Chart::~Chart() = default;

