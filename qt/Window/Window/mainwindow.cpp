#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("Capturability Based Analysis"));

    createActions();
    createMenus();
    createToolBars();

    cw = new QWidget(this);
    this->setCentralWidget(cw);

    MenuWidget *widgetMenu = new MenuWidget(80, 890);
    QWidget *widgetSetting = new QWidget();
    QWidget *widgetScene   = new QWidget();
    QWidget *widgetDetail  = new QWidget();
    QWidget *widgetConsole = new QWidget();

    QGridLayout* layout = new QGridLayout;
    layout->setSpacing(0);
    layout->setMargin(0);
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(widgetMenu   ,0,0,2,1);
    layout->addWidget(widgetSetting,0,1,2,1);
    layout->addWidget(widgetScene  ,0,2);
    layout->addWidget(widgetDetail ,0,3);
    layout->addWidget(widgetConsole,1,2,1,2);
    this->centralWidget()->setLayout(layout);

    widgetSetting->setFixedSize( 240, 890);
    widgetScene  ->setFixedSize( 700, 700);
    widgetDetail ->setFixedSize( 250, 700);
    widgetConsole->setFixedSize( 950, 186);

    setWindowColor(widgetSetting, 240, 890, QColor("#FFFFFF"));
    setWindowColor(widgetScene  , 700, 700, QColor("#FFFFFF"));
    setWindowColor(widgetDetail , 250, 700, QColor("#FFFFFF"));
    setWindowColor(widgetConsole, 950, 186, QColor("#FFFFFF"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createActions()
{
    QIcon icon;

    // Open file
    icon = QApplication::style()->standardIcon( QStyle::SP_DialogOpenButton );
    openAct = new QAction(icon, tr("Open"), this);
    openAct->setStatusTip(tr("Open the project file"));
    //connect(openAct, SIGNAL(triggered()), this, SLOT(saveAs()));

    // Save File
    icon = QApplication::style()->standardIcon( QStyle::SP_DialogSaveButton );
    saveAsAct = new QAction(icon, tr("Save&As"), this);
    saveAsAct->setShortcuts(QKeySequence::SaveAs);
    saveAsAct->setStatusTip(tr("Save the project file under a new filename"));
    //connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));
}

void MainWindow::createMenus()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAsAct);
}

void MainWindow::createToolBars()
{
    QToolBar *fileToolBar = addToolBar(tr("File"));
    fileToolBar->addAction(openAct);
    fileToolBar->addAction(saveAsAct);
}

void MainWindow::setWindowColor(QWidget *widget, int width, int height, const QColor color)
{
    QLabel *plabel=new QLabel(widget);
    plabel->setFixedSize(width, height);
    QPalette palette = plabel->palette();
    palette.setColor(plabel->backgroundRole(), color);
    palette.setColor(plabel->foregroundRole(), color);
    plabel->setPalette(palette);
    plabel->setAutoFillBackground(true);
}
