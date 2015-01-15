#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <ApplicationLayer.h>
#include <DataAccessLayer/xmppClient.h>

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    xmppClient *p_xmppClient;
    ~MainWindow();

private slots:
    void on_connect_2_clicked();

private:
    Ui::MainWindow *ui;
};
extern MainWindow * pMainWindow;
#endif // MAINWINDOW_H
