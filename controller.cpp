#include "controller.h"
#include <QDir>
#include <QFileDialog>
#include <QMessageBox> // Forse inutile includerlo
#include <QtCharts/QBarCategoryAxis>

Controller::Controller() : QObject() {}

void Controller::SetModel(Model* m) {model = m;}
void Controller::SetView(MainWindow* v) {view = v;}

void Controller::CallNewWindow(){
    neww = new NewWindow(view);
    neww->SetController(this);
    neww->show();
}

void Controller::CallInputForm(){
    inputw = new InputForm(neww->RowsValue(),neww);
    inputw->SetController(this);
    inputw->show();
}

void Controller::AddToTab() const {
    //Warning: se da errore lo comunica a chi lo invoca?
    Table* t = view->getTable();
    int r = t->rowCount();
    if(r<=10){
        t->InsertNew(r);
        t->DisableRows();
    } else {
        QMessageBox::warning(0,"Warning","There are not supposed to be more than 11 rows");
        view->ApplyUpdate();
    }
}

void Controller::deleteAxis() const {
    BarChart* bar = dynamic_cast<BarChart*>(model->getChart());
    if(bar && bar->GetAxisX() != nullptr){
        QtCharts::QBarCategoryAxis* ax = new QtCharts::QBarCategoryAxis();
        view->getChart()->setAxisX(ax);
        //oppure
        //view->getMainw()->getChart()->removeAxis(bar->GetAxisX());
    }
}

void Controller::Apply() {
    Table* t = view->getTable();
    if(!t->getVal()->YearCheck()){
        qDebug()<<"Apply()-> YearCheck triggered";
        QMessageBox::warning(0,"Error","Same year values are not allowed");
        t->DeleteRow(t->rowCount()-1);
        t->EnableRows();
        view->ApplyUpdate();
    } else {
        int i = t->getVal()->GetSize()-1;
        Values* val = t->getVal();
        int m=(*val)[i]->getMale(), f=(*val)[i]->getFemale(), y=model->ValueToIndex((*val)[i]->getYear());
        if(m!=0 && f!=0 && y!=0){
            Data* d = new Data(m,f,y,t);
            val->Add(d);
            t->EnableRows();
            view->ApplyUpdate();
            UpdateViewChart();
        } else {
            QMessageBox::warning(0,"Error","Null values are not allowed");
            //Le successive sono aggiunte
            t->DeleteRow(t->rowCount()-1);
            t->EnableRows();
            view->ApplyUpdate();
        }
    }
}

void Controller::RemoveFromTab() const {
    Table* t = view->getTable();
    int row = t->rowCount()-1;
    if(row==0){
        Clear();
        return;
    }
    if(row>0){
        t->DeleteRow(row);
        t->EnableRows();
    }
    deleteAxis(); //Piu` probabile vada solo aggiornato
    UpdateViewChart();
}

void Controller::Clear() const{
    view->getChart()->removeAllSeries();
    view->getTable()->DeleteAll();
    //view->getTable()->getVal()->DeleteAll(); Non dovrebbe servire
    view->getChart()->setTitle("Void Chart");
    view->getChart()->legend()->hide();
    deleteAxis();
    view->ClearUpdate();
}

void Controller::UpdateModelChart() const{
    int i=1;
    if(inputw->isActiveWindow())
        i=neww->getComboIndex()+1;

    model->CreateTypeChart(i);
    model->getChart()->setTitle(neww->getTitle());
    model->getChart()->setDescription(neww->getDescription());
    }

