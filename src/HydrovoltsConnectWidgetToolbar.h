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
#include "HydrovoltsConnectModel.h"

#include <Wt/Ext/ToolBar>
#include <Wt/WComboBox>
#include <Wt/WDatePicker>
#include <Wt/WStringListModel>

using namespace Wt;
class HydrovoltsConnectWidgetToolbar : public Ext::ToolBar
{
public:
    HydrovoltsConnectWidgetToolbar( HydrovoltsConnectModel* pModel, WContainerWidget* pParent=0); 
    ~HydrovoltsConnectWidgetToolbar(void);

private:

    // Methods
    void OnQuickpickerSelected();
    void OnBeginDateChanged();
    void OnEndDateChanged();

    // widgets
    Wt::WComboBox   *m_pQuickpicker;
    Wt::WDatePicker *m_pBeginDate;
    Wt::WDatePicker *m_pEndDate;
    Wt::WText       *m_pCumPower;

    HydrovoltsConnectModel* m_pModel;
};
