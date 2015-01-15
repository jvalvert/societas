 #ifndef XMPPCLIENTTEST_H
#define XMPPCLIENTTEST_H
/*
 *  Copyright (c) 2004-2014 by Jakob Schröter <js@camaya.net>
 *  This file is part of the gloox library. http://camaya.net/gloox
 *
 *  This software is distributed under a license. The full license
 *  agreement can be found in the file LICENSE in this distribution.
 *  This software may not be copied, modified, sold or distributed
 *  other than expressed in the named license agreement.
 *
 *  This software is distributed without any warranty.
 */

#include "gloox/client.h"
#include "gloox/messagesessionhandler.h"
#include "gloox/messageeventhandler.h"
#include "gloox/messageeventfilter.h"
#include "gloox/chatstatehandler.h"
#include "gloox/chatstatefilter.h"
#include "gloox/connectionlistener.h"
#include "gloox/disco.h"
#include "gloox/message.h"
#include "gloox/gloox.h"
#include "gloox/lastactivity.h"
#include "gloox/loghandler.h"
#include "gloox/logsink.h"
#include "gloox/connectiontcpclient.h"
#include "gloox/connectionsocks5proxy.h"
#include "gloox/connectionhttpproxy.h"
#include "gloox/messagehandler.h"
#include "gloox/rostermanager.h"
using namespace gloox;

#ifndef _WIN32
# include <unistd.h>
#endif

#include <stdio.h>
#include <string>

#include <cstdio> // [s]print[f]

#if defined( WIN32 ) || defined( _WIN32 )
# include <windows.h>
#endif

class xmppClient : public MessageSessionHandler, ConnectionListener, LogHandler,
                    MessageEventHandler, MessageHandler, ChatStateHandler,RosterListener
{
  public:
    xmppClient() : m_session( 0 ), m_messageEventFilter( 0 ), m_chatStateFilter( 0 ) {}
    virtual ~xmppClient() {}
    void startXmppSession(std::string strJid,std::string strXmppServer,std::string strXmppResource,std::string strJidPassword);
    bool sendMessage(std::string strJid,std::string strXmppServer,std::string message);

// implement methods
    virtual void onConnect();
    virtual void onDisconnect( ConnectionError e );
    virtual bool onTLSConnect( const CertInfo& info );
    virtual void handleMessage( const Message& msg, MessageSession * /*session*/ );
    virtual void handleMessageEvent( const JID& from, MessageEventType event );
    virtual void handleChatState( const JID& from, ChatStateType state );
    virtual void handleMessageSession( MessageSession *session );
    virtual void handleLog( LogLevel level, LogArea area, const std::string& message );
    virtual void handleItemSubscribed( const JID& jid )
        {
          printf( "subscribed %s\n", jid.bare().c_str() );
        }

        virtual void handleItemAdded( const JID& jid )
        {
          printf( "added %s\n", jid.bare().c_str() );
        }

        virtual void handleItemUnsubscribed( const JID& jid )
        {
          printf( "unsubscribed %s\n", jid.bare().c_str() );
        }

        virtual void handleItemRemoved( const JID& jid )
        {
          printf( "removed %s\n", jid.bare().c_str() );
        }

        virtual void handleItemUpdated( const JID& jid )
        {
          printf( "updated %s\n", jid.bare().c_str() );
        }

    virtual void handleRoster( const Roster& roster )
        {
          printf( "roster arriving\nitems:\n" );
          Roster::const_iterator it = roster.begin();
          for( ; it != roster.end(); ++it )
          {
            printf( "jid: %s, name: %s, subscription: %d\n",
                    (*it).second->jidJID().full().c_str(), (*it).second->name().c_str(),
                    (*it).second->subscription() );
            StringList g = (*it).second->groups();
            StringList::const_iterator it_g = g.begin();
            for( ; it_g != g.end(); ++it_g )
              printf( "\tgroup: %s\n", (*it_g).c_str() );
            RosterItem::ResourceMap::const_iterator rit = (*it).second->resources().begin();
            for( ; rit != (*it).second->resources().end(); ++rit )
              printf( "resource: %s\n", (*rit).first.c_str() );
          }
        }

        virtual void handleRosterError( const IQ& /*iq*/ )
        {
          printf( "a roster-related error occured\n" );
        }

        virtual void handleRosterPresence( const RosterItem& item, const std::string& resource,
                                           Presence::PresenceType presence, const std::string& /*msg*/ )
        {
          printf( "presence received: %s/%s -- %d\n", item.jidJID().full().c_str(), resource.c_str(), presence );
        }

         virtual void handleSelfPresence( const RosterItem& item, const std::string& resource,
                                           Presence::PresenceType presence, const std::string& /*msg*/ )
        {
          printf( "self presence received: %s/%s -- %d\n", item.jidJID().full().c_str(), resource.c_str(), presence );
        }

        virtual bool handleSubscriptionRequest( const JID& jid, const std::string& /*msg*/ )
        {
          printf( "subscription: %s\n", jid.bare().c_str() );
          StringList groups;
          JID id( jid );
          j->rosterManager()->subscribe( id, "", groups, "" );
          return true;
        }

        virtual bool handleUnsubscriptionRequest( const JID& jid, const std::string& /*msg*/ )
        {
          printf( "unsubscription: %s\n", jid.bare().c_str() );
          return true;
        }

        virtual void handleNonrosterPresence( const Presence& presence )
        {
          printf( "received presence from entity not in the roster: %s\n", presence.from().full().c_str() );
        }




  private:
    Client *j;
    MessageSession *m_session;
    MessageEventFilter *m_messageEventFilter;
    ChatStateFilter *m_chatStateFilter;
};


#endif // XMPPCLIENTTEST_H
