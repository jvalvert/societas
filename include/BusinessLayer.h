#ifndef BusinessLayer_H
#define BusinessLayer_H
/*
BusinessLayer is an Api entry point to all Sopro logic.

BusinessLayer was designed to receive a call originated from restful webservice request (served by mongoose)
As a midle tier component, it has some services to facilitate the api routing to the webserver
*/

#include <iostream>
#include <qglobal.h>
#include <QTime>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariant>
#include <iostream>
#include <string>

class BusinessLayer
{

public:
    BusinessLayer();
    ~BusinessLayer();

//crypto methods
    std::string crypto_secureRandom(int low, int high,std::string source);

//test methods
    std::string test_Mult(int n1, int n2);



//json management
    bool addJSonAttribute(QJsonObject &json, QString attribute,QString value);
    bool getJsonAttribute(QJsonObject &json, QString attribute,QString &value);
    std::string jsonDocumentString(QJsonObject json);
    QJsonObject stringDocumentJson(QString strJson);

};

#endif // BusinessLayer_H
