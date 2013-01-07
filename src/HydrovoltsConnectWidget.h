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
#include <Wt/WTabWidget>
#include <Wt/WImage>

#include "HydrovoltsConnectModel.h"
#include "HydrovoltsConnectProjectsTab.h"

using namespace Wt;

/*
 * Widget to contain:
 *   - Toolbar 
 *   - Project list widget
 *   - Tab widget  
 */
class HydrovoltsConnectWidget : public WContainerWidget {
    public:
        HydrovoltsConnectWidget(HydrovoltsConnectModel* pModel);
        ~HydrovoltsConnectWidget(void);

        // Slots
    private:
        // Data
        HydrovoltsConnectModel*         m_pModel;

        // Widgets
        WContainerWidget*               m_pToolbar;
        //WContainerWidget*             m_pProjectList;
        HydrovoltsConnectProjectsTab*   m_pProjectsTab;
        WImage*                         m_pBannerImage;
        WTabWidget*                     m_pTabs;


        // Layout
        WGridLayout*                    m_pCanvasLayout;

        // Methods
        void Create();
};
