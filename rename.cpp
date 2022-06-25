#include "rename.h"
#include "controller.h"
#include <QHBoxLayout>
#include <QVBoxLayout>

Rename::Rename(QString title, QString desc) : QDialog(), t_input(new QLineEdit(title)), d_input(new QLineEdit(desc)),
                                              apply(new QPushButton(tr("Confirm"))), cancel(new QPushButton(tr("Cancel"))){
    setWindowTitle("Rename Title and Description");
    resize(700,400);
    setModal(true);
    reject();
    QLabel* t = new QLabel("Insert Title");
    QLabel* d = new QLabel("Insert Description");

    QHBoxLayout* row_t = new QHBoxLayout();
    QHBoxLayout* row_d = new QHBoxLayout();
    QVBoxLayout* main = new QVBoxLayout();

    row_t->addWidget(t);
    row_t->addWidget(t_input);

    row_d->addWidget(d);
    row_d->addWidget(d_input);

    main->addLayout(row_t);
    main->addLayout(row_d);

    QDialogButtonBox* buttons = new QDialogButtonBox(Qt::Horizontal);
    apply->setFont(QFont("Times",18,QFont::Black));
    cancel->setFont(QFont("Times",18,QFont::Black));
    buttons->addButton(apply,QDialogButtonBox::ActionRole);
    buttons->addButton(cancel,QDialogButtonBox::ActionRole);

    main->addWidget(buttons);

    setLayout(main);
    connect(cancel, SIGNAL(clicked()), this, SLOT(close()));
}

void Rename::SetController(Controller* c){
    controller = c;
    connect(apply, SIGNAL(clicked()), controller, SLOT(RenameSlot()));
}

QString Rename::getTitle() const{ return t_input->text();}
QString Rename::getDescription() const{ return d_input->text();}
Rename::~Rename(){}
