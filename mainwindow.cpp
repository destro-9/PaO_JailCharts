#include "mainwindow.h"
#include "controller.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    qDebug()<<"start mainw";
    setGeometry(180,100,1300,800);
    setWindowTitle("JailCharts");
    NewA = new QAction(QIcon(":/icon/images/add-file.png"),tr("New"),this);
    NewA->setShortcut(QKeySequence::New);
    OpenA = new QAction(QIcon(":/icon/images/open-folder.png"),tr("Open"),this);
    OpenA->setShortcuts(QKeySequence::Open);
    SaveA=new QAction(QIcon(":/icon/images/save.png") ,tr("Save"),this);
    SaveA->setShortcuts(QKeySequence::Save);
    CloseA=new QAction(QIcon(":/icon/images/cancel.png"),tr("Close"),this);
    CloseA->setShortcuts(QKeySequence::Close);
    QuitA=new QAction(tr("Quit"), this);
    QuitA->setShortcuts(QKeySequence::Quit);

    BarChartA=new QAction(QIcon(":/icon/images/bar-chart.png"),tr("Barchart"),this);
    LineChartA=new QAction(QIcon(":/icon/images/line-chart.png"),tr("Linechart"),this);
    ScatterChartA=new QAction(QIcon(":/icon/images/scatter-graph.png"),tr("ScatterChart"),this);
    AreaChartA=new QAction(QIcon(":/icon/images/area-chart.png"),tr("AreaChart"),this);
    PieChartA=new QAction(QIcon(":/icon/images/pie-graph.png"),tr("PieChart"),this);


    AddA=new QAction(QIcon(":/icon/images/plus.png"),tr("Add"),this);
    RemoveA=new QAction(QIcon(":/icon/images/remove.png"),tr("Remove"),this);
    ConfirmA=new QAction(QIcon(":/icon/images/confirm.png"),tr("Confirm"),this);


    FileM =new QMenu(tr("File"),this);
    FileM->addAction(NewA);
    FileM->addAction(OpenA);
    FileM->addAction(SaveA);
    FileM->addAction(CloseA);
    FileM->addAction(QuitA);

    EditM= new QMenu(tr("Edit"),this);
    EditM->addAction(AddA);
    EditM->addAction(RemoveA);
    EditM->addAction(ConfirmA);

    ViewM =new QMenu(tr("View"),this);
    ViewM->addAction(BarChartA);
    ViewM->addAction(LineChartA);
    ViewM->addAction(ScatterChartA);
    ViewM->addAction(AreaChartA);
    ViewM->addAction(PieChartA);

    menuBar()->addMenu(FileM);
    menuBar()->addMenu(EditM);
    menuBar()->addMenu(ViewM);

    menuBar()->addSeparator();
    statusBar();
    FileT=addToolBar(tr("File"));
    FileT->addAction(NewA);
    FileT->addAction(OpenA);
    FileT->addAction(SaveA);
    FileT->addAction(CloseA);

    ModificaT=addToolBar(tr("Edit"));
    ModificaT->addAction(AddA);
    ModificaT->addAction(ConfirmA);
    ModificaT->addAction(RemoveA);

    ChartT=addToolBar(tr("View"));
    ChartT->addAction(BarChartA);
    ChartT->addAction(LineChartA);
    ChartT->addAction(ScatterChartA);
    ChartT->addAction(AreaChartA);
    ChartT->addAction(PieChartA);

    SaveA->setEnabled(false);
    CloseA->setEnabled(false); // Should be true???
    AddA->setEnabled(false);
    RemoveA->setEnabled(false);
    ConfirmA->setEnabled(false);
    BarChartA->setEnabled(false);
    LineChartA->setEnabled(false);
    ScatterChartA->setEnabled(false);
    AreaChartA->setEnabled(false);
    PieChartA->setEnabled(false);

    QHBoxLayout* container = new QHBoxLayout();
    QVBoxLayout* tabdesc = new QVBoxLayout();
    table = new Table(this);
    desc = new QLabel("Description");
    desc->setFixedHeight(50);
    tabdesc->addWidget(table);
    tabdesc->addWidget(desc);
    container->setSpacing(10);
    table->setFixedWidth(360);
    container->addLayout(tabdesc);


    QtCharts::QChart* chart = new QtCharts::QChart();
    chartView = new QtCharts::QChartView(chart);

    QtCharts::QLineSeries* series = new QtCharts::QLineSeries();
    series->append(0,1);
    chart->addSeries(series);
    chart->setTitle("Void Chart");
    chart->createDefaultAxes();
    chart->legend()->hide();
    chartView->setRenderHint(QPainter::Antialiasing);
    container->addWidget(chartView);
    QWidget* main = new QWidget();
    main->setLayout(container);
    setCentralWidget(main);

    connect(FileM->actions()[4],SIGNAL(triggered(bool)),this,SLOT(close()));
    connect(EditM->actions()[0],SIGNAL(triggered(bool)),this,SLOT(AddUpdate()));
    connect(EditM->actions()[1],SIGNAL(triggered(bool)),this,SLOT(RemoveUpdate()));
    qDebug()<<"mainw constructor";
}

