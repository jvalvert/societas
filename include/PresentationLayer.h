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
    ~MainWindow();
public slots:
    void SL_Quitting();


private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};
extern MainWindow * pMainWindow;
extern bool societasQuit;
#endif // MAINWINDOW_H