void Controller::UpdateViewChart() const{
    view->setChart();
    QtCharts::QChart* vChart = view->getChart();
    if(view->getTable()->getVal()->IsEmpty())
        return;
    //vChart->removeAllSeries();

    //WARNING
    //deleteAxis();

    UpdateModelChart(); //Aggiorno i valori di model

    Chart* mChart = model->getChart();
    int i=mChart->getTypeChart();
    BarChart* bar = dynamic_cast<BarChart*>(mChart);
    LineChart* line = dynamic_cast<LineChart*>(mChart);
    ScatterChart* scatter = dynamic_cast<ScatterChart*>(mChart);
    AreaChart* area =dynamic_cast<AreaChart*>(mChart);
    PieChart* pie =dynamic_cast<PieChart*>(mChart);
    switch(i){
    case 1:
        qDebug()<<"UVC -> barchart";
        vChart->addSeries(bar->GetSeries());
        /*
        if(vChart->axisX())
            vChart->setAxisX(bar->GetAxisX());
        else
        */
        vChart->addAxis(bar->GetAxisX(), Qt::AlignBottom);
        vChart->addAxis(bar->GetAxisY(), Qt::AlignLeft);
        vChart->axisX()->setVisible(true);
        vChart->axisY()->setVisible(true);
        vChart->legend()->show();
        break;
    case 2:
        vChart->addSeries(line->GetSerieMale());
        vChart->addSeries(line->GetSerieFemale());
        vChart->legend()->show();
        break;
    case 3:
        vChart->addSeries(scatter->GetSerieMale());
        vChart->addSeries(scatter->GetSerieFemale());
        vChart->legend()->show();
        break;
    case 4:
        vChart->addSeries(area->GetSeries());
        vChart->legend()->show();
        break;
    case 5:
        for(int i=0; i < view->getTable()->getVal()->GetSize(); i++)
            vChart->addSeries(pie->GetSeries(i));
        vChart->axisX()->setVisible(false);
        vChart->axisY()->setVisible(false);
        break;
    default:
        qDebug()<<"UVC -> FAIL on switch";
        return;
    }
    qDebug()<<"UVC -> Out of switch";
    vChart->setTitle(mChart->getTitle());
    //vChart->axes(Qt::Horizontal).back()->setRange(2010,2020);
    //vChart->axes(Qt::Vertical).back()->setRange(1,view->getTable()->getVal()->GetValMax()+1);
    view->Update(i);
    vChart->show();
    inputw->close();
    neww->close();
}

void Controller::CreateBarChart() const {
    qDebug()<<"CreateBarChart()";
    QtCharts::QChart* v = view->getChart();
    v->removeAllSeries();

    v->axisX()->setVisible(false);
    v->axisY()->setVisible(true);
    //deleteAxis();
    model->CreateTypeChart(1);
    BarChart* bar = dynamic_cast<BarChart*>(model->getChart());
    v->addSeries(bar->GetSeries());
    v->legend()->show();
    v->addAxis(bar->GetAxisX(), Qt::AlignBottom);
    view->Update(1);
    //v->show; //Sospetto non serva;
}

void Controller::CreateLineChart() const {
    QtCharts::QChart* v = view->getChart();
    v->removeAllSeries();
    v->axisX()->setVisible(true);
    v->axisY()->setVisible(true);
    //deleteAxis();
    model->CreateTypeChart(2);
    LineChart* line = dynamic_cast<LineChart*>(model->getChart());
    v->addSeries(line->GetSerieMale());
    v->addSeries(line->GetSerieFemale());
    v->legend()->show();
    view->Update(2);
    v->show(); // Credo non serva
}

void Controller::CreateScatterChart() const {
    QtCharts::QChart* v = view->getChart();
    v->removeAllSeries();
    v->axisX()->setVisible(true);
    v->axisY()->setVisible(true);
    //deleteAxis();
    model->CreateTypeChart(3);
    ScatterChart* scatter = dynamic_cast<ScatterChart*>(model->getChart());
    v->addSeries(scatter->GetSerieMale());
    v->addSeries(scatter->GetSerieFemale());
    v->legend()->show();
    view->Update(3);
    //v->show(); //Ho ragione di credere non serva
}

void Controller::CreateAreaChart() const {
    QtCharts::QChart* v = view->getChart();
    v->removeAllSeries();
    v->axisX()->setVisible(true);
    v->axisY()->setVisible(true);
    //deleteAxis();
    model->CreateTypeChart(4);
    AreaChart* area = dynamic_cast<AreaChart*>(model->getChart());
    v->addSeries(area->GetSeries());
    view->Update(4);
    v->legend()->show();
    //v->show(); // Prima non c'era... Serve?
}

void Controller::CreatePieChart() const {
    QtCharts::QChart* v = view->getChart();
    v->removeAllSeries();
    v->axisX()->setVisible(false);
    v->axisY()->setVisible(false);
    //deleteAxis();
    model->CreateTypeChart(5);
    PieChart* pie = dynamic_cast<PieChart*>(model->getChart());
    for(int i=0; i < view->getTable()->getVal()->GetSize(); i++)
        v->addSeries(pie->GetSeries(i));
    view->Update(5);
    v->legend()->hide();
    //v->show(); // Anche questo mancava... Mmm...
}

