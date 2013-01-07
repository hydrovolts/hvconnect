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
#include "HydrovoltsConnectMainWnd.h"

#include <Wt/WContainerWidget>
#include <Wt/WPushButton>
#include <Wt/WFitLayout>
#include <Wt/WTabWidget>

HydrovoltsConnectMainWnd::HydrovoltsConnectMainWnd(WContainerWidget* pRoot,
                                                   HydrovoltsConnectModel* pModel) 
{
    // Set up root container
    m_pRoot = pRoot;
    
    // Set up root layout
    m_pCanvasLayout = new WGridLayout();
    m_pCanvasLayout->setRowStretch(0, 0);
    m_pCanvasLayout->setColumnStretch(0, 0);
    m_pRoot->setLayout(m_pCanvasLayout);

    // HydrovoltsConnect Widget is the main application 
    // Login Dialog is shown if the user isn't logged in.
    m_pHydrovoltsConnectWidget = new HydrovoltsConnectWidget(pModel);                              

    // TODO:  Show login widget if user isn't logged in.
    // Use new Wt Session stuff instead of my custom stuff
    //
    // Create Login Widget if user not logged in                                              
//    if (! m_model.GetUserProfile()->IsLoggedIn())                      
//    {                                                                  
//        m_pDlg = new LoginDialog();                                    
//        m_pDlg->finished().connect(SLOT(this, HydrovoltsConnectMainWnd::OnLogin));
//        m_pDlg->show();                                                
//
//        WContainerWidget* dlg = new WContainerWidget();                
//        dlg->setStyleClass("layoutdiv");                               
//        dlg->addWidget(m_pDlg);                                        
//
//        SetWidget(dlg);                                                  
//    }                                                                  
//    else                                                               
//    {                                                                  
//        // User logged in, fill the main window with the main app widget
          SetWidget(m_pHydrovoltsConnectWidget);                                          
//    }                                                                  
}

HydrovoltsConnectMainWnd::~HydrovoltsConnectMainWnd(void) 
{
    // Delete classes created in constructor.
//    if (m_pHydrovoltsConnectWidget != NULL)                 
//    {                                        
//        delete m_pHydrovoltsConnectWidget;                  
//        m_pHydrovoltsConnectWidget = NULL;                  
//    }                                        
}

void HydrovoltsConnectMainWnd::OnLogin() 
{
   // std::wstring username = m_pDlg->GetUsername();      
   // std::wstring password = m_pDlg->GetPassword();      
   // m_model.GetUserProfile()->Login(username, password);

   // if (m_model.GetUserProfile()->IsLoggedIn())         
   // {                                                   
   //     SetWidget(m_pMainPage);                           
   // }                                                   
   // else                                                
   // {                                                   
   //     m_pDlg->show();                                 
   // }                                                   
}

///////////////////////////////////////////////////////////////////////////////
// Switches the active page.  Doesn't delete the old one.
///////////////////////////////////////////////////////////////////////////////
void HydrovoltsConnectMainWnd::SetWidget(WContainerWidget* pWidget) 
{
    m_pCurrentWidget = pWidget;
    m_pCanvasLayout->addWidget(pWidget, 0, 0);
}
