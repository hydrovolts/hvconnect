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
#include "HydrovoltsConnectTableView.h"
#include <Wt/WTableView>
#include <Wt/WGridLayout>
#include <Wt/Dbo/QueryModel>
#include <Wt/WItemDelegate>

#include "HydrovoltsConnectOpHistory.h"

using namespace Wt;
using namespace Wt::Dbo;

HydrovoltsConnectTableView::HydrovoltsConnectTableView(
        HydrovoltsConnectModel* pModel,
        WContainerWidget* parent): WContainerWidget(parent)
{
    m_pModel = pModel;

    CreateTable();
    WGridLayout *pLayout = new WGridLayout();
    
    if (pLayout != NULL && m_pTable != NULL)
    {
        setWidth(WLength::Auto);
        
        setHeight(600);
        //setHeight(WLength::Auto); 
        
        setLayoutSizeAware(true);
        pLayout->addWidget(m_pTable, 0, 0);
        pLayout->setRowStretch(0, 0);
        pLayout->setColumnStretch(0, 0);
        
        setLayout(pLayout);
        setLayoutSizeAware(true);
    }
}

HydrovoltsConnectTableView::~HydrovoltsConnectTableView()
{
    if (m_pTable != NULL)
    {
        delete m_pTable;
        m_pTable = NULL;
    }
}

