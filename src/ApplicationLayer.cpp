
/*
 *Aplication Layer
 * Aplication Layer serves webservices and websockets using an embeeded Mongoose web server.
 * The webervices are provided using a normal HTTP request (GET or POST) using json objects
 * and HTTP responses to get and json object with the result.
 * ==========example of common script used call a restfull webservice
 *
 * $(document).on('keyup', '#n1, #n2', function() {
                                    $.ajax({
                                            url: 'http://localhost:38000/restful/mult',
                                            method: 'POST',
                                            dataType: 'json',
                                            data: { n1: $('#n1').val(), n2: $('#n2').val() },
                                            success: function(json) {
                                            $('#result1').html(json.result);
                                            }
                                           });
                                       });

 *
 * The websocket is
 */

#include "ApplicationLayer.h"
#include "BusinessLayer.h"

//******************************* Mongoose parameters*********************************************************
// webserver Startup info
QString g_http_mode = "http"; // if the server has a certificate instaled, we can use https (TODO: create and install autosigned ssl certificate )
QString  g_webServerAddress = "localhost"; // the Http server  for serve Apps from Mongoose server
QString  g_webServerPort= "38000"; // the listening port, used to start the server and as reference to open the apps and call the restful webservices

// Apps and Restful services info for routing
QString g_Apps_route = "/Apps/"; // route for all apps
QString g_Api_route = "/api/";// route for all Restful Apis


//======================================THREAD MANAGEMENT AND SERVER STARTUP===========================================
//protected method that start the mongoose server in a separate thread



void
ApplicationService::run()
    {
    int a;
    a = 10;
    a--;
    qDebug()<<"Webserver API running in a process thread: " << currentThreadId();
    // Create and configure the server
    server = mg_create_server(NULL, ev_handler);
    // Create the websocket to listen on a particular address (by default localhost)
    // TIP: To publish the webserver over the network, just assign "g_webServerPort" to "webSocket"

    QString webSocket=g_webServerAddress+":"+g_webServerPort;
    // set the document root relative to the executable location and serving the "Apps" folder
    QString qAppPath= QCoreApplication::applicationDirPath()+g_Apps_route;

    mg_set_option(server, "listening_port", webSocket.toStdString().c_str() );
    // set the document root to the working directory of the app
    // in mac, inside a bundle directory where the executable is
    mg_set_option(server, "document_root", qAppPath.toStdString().c_str());

    qDebug() << "Society Pro Web API. by Central Services. Listening at port "+g_webServerPort+"...";

    while(true)
        mg_poll_server(server, 1000);
    }

void ApplicationService::sl_quit()
{

    qDebug()<<"Closing Webserver API with thread: "<< QThread::currentThreadId();
    // Cleanup, and free server instance
   // if (NULL != server) // check if the server is not loaded at quit time
   //    mg_destroy_server(&server);
   // close the thread
    terminate();
}




//================================WEBSERVICES HANDLING===========================

// for testing purposes
void ApplicationService::ApiWrap_Mult(struct mg_connection *conn)
{
  char n1[100], n2[100];
  // Get form variables
  mg_get_var(conn, "n1", n1, sizeof(n1));
  mg_get_var(conn, "n2", n2, sizeof(n2));
  mg_printf_data(conn, "{ \"result\": %lf }", strtod(n1, NULL) * strtod(n2, NULL));
}



//=========================================API ROUTING======================================================
// parseApiRoute, receive and uri, parse it and return the app code based in the apps Matrix

 bool ApplicationService::parseApiRoute(std::string restUri, int &namespaceCode,int  &methodCode)
{  //remove the /api/
   std::string apiUri;
   std::string nameSpace;
   std::string methodName;
   size_t dotPos;

   apiUri=restUri.substr(5,restUri.length());

   // obtain the Method name first.
   // A valid restful call call must be formated like <namespace>.<method>

   // Get the position where a "." apears

   dotPos= apiUri.find(".");

   // if no . is present return false because the call is not propery formed
     if (dotPos == std::string::npos)
      return false;

   // get the namespace
     nameSpace= apiUri.substr(0,dotPos);
     methodName=apiUri.substr(dotPos+1,methodName.length()-1);
     fprintf(stderr,"\n Namespace: %s \n Method: %s\n",nameSpace.c_str(),methodName.c_str());


    // find if the api is registered in apiMatrix
    //initialize the codes to know if the api and the api matches
    namespaceCode=-1;
    methodCode=-1;

   for (int i=0;i < maxNamespaces;i++ ) // search for the  namespace , that is  located at the first api matrix element
   {

         if (apiMatrix[i][0].compare("@")==0) break; // exit because reach an empty app name defined by @

         if (nameSpace.compare(apiMatrix[i][0])==0)  // found the api
         {
           namespaceCode=i;
           break; // api found exit the loop
         }


   }

   if (namespaceCode >= 0) // the apiName exists, find the method
     {

       for (int i=1;i < maxMethod;i++ ) // search for the method name, that is defined from the second and max method array (0 is for api name)
       {


           if (apiMatrix[namespaceCode][i].compare("@")==0) break; // exit because reach an empty method name defined by @

             if (methodName.compare(apiMatrix[namespaceCode][i])==0)  // found the method
             {
               methodCode=i;
               break; // method found exit the loop
             }
       }

    }

     if (methodCode < 0) return false; // the method does not exists


   return true; // the api and method exists
}

 //return string parameter value
