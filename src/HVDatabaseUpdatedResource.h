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
#pragma once

#include "HydrovoltsConnectApp.h"
#include <Wt/WResource>
#include <Wt/Http/Request>
#include <Wt/Http/Response>
#include <Wt/WObject>
#include <boost/thread.hpp>

typedef boost::function<void(int)> DatabaseUpdatedCallback;

class HydrovoltsConnectApp; // Forward declaration required due to callbacks.


using namespace Wt;

// Class that notifies all sessions that the database has been updated.
// Typically used by an external process to notify the website that the
// underlying database has been updated and that they should refresh their
// view of it.
class HVDatabaseUpdatedResource : public WResource
{
public:
    HVDatabaseUpdatedResource(WServer *pServer, WObject *parent=0);
    virtual ~HVDatabaseUpdatedResource();
    
    bool registerForUpdates(HydrovoltsConnectApp *client, boost::function<void(int)>&  databaseUpdated);
    bool unregisterForUpdates(HydrovoltsConnectApp *client);

private:
    void handleRequest  (const Wt::Http::Request&   request, 
                         Wt::Http::Response&  response);
        
    struct ClientInfo {
            std::string sessionId;
            DatabaseUpdatedCallback databaseUpdatedCallback;
    };
        
    typedef std::map<HydrovoltsConnectApp*, ClientInfo> ClientMap;

    WServer *m_pServer;    
    ClientMap   m_activeClients;
    boost::recursive_mutex m_mutex;
};
