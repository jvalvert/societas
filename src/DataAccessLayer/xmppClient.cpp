#include <DataAccessLayer/xmppClient.h>
#include <iostream>
#include <QMessageBox>
#include <PresentationLayer.h>

void xmppClient::startXmppSession(std::string strJid,std::string strXmppServer,std::string strXmppResource,std::string strJidPassword)
{
  // Login to the server
  JID jid( strJid+"@"+strXmppServer+"/"+strXmppResource);
  // on this example, the password is empty to login without authentication
  j = new Client( jid, strJidPassword);
  j->registerConnectionListener( this );
  j->registerMessageSessionHandler( this, 0 );
  j->rosterManager()->registerRosterListener(this);
  j->disco()->setVersion( "xmppClient", GLOOX_VERSION, "Linux" );
  j->disco()->setIdentity( "client", "bot" );
  j->disco()->addFeature( XMLNS_CHAT_STATES );
  StringList ca;
  ca.push_back( "/path/to/cacert.crt" );
  j->setCACerts( ca );
  j->logInstance().registerLogHandler( LogLevelError, LogAreaAll, this );
  starting=true;
  if( j->connect( false ) )
  {
   ConnectionError ce = ConnNoError;
   while (ce==ConnNoError && starting)
   ce = j->recv();
    if (ce != ConnNoError)
         printf( "ce: %d\n", ce );

}
}
void xmppClient::finishXmppSession()
{
delete( j );
}

ConnectionError xmppClient::receiveXmppMessages()
{

    // due the conection (j->connect(false)) was initiated on a "Non Blocking Mode"
    // we need to set a timeout for the recv call (1000 micro seconds)
    // the timeout ocurrs when no data is available to receive
   return j->recv(1000);


}
 bool xmppClient::sendMessage(std::string strJid,std::string message)
 {
     if(j->authed()) {
     qDebug()<<"Sending reply to :"+QString::fromStdString(strJid);
     Message m( Message::Chat, JID( strJid ), message );
     j->send( m );
     return true;

     }
     else
     {
     qDebug() <<"Error, user not authenticated,can´t send the message to "+QString::fromStdString(strJid);;
     }

 return false;
 }

void xmppClient::onConnect()
{
  printf( "connected to XMPP server\n" );
  qDebug() << "Conected !!";
  //QMessageBox::information( pMainWindow,"Connection info","Connection successful",QMessageBox::Ok);
  starting=false;
}


 void xmppClient::onDisconnect( ConnectionError e )
{
  printf( "message_test: disconnected: %d\n", e );
  if( e == ConnAuthenticationFailed )
    printf( "auth failed. reason: %d\n", j->authError() );

 }

 bool xmppClient::onTLSConnect( const CertInfo& info )
{
  time_t from( info.date_from );
  time_t to( info.date_to );

  //QMessageBox::information( pMainWindow,"Connection info","TLS Connection successful",QMessageBox::Ok);
  qDebug()<< "Connecting over TLS..";
  printf( "status: %d\nissuer: %s\npeer: %s\nprotocol: %s\nmac: %s\ncipher: %s\ncompression: %s\n"
          "from: %s\nto: %s\n ",
          info.status, info.issuer.c_str(), info.server.c_str(),
          info.protocol.c_str(), info.mac.c_str(), info.cipher.c_str(),
          info.compression.c_str(), ctime( &from ), ctime( &to ) );
  return true;
}

 void xmppClient::handleMessage( const Message& msg, MessageSession * /*session*/ )
{
  //printf( "\nNew Message Arrived from id %s:\n type: %d, subject: %s, message: %s, thread id: %s\n",msg.from().bare().c_str(),
  //        msg.subtype(), msg.subject().c_str(), msg.body().c_str(), msg.thread().c_str() );

  qDebug() << QTime::currentTime()<< " - Message Content :"<< QString::fromStdString(msg.body());

  //Response
  sendMessage(msg.from().bare(),"Response from original message >>>>>>\n"+msg.body()+"\n<<<<<");



  m_messageEventFilter->raiseMessageEvent( MessageEventDisplayed );

#if defined( WIN32 ) || defined( _WIN32 )
        Sleep( 1000 );
    #else
        sleep( 1 );
    #endif
  m_messageEventFilter->raiseMessageEvent( MessageEventComposing );
  m_chatStateFilter->setChatState( ChatStateComposing );
/*
    #if defined( WIN32 ) || defined( _WIN32 )
        Sleep( 2000 );
    #else
        sleep( 2 );
    #endif
*/
  if( msg.body() == "quit" )
    j->disconnect();
  else if( msg.body() == "subscribe" )
    j->rosterManager()->subscribe( msg.from() );
  else if( msg.body() == "unsubscribe" )
    j->rosterManager()->unsubscribe( msg.from() );
  else if( msg.body() == "cancel" )
    j->rosterManager()->cancel( msg.from() );
  else if( msg.body() == "remove" )
    j->rosterManager()->remove( msg.from() );
  else
    printf( "msg: %s\n", msg.body().c_str() );


}

 void xmppClient::handleMessageEvent( const JID& from, MessageEventType event )
{
  printf( "received event: %d from: %s\n", event, from.full().c_str() );
}

 void xmppClient::handleChatState( const JID& from, ChatStateType state )
{
  printf( "received state: %d from: %s\n", state, from.full().c_str() );
}

 void xmppClient::handleMessageSession( MessageSession *session )
{
  qDebug() << " New session established \n";
  // we can handle only one session. so we get rid of the old session
  j->disposeMessageSession( m_session );
  m_session = session;
  m_session->registerMessageHandler( this );
  m_messageEventFilter = new MessageEventFilter( m_session );
  m_messageEventFilter->registerMessageEventHandler( this );
  m_chatStateFilter = new ChatStateFilter( m_session );
  m_chatStateFilter->registerChatStateHandler( this );

 }

 void xmppClient::handleLog( LogLevel level, LogArea area, const std::string& message )
{
  //qDebug() << "log: level: %d, area: %d, %s\n", level, area, message.c_str() ;
  QString qlevel(level);
  QString qarea(area);
  QString qmessage = QString::fromStdString(message);
  qDebug() << "LOG => level: " << qlevel << " area: " << qarea <<" message: " << qmessage;

}