void HydrovoltsConnectTableView::CreateTable()
{
    // Layout
    // Table
    m_pTable = new WTableView();
    //m_pTable->resize(380, 670);
    m_pTable->setModel(m_pModel->OpHistoryModel());
    m_pTable->setSelectionBehavior(SelectRows);
    m_pTable->setSelectionMode(SingleSelection);
    m_pTable->setAlternatingRowColors(true);
    m_pTable->setHeaderHeight(WLength(75));


    // Date YYYYMMDDHHMMSS
    m_pTable->setColumnWidth(0,WLength(140, WLength::Pixel));
    WItemDelegate* pDateTimeDelegate = new WItemDelegate();
    pDateTimeDelegate->setTextFormat("MM-dd-yyyy hh:mm:ss");
    m_pTable->setItemDelegateForColumn(0, pDateTimeDelegate);
    m_pTable->setColumnAlignment(0, AlignLeft);

    // Frequency
    m_pTable->setColumnWidth(1,WLength(100, WLength::Pixel));
    WItemDelegate* pFreqDelegate = new WItemDelegate();
    pFreqDelegate->setTextFormat("%.3f");
    m_pTable->setItemDelegateForColumn(1, pFreqDelegate);
    m_pTable->setColumnAlignment(1, AlignRight);
   
    // Rotor Speed 
    m_pTable->setColumnWidth(2,WLength(110, WLength::Pixel));
    WItemDelegate* pRotorSpeedDelegate = new WItemDelegate();
    pRotorSpeedDelegate->setTextFormat("%.3f");
    m_pTable->setItemDelegateForColumn(2, pRotorSpeedDelegate);
    m_pTable->setColumnAlignment(2, AlignRight);
   
    // Volts 
    m_pTable->setColumnWidth(3,WLength(80, WLength::Pixel));
    WItemDelegate* pVoltsDelegate = new WItemDelegate();
    pVoltsDelegate->setTextFormat("%.3f");
    m_pTable->setItemDelegateForColumn(3, pVoltsDelegate);
    m_pTable->setColumnAlignment(3, AlignRight);
   
    // Amps 
    m_pTable->setColumnWidth(4,WLength(80, WLength::Pixel));
    WItemDelegate* pAmpsDelegate = new WItemDelegate();
    pAmpsDelegate->setTextFormat("%.3f");
    m_pTable->setItemDelegateForColumn(4, pAmpsDelegate);
    m_pTable->setColumnAlignment(4, AlignRight);
   
    // Flow 1  
    m_pTable->setColumnWidth(5,WLength(80, WLength::Pixel));
    WItemDelegate* pFlow1Delegate = new WItemDelegate();
    pFlow1Delegate->setTextFormat("%.3f");
    m_pTable->setItemDelegateForColumn(5, pFlow1Delegate);
    m_pTable->setColumnAlignment(5, AlignRight);
   
    // Flow 2 
    m_pTable->setColumnWidth(6,WLength(80, WLength::Pixel));
    WItemDelegate* pFlow2Delegate = new WItemDelegate();
    pFlow2Delegate->setTextFormat("%.3f");
    m_pTable->setItemDelegateForColumn(6, pFlow2Delegate);
    m_pTable->setColumnAlignment(6, AlignRight);
   
    // Strain 
    m_pTable->setColumnWidth(7,WLength(80, WLength::Pixel));
    WItemDelegate* pStrainDelegate = new WItemDelegate();
    pStrainDelegate->setTextFormat("%.3f");
    m_pTable->setItemDelegateForColumn(7, pStrainDelegate);
    m_pTable->setColumnAlignment(7, AlignRight);
   
    // Gen Temp 
    m_pTable->setColumnWidth(8,WLength(90, WLength::Pixel));
    WItemDelegate* pGenTempDelegate = new WItemDelegate();
    pGenTempDelegate->setTextFormat("%.3f");
    m_pTable->setItemDelegateForColumn(8, pGenTempDelegate);
    m_pTable->setColumnAlignment(8, AlignRight);
   
    // Alarm 
    m_pTable->setColumnWidth(9,WLength(80, WLength::Pixel));
    m_pTable->setColumnAlignment(9, AlignCenter);
    // TODO:  Display icon when true.
    
    // Power  
    m_pTable->setColumnWidth(10,WLength(80, WLength::Pixel));
    WItemDelegate* pPowerDelegate = new WItemDelegate();
    pPowerDelegate->setTextFormat("%.3f");
    m_pTable->setItemDelegateForColumn(10, pPowerDelegate);
    m_pTable->setColumnAlignment(10, AlignRight);
    
    // CumPower 
    m_pTable->setColumnWidth(11,WLength(145, WLength::Pixel));
    WItemDelegate* pCumPowerDelegate = new WItemDelegate();
    pCumPowerDelegate->setTextFormat("%.3f");
    m_pTable->setItemDelegateForColumn(11, pCumPowerDelegate);
    m_pTable->setColumnAlignment(11, AlignRight);

    // ec1WaterL 
    m_pTable->setColumnWidth(12,WLength(100, WLength::Pixel));
    WItemDelegate* pEc1WaterLDelegate = new WItemDelegate();
    pEc1WaterLDelegate->setTextFormat("%.3f");
    m_pTable->setItemDelegateForColumn(12, pEc1WaterLDelegate);
    m_pTable->setColumnAlignment(12, AlignRight);

    // ec1WaterH 
    m_pTable->setColumnWidth(13,WLength(100, WLength::Pixel));
    WItemDelegate* pEc1WaterHDelegate = new WItemDelegate();
    pEc1WaterHDelegate->setTextFormat("%.3f");
    m_pTable->setItemDelegateForColumn(13, pEc1WaterHDelegate);
    m_pTable->setColumnAlignment(13, AlignRight);

    // ec2WaterL 
    m_pTable->setColumnWidth(14,WLength(100, WLength::Pixel));
    WItemDelegate* pEc2WaterLDelegate = new WItemDelegate();
    pEc2WaterLDelegate->setTextFormat("%.3f");
    m_pTable->setItemDelegateForColumn(14, pEc2WaterLDelegate);
    m_pTable->setColumnAlignment(14, AlignRight);

    // ec2WaterH 
    m_pTable->setColumnWidth(15,WLength(100, WLength::Pixel));
    WItemDelegate* pEc2WaterHDelegate = new WItemDelegate();
    pEc2WaterHDelegate->setTextFormat("%.3f");
    m_pTable->setItemDelegateForColumn(15, pEc2WaterHDelegate);
    m_pTable->setColumnAlignment(15, AlignRight);

    // gate 
    m_pTable->setColumnWidth(16,WLength(80, WLength::Pixel));
    WItemDelegate* pGateDelegate = new WItemDelegate();
    pGateDelegate->setTextFormat("%.3f");
    m_pTable->setItemDelegateForColumn(16, pGateDelegate);
    m_pTable->setColumnAlignment(16, AlignRight);

    // head 
    m_pTable->setColumnWidth(17,WLength(80, WLength::Pixel));
    WItemDelegate* pHeadDelegate = new WItemDelegate();
    pHeadDelegate->setTextFormat("%.3f");
    m_pTable->setItemDelegateForColumn(17, pHeadDelegate);
    m_pTable->setColumnAlignment(17, AlignRight);

    // pwrState 
    m_pTable->setColumnWidth(18,WLength(110, WLength::Pixel));
    WItemDelegate* pPwrStateDelegate = new WItemDelegate();
    pPwrStateDelegate->setTextFormat("%.1f");
    m_pTable->setItemDelegateForColumn(18, pPwrStateDelegate);
    m_pTable->setColumnAlignment(18, AlignRight);
}
