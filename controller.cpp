#include "controller.h"
#include <QDir>
#include <QtXml>
#include <QFileDialog>
#include <QMessageBox> // Forse inutile includerlo
#include <QtCharts/QBarCategoryAxis>

Controller::Controller() : QObject() {InputMode_=false;}

void Controller::SetModel(Model* m) {model = m;}
void Controller::SetView(MainWindow* v) {view = v;}

void Controller::InputSequence(){
    InputMode_=true;
    InsertToVal();
    if(!view->getTable()->IsEmpty()){
        UpdateViewChart();
        CloseInputForm();
    }
    InputMode_=false;
}

void Controller::RenameSlot() const{
    model->getChart()->setTitle(rename->getTitle());
    model->getChart()->setDescription(rename->getDescription());
    view->getChart()->setTitle(rename->getTitle());
    view->getDesc()->setText(rename->getDescription());
    rename->close();
}

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

void Controller::CallRenameWindow(){
    rename = new Rename(model->getChart()->getTitle(),
                        model->getChart()->getDescription());
    rename->SetController(this);
    rename->show();
}

void Controller::AddToTab() const {
    Table* t = view->getTable();
    int r = t->rowCount();
    if(r<=10){
        t->InsertNew(r); //Aggiunge una row di tipo Data senza parent
        t->DisableRows();
    } else {
        QMessageBox::warning(0,"Warning","There are not supposed to be more than 11 rows");
        view->ApplyUpdate();
    }
}

