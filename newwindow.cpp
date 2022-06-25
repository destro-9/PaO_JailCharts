#include "newwindow.h"
#include "controller.h"

NewWindow::NewWindow(QWidget* parent) : QDialog(parent){
    setWindowTitle("Create a new chart");
    resize(700,400);
    setModal(true);
    reject();
    QLabel* rowsLabel = new QLabel("Insert number of data taken in exam");
    rows = new QSpinBox();
    rows->setRange(2,11);
    rows->setValue(2);
    rows->setAccelerated(true);
    QHBoxLayout* rowsLayout = new QHBoxLayout();
    rowsLayout->addWidget(rowsLabel);
    rowsLayout->addWidget(rows);

    WhatChart = new QComboBox();
    WhatChart->addItem("Barchart",1);
    WhatChart->addItem("Linechart",2);
    WhatChart->addItem("Scatterchart",3);
    WhatChart->addItem("Areachart",4);
    WhatChart->addItem("Piechart",5);
    QHBoxLayout* chartLayout = new QHBoxLayout();
    chartLayout->addWidget(new QLabel("Choose kind of chart"));
    chartLayout->addWidget(WhatChart);

    WhatTitle = new QLineEdit();
    QHBoxLayout* titleLayout = new QHBoxLayout();
    titleLayout->addWidget(new QLabel("Insert chart title"));
    titleLayout->addWidget(WhatTitle);

    Description = new QTextEdit();
    QHBoxLayout* descLayout = new QHBoxLayout();
    descLayout->addWidget(new QLabel("Insert description"));
    descLayout->addWidget(Description);

    apply = new QPushButton(tr("Confirm"));
    cancel = new QPushButton(tr("Cancel"));
    apply->setFont(QFont("Times",18,QFont::Black));
    cancel->setFont(QFont("Times",18,QFont::Black));

    QDialogButtonBox* buttons = new QDialogButtonBox(Qt::Horizontal);
    buttons->addButton(apply,QDialogButtonBox::ActionRole);
    buttons->addButton(cancel,QDialogButtonBox::ActionRole);

    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addLayout(rowsLayout);
    mainLayout->addLayout(chartLayout);
    mainLayout->addLayout(titleLayout);
    mainLayout->addLayout(descLayout);
    mainLayout->addWidget(buttons);

    setLayout(mainLayout);
    connect(cancel, SIGNAL(clicked()), this, SLOT(close()));
}

void NewWindow::SetController(Controller* c){
    controller = c;
    connect(apply, SIGNAL(clicked()), controller, SLOT(CallInputForm()));
}

int NewWindow::RowsValue() const {return rows->value();}
QString NewWindow::getTitle() const {return WhatTitle->displayText();}
QString NewWindow::getDescription() const {return Description->toPlainText();}
int NewWindow::getComboIndex() const {return WhatChart->currentIndex();}
NewWindow::~NewWindow(){}
