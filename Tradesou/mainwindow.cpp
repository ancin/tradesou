#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "crawler.h"
#include "runScanner.h"
#include <QtGui>
#include <qstringlist.h>
#include <QSqlTableModel>


/***
 *将相邻的QWidget属性中sizePolicy的Horizontal Policy(或Vertical Policy)都设置成Expanding或Prefered后，
 *再设置Stretch就可以按比例调整QWidget控件的大小
 *
 *
 ****/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    trayIcon= new QSystemTrayIcon(QIcon(":/images/crawler.ico"),this);
    trayIcon->show();
    QIcon icon;
    icon.addFile(QString::fromUtf8(":/images/main.ico"), QSize(), QIcon::Normal, QIcon::Off);
    this->setWindowIcon(icon);


    createHorizontalGroupBox();
    createGridGroupBox();
    createActions();
    createMenus();


    createToolBars();
    createStatusBar();

     ui->setupUi(this);


    QVBoxLayout *mainLayout = new QVBoxLayout;
    //! [2] //! [3]

    //! [3] //! [4]
    mainLayout->addWidget(horizontalGroupBox);
    mainLayout->addWidget(gridGroupBox);

    //! [4] //! [5]
    QWidget *widget = new QWidget();
    widget->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Expanding);

    widget->setLayout(mainLayout);
    setCentralWidget(widget);

    /***
    QTextEdit *title =new QTextEdit(this);//new QTextEdit
    title->setText("Main Window");
    title->setAlignment(Qt::AlignCenter);//设置title居中布局
    this->setCentralWidget(title);//设置title为主体控件
   ***/


    /*************DockWindow 1***********************/
    QDockWidget *dock = new QDockWidget(tr("DockWindow 1"),this);
    dock->setFeatures(QDockWidget::DockWidgetMovable);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
    QTextEdit *title1 = new QTextEdit();
    title1->setText("Property setting");
    dock->setWidget(title1);
    this->addDockWidget(Qt::LeftDockWidgetArea,dock);
    dock = new QDockWidget(tr("DockWindow 2"),this);
    dock->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetClosable);



    /*************DockWindow 2***********************/
    QTextEdit *title2 = new QTextEdit();
    title2->setText("2 other setting");
    dock->setWidget(title2);
    this->addDockWidget(Qt::LeftDockWidgetArea,dock);

    /*************DockWindow 3***********************/
    dock = new QDockWidget(tr("DockWindow 3"),this);
    dock->setFeatures(QDockWidget::AllDockWidgetFeatures);
    output = new QTextEdit();
    output->setText("Resul output");
    dock->setWidget(output);
    this->addDockWidget(Qt::BottomDockWidgetArea,dock);


    //connect(searchBtn,SIGNAL(clicked()),this,SLOT(on_searchBtn_clicked()));

}

void MainWindow::createHorizontalGroupBox()
{
    horizontalGroupBox = new QGroupBox(tr("Search Now"));
    horizontalGroupBox->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Minimum);
    QHBoxLayout *hLayout = new QHBoxLayout;


    QLabel *souLable = new QLabel(tr("Orientation of buttons:"));
    souLable->setText(QString("Test sou "));
    hLayout->addWidget(souLable);
    //
    urlLnEdit = new QLineEdit;
    hLayout->addWidget(urlLnEdit);

    searchBtn = new QPushButton(this);
    searchBtn->setObjectName(QString::fromUtf8("searchBtn"));
    searchBtn->connect(searchBtn, SIGNAL(clicked()), this, SLOT(on_searchBtn_clicked()));
    searchBtn->setText(QString("Search"));
    hLayout->addWidget(searchBtn);

    hLayout->setAlignment(Qt::AlignTop);
    horizontalGroupBox->setAlignment(Qt::AlignTop);


    horizontalGroupBox->setLayout(hLayout);

}

