#include "PresentationLayer.h"
#include "DataAccessLayer.h"
#include "ui_MainWindow.h"
MainWindow * pMainWindow;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pMainWindow=this;
}

MainWindow::~MainWindow()
{
    delete ui;
}


