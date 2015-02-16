#include "PresentationLayer.h"

#include "ui_MainWindow.h"
MainWindow * pMainWindow;
bool societasQuit;

template<typename Arg, typename R, typename C>
struct InvokeWrapper {
    R *receiver;
    void (C::*memberFun)(Arg);
    void operator()(Arg result) {
        (receiver->*memberFun)(result);
    }
};

template<typename Arg, typename R, typename C>
InvokeWrapper<Arg, R, C> invoke(R *receiver, void (C::*memberFun)(Arg))
{
    InvokeWrapper<Arg, R, C> wrapper = {receiver, memberFun};
    return wrapper;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pMainWindow=this;

    //Setup Web Engine
    progress = 0;

 /* Inyect a script file example
    QFile file;
    file.setFileName(":/jquery.min.js");
    file.open(QIODevice::ReadOnly);
    jQuery = file.readAll();
    jQuery.append("\nvar qt = { 'jQuery': jQuery.noConflict(true) };");
    file.close();
*/
    view = new QWebEngineView(this);
    view->load(QUrl("http://localhost:8080"));
    connect(view, SIGNAL(titleChanged(QString)), SLOT(adjustTitle()));
    //connect(view, SIGNAL(loadProgress(int)), SLOT(setProgress(int)));
   // connect(view, SIGNAL(loadFinished(bool)), SLOT(finishLoading(bool)));
    connect(view->page(), &QWebEnginePage::featurePermissionRequested, this, &MainWindow::onFeaturePermissionRequested);

   splashScreen(false); //show the progress bar and splash screen while the app loads
 setCentralWidget(view);
}

void MainWindow::SL_Quitting()
{   // flag for all concurrent sub-processes
    qDebug() << "Sopro gui is quitting..";
    societasQuit=true;


}

void MainWindow::splashScreen(bool show)
{
   if (show) // show Splash Screen components only
   {
        view->hide();
        ui->Label_Progress_Bar->setText("Loading Societas..");
   // Handle startup page load progress
        connect(view, SIGNAL(loadProgress(int)), SLOT(setProgress(int)));
        connect(view, SIGNAL(loadFinished(bool)), SLOT(finishLoading(bool)));
   }
   else
   {
       // hide progress bar
        ui->progressBar->hide();
        ui->Label_Progress_Bar->hide();
     view->show();

   }
}

void MainWindow::refreshLoadProgress(int progress)
{
    //show progress bar
    ui->progressBar->show();
    if (progress >= 0 || progress < 100)
    {
    // update the progress bar
       ui->progressBar->setValue(progress);

    }


}

void MainWindow::finishLoading(bool)
 {
     //refreshLoadProgress(100);
     splashScreen(false);
     progress = 100;
     adjustTitle();
     //view->page()->runJavaScript(jQuery);



 }

void MainWindow::viewSource()
{
    QTextEdit* textEdit = new QTextEdit(NULL);
    textEdit->setAttribute(Qt::WA_DeleteOnClose);
    textEdit->adjustSize();
    textEdit->move(this->geometry().center() - textEdit->rect().center());
    textEdit->show();

    view->page()->toHtml(invoke(textEdit, &QTextEdit::setPlainText));
}


void MainWindow::adjustTitle()
{
    if (progress <= 0 || progress >= 100)
        setWindowTitle("Society Pro");
    else
        setWindowTitle(QString("%1 (%2%)").arg(view->title()).arg(progress));
}

void MainWindow::setProgress(int p)
{
    progress = p;
    adjustTitle();
   // refreshLoadProgress(p);
}




void MainWindow::onFeaturePermissionRequested(const QUrl &securityOrigin, QWebEnginePage::Feature feature)
{
    FeaturePermissionBar *permissionBar = new FeaturePermissionBar(this);
    connect(permissionBar, &FeaturePermissionBar::featurePermissionProvided, view->page(), &QWebEnginePage::setFeaturePermission);

    // Discard the bar on new loads (if we navigate away or reload).
    connect(view->page(), &QWebEnginePage::loadStarted, permissionBar, &QObject::deleteLater);

    permissionBar->requestPermission(securityOrigin, feature);
}


MainWindow::~MainWindow()
{
    delete ui;
}

