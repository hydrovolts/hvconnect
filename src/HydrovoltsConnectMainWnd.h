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

#include <Wt/WContainerWidget>
#include <Wt/WText>
#include <Wt/WString>
#include <Wt/WTreeView>
#include <Wt/WPopupMenu>
#include <Wt/WStandardItemModel>
#include <Wt/WGridLayout>
#include <Wt/WLineEdit>


#include "HydrovoltsConnectModel.h"
#include "HydrovoltsConnectWidget.h"

using namespace Wt;

class HydrovoltsConnectMainWnd {
    public:
        HydrovoltsConnectMainWnd(WContainerWidget* pRoot,
                                 HydrovoltsConnectModel* pModel);
        ~HydrovoltsConnectMainWnd(void);

        // Slots
        void OnLogin(); // Called when user has submitted their user/password

    private:

        // Widgets
        WContainerWidget*   m_pRoot;
        WGridLayout*        m_pCanvasLayout;
        WContainerWidget*   m_pCurrentWidget; // never delete

        HydrovoltsConnectWidget*  m_pHydrovoltsConnectWidget;

        // Widget switching
        void SetWidget(WContainerWidget* pWidget);

        ///////////////////////////////
        // Login Page Widgets

        //TODO:  Try out the new Wt Login Dialog instead of your own.
        //LoginDialog*        m_pDlg;
};
