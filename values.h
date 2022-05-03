#ifndef VALUES_H
#define VALUES_H

#include <vector>
#include "data.h"
using std::vector;
class Values{
private:
    vector<Data*> val;
public:
    Values();
    void Add(Data*);
    void Delete(int);
    void DeleteAll();
    int GetSize() const;
    int GetValMax() const;
    bool IsEmpty() const;
    Data* operator[](int) const;
    void Change(int,Data*);
    void Sort();
    //Da definire
    bool YearCheck() const;

    ~Values();
};

#endif // VALUES_H
