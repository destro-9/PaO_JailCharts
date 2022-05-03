#include "inputform.h"
#include "controller.h"

InputForm::InputForm(int r, QDialog* parent) : QDialog(parent), rows(r) {
    setWindowTitle("Insert data");
    setModal(true);
    resize(500,500);
    QDialog::reject();
    QHBoxLayout* valNames = new QHBoxLayout();
    QLabel* male = new QLabel("Male Data");
    QLabel* female = new QLabel("Female Data");
    QLabel* year = new QLabel("Year");
    valNames->addSpacing(30);
    valNames->addWidget(male);
    valNames->addSpacing(30);
    valNames->addWidget(female);
    valNames->addSpacing(30);
    valNames->addWidget(year);
    valNames->addSpacing(30);
    QVBoxLayout* main=new QVBoxLayout();
    main->addLayout(valNames);
    QVBoxLayout* vertical =new QVBoxLayout();
    QWidget* insertRows = new QWidget();
    for(int i=0;i<rows;i++){
        Data* row = new Data();
        QHBoxLayout* r = new QHBoxLayout();
        r->addWidget(row->getMaleWidget());
        r->addWidget(row->getFemaleWidget());
        r->addWidget(row->getYearWidget());
        vertical->addLayout(r);
        list.push_back(row);
    }
    insertRows->setLayout(vertical);
    area = new QScrollArea();
    area->setWidgetResizable(true);
    area->setWidget(insertRows);
    main->addWidget(area);
    QDialogButtonBox* buttons =new QDialogButtonBox;
    confirm=new QPushButton("Confirm");
    cancel=new QPushButton("Cancel");
    confirm->setFont(QFont("Times", 18 ,QFont::Black));
    cancel->setFont(QFont("Times", 18 ,QFont::Black));
    buttons->addButton(confirm, QDialogButtonBox::ActionRole);
    buttons->addButton(cancel, QDialogButtonBox::ActionRole);
    main->addWidget(buttons);
    setLayout(main);
    connect (cancel, SIGNAL(clicked()), this, SLOT(close()));
}

void InputForm::SetController(Controller* c){
    controller = c;
    connect (confirm, SIGNAL(clicked()), controller, SLOT(InsertToVal()));
    connect (confirm, SIGNAL(clicked()), controller, SLOT(UpdateViewChart()));
}

bool InputForm::BlanksCheck() const{
    QList<Data*>::const_iterator it=list.begin();
    for(;it!=list.end();it++){
        if((*it)->getFemale()==0 || (*it)->getMale()==0)
            return false;
    }
    return true;
}

bool InputForm::YearCheck() const {
    QList<Data*>::const_iterator it=list.begin(), iter;
    for (; it != list.end(); ++it)
        for (iter=it+1; iter != list.end(); ++iter)
            if ((*it)->getYear() == (*iter)->getYear())
                return false;
    return true;
}


Data* InputForm::getData(int i) const {
    QList<Data*>::const_iterator it=list.begin()+i;
    return *it;
}

int InputForm::getInputRowsNum() const {
    return rows;
}

InputForm::~InputForm(){
    QList<Data*>::const_iterator it=list.begin();
    for(; it != list.end(); ++it)
        delete *it;
}
