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

#include <Wt/WServer>
#include "HVDatabaseUpdatedResource.h"
#include "HydrovoltsConnectApp.h"
#include "HydrovoltsConnectModel.h"

using namespace Wt;


class HydrovoltsConnectApp; // Forward declaration required due to callbacks.
class HVDatabaseUpdatedResource;

class HydrovoltsConnectRestApi
{
    public:
        HydrovoltsConnectRestApi(WServer* pServer);
        ~HydrovoltsConnectRestApi(void);
        bool registerForUpdates(HydrovoltsConnectApp *client,
                                boost::function<void(int)>& databaseUpdated);
        bool unregisterForUpdates(HydrovoltsConnectApp *client);

    private:
        HVDatabaseUpdatedResource *m_pDatabaseUpdatedResource;

        WServer*    m_pServer;
};