void MainWindow::createGridGroupBox()
{
    gridGroupBox = new QGroupBox(tr("Search Result"));
    gridGroupBox->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    //! [8]
    QGridLayout *layout = new QGridLayout;

    //! [9]
    for (int i = 0; i < NumGridRows; ++i) {
        labels[i] = new QLabel(tr("Line %1:").arg(i + 1));
        lineEdits[i] = new QLineEdit;
        layout->addWidget(labels[i], i + 1, 0);
        layout->addWidget(lineEdits[i], i + 1, 1);
    }

    //! [9] //! [10]
    smallEditor = new QTextEdit;
    smallEditor->setPlainText(tr("This widget takes up about two thirds of the "
                                 "grid layout."));
    // table;
     QSqlTableModel *model = new QSqlTableModel(this);
     model->setTable(QString("tableName"));
        model->setEditStrategy(QSqlTableModel::OnManualSubmit);
        model->select();

        model->setHeaderData(0, Qt::Horizontal, tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, tr("First name"));
        model->setHeaderData(2, Qt::Horizontal, tr("Last name"));

        QTableView *view = new QTableView;
        view->setModel(model);

     layout->addWidget(view, 0, 2, 4, 1);
    //layout->addWidget(smallEditor, 0, 2, 4, 1);
    //! [10]

    //! [11]
    layout->setColumnStretch(1, 10);
    layout->setColumnStretch(2, 20);
    gridGroupBox->setLayout(layout);
}

void MainWindow::createToolBars()
{
    fileToolBar = addToolBar(tr("File"));
    fileToolBar->addAction(newAct);
    fileToolBar->addAction(openAct);
    fileToolBar->addAction(saveAct);

    editToolBar = addToolBar(tr("Edit"));
    editToolBar->addAction(cutAct);
    editToolBar->addAction(copyAct);
    editToolBar->addAction(pasteAct);
}
void MainWindow::createActions(){

    newAct = new QAction(QIcon(":/images/new.png"), tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    openAct = new QAction(QIcon(":/images/open.png"), tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    saveAct = new QAction(QIcon(":/images/save.png"), tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the document to disk"));
    cutAct = new QAction(QIcon(":/images/cut.png"), tr("Cu&t"), this);
    cutAct->setShortcuts(QKeySequence::Cut);
    cutAct->setStatusTip(tr("Cut the current selection's contents to the "
                            "clipboard"));
    copyAct = new QAction(QIcon(":/images/copy.png"), tr("&Copy"), this);
    copyAct->setShortcuts(QKeySequence::Copy);
    copyAct->setStatusTip(tr("Copy the current selection's contents to the "
                             "clipboard"));
    pasteAct = new QAction(QIcon(":/images/paste.png"), tr("&Paste"), this);
    pasteAct->setShortcuts(QKeySequence::Paste);
    pasteAct->setStatusTip(tr("Paste the clipboard's contents into the current "
                              "selection"));
}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}

void MainWindow::createMenus()
{


    fileMenu = QMainWindow::menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
//! [9]
    fileMenu->addAction(openAct);
    //    fileMenu = menuBar()->addMenu(tr("&File"));
    //    fileMenu->addAction(newAct);
    //    fileMenu->addAction(openAct);
    //    fileMenu->addAction(saveAct);
    //    fileMenu->addAction(saveAsAct);
    //    fileMenu->addSeparator();
    //    QAction *action = fileMenu->addAction(tr("Switch layout direction"));
    ////    connect(action, SIGNAL(triggered()), this, SLOT(switchLayoutDirection()));
    //    fileMenu->addAction(exitAct);

    //    editMenu = menuBar()->addMenu(tr("&Edit"));
    //    editMenu->addAction(cutAct);
    //    editMenu->addAction(copyAct);
    //    editMenu->addAction(pasteAct);

    //    windowMenu = menuBar()->addMenu(tr("&Window"));
    //    //updateWindowMenu();
    ////    connect(windowMenu, SIGNAL(aboutToShow()), this, SLOT(updateWindowMenu()));

    //    menuBar()->addSeparator();

    //    helpMenu = menuBar()->addMenu(tr("&Help"));
    //helpMenu->addAction(aboutAct);
    // helpMenu->addAction(aboutQtAct);
}

void MainWindow::on_searchBtn_clicked(){
    qDebug(">>>>degug....starting...");
    QUrl url(urlLnEdit->text());
  // runScanner *r = new runScanner(this,url);
    QTreeWidget *tr_result = new QTreeWidget();
    Crawler *s=new Crawler(url,tr_result);

}
MainWindow::~MainWindow()
{
    delete ui;
}
