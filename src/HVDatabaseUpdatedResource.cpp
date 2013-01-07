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
#include "HVDatabaseUpdatedResource.h"
#include <sstream>
#include <Wt/WObject>
#include <Wt/Http/Request>
#include <Wt/Http/Response>

HVDatabaseUpdatedResource::HVDatabaseUpdatedResource(WServer *pServer, Wt::WObject *parent) : Wt::WResource(parent)
{
    m_pServer = pServer;
    //suggestFileName("data.txt");
}

HVDatabaseUpdatedResource::~HVDatabaseUpdatedResource () {
    beingDeleted(); // see "Concurrency issues" below.
}

bool HVDatabaseUpdatedResource::registerForUpdates(HydrovoltsConnectApp *client, 
                                                   DatabaseUpdatedCallback& databaseUpdated)
{
    // Lock so only one thread at a time can modify active clients.
    boost::recursive_mutex::scoped_lock lock(m_mutex);

    if (m_activeClients.count(client) == 0) 
    {
        ClientInfo clientInfo;
        clientInfo.sessionId = WApplication::instance()->sessionId();
        clientInfo.databaseUpdatedCallback = databaseUpdated;

        m_activeClients[client] = clientInfo;

        return true;
    }
    
    return false;
}

bool HVDatabaseUpdatedResource::unregisterForUpdates(HydrovoltsConnectApp *client)
{
    if (client == NULL)
    {
        return false;
    }
    
    m_activeClients.erase(client);
    return true;
}

void HVDatabaseUpdatedResource::handleRequest(const Wt::Http::Request& request, 
                                              Wt::Http::Response& response)
{
    int projectId = -1;
    const std::string * pStrProjectId = request.getParameter("projectid");
    if (pStrProjectId && pStrProjectId->size() > 0)
    {
        cout << "PROJECT ID:  " << *pStrProjectId << endl;
        istringstream ( *pStrProjectId) >> projectId;
        cout << "projectId:  " << projectId << endl;

        if (projectId > 0)
        {
            // Notify each client (HydrovoltsConnectApp Session) that the database was
            // updated.
            for (ClientMap::const_iterator i = m_activeClients.begin(); i != m_activeClients.end(); i++)
            {
                m_pServer->post(i->second.sessionId, 
                                boost::bind(i->second.databaseUpdatedCallback, projectId));
            }
        }
    }
    
    // Send a response back to the TCP Daemon
    response.setMimeType("text/html");
    response.out() << "OK" << std::endl;
}
