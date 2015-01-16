//======================================DATA ACCESS THREAD MANAGEMENT ===========================================
//protected method that start the XMPP CLIENT into a separate thread
#include <DataAccessLayer.h>


std::string DataAccessService::xmpp_Login(std::string strJid,std::string strPassword )
{
p_xmppClient->startXmppSession(strJid,"xmpp.cambrian.org","Cambrian",strPassword);
return "ok";
}
std::string DataAccessService::xmpp_Logout()
{
p_xmppClient->finishXmppSession();
}
std::string DataAccessService::xmpp_sendMessage(std::string recipient,std::string message)
{
    return "ok";
}
std::string DataAccessService::xmpp_retrieveMessages()
{
    return "ok";
}
DataAccessService::DataAccessService()
{
    //loggedIn=false;
}
DataAccessService::~DataAccessService()
{
    if (loggedIn)
        xmpp_Logout();
}
