/*
   Hydrovolts Connect - Hydrovolts Connect is a web application for presenting 
   a graph and tabular view of Hydrovolts turbine data stored in a database.
      
   © Copyright 2012 Hydrovolts, Inc. All Rights Reserved.
  
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
  
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
  
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "HydrovoltsConnectApp.h"
#include <Wt/WApplication>
#include <Wt/WServer>
#include "HydrovoltsConnectRestApi.h"

using namespace Wt;

// Startup/HTTPD related functions
WApplication* createApplication(const WEnvironment& env,
                                HydrovoltsConnectRestApi& restApi) {
    HydrovoltsConnectApp* app = new HydrovoltsConnectApp(env, restApi);
    app->refresh();

    return app;
}

int main(int argc, char** argv) {
  try {
    Wt::WServer server(argv[0]);
    HydrovoltsConnectRestApi restApi(&server);

    server.setServerConfiguration(argc, argv, WTHTTP_CONFIGURATION);
    // Let's explain boost::bind
    // createApplication - Name of function we are binding too.  See above.
    // _1                - Means take the first argument being passed and 
    //                     use it.  In this case it will always be the 
    //                     WEnvironment of the application.
    // boost:ref(restApi)- Pass the restAPI object by reference.
    //
    server.addEntryPoint(Wt::Application,boost::bind(createApplication, _1,boost::ref(restApi)));
    //server.addEntryPoint(Wt::Application, createApplication); // Original
    
    // RESTFul API
 //   Session::configureAuth();

    if (server.start()) {
      Wt::WServer::waitForShutdown();
      server.stop();
    }
  } catch (Wt::WServer::Exception& e) {
    std::cerr << e.what() << std::endl;
  } catch (std::exception& e) {
    std::cerr << "exception: " << e.what() << std::endl;
  }
}