void Controller::Apply() {
    Table* t = view->getTable();
    if(!t->getVal()->YearCheck()){
        QMessageBox::warning(0,"Error","Same year values are not allowed");
        t->DeleteRow(t->rowCount()-1);
        t->EnableRows();
        view->ApplyUpdate();
    } else {
        int i = t->getVal()->GetSize()-1;
        Values* val = t->getVal();
        //Viene aggiunta alla tabella una row che possiede il parent, quindi puo` aggiornare il grafico in tempo reale
        Data* d = (*val)[i]->ReassignParent(t);
        t->DeleteRow(i); // Elimina la row e dealloca (*val)[i]
        t->InsertDataOnNewRow(d,i); //Aggiunge a fine tabella
        t->EnableRows();
        view->ApplyUpdate();
        UpdateViewChart();
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
    UpdateViewChart();
}

void Controller::Clear() const{
    view->setChart(); //Dealloco l'attuale grafico e ne rialloco uno nuovo
    QtCharts::QChart* chart = view->getChart(); //Ottengo il puntatore al nuovo grafico
    view->getTable()->DeleteAll();
    chart->setTitle("Void Chart");
    chart->legend()->hide();
    view->ClearUpdate();
}

void Controller::UpdateModelChart() const{
    int i=1;
    if(InputMode_){
        i=neww->getComboIndex()+1;
        model->CreateTypeChart(i);
        model->getChart()->setTitle(neww->getTitle());
        model->getChart()->setDescription(neww->getDescription());    
        return;
    }
    QString tit = model->getChart()->getTitle(), desc = model->getChart()->getDescription();
    i=model->getChart()->getTypeChart();
    model->CreateTypeChart(i);
    model->getChart()->setTitle(tit);
    model->getChart()->setDescription(desc);
}

void Controller::UpdateViewChart() const{
    view->setChart();
    QtCharts::QChart* vChart = view->getChart();
    if(view->getTable()->IsEmpty())
        return;
    Chart* oldChart;
    if(model->getChart())
        oldChart = model->getChart();
    UpdateModelChart(); //Aggiorno i valori di model a partire dai valori presenti in tabella (val)

    Chart* mChart = model->getChart();
    int i=mChart->getTypeChart();
    BarChart* bar = dynamic_cast<BarChart*>(mChart);
    LineChart* line = dynamic_cast<LineChart*>(mChart);
    ScatterChart* scatter = dynamic_cast<ScatterChart*>(mChart);
    AreaChart* area =dynamic_cast<AreaChart*>(mChart);
    PieChart* pie =dynamic_cast<PieChart*>(mChart);
    switch(i){
    case 1:
        vChart->addSeries(bar->GetSeries());
        vChart->addAxis(bar->GetAxisX(), Qt::AlignBottom);
        vChart->addAxis(bar->GetAxisY(), Qt::AlignLeft);
        vChart->axisX()->setVisible(true);
        vChart->axisY()->setVisible(true);
        vChart->legend()->show();
        break;
    case 2:
        vChart->addSeries(line->GetSerieMale());
        vChart->addSeries(line->GetSerieFemale());
        vChart->createDefaultAxes();
        vChart->addAxis(line->GetAxisX(), Qt::AlignBottom);
        vChart->axisX()->setVisible(true);
        vChart->axisY()->setVisible(true);
        vChart->axisX()->setLineVisible();
        vChart->legend()->show();
        break;
    case 3:
        vChart->addSeries(scatter->GetSerieMale());
        vChart->addSeries(scatter->GetSerieFemale());
        vChart->createDefaultAxes();
        vChart->zoomOut();
        vChart->axisX()->setVisible(true);
        vChart->axisY()->setVisible(true);
        vChart->axisX()->setLineVisible();
        vChart->legend()->show();
        break;
    case 4:
        vChart->addSeries(area->GetSeries());
        vChart->createDefaultAxes();
        vChart->axisX()->setVisible(true);
        vChart->axisY()->setVisible(true);
        vChart->axisX()->setLineVisible();
        vChart->legend()->show();
        break;
    case 5:
        for(int i=0; i < view->getTable()->getVal()->GetSize(); i++)
            vChart->addSeries(pie->GetSeries(i));
        vChart->legend()->hide();
        break;
    default:
        return;
    }
    vChart->setTitle(mChart->getTitle());
    view->getDesc()->setText(mChart->getDescription());
    view->Update(i);
    vChart->show();
    if(oldChart)
        delete oldChart;
}

void Controller::CloseInputForm() const{
    inputw->close();
    neww->close();
}

void Controller::CreateBarChart() const {
    view->setChart();
    QtCharts::QChart* v = view->getChart();
    QString tit=model->getChart()->getTitle(), desc=model->getChart()->getDescription();
    model->CreateTypeChart(1);
    model->getChart()->setTitle(tit); model->getChart()->setDescription(desc);
    BarChart* bar = dynamic_cast<BarChart*>(model->getChart());
    v->setTitle(tit);
    view->getDesc()->setText(desc);
    v->addSeries(bar->GetSeries());
    v->legend()->show();
    v->addAxis(bar->GetAxisX(), Qt::AlignBottom);
    v->addAxis(bar->GetAxisY(), Qt::AlignLeft);
    v->axisX()->setVisible(true);
    v->axisY()->setVisible(true);
    view->Update(1);
}

void Controller::CreateLineChart() const {
    view->setChart();
    QtCharts::QChart* v = view->getChart();
    QString tit=model->getChart()->getTitle(), desc=model->getChart()->getDescription();
    model->CreateTypeChart(2);
    model->getChart()->setTitle(tit); model->getChart()->setDescription(desc);
    LineChart* line = dynamic_cast<LineChart*>(model->getChart());
    v->setTitle(tit);
    v->addSeries(line->GetSerieMale());
    v->addSeries(line->GetSerieFemale());
    v->createDefaultAxes();
    v->legend()->show();
    v->axisX()->setVisible(true);
    v->axisY()->setVisible(true);
    view->Update(2);
}

void Controller::CreateScatterChart() const {

    view->setChart();
    QtCharts::QChart* v = view->getChart();
    QString tit=model->getChart()->getTitle(), desc=model->getChart()->getDescription();
    model->CreateTypeChart(3);
    model->getChart()->setTitle(tit); model->getChart()->setDescription(desc);
    ScatterChart* scatter = dynamic_cast<ScatterChart*>(model->getChart());
    v->setTitle(tit);
    v->addSeries(scatter->GetSerieMale());
    v->addSeries(scatter->GetSerieFemale());
    v->createDefaultAxes();
    v->zoomOut();
    v->axisX()->setVisible(true);
    v->axisY()->setVisible(true);
    v->axisX()->setLineVisible(true);
    v->legend()->show();
    view->Update(3);
}

void Controller::CreateAreaChart() const {
    view->setChart();
    QtCharts::QChart* v = view->getChart();
    QString tit=model->getChart()->getTitle(), desc=model->getChart()->getDescription();
    model->CreateTypeChart(4);
    model->getChart()->setTitle(tit); model->getChart()->setDescription(desc);
    AreaChart* area = dynamic_cast<AreaChart*>(model->getChart());
    v->setTitle(tit);
    v->addSeries(area->GetSeries());
    v->createDefaultAxes();
    v->axisX()->setVisible(true);
    v->axisY()->setVisible(true);
    v->axisX()->setLineVisible(true);
    v->legend()->show();
    view->Update(4);
}

void Controller::CreatePieChart() const {
    view->setChart();
    QtCharts::QChart* v = view->getChart();
    QString tit=model->getChart()->getTitle(), desc=model->getChart()->getDescription();
    model->CreateTypeChart(5);
    model->getChart()->setTitle(tit); model->getChart()->setDescription(desc);
    PieChart* pie = dynamic_cast<PieChart*>(model->getChart());
    v->setTitle(tit);
    for(int i=0; i < view->getTable()->getVal()->GetSize(); i++)
        v->addSeries(pie->GetSeries(i));
    view->Update(5);
    v->legend()->hide();
}

void Controller::InsertToVal() {
    Table* tab = view->getTable();
    tab->setController(this);
    if(!tab->IsEmpty())
        tab->DeleteAll();
    if (!inputw->YearCheck())
        QMessageBox::warning(0, "Error", "Do not insert equal years. Try again.");
    else {
        int row = inputw->getInputRowsNum();
        for(int i=0; i<row; i++){
            Data* aux = inputw->getData(i)->ReassignParent(tab);
            tab->InsertDataOnNewRow(aux,i);
        }
    }
}

void Controller::ChangedValue() {
    if(!view->ApplyIsEnabled()){
        if(view->getTable()->getVal()->YearCheck())
            UpdateViewChart();
        else
            QMessageBox::warning(0,"Error","Same year values are not allowed");
    }
}

void Controller::open() {
    Table* t = view->getTable();
    if(!t->getTableController())
        t->setController(this);
    path = QFileDialog::getOpenFileName(view,tr("Choose a .jail file"),QDir::currentPath(),"*.jail");
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
        table->DeleteAll();
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
    QString desc = root.childNodes().at(2).toElement().attribute("description");
    table->Update();//Popolo la table di widget
    model->InitChart(title,desc);
    CreateBarChart(); //Aggiorno il chart coi valori presenti in tabella
    model->getChart()->setTitle(title);
    model->getChart()->setDescription(desc);
    view->getChart()->setTitle(title);


}

void Controller::save(){
    if(!view->getTable()->getVal()->IsEmpty()){
        path = QFileDialog::getSaveFileName(view,tr("Save as"),QDir::currentPath(),"*.jail");
        writeXML();
    } else
        QMessageBox::warning(0,"File is empty","Provide some input");
}

void Controller::writeXML(){
    QDomDocument doc;
    QFile file(path); //Qui andra` inserito il percorso del file
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QMessageBox::warning(0,"Failed to create/open file","Sorry for the incovenience, try to create a .jail file by yourself");
        return;
    }
    file.resize(0);
    Values* val = view->getTable()->getVal();
    QDomElement root = doc.createElement("Chart");
    QDomElement Points = doc.createElement("Points");
    QDomElement Title = doc.createElement("Title");
    QDomElement Description = doc.createElement("Description");
    doc.appendChild(root);
    root.appendChild(Points);
    Title.setAttribute("title",model->getChart()->getTitle());
    Description.setAttribute("description",model->getChart()->getDescription());
    root.appendChild(Title);
    root.appendChild(Description);
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
