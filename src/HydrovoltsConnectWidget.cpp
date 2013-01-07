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
#include "HydrovoltsConnectWidget.h"
#include "HydrovoltsConnectWidgetToolbar.h"
#include "HydrovoltsConnectProjects.h"
#include "HydrovoltsConnectTabs.h"

#include <Wt/WTableView>
#include <Wt/WGridLayout>
#include <Wt/WImage>

HydrovoltsConnectWidget::HydrovoltsConnectWidget(HydrovoltsConnectModel* pModel)
{
    m_pModel = pModel;
    Create();
}

HydrovoltsConnectWidget::~HydrovoltsConnectWidget(void)
{
}

void HydrovoltsConnectWidget::Create()
{
    setStyleClass("layoutdiv");
    m_pBannerImage= new Wt::WImage("img/HydrovoltsConnect.png", this);
    m_pBannerImage->setAlternateText("Hydrovolts Connect"); // TODO:  Localize (for browser based locale?)
    
    HydrovoltsConnectWidgetToolbar* pToolbar = new HydrovoltsConnectWidgetToolbar(m_pModel, this);

    // The main layout is a 3x3 grid layout.
    WContainerWidget* pMainLayout = new WContainerWidget(this);
    pMainLayout->setStyleClass("layoutdiv");
    WGridLayout *pLayout = new WGridLayout();
    
    // Row 0
    // Logo
    //pLayout->addWidget(pToolbar, 0, 0);

    // Row 1
    // Column 0 
    m_pProjectsTab = new HydrovoltsConnectProjectsTab(m_pModel, this);
    pLayout->addWidget(m_pProjectsTab, 1, 0);
   
    // Column 1 - Tabs
    m_pTabs = new HydrovoltsConnectTabs(m_pModel, this);
    pLayout->addWidget(m_pTabs, 1, 1);
    
    // Let row 2 and column 2 take the excess space.
    pLayout->setRowStretch(1, 1);
    pLayout->setColumnStretch(1, 1);
    
    pMainLayout->setLayout(pLayout);
    addWidget(pMainLayout);
}
