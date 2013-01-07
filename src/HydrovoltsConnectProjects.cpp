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
#include "HydrovoltsConnectProjects.h"

#include <Wt/WTableView>
#include <Wt/Dbo/QueryModel>
#include <Wt/WGridLayout>
#include <Wt/WItemDelegate> 
#include "HydrovoltsConnectProject.h"

using namespace Wt;

HydrovoltsConnectProjects::HydrovoltsConnectProjects(HydrovoltsConnectModel* pModel)
{
    // Database
    m_pModel = pModel;

    CreateProjectsTableView();
    m_pLayout = new WGridLayout();
    
    if (m_pLayout != NULL && m_pTableView != NULL)
    {
        setLayoutSizeAware(true);
        m_pLayout->addWidget(m_pTableView, 0, 0);
        m_pLayout->setRowStretch(0, 0);
        m_pLayout->setColumnStretch(0, 0);
        
        setLayout(m_pLayout);
        setLayoutSizeAware(true);
    }
}

HydrovoltsConnectProjects::~HydrovoltsConnectProjects()
{
    if (m_pTableView != NULL)
    {
        delete m_pTableView;
        m_pTableView = NULL;
    }

    if (m_pLayout != NULL)
    {
        delete m_pLayout;
        m_pLayout = NULL;
    }
}


void HydrovoltsConnectProjects::CreateProjectsTableView()
{
    // Layout
    // Table
    m_pTableView = new WTableView();
    m_pTableView->setModel(m_pModel->ProjectModel());
    m_pTableView->setSelectionBehavior(SelectRows);
    m_pTableView->setSelectionMode(SingleSelection);
    m_pTableView->setAlternatingRowColors(true);
    m_pTableView->setSortingEnabled(false);
   
    // Set width of ID field so it won't take up so much room 
    m_pTableView->setColumnWidth(0,WLength(40, WLength::Pixel));
    m_pTableView->setColumnHidden(0, true);
  
    // Name 
    m_pTableView->setColumnWidth(1, WLength(100, WLength::Pixel));

    // Install Date
    m_pTableView->setColumnWidth(2, WLength(100, WLength::Pixel));
    WItemDelegate* pDateTimeDelegate = new WItemDelegate();
    pDateTimeDelegate->setTextFormat("MM-dd-yyyy");
    m_pTableView->setItemDelegateForColumn(2, pDateTimeDelegate);
    m_pTableView->setColumnAlignment(2, AlignLeft);

    // IP Address
    m_pTableView->setColumnWidth(3, WLength(100, WLength::Pixel));

    // Hook up slot to signal, so we get called back when a project is selected.
    m_pTableView->selectionChanged().connect(this, &HydrovoltsConnectProjects::selectionChanged);
}

//void HydrovoltsConnectProjects::clicked(WModelIndex index, WMouseEvent mouseEvent)
void HydrovoltsConnectProjects::selectionChanged()
{
    const WModelIndexSet indexSet = m_pTableView->selectedIndexes();
    //const WModelIndexSet index_set = view->selectionModel().selectedIndexes();
    for (WModelIndexSet::iterator indexIterator = indexSet.begin();
         indexIterator != indexSet.end(); 
         ++indexIterator) 
    {
        WModelIndex index = *indexIterator;
        int projectId = Wt::asNumber(index.data());
        m_pModel->SetActiveProject(projectId);
    }
}
