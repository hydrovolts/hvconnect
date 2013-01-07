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
#include <Wt/WStringListModel>
#include <Wt/WContainerWidget>


//class HydrovoltsConnectChartToolbar : public Wt::WContainerWidget
class HydrovoltsConnectChartToolbar : public Wt::Ext::ToolBar
{
public:
    HydrovoltsConnectChartToolbar( HydrovoltsConnectModel* pModel, WContainerWidget* pParent=0); 
    ~HydrovoltsConnectChartToolbar();

   // provide an accessor for the signal
   Wt::Signal<HydrovoltsConnectModel::OpHistoryCol>& y1Changed() { return y1Changed_; }
   Wt::Signal<HydrovoltsConnectModel::OpHistoryCol>& y2Changed() { return y2Changed_; }

private:
    
    // Defines index for each item in the chart y-axis picker combo boxes
    // NOTE:  This enum doesn't include the timestamp column (column 0).
    static const int SKIPPED_COLS = 1;
    enum OpHistoryPickerField { FIELD_FREQUENCY   , // 0
                                FIELD_ROTOR_SPEED , // 1
                                FIELD_VOLTS       , // 2
                          	    FIELD_AMPS        , // 3
                          	    FIELD_FLOW1       , // 4
                          	    FIELD_FLOW2       , // 5
                          	    FIELD_STRAIN      , // 6
                          	    FIELD_TEMP        , // 7
                          	    FIELD_ALARM       , // 8
                          	    FIELD_POWER       , // 9
                                FIELD_CUMPOWER    , // 10
                                FIELD_EC1WATERL   , // 11
                                FIELD_EC1WATERH   , // 12
                                FIELD_EC2WATERL   , // 13
                                FIELD_EC2WATERH   , // 14
                                FIELD_GATE        , // 15
                                FIELD_HEAD        , // 16 
                                FIELD_PWRSTATE
    };

    Wt::WComboBox *m_pY1Picker;
    Wt::WComboBox *m_pY2Picker;
    HydrovoltsConnectModel* m_pModel;
    Wt::WStringListModel m_opHistoryFieldModel;
  
    // Signals
    Wt::Signal<HydrovoltsConnectModel::OpHistoryCol> y1Changed_;
    Wt::Signal<HydrovoltsConnectModel::OpHistoryCol> y2Changed_;
   
    void OnY1PickerSelected();
    void OnY2PickerSelected();
    bool CreateOpHistoryFieldModel();
    HydrovoltsConnectModel::OpHistoryCol ToOpHistoryCol(OpHistoryPickerField field);
};
