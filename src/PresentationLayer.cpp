#include "PresentationLayer.h"
#include "ui_mainwindow.h"
MainWindow * pMainWindow;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    p_xmppClient = new xmppClient();
    pMainWindow=this;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_connect_2_clicked()
{
    p_xmppClient->startXmppSession(ui->jid->text().toStdString(),ui->xmppServer->text().toStdString(),
                                   ui->resource->text().toStdString(),ui->password->text().toStdString());
}
