#include "PresentationLayer.h"
#include "DataAccessLayer.h"
#include "ui_MainWindow.h"
MainWindow * pMainWindow;
bool societasQuit;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pMainWindow=this;

}

void MainWindow::SL_Quitting()
{   // flag for all concurrent sub-processes
    qDebug() << "Sopro gui is quitting..";
    societasQuit=true;


}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_clicked()
{  societasQuit=true;
   //this->close();
}