std::string ApplicationService::getRequestParameter(struct mg_connection *conn,std::string parameterName)
{
    char  parameter[100];

    //get te str parameter
    mg_get_var(conn, parameterName.c_str(), parameter, sizeof(parameter));

    std::string outParameter(parameter);

   return outParameter;
}

 // Route the api and method properly, and execute it returning an json object
 int  ApplicationService::route_api_requests(struct mg_connection *conn)
{
    std::string restUri(conn->uri);
    int apiCode,methodCode;

    if (parseApiRoute (restUri, apiCode, methodCode)) // correct api method was invoked
     {
     BusinessLayer BusinessLayer;
     std::string jsonResponse="{result:\"Valid but not implemented yet\" s s}";
     fprintf(stderr,"\nApi Exists: Api Code %i Method Code %i",apiCode,methodCode);

// Given and app code and method code invoke the apropiate method and return the json object
// Define all the api paths for restful webservices in const std::string apiMatrix[][] (headerfile)

     switch(apiCode) //evaluate the api code
    {
        case 0: /////////////API CODE 0 ///////////////////////
        {
            switch (methodCode) // for testing pruposes
            {
                case 1:              ///test 1
                {

                    break;
                }
                case 2:             ///test 2
                {

                    break;
                }
            }
         break;
       }///////////////////END APICODE 0/////////////////////////////

       case 1: ///////////////////API CODE 1////////////////////////////
       {
            switch (methodCode)
            {
                case 1:
                {


                    break;
               }
                case 2:
                {
                    break;
                }
            }

         break;
        } ///////////////////END APICODE 1/////////////////////////////

        case 2: //////////////////APICODE 2/////////////////////////////
        {
            switch (methodCode)
            {
                case 1:
                {
                    break;
                }
                case 2:
                {
                    break;
                }
            }

         break;
        }    ///////////////////END APICODE 2/////////////////////////////////

        case 3: //////////////////APICODE 3/////////////////////////////
        {
            switch (methodCode) ///files.
            {
                case 1:
                {

                break;
                }
                case 2:
                {
                break;
                }
            }
          break;
        } ///////////////////APICODE 2/////////////////////////////

        case 4: ////////////////// NAMESPACE TEMPLATE/////////////////////////////
        {
            switch (methodCode) ///namespace.
            {
                case 1:                  ///method
            {
               //request parameters
               ///getRequestParameter(conn,"parameter");
               // call the correspondant BusinessLayer method and asign the return value to jsonResponse. for example:
              /// jsonResponse= BusinessLayer.test_OT(role,1);
              break;
             }
            }
          break;
        } ///////////////////END TEMPLATE NAMESPACE/////////////////////////////
      }
     mg_printf_data(conn, jsonResponse.c_str());
     return MG_TRUE;
     }

    // wrong request go resource not found
    mg_send_file(conn, s_notfound_uri, s_no_cache_header);
    return MG_MORE;



}


//============================================HANDLE WEB REQUESTS======================================================


//======================SESSION AND API KEY=====================================



 static void generate_ssid(const char *user_name, const char *expiration_date,
                          char *ssid, size_t ssid_size) {
  char hash[33];
  mg_md5(hash, user_name, ":", expiration_date, ":", s_secret, NULL);
  snprintf(ssid, ssid_size, "%s|%s|%s", user_name, expiration_date, hash);
}



