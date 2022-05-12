#ifndef CHART_H
#define CHART_H

#include <QString>
#include "values.h"

class Chart
{
private:
    QString title;
    QString description;
public:
    QString getTitle() const;
    QString getDescription() const;
    void setTitle(QString ="Unknown");
    void setDescription(QString ="");
    virtual int getTypeChart() const =0;
    Values* GetSortedDeepCopyOfVal(Values*) const;
    //Serve un distruttore virtuale :(

};
#endif // CHART_H
