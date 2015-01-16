#include <QApplication>
#include <qtconcurrent/QtConcurrent>
#include "PresentationLayer.h"
//#include "DataAccessLayer.h"
#include "DataAccessLayer/xmppClient.h"


void startXmppClient()
{
    xmppClient xc;
    xc.startXmppSession("valvert","xmpp.cambrian.org","Cambrian","CentralServices");
    xc.receiveXmppMessages();
}
int main(int argc, char *argv[])
{
   /// Instanciate Main Process
    QApplication mainProcess(argc, argv);
    qDebug()<<"Main Societas Thread: "<<QThread::currentThreadId();
/*
  /// Start Application THREAD
    ApplicationService appServiceThread;
    // destroy the Application Thread before kill the main process
    QObject::connect(&mainProcess, SIGNAL(aboutToQuit()), &appServiceThread, SLOT(sl_quit()));
    //start application service Thread
    appServiceThread.start();
*/

    // Presentation Layer Start the Main Window
    MainWindow societasMainWindow;
    societasMainWindow.show();

    //DataAccessService *ds = new DataAccessService();
    //ds->xmpp_Login("valvert","CentralServices");

     QFuture<void> result = QtConcurrent::run(startXmppClient);

     //xc.sendMessage("mac",std::string strXmppServer,std::string message);
    //Execute the main process and all threads

    mainProcess.exec();
    return 0;
}
