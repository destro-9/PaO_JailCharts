#include "values.h"

Values::Values() {}

void Values::Add(Data* d){
    val.push_back(d);
}

void Values::Delete(int i){
    vector<Data*>::iterator it = val.begin()+i;
    if(*it) delete *it;
    val.erase(it);
}

void Values::DeleteAll(){
    vector<Data*>::iterator it = val.begin();
    while(it != val.end()){
        delete *it;
        it++;
    }
    val.clear();
}

int Values::GetSize() const{
    int aux = val.size();
    return aux;
}

int Values::GetValMax() const{
    int max=0;
    for (int i=0; i < GetSize(); ++i) {
        if (val[i]->getMale() > max)
            max = val[i]->getMale();
        if (val[i]->getFemale() > max)
            max = val[i]->getFemale();
    }
    return max;
}

bool Values::IsEmpty() const{
    return val.size() == 0;
}

Data* Values::operator[](int i) const{
    vector<Data*>::const_iterator it = val.begin() + i;
    return *it;
}

void Values::Change(int i, Data* d){
    delete val[i];
    val[i]=d;
}

void Values::Sort(){
    if(!IsEmpty()){
        Data* aux;
        for(int i=1; i < val.size(); i++){
            aux = val[i];
            int j = i-1;
            while(j>0 && *(val[i]) > *aux){
                Change(j+1,val[j]);
                j--;
            }
            Change(j+1,aux);
        }
    }
}

bool Values::YearCheck() const{
    int n = val.size();
    for(int i=0; i < n-1; i++)
        for(int j=i+1; j < n; j++)
            if(val[i]->getYear() == val[j]->getYear())
                return false;
    return true;
}

Values::~Values(){
    vector<Data*>::iterator it = val.begin();
    for(; it != val.end(); it++) delete *it;
}
