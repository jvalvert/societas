#include <QApplication>
#include "PresentationLayer.h"
#include "DataAccessLayer.h"



int main(int argc, char *argv[])
{

   /// Instanciate Main Process
    QApplication mainProcess(argc, argv);
    qDebug()<<"Main Societas Thread: "<<QThread::currentThreadId();

    /// Data Access Thread
      DataAccessService dataAccessServiceThread;
      // destroy the Application Thread before kill the main process
      QObject::connect(&mainProcess, SIGNAL(aboutToQuit()), &dataAccessServiceThread, SLOT(sl_quit()));
      //start application service Thread
      dataAccessServiceThread.start();

   /// Start Application Thread
    ApplicationService appServiceThread;
    // destroy the Application Thread before kill the main process
    QObject::connect(&mainProcess, SIGNAL(aboutToQuit()), &appServiceThread, SLOT(sl_quit()));
    //start application service Thread
    appServiceThread.start();



    /// Presentation Layer Start the Main Window
    MainWindow societasMainWindow;
    QObject::connect(&mainProcess, SIGNAL(aboutToQuit()), &societasMainWindow, SLOT(SL_Quitting()));
    societasMainWindow.show();

    mainProcess.exec();

    return 0;
}