void Controller::InsertToVal() {
    qDebug()<<"InsertToVal";
    Table* tab = view->getTable();
    Values* val = tab->getVal();
    tab->setController(this);

    if(!val->IsEmpty())
        tab->DeleteAll();//Prima era: val->DeleteAll();

    if(!inputw->BlanksCheck()) //Spostare il controllo altrove
        QMessageBox::warning(0, "Error", "Do not insert null values. Try again.");
    else  if (!val->YearCheck())
        QMessageBox::warning(0, "Error", "Do not insert equal years. Try again.");
    else {
        int row = inputw->getInputRowsNum();
        qDebug()<<"Inputw number " <<row;
        for(int i=0; i<row; i++){
            Data* aux = inputw->getData(i);
            int y=model->ValueToIndex(aux->getYear()), m=aux->getMale(), f=aux->getFemale();
            aux = new Data(m,f,y,tab);
            qDebug()<<y<<m<<f<<i;
            val->Add(aux);
        }
        tab->Update();
    }
}

void Controller::ChangedValue() {
    //WARNING
    //Va implementato in modo che valga per tutte le spinbox e combobox
    if(!view->ApplyIsEnabled()){
        if(view->getTable()->getVal()->YearCheck())
        {
            //deleteAxis(); // ???
            UpdateViewChart();
        }
        else
            QMessageBox::warning(0,"Error","Same year values are not allowed");
    }
}

void Controller::open() {
    Table* t = view->getTable();
    if(!t->getTableController())
        t->setController(this);
    path = QFileDialog::getOpenFileName(view,tr("Choose an xml file"),QDir::currentPath(),"*.xml");
    if(!path.isNull())
        Clear();
    readXML();
}

void Controller::readXML(){
    QDomDocument doc;
    QFile file(path); //Qui andra` inserito il percorso del file
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::warning(0,"Failed to open file","The file chosen is not in XML format or readonly");
        return;
    }
    if(!doc.setContent(&file)){
        QMessageBox::warning(0,"Failed to load file","The file chosen has not the right XML structure");
        return;
    }
    file.close();
    Table* table = view->getTable();
    Values* val = table->getVal();
    if(!val->IsEmpty())
        val->DeleteAll();
    QDomElement root = doc.firstChildElement(); //Ottengo la root
    QDomElement points = root.firstChildElement(); //Ottengo il tag Points
    QDomNodeList pointsList = points.elementsByTagName("Point"); //Lista dei dati
    for(int i=0;i < pointsList.count(); i++){
        QDomNode node = pointsList.at(i);
        if(node.isElement()){
            QDomElement dato = node.toElement();
            Data* d = new Data(
                dato.attribute("male").toInt(),
                dato.attribute("female").toInt(),
                dato.attribute("year").toInt(), table
            );
            val->Add(d);
        }
    }
    QString title = root.childNodes().at(1).toElement().attribute("title");
    model->getChart()->setTitle(title);
    table->Update();//Popolo la table di widget
    view->getChart()->setTitle(title);
    CreateBarChart(); //Aggiorno il chart coi valori presenti in tabella
}

void Controller::save(){
    if(!view->getTable()->getVal()->IsEmpty()){
        path = QFileDialog::getSaveFileName(view,tr("Save as"),QDir::currentPath(),"*.xml");
        writeXML();
    } else
        QMessageBox::warning(0,"File is empty","Fill my vector please xD");
}

void Controller::writeXML(){
    QDomDocument doc;
    QFile file(path); //Qui andra` inserito il percorso del file
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QMessageBox::warning(0,"Failed to create/open file","Sorry for the incovenience, try to create a xml file by yourself");
        return;
    }
    file.resize(0);
    Values* val = view->getTable()->getVal();
    QDomElement root = doc.createElement("Chart");
    QDomElement Points = doc.createElement("Points");
    QDomElement Title = doc.createElement("Title");
    doc.appendChild(root);
    root.appendChild(Points);
    Title.setAttribute("title",model->getChart()->getTitle());
    root.appendChild(Title);
    for(int i=0; i < val->GetSize(); i++){
        QDomElement p = doc.createElement("Point");
        p.setAttribute("male",(*val)[i]->getMale());
        p.setAttribute("female",(*val)[i]->getFemale());
        p.setAttribute("year",(*val)[i]->getYear());
        Points.appendChild(p);
    }
    QTextStream stream(&file);
    stream << "<?xml version=\"1.0\"?>\n" << doc.toString();
    file.close();
}
