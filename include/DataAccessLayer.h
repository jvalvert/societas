#ifndef DATAACCESSLAYER_H
#define DATAACCESSLAYER_H
#include <DataAccessLayer/xmppClient.h>
using namespace std;
class DataAccessService
{
 public:
  DataAccessService();
 ~DataAccessService();
// xmpp Services methods
 string xmpp_Login(string strJid, string strPassword );
 string xmpp_Logout();
 string xmpp_sendMessage(string recipient,string message);
 string xmpp_retrieveMessages();

 // sqllite Services methods
 // 0mq Services methods
private:
 const string xmppServer = "xmpp.cambrian.org";
 const string xmppResource = "Cambrian";
 xmppClient *p_xmppClient;
 bool loggedIn;

};

#endif // DATAACCESSLAYER_H
