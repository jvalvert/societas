#include "PresentationLayer.h"

#include <QApplication>


#include <DataAccessLayer/webSocketEchoServer.h>

//#define WEBSOCKETS_POC
//#define GLOOX_POC

int main(int argc, char *argv[])
{
    QApplication mainProcess(argc, argv);

    qDebug()<<"Main Societas Thread: "<<QThread::currentThreadId();

    // Start a thread inside the main process
    ApplicationService appServiceThread;
    // destroy the thread before quit the app
     QObject::connect(&mainProcess, SIGNAL(aboutToQuit()), &appServiceThread, SLOT(sl_quit()));
    //start the webserver thread
    appServiceThread.start();
    //The gui must be called after the server loads...


    MainWindow societasMainWindow;

#ifdef GLOOX_POC

   /*  Use for command line tests
    * if (argc !=5)
    {
      printf("\nSocietas 2015. Incorrect parameters. \nrun > Societas <jabberid> <xmpp server FQDN> <xmpp Path> <password>\n");
      return 0;
    }
   // get commandline parameters
    std::string jid (argv[1]);
    std::string xmppServer (argv[2]);
    std::string xmppResource (argv[3]);
    std::string password (argv[4]);

   */


    // r->sendMessage("jorge-linux10849380","xmpp.cambrian.org","Hi Jorge from Societas");
     //r->sendMessage("mac15915979","xmpp.cambrian.org","Hi Mac from Societas");


#endif

#ifdef WEBSOCKETS_POC
return startWebSocketServer("8080");
#endif


    societasMainWindow.show();
    mainProcess.exec();
    return 0;
}
