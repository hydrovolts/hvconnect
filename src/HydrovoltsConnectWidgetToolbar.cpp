/*
   Hydrovolts Connect - Hydrovolts Connect is a web application for presenting 
   a graph and tabular view of Hydrovolts turbine data stored in a database.
      
   © Copyright 2012 Hydrovolts, Inc.  All Rights Reserved.
  
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
#include "HydrovoltsConnectWidgetToolbar.h"
#include "HydrovoltsConnectModel.h"
#include "WCSVFileResource.h"

#include "Wt/Ext/ToolBar"

#include <Wt/WText>
#include <Wt/WStringListModel>
#include <Wt/WAnchor>
#include <Wt/WImage>

#include <Wt/Dbo/SqlTraits>

#include <iostream>

// Defines for the date range quick picker combo box
#define DAY           0
#define WEEK          1
#define MONTH         2
#define THREEMONTHS   3
#define YEAR          4



using namespace Wt;

///
// The Toolbar at the top of the screen
// 
HydrovoltsConnectWidgetToolbar::HydrovoltsConnectWidgetToolbar(
        HydrovoltsConnectModel* pModel, 
        WContainerWidget* pParent): 
    Ext::ToolBar(pParent)
{
    m_pModel = pModel;

    //Use this for selecting preset date ranges 
    addSeparator();
    m_pQuickpicker = new Wt::WComboBox();
    m_pQuickpicker->insertItem(DAY,         "Day");
    m_pQuickpicker->insertItem(WEEK,        "Week");
    m_pQuickpicker->insertItem(MONTH,       "Month");
    m_pQuickpicker->insertItem(THREEMONTHS, "3 Months");
    m_pQuickpicker->insertItem(YEAR,        "Year");
    m_pQuickpicker->activated().connect(SLOT(this, HydrovoltsConnectWidgetToolbar::OnQuickpickerSelected));
    m_pQuickpicker->setCurrentIndex(0);
    add(m_pQuickpicker);

    // Start Date
    // Label
    addSeparator();
    Wt::WText* pBeginLabel = new Wt::WText("  Begin:  ");  // TODO:  Localize
    add(pBeginLabel);

    // Picker
    m_pBeginDate = new Wt::WDatePicker();
    m_pBeginDate->setFormat("MM-dd-yyyy");
    Wt::WDate begin = m_pModel->BeginDate();
    if (begin.isValid())
    {
        m_pBeginDate->setDate(begin);
    }
    m_pBeginDate->changed().connect(this, &HydrovoltsConnectWidgetToolbar::OnBeginDateChanged);
    add(m_pBeginDate);
    
    // End Date
    // Label
    addSeparator();
    Wt::WText* pEndLabel = new Wt::WText("  End:  ");  // TODO:  Localize
    add(pEndLabel);
    
    // Picker
    m_pEndDate = new Wt::WDatePicker();
    m_pEndDate->setFormat("MM-dd-yyyy");
    Wt::WDate end = m_pModel->EndDate();
    if (end.isValid())
    {
        m_pEndDate->setDate(end);
    }
    m_pEndDate->changed().connect(this, &HydrovoltsConnectWidgetToolbar::OnEndDateChanged);
    add(m_pEndDate);

    // CSV 
    addSeparator();
    WCSVFileResource* csvFile = new WCSVFileResource(m_pModel, "text/csv", "./hydrovolts.csv");
    csvFile->suggestFileName("hydrovolts.csv");
    csvFile->setDispositionType(Wt::WResource::Attachment);
    
    WImage* pIconCSV = new WImage("img/csv_export.png");
    WAnchor* pAnchor = new WAnchor(csvFile);
    pAnchor->setImage(pIconCSV);
    
    add(pAnchor);
   
    // Fill the rest of the way across the screen 
    addStretch();

    // cumPower
    m_pCumPower = new Wt::WText(m_pModel->cumPowerDisplayText);
    add(m_pCumPower);
}

// Destructor
HydrovoltsConnectWidgetToolbar::~HydrovoltsConnectWidgetToolbar(void)
{
//    if (m_pQuickpicker != NULL)
//    {
//        delete m_pQuickpicker;
//        m_pQuickpicker = NULL;
//    }
//    if (m_pBeginDate != NULL)
//    {
//        delete m_pBeginDate;
//        m_pBeginDate = NULL;
//    }
//
//    if (m_pModel != NULL)
//    {
//        delete m_pModel;
//        m_pModel = NULL;
//    }
}

///
// Sets the begin/end dates that filter the records in response
// to the item picked from the quick picker combobox.
void HydrovoltsConnectWidgetToolbar::OnQuickpickerSelected()
{
    switch(m_pQuickpicker->currentIndex())
    {
        case WEEK:
        {
            WDate today = WDate::currentDate();
            WDate begin = today.addDays(-7);

            // Update GUI 
            m_pBeginDate->setDate(begin);
            m_pEndDate->setDate(today);
            
            // Update model (and GUI table)
            m_pModel->SetDates(begin, today);
            break;
        }
        case MONTH:
        {
            WDate today = WDate::currentDate();
            WDate begin = today.addMonths(-1);
           
            // Update GUI 
            m_pBeginDate->setDate(begin);
            m_pEndDate->setDate(today);
            
            // Update model (and GUI table)
            m_pModel->SetDates(begin, today);
            break;
        }
        case THREEMONTHS:
        {
            WDate today = WDate::currentDate();
            WDate begin = today.addMonths(-3);
            
            // Update GUI 
            m_pBeginDate->setDate(begin);
            m_pEndDate->setDate(today);
            
            // Update model (and GUI table)
            m_pModel->SetDates(begin, today);
            break;
        }
        case YEAR:
        {
            WDate today = WDate::currentDate();
            WDate begin = today.addYears(-1);

            // Update GUI 
            m_pBeginDate->setDate(begin);
            m_pEndDate->setDate(today);

            // Update model (and GUI table)
            m_pModel->SetDates(begin, today);

            break;
        }
        case DAY:
        default:
        {
            WDate today = WDate::currentDate();
            
            // Update GUI 
            m_pBeginDate->setDate(today);
            m_pEndDate->setDate(today);

            // Update model (and GUI table)
            m_pModel->SetDates(today, today);
        }
    }
}

///
// Updates the begin date used to filter the data in response
// to it being changed in the toolbar begin date picker.
void HydrovoltsConnectWidgetToolbar::OnBeginDateChanged()
{
    WDate date = m_pBeginDate->date();
    if (date.isValid())
    {
        m_pModel->SetBeginDate(date);
    }
}


///
// Updates the end date used to filter the data in response
// to it being changed in the toolbar end date picker.
void HydrovoltsConnectWidgetToolbar::OnEndDateChanged()
{
    WDate date = m_pEndDate->date();
    if (date.isValid())
    {
        m_pModel->SetEndDate(date);
    }
}
