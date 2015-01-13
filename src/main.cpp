#include "gui.h"
#include <QApplication>
#include "xmppClientTest.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    gui w;
    if (argc !=4)
    {
      printf("\nSocietas 2015. Incorrect parameters. \nrun > Societas <jabberid> <xmpp server FQDN> <xmpp Path> <password>\n");
      return 0;
    }
   // w.show();
     MessageTest *r = new MessageTest();
     r->startXmppSession("valvert","xmpp.cambrian.org","Cambrian","CentralServices");

     delete( r );
     return 0;
}
