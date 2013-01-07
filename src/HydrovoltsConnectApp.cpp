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
#include <Wt/WString>

#include "HydrovoltsConnectProject.h"
#include "HydrovoltsConnectOpHistory.h"

using namespace Wt;

/*
 * The env argument contains information about the new session, and
 * the initial request. It must be passed to the WApplication
 * constructor so it is typically also an argument for your custom
 * application constructor.
 */
HydrovoltsConnectApp::HydrovoltsConnectApp(const WEnvironment& env,
                                           HydrovoltsConnectRestApi& restApi) :
    WApplication(env), m_restApi(restApi)
{
    // Localized resource bundle and title for browser tab.
    messageResourceBundle().use(this->appRoot() + "HydrovoltsConnect");
    setTitle(WString::tr("main.app.title"));

    m_pModel = new HydrovoltsConnectModel();

    DatabaseUpdatedCallback callbackFunction 
        = boost::bind(&HydrovoltsConnectApp::databaseUpdated, this, _1);

    if (m_restApi.registerForUpdates(this, callbackFunction))
    {
        Wt::WApplication::instance()->enableUpdates(true);
    }

    // Main Window 
    m_pMainWnd = new HydrovoltsConnectMainWnd(root(), m_pModel);

}

HydrovoltsConnectApp::~HydrovoltsConnectApp(void) 
{
    // Stop recevieving incoming update notifications
    m_restApi.unregisterForUpdates(this);

    // Delete the UI
    if (m_pMainWnd != NULL)
    {                         
        delete m_pMainWnd; 
        m_pMainWnd = NULL; 
    }               
    
    // Delete the data model.    
    if (m_pModel != NULL)
    {
        delete m_pModel;
        m_pModel = NULL;
    }
}

void HydrovoltsConnectApp::databaseUpdated(int projectId)
{
    // Only refresh if the project currently being viewed is what's been
    // updated.
    if (m_pModel->ActiveProject() == projectId || -1 == projectId)
    {
        m_pModel->Refresh();
    }
}
