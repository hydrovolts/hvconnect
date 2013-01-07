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

#include "HydrovoltsConnectChartToolbar.h"
#include "HydrovoltsConnectModel.h"

#include <Wt/WText>

HydrovoltsConnectChartToolbar::HydrovoltsConnectChartToolbar( 
        HydrovoltsConnectModel* pModel, 
        WContainerWidget* pParent) :
        Wt::Ext::ToolBar(pParent)
        //WContainerWidget(pParent)
{
    m_pModel = pModel;
    
    // Chart fields
    // Get the fields to put in the pickers
    CreateOpHistoryFieldModel();

    // Chart:  Line 1
    // Label
    addSeparator();
    Wt::WText* pY1Label = new Wt::WText("Y1:  ");  // TODO:  Localize
    add(pY1Label);

    // Picker
    m_pY1Picker = new Wt::WComboBox();
    m_pY1Picker->setModel(&m_opHistoryFieldModel);
    m_pY1Picker->activated().connect(SLOT(this, HydrovoltsConnectChartToolbar::OnY1PickerSelected));
    m_pY1Picker->setCurrentIndex(FIELD_POWER);
    add(m_pY1Picker);
    
    // Chart:  Line 2
    // Label
    addSeparator();
    Wt::WText* pY2Label = new Wt::WText("Y2:  ");  // TODO:  Localize
    add(pY2Label);

    // Picker
    m_pY2Picker = new Wt::WComboBox();
    m_pY2Picker->setModel(&m_opHistoryFieldModel);
    m_pY2Picker->activated().connect(SLOT(this, HydrovoltsConnectChartToolbar::OnY2PickerSelected));
    m_pY2Picker->setCurrentIndex(FIELD_POWER);
    add(m_pY2Picker);

    //resize(WLength::Auto, WLength(50));
}

HydrovoltsConnectChartToolbar::~HydrovoltsConnectChartToolbar()
{
}

void HydrovoltsConnectChartToolbar::OnY1PickerSelected()
{
    OpHistoryPickerField field = (OpHistoryPickerField) m_pY1Picker->currentIndex();
    HydrovoltsConnectModel::OpHistoryCol col = ToOpHistoryCol(field);
    y1Changed_.emit(col); // emit the signal
}

void HydrovoltsConnectChartToolbar::OnY2PickerSelected()
{
    OpHistoryPickerField field = (OpHistoryPickerField) m_pY2Picker->currentIndex();
    HydrovoltsConnectModel::OpHistoryCol col = ToOpHistoryCol(field);
    y2Changed_.emit(col); // emit the signal
}

HydrovoltsConnectModel::OpHistoryCol HydrovoltsConnectChartToolbar::ToOpHistoryCol(OpHistoryPickerField field)
{
    switch (field)
    {
        case FIELD_FREQUENCY:
            return HydrovoltsConnectModel::COL_FREQUENCY;

        case FIELD_ROTOR_SPEED:
            return HydrovoltsConnectModel::COL_ROTOR_SPEED;

        case FIELD_VOLTS:
            return HydrovoltsConnectModel::COL_VOLTS;

        case FIELD_AMPS:
            return HydrovoltsConnectModel::COL_AMPS;

        case FIELD_FLOW1:
            return HydrovoltsConnectModel::COL_FLOW1;

        case FIELD_FLOW2:
            return HydrovoltsConnectModel::COL_FLOW2;

        case FIELD_STRAIN:
            return HydrovoltsConnectModel::COL_STRAIN;

        case FIELD_TEMP:
            return HydrovoltsConnectModel::COL_TEMP;

        case FIELD_ALARM:
        {
            cout << "FIELD_ALARM" << endl;
            return HydrovoltsConnectModel::COL_ALARM;
        }

        case FIELD_POWER:
        {
            cout << "FIELD_POWER" << endl;
            return HydrovoltsConnectModel::COL_POWER;
        }
        case FIELD_CUMPOWER:
        {
            cout << "FIELD_CUMPOWER" << endl;
            return HydrovoltsConnectModel::COL_CUMPOWER;
        }
        case FIELD_EC1WATERL:
        {
            cout << "FIELD_EC1WATERL" << endl;
            return HydrovoltsConnectModel::COL_EC1WATERL;
        }
        case FIELD_EC1WATERH:
        {
            cout << "FIELD_EC1WATERH" << endl;
            return HydrovoltsConnectModel::COL_EC1WATERH;
        }
        case FIELD_EC2WATERL:
        {
            cout << "FIELD_EC2WATERL" << endl;
            return HydrovoltsConnectModel::COL_EC2WATERL;
        }
        case FIELD_EC2WATERH:
        {
            cout << "FIELD_EC2WATERH" << endl;
            return HydrovoltsConnectModel::COL_EC2WATERH;
        }
        case FIELD_GATE:
        {
            cout << "FIELD_GATE" << endl;
            return HydrovoltsConnectModel::COL_GATE;
        }
        case FIELD_HEAD:
        {
            cout << "FIELD_HEAD" << endl;
            return HydrovoltsConnectModel::COL_HEAD;
        }
        case FIELD_PWRSTATE:
        {
            cout << "FIELD_PWRSTATE" << endl;
            return HydrovoltsConnectModel::COL_PWRSTATE;
        }
        default:
        {
            cout << "ERROR:  Invalid field picked from chart toolbar." << endl;
            return HydrovoltsConnectModel::COL_POWER;
        }
    }

}
bool HydrovoltsConnectChartToolbar::CreateOpHistoryFieldModel()
{
    m_opHistoryFieldModel.insertString(int(FIELD_FREQUENCY),  "Frequency");
    m_opHistoryFieldModel.insertString(int(FIELD_ROTOR_SPEED),"Rotor Speed"); 
    m_opHistoryFieldModel.insertString(int(FIELD_VOLTS),      "Volts"); 
    m_opHistoryFieldModel.insertString(int(FIELD_AMPS),       "Amps"); 
    m_opHistoryFieldModel.insertString(int(FIELD_FLOW1),      "Flow 1"); 
    m_opHistoryFieldModel.insertString(int(FIELD_FLOW2),      "Flow 2"); 
    m_opHistoryFieldModel.insertString(int(FIELD_STRAIN),     "Strain"); 
    m_opHistoryFieldModel.insertString(int(FIELD_TEMP),       "Temp"); 
    m_opHistoryFieldModel.insertString(int(FIELD_ALARM),      "Alarm"); 
    m_opHistoryFieldModel.insertString(int(FIELD_POWER),      "Power");
    m_opHistoryFieldModel.insertString(int(FIELD_CUMPOWER),   "CumPower");
    m_opHistoryFieldModel.insertString(int(FIELD_EC1WATERL),  "EC1WaterL");
    m_opHistoryFieldModel.insertString(int(FIELD_EC1WATERH),  "EC1WaterH");
    m_opHistoryFieldModel.insertString(int(FIELD_EC2WATERL),  "EC2WaterL");
    m_opHistoryFieldModel.insertString(int(FIELD_EC2WATERH),  "EC2WaterH");
    m_opHistoryFieldModel.insertString(int(FIELD_GATE),       "Gate");
    m_opHistoryFieldModel.insertString(int(FIELD_HEAD),       "Head");
    m_opHistoryFieldModel.insertString(int(FIELD_PWRSTATE),   "Power State");
   
   return true;
}
