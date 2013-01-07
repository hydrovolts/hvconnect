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
#include "HydrovoltsConnectChartView.h"
#include <Wt/Chart/WCartesianChart>
#include <Wt/Chart/WAxis>
#include <Wt/WVBoxLayout>
#include <Wt/Dbo/QueryModel>

#define TIMESTAMP_COLUMN 1  // Width of one column, which is in column 0.
#include "HydrovoltsConnectOpHistory.h"
#include "HydrovoltsConnectChartToolbar.h"

using namespace Wt;
using namespace Wt::Dbo;
using namespace Wt::Chart;

HydrovoltsConnectChartView::HydrovoltsConnectChartView(
        HydrovoltsConnectModel* pModel,
        WContainerWidget* parent): 
	WContainerWidget(parent), 
        m_y1(HydrovoltsConnectModel::COL_POWER), 
	m_y2(HydrovoltsConnectModel::COL_POWER, LineSeries, Y2Axis)
{
    m_pModel = pModel;
    resize(WLength::Auto, 600);
    //resize(WLength::Auto, WLength::Auto);

    setStyleClass("layoutdiv");
    CreateChart();
    HydrovoltsConnectChartToolbar* pToolbar = new HydrovoltsConnectChartToolbar( m_pModel, this);
    pToolbar->y1Changed().connect(this, &HydrovoltsConnectChartView::OnY1Changed);
    pToolbar->y2Changed().connect(this, &HydrovoltsConnectChartView::OnY2Changed);
    
    WVBoxLayout *pLayout = new WVBoxLayout();
   
   if (pLayout != NULL && m_pChart != NULL && pToolbar != NULL)
   {

    setWidth(WLength::Auto);
    
    // Toolbar 
    pLayout->addWidget(pToolbar);
    pLayout->setStretchFactor(pToolbar, 0);

    // Chart
    pLayout->addWidget(m_pChart);
    pLayout->setStretchFactor(m_pChart,100);
    //pLayout->setRowStretch();
    //pLayout->setColumnStretch();
        
    setLayoutSizeAware(true);
    setLayout(pLayout);
   }
}

HydrovoltsConnectChartView::~HydrovoltsConnectChartView()
{
    if (m_pChart != NULL)
    {
        delete m_pChart;
        m_pChart = NULL;
    }
}

void HydrovoltsConnectChartView::CreateChart()
{
    // Table:  X-Axis is DateTime, 2 Numeric Y axes.
    // All data must be convertible to a number.
    // NULL VALUES will crash the browser.
    m_pChart = new Wt::Chart::WCartesianChart();
    //m_pChart->setModel(m_pModel->OpHistoryModel());
    m_pChart->setModel(m_pModel->GraphModel());
    m_pChart->setType(Wt::Chart::ScatterPlot);
    m_pChart->setPlotAreaPadding(150, Wt::Left);  // 150 Pixels
    m_pChart->setPlotAreaPadding(150, Wt::Bottom); // 150 Pixels
    
    m_pChart->setLegendLocation(Wt::Chart::LegendOutside, Wt::Left, Wt::AlignMiddle);
    m_pChart->setLegendEnabled(true);
   
    // X-Axis:  Time 
    m_pChart->axis(Wt::Chart::XAxis).setScale(Wt::Chart::DateTimeScale);
    m_pChart->axis(Wt::Chart::XAxis).setLabelAngle(45);
    m_pChart->setXSeriesColumn(HydrovoltsConnectModel::COL_TIMESTAMP); // 0 = Timestamp column


    // Y-Axis:  Data
    m_pChart->axis(Wt::Chart::Y2Axis).setScale(Wt::Chart::LinearScale);
    m_pChart->axis(Wt::Chart::Y2Axis).setRange(Wt::Chart::WAxis::AUTO_MINIMUM, Wt::Chart::WAxis::AUTO_MAXIMUM);
    m_pChart->axis(Wt::Chart::Y2Axis).setAutoLimits(Wt::Chart::MinimumValue | Wt::Chart::MaximumValue); 
    m_pChart->axis(Wt::Chart::Y2Axis).setVisible(true); 
    
    m_y1.setType(Wt::Chart::LineSeries);
    m_y1.setMarker(Wt::Chart::NoMarker);
    m_y1.setLegendEnabled(true);
    m_pChart->addSeries(m_y1);

    m_y2.setType(Wt::Chart::LineSeries);
    m_y2.setMarker(Wt::Chart::NoMarker);
    m_y2.setLegendEnabled(true);
    m_pChart->addSeries(m_y2);    
}

void HydrovoltsConnectChartView::OnY1Changed(HydrovoltsConnectModel::OpHistoryCol col)
{
    int modelColumn = int(col);
    cout << "OnY1Changed:  OpHistoryCol = " << modelColumn;
    m_pChart->series(m_y1.modelColumn()).setModelColumn(modelColumn);;
    m_y1.setModelColumn(modelColumn);
}

void HydrovoltsConnectChartView::OnY2Changed(HydrovoltsConnectModel::OpHistoryCol col)
{
    int modelColumn = int(col);
    cout << "OnY2Changed:  OpHistoryCol = " << modelColumn;
    m_pChart->series(m_y2.modelColumn()).setModelColumn(modelColumn);;
    m_y2.setModelColumn(modelColumn);
}
