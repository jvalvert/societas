#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <ApplicationLayer.h>
#include <PresentationLayer/featurepermissionbar.h>
#include <QWebEnginePage>
#include <QtWebEngineWidgets>
#include <QWebEngineHistory>
#include <QWebEngineSettings>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QWebEngineView;
QT_END_NAMESPACE

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow // Implement the sopro Gui using a single webview + HTML5 apps
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void SL_Quitting();
protected slots:
    void setProgress(int p);
    void finishLoading(bool);
    void adjustTitle();
    void viewSource();

private:
    Ui::MainWindow *ui;
    void refreshLoadProgress(int progress);
    void splashScreen(bool show);
    QString jQuery;
    QWebEngineView *view;
    int progress;

private slots:
    void onFeaturePermissionRequested(const QUrl &securityOrigin, QWebEnginePage::Feature feature);

};
extern MainWindow * pMainWindow;
extern bool societasQuit;
#endif // MAINWINDOW_H
