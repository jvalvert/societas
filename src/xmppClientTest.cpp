#include <xmppClientTest.h>

void MessageTest::startXmppSession(std::string strJid,std::string strXmppServer,std::string strXmppPath,std::string strJidPassword)
{
  // Login to the server

  JID jid( strJid+"@"+strXmppServer+"/"+strXmppPath);
  // on this example, the password is empty to login without authentication
  j = new Client( jid, strJidPassword);
  j->registerConnectionListener( this );
  j->registerMessageSessionHandler( this, 0 );
  j->disco()->setVersion( "messageTest", GLOOX_VERSION, "Linux" );
  j->disco()->setIdentity( "client", "bot" );
  j->disco()->addFeature( XMLNS_CHAT_STATES );
  StringList ca;
  ca.push_back( "/path/to/cacert.crt" );
  j->setCACerts( ca );

  j->logInstance().registerLogHandler( LogLevelDebug, LogAreaAll, this );

  if( j->connect( false ) )
  {
    ConnectionError ce = ConnNoError;
    while( ce == ConnNoError )
    {
      ce = j->recv();
    }
    printf( "ce: %d\n", ce );
  }

  delete( j );
}

 void MessageTest::onConnect()
{
  printf( "connected!!!\n" );
}

 void MessageTest::onDisconnect( ConnectionError e )
{
  printf( "message_test: disconnected: %d\n", e );
  if( e == ConnAuthenticationFailed )
    printf( "auth failed. reason: %d\n", j->authError() );
}

 bool MessageTest::onTLSConnect( const CertInfo& info )
{
  time_t from( info.date_from );
  time_t to( info.date_to );

  printf( "status: %d\nissuer: %s\npeer: %s\nprotocol: %s\nmac: %s\ncipher: %s\ncompression: %s\n"
          "from: %s\nto: %s\n",
          info.status, info.issuer.c_str(), info.server.c_str(),
          info.protocol.c_str(), info.mac.c_str(), info.cipher.c_str(),
          info.compression.c_str(), ctime( &from ), ctime( &to ) );
  return true;
}

 void MessageTest::handleMessage( const Message& msg, MessageSession * /*session*/ )
{
  printf( "type: %d, subject: %s, message: %s, thread id: %s\n", msg.subtype(),
          msg.subject().c_str(), msg.body().c_str(), msg.thread().c_str() );

  std::string re = "You said:\n> " + msg.body() + "\n Hey Sopro :).";
  std::string sub;
  if( !msg.subject().empty() )
    sub = "Re: " +  msg.subject();

  m_messageEventFilter->raiseMessageEvent( MessageEventDisplayed );
#if defined( WIN32 ) || defined( _WIN32 )
  Sleep( 1000 );
#else
  sleep( 1 );
#endif
  m_messageEventFilter->raiseMessageEvent( MessageEventComposing );
  m_chatStateFilter->setChatState( ChatStateComposing );
#if defined( WIN32 ) || defined( _WIN32 )
  Sleep( 2000 );
#else
  sleep( 2 );
#endif
  m_session->send( re, sub );

  if( msg.body() == "quit" )
    j->disconnect();
}

 void MessageTest::handleMessageEvent( const JID& from, MessageEventType event )
{
  printf( "received event: %d from: %s\n", event, from.full().c_str() );
}

 void MessageTest::handleChatState( const JID& from, ChatStateType state )
{
  printf( "received state: %d from: %s\n", state, from.full().c_str() );
}

 void MessageTest::handleMessageSession( MessageSession *session )
{
  printf( "got new session\n");
  // this example can handle only one session. so we get rid of the old session
  j->disposeMessageSession( m_session );
  m_session = session;
  m_session->registerMessageHandler( this );
  m_messageEventFilter = new MessageEventFilter( m_session );
  m_messageEventFilter->registerMessageEventHandler( this );
  m_chatStateFilter = new ChatStateFilter( m_session );
  m_chatStateFilter->registerChatStateHandler( this );
}

 void MessageTest::handleLog( LogLevel level, LogArea area, const std::string& message )
{
  printf("log: level: %d, area: %d, %s\n", level, area, message.c_str() );
}
