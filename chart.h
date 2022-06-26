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
    static Values* GetSortedDeepCopyOfVal(Values*);
    virtual ~Chart() =0;

};
#endif // CHART_H
