#include <BusinessLayer.h>
#include <zmq/zmq.h>
#include <zmq/zmq.hpp>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <iostream>
#include <msgpack/msgpack.hpp>
#include <vector>


//======================================THREAD MANAGEMENT ===========================================
//protected method that start zeromq using REQ/REP pattern
void BusinessLayerService::run()
    {
    qDebug()<<"*Bussines layer process thread: " << currentThreadId();
    qDebug() << "   Bussines Logic Server listening at "<< QString::fromStdString(zmqRepReqPort)<<"...";
    // Socket to talk to clients
    void *context = zmq_ctx_new ();
    void *responder = zmq_socket (context, ZMQ_REP);
    std::string bindString = "tcp://127.0.0.1:"+zmqRepReqPort;
    int rc = zmq_bind (responder, bindString.c_str());

    assert (rc == 0);
    char buffer[500];
    forever {

    zmq_recv (responder, buffer, 500, 0);

    msgpack::unpacked msg;    // includes memory pool and deserialized object
    msgpack::unpack(msg, buffer, 500);
    msgpack::object obj = msg.get();
    qDebug() << "Received zmq message from client";
    std::cout <<"zmq response: "<< obj << std::endl;
    sleep (1); // Do some 'work'
    zmq_send (responder, "Message received from zmq server", 20, 0);
    }
}

void BusinessLayerService::sl_quit()
{

    qDebug()<<"Closing Bussines Service with thread: "<< QThread::currentThreadId();

    terminate();
}


/////////////////////////////////API CALLS TO AL SOPRO LOGIC/////////////////////////////////////////

//==================================================================================================
//========= Every app returns a json formated string USING QJSON objects
//==================================================================================================



///////////////////////////////JSON OBJECTS PARSING AND HANDLING//////////////////////////////////////
// Utilities for json objects parsing and handling
// Add and attribute to a QJsonObject (created or not)
bool BusinessLayerService::addJSonAttribute(QJsonObject &json, QString attribute,QString value)
{
 json[attribute]=value;
 return true;
}

// Read a particular atribute contained into a json object (not tested yet)
bool BusinessLayerService::getJsonAttribute(QJsonObject &json, QString attribute,QString &value)
{

   value = json[attribute].toString();
   return true;
}

// Given an QJson Object, convert it into a Json Document and convert this document to json text format
std::string BusinessLayerService::jsonDocumentString(QJsonObject json)
{
     QJsonDocument jsonDoc(json);
     QString jsonString = jsonDoc.toJson();

     return jsonString.toStdString();
}

QJsonObject BusinessLayerService::stringDocumentJson(QString strJson)
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(strJson.toUtf8());
    QJsonObject jsonObj = jsonDoc.object();

    return jsonObj;
}



/////////////BASIC RESTFUL///////////////
std::string BusinessLayerService::test_Mult(int n1, int n2) {

    int result;
    std::string json;
    QJsonObject jsonObj;

    result=n1 * n2;
    QString strRes(result);
    addJSonAttribute(jsonObj,"result", strRes);
    json=jsonDocumentString(jsonObj);


return json;
}