void MainWindow::SetController(Controller* c){
    controller = c;
    connect(FileM->actions()[0], SIGNAL(triggered()), controller, SLOT(CallNewWindow()));
    connect(FileM->actions()[1], SIGNAL(triggered(bool)), controller, SLOT(open()));
    connect(FileM->actions()[2], SIGNAL(triggered(bool)), controller, SLOT(save()));
    connect(FileM->actions()[3], SIGNAL(triggered(bool)), controller, SLOT(Clear()));

    connect(EditM->actions()[0],SIGNAL(triggered(bool)),controller,SLOT(AddToTab()));
    connect(EditM->actions()[1],SIGNAL(triggered(bool)),controller,SLOT(RemoveFromTab()));
    connect(EditM->actions()[2],SIGNAL(triggered(bool)),controller,SLOT(Apply()));

    connect(ViewM->actions()[0], SIGNAL(triggered(bool)), controller, SLOT(CreateBarChart()));
    connect(ViewM->actions()[1], SIGNAL(triggered(bool)), controller, SLOT(CreateLineChart()));
    connect(ViewM->actions()[2], SIGNAL(triggered(bool)), controller, SLOT(CreateScatterChart()));
    connect(ViewM->actions()[3], SIGNAL(triggered(bool)), controller, SLOT(CreateAreaChart()));
    connect(ViewM->actions()[4], SIGNAL(triggered(bool)), controller, SLOT(CreatePieChart()));
}

Table* MainWindow::getTable() const{
    return table;
}

QLabel* MainWindow::getDesc() const{
    return desc;
}

void MainWindow::Update(int i){
    switch(i){
    case 1:
        SaveA->setEnabled(true);
        CloseA->setEnabled(true);
        BarChartA->setEnabled(false);
        LineChartA->setEnabled(true);
        ScatterChartA->setEnabled(true);
        AreaChartA->setEnabled(true);
        PieChartA->setEnabled(true);
        break;
    case 2:
        SaveA->setEnabled(true);
        CloseA->setEnabled(true);
        BarChartA->setEnabled(true);
        LineChartA->setEnabled(false);
        ScatterChartA->setEnabled(true);
        AreaChartA->setEnabled(true);
        PieChartA->setEnabled(true);
        break;
    case 3:
        SaveA->setEnabled(true);
        CloseA->setEnabled(true);
        BarChartA->setEnabled(true);
        LineChartA->setEnabled(true);
        ScatterChartA->setEnabled(false);
        AreaChartA->setEnabled(true);
        PieChartA->setEnabled(true);
        break;
    case 4:
        SaveA->setEnabled(true);
        CloseA->setEnabled(true);
        BarChartA->setEnabled(true);
        LineChartA->setEnabled(true);
        ScatterChartA->setEnabled(true);
        AreaChartA->setEnabled(false);
        PieChartA->setEnabled(true);
        break;
    case 5:
        SaveA->setEnabled(true);
        CloseA->setEnabled(true);
        BarChartA->setEnabled(true);
        LineChartA->setEnabled(true);
        ScatterChartA->setEnabled(true);
        AreaChartA->setEnabled(true);
        PieChartA->setEnabled(false);
        break;
    default:
        return;
    }
    AddA->setEnabled(true);
    RemoveA->setEnabled(true);
    ConfirmA->setEnabled(false);
}

QtCharts::QChart* MainWindow::getChart() const {return chartView->chart();}

void MainWindow::setChart() {
    QtCharts::QChart* aux = chartView->chart();
    QtCharts::QChart* chart = new QtCharts::QChart();
    chart->createDefaultAxes();
    chartView->setChart(chart);
    delete aux;
}

void MainWindow::AddUpdate() {
    AddA->setEnabled(false);
    RemoveA->setEnabled(true);
    ConfirmA->setEnabled(true);
    NewA->setEnabled(false);
    OpenA->setEnabled(false);
    SaveA->setEnabled(false);
    BarChartA->setEnabled(false);
    LineChartA->setEnabled(false);
    ScatterChartA->setEnabled(false);
    AreaChartA->setEnabled(false);
    PieChartA->setEnabled(false);
}

void MainWindow::RemoveUpdate() {
    AddA->setEnabled(false);
    RemoveA->setEnabled(false);
    ConfirmA->setEnabled(false);
}
void MainWindow::ApplyUpdate() {
    AddA->setEnabled(true);
    RemoveA->setEnabled(true);
    ConfirmA->setEnabled(false);
    NewA->setEnabled(true);
    OpenA->setEnabled(true);
    SaveA->setEnabled(true);
}

void MainWindow::ClearUpdate() {
    AddA->setEnabled(false);
    RemoveA->setEnabled(false);
    ConfirmA->setEnabled(false);
    SaveA->setEnabled(false);
    CloseA->setEnabled(false);
    BarChartA->setEnabled(false);
    LineChartA->setEnabled(false);
    ScatterChartA->setEnabled(false);
    AreaChartA->setEnabled(false);
    PieChartA->setEnabled(false);
}

bool MainWindow::ApplyIsEnabled() const {
    return ConfirmA->isEnabled();
}

MainWindow::~MainWindow() {}