// *************  CHECK AUTHENTICATION EVENT: Check if the session cookie is created, if not go to login page or show error
static int check_auth(struct mg_connection *conn) {

  char ssid[100], calculated_ssid[100], name[100], expire[100];
  // Always authenticate requests to login page

  if (strcmp(conn->uri, s_login_uri) == 0 ||strcmp(conn->uri, s_error_uri) == 0) {

      return MG_TRUE;
  }

  // Look for session ID in the Cookie.
  // That session ID can be validated against the database that stores
  // current active sessions.
   mg_parse_header(mg_get_header(conn, "Cookie"), "ssid", ssid, sizeof(ssid));
  if (sscanf(ssid, "%[^|]|%[^|]|", name, expire) == 2) {
      generate_ssid(name, expire, calculated_ssid, sizeof(calculated_ssid));
    if (strcmp(ssid, calculated_ssid) == 0) {
        //fprintf(stderr,"\n SSid generated: ssid %s ,calculated ssid %s , name %s,expire %s ... \n",ssid,calculated_ssid,name,expire);
        return MG_TRUE;  // Authenticate
    }
  }

  // Auth failed, do NOT authenticate, redirect to login page

  mg_printf(conn, "HTTP/1.1 302 Moved\r\nLocation: %s\r\n\r\n", s_error_uri);


 return MG_FALSE;
}

//TO DO: BASIC AUTHENTICATION Right now for demo purposses a hardcoded user is validated

// this function perform the call to the users and passwords handler (TO DO)
bool AuthenticateUser (char * name, char * password)
{
   // for POC pruposes use sopro as user and password
   if (strcmp(name, "sopro") == 0 && strcmp(password, "sopro") == 0)
   {  s_secret=password;
       return true;}
   else
   {return false;}
}

int ApplicationService::check_login_form_submission(struct mg_connection *conn)
  {

    char name[100], password[100], ssid[100], expire[100], expire_epoch[100];

     mg_get_var(conn, "name", name, sizeof(name));
     mg_get_var(conn, "password", password, sizeof(password));

     //To do: routine that validate users (maybe passprhase?)
     if (AuthenticateUser(name,password)){
       // Generate expiry date
       time_t t = time(NULL) + 3600;  // Valid for 1 hour
       snprintf(expire_epoch, sizeof(expire_epoch), "%lu", (unsigned long) t);
       strftime(expire, sizeof(expire), "%a, %d %b %Y %H:%M:%S GMT", gmtime(&t));

       generate_ssid(name, expire_epoch, ssid, sizeof(ssid));
       // Set "session id" cookie, there could be some data encoded in it.
       mg_printf(conn,
                 "HTTP/1.1 302 Moved\r\n"
                 "Set-Cookie: ssid=%s; expire=\"%s\"; http-only; HttpOnly;\r\n"
                 "Location: /\r\n\r\n",
                 ssid, expire);
      fprintf(stderr,"\nAutenticated successfully\n");

      return MG_FALSE;
     }
      mg_printf(conn, "HTTP/1.1 302 Moved\r\nLocation: %s\r\n\r\n", s_error_uri);
     return MG_FALSE;
   }


//=================HTML REQUESTS AND EVENTS=====================



// manage the request
int ApplicationService::serve_request(struct mg_connection *conn) {
    fprintf(stderr,"\nUri: %s\n",conn->uri);
    fprintf(stderr,"\nserver requests at  %s\n",conn->uri);

    std::string uri (conn->uri);

    if ( uri.compare(s_login_uri) == 0 &&
         strcmp(conn->request_method, "POST") == 0)
         {
          fprintf(stderr,"\nPost received send the form to check user and password. %s \n",conn->uri);
         return check_login_form_submission(conn);
         }
        else
        {  //check if is a restful request
            if (uri.find(g_Api_route.toStdString()) !=std::string::npos) // check if its a restfull call
            {
                fprintf(stderr,"\nRouting Restful Request:  %s \n",conn->uri);
                return route_api_requests(conn);

            }


      }

return MG_FALSE;  // Serve files in the document_root
}

// handle events

int ApplicationService::ev_handler(struct mg_connection *conn, enum mg_event ev) {

  switch (ev) {
   case MG_AUTH: // TO DO: a full user authentication mecanism calling CHECK_AUTH
                 //        in this stage, assume a non hostile environment :)
      return MG_TRUE; //check_auth(conn);

  case MG_REQUEST:

    return serve_request(conn);

  default: return MG_FALSE;
 }
}
