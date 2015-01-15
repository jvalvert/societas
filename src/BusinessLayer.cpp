#include <BusinessLayer.h>

/*
Sopro Api Restful Api Middle Tier
*/

/////////////////////////////////API CALLS TO AL SOPRO LOGIC/////////////////////////////////////////

//==================================================================================================
//========= Every app returns a json formated string USING QJSON objects
//==================================================================================================



///////////////////////////////JSON OBJECTS PARSING AND HANDLING//////////////////////////////////////
// Utilities for json objects parsing and handling
// Add and attribute to a QJsonObject (created or not)
bool BusinessLayer::addJSonAttribute(QJsonObject &json, QString attribute,QString value)
{
 json[attribute]=value;
 return true;
}

// Read a particular atribute contained into a json object (not tested yet)
bool BusinessLayer::getJsonAttribute(QJsonObject &json, QString attribute,QString &value)
{

   value = json[attribute].toString();
   return true;
}

// Given an QJson Object, convert it into a Json Document and convert this document to json text format
std::string BusinessLayer::jsonDocumentString(QJsonObject json)
{
     QJsonDocument jsonDoc(json);
     QString jsonString = jsonDoc.toJson();

     return jsonString.toStdString();
}

QJsonObject BusinessLayer::stringDocumentJson(QString strJson)
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(strJson.toUtf8());
    QJsonObject jsonObj = jsonDoc.object();

    return jsonObj;
}



/////////////BASIC RESTFUL///////////////
std::string BusinessLayer::test_Mult(int n1, int n2) {

    int result;
    std::string json;
    QJsonObject jsonObj;

    result=n1 * n2;
    QString strRes(result);
    addJSonAttribute(jsonObj,"result", strRes);
    json=jsonDocumentString(jsonObj);


return json;
}


BusinessLayer::BusinessLayer(){}
BusinessLayer::~BusinessLayer(){}


