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
#include "HydrovoltsConnectModel.h"
#include "HydrovoltsConnectOpHistory.h"
#include "HydrovoltsConnectProject.h"

#include <Wt/Dbo/backend/Sqlite3>
#include <Wt/Dbo/QueryModel>
#include <Wt/WStandardItem>
#include <Wt/WApplication>

//#include "boost/date_time/gregorian/gregorian.hpp"

using namespace Wt;
HydrovoltsConnectModel::HydrovoltsConnectModel():
    sqlite3("../../db/HydrovoltsConnect.sqlite"),
    m_pGraphModel(NULL),
    m_pOpHistoryModel(NULL),
    m_pProjectModel(NULL)

{
    sqlite3.setDateTimeStorage(Wt::Dbo::SqlDateTime, Wt::Dbo::backend::Sqlite3::ISO8601AsText);
    m_dbSession.setConnection(sqlite3);

    std::string strNumGraphPoints;
    if ( WApplication::readConfigurationProperty("num_graph_points", strNumGraphPoints))
    {
        std::stringstream streamNumGraphPoints(strNumGraphPoints);
        streamNumGraphPoints >> NUM_GRAPH_POINTS;
    }
    else
    {
        NUM_GRAPH_POINTS = 500;
        cout << "ERROR:  Unable to read num_graph_points from config file. Using default of 500." << endl;
        //exit(1);
    }
    
    // Map class to table 
    m_dbSession.mapClass<HydrovoltsConnectProject>("Project"); 
    m_dbSession.mapClass<HydrovoltsConnectOpHistory>("OpHistory"); 
    //m_dbSession.createTables();  

    CreateProjectModel();
    CreateOpHistoryModel();
    CreateGraphModel();  
    
    // Begin and End range of query. 
    // DEFAULT is last day
    WDateTime begin(WDate::currentDate(), WTime(0,0));
    WDateTime end(WDate::currentDate(),WTime(23,59,59,999));

    m_begin = begin;
    m_end = end;
    m_activeProjectId=-1;  // TODO:  Set this to ???

    SetOpHistoryFilter();
}

HydrovoltsConnectModel::~HydrovoltsConnectModel()
{
}

void HydrovoltsConnectModel::SetDates(WDate beginDate, WDate endDate)
{

    if (beginDate.isValid() && endDate.isValid())
    {
        WDateTime begin(beginDate, WTime(0,0));
        m_begin = begin;
        
        WDateTime end(endDate,WTime(23,59,59,999));
        m_end = end;
        
        // Refresh the model using the new values
        SetOpHistoryFilter();
    }
}

WDate HydrovoltsConnectModel::BeginDate()
{
  return m_begin.date();
}

void HydrovoltsConnectModel::SetBeginDate(WDate beginDate)
{
    if (beginDate.isValid())
    {
        WDateTime begin(beginDate, WTime(0,0));
        m_begin = begin;

        // Refresh the model using the new value.
        SetOpHistoryFilter();
    }
}

WDate HydrovoltsConnectModel::EndDate()
{
    return m_end.date();
}

void HydrovoltsConnectModel::SetEndDate(WDate endDate)
{
    if (endDate.isValid())
    {
        WDateTime end(endDate,WTime(23,59,59,999));
        m_end = end;

        // Refresh the model using the new value
        SetOpHistoryFilter();
    }
}

OpHistoryModelType* HydrovoltsConnectModel::OpHistoryModel()
{
    return m_pOpHistoryModel;
}

ProjectModelType* HydrovoltsConnectModel::ProjectModel()
{
    return m_pProjectModel;
}

WStandardItemModel* HydrovoltsConnectModel::GraphModel()
{
    return m_pGraphModel;
}

void HydrovoltsConnectModel::SetActiveProject(int projectId)
{
    m_activeProjectId = projectId;
    SetOpHistoryFilter();
}

int HydrovoltsConnectModel::ActiveProject()
{
    return m_activeProjectId;
}

// Set's the SQL WHERE clause to limit the records by:
// projectID = the id field in the Project table.  E.g. Roza or Butte.
// Begin Date
// End Date
void HydrovoltsConnectModel::SetOpHistoryFilter()
{
    m_pOpHistoryModel->setBatchSize(1000);
    m_pOpHistoryModel->setQuery(
            m_dbSession.find<HydrovoltsConnectOpHistory>().where("projectId = ?").bind(m_activeProjectId).where("timestamp >= ?").bind(m_begin).where("timestamp < ?").bind(m_end), 
            true); // true => keep previous model columns.
    
    // Sort on timestamp 
    m_pOpHistoryModel->sort(0, Wt::AscendingOrder);

    PopulateGraphModel();
}

// Creates columns and sets header names.
void HydrovoltsConnectModel::InitializeGraphModel()
{
    if (m_pGraphModel == NULL) 
    {
        return;
    }
    
    m_pGraphModel->clear();
    m_pGraphModel->insertColumns(0,NUM_COLUMNS);

    // TODO:  Localize second parameter (Column header title)
    //model->setHeaderData(col, boost::any(Wt::WString::fromUTF8(*i)));
    m_pGraphModel->setHeaderData(COL_TIMESTAMP,     boost::any(WString("Time")));
    m_pGraphModel->setHeaderData(COL_FREQUENCY,     boost::any(WString("Frequency")));
    m_pGraphModel->setHeaderData(COL_ROTOR_SPEED,   boost::any(WString("Rotor Speed")));
    m_pGraphModel->setHeaderData(COL_VOLTS,         boost::any(WString("Volts")));
    m_pGraphModel->setHeaderData(COL_AMPS,          boost::any(WString("Amps")));
    m_pGraphModel->setHeaderData(COL_FLOW1,         boost::any(WString("Flow 1")));
    m_pGraphModel->setHeaderData(COL_FLOW2,         boost::any(WString("Flow 2")));
    m_pGraphModel->setHeaderData(COL_STRAIN,        boost::any(WString("Strain")));
    m_pGraphModel->setHeaderData(COL_TEMP,          boost::any(WString("Temp")));
    m_pGraphModel->setHeaderData(COL_ALARM,         boost::any(WString("Alarm")));
    m_pGraphModel->setHeaderData(COL_POWER,         boost::any(WString("Power")));
    m_pGraphModel->setHeaderData(COL_CUMPOWER,      boost::any(WString("cumPower")));
    m_pGraphModel->setHeaderData(COL_EC1WATERL,     boost::any(WString("ec1WaterL")));
    m_pGraphModel->setHeaderData(COL_EC1WATERH,     boost::any(WString("ec1WaterH")));
    m_pGraphModel->setHeaderData(COL_EC2WATERL,     boost::any(WString("ec2WaterL")));
    m_pGraphModel->setHeaderData(COL_EC2WATERH,     boost::any(WString("ec2WaterH")));
    m_pGraphModel->setHeaderData(COL_GATE,          boost::any(WString("Gate")));
    m_pGraphModel->setHeaderData(COL_HEAD,          boost::any(WString("Head")));
    m_pGraphModel->setHeaderData(COL_PWRSTATE,      boost::any(WString("Power State")));
}

void HydrovoltsConnectModel::PopulateGraphModel()
{

    // Remove any existing data
    m_pGraphModel->removeRows(0, m_pGraphModel->rowCount());

    WDateTime lastTime;
    double freq_total              = 0.0;
    double speed_total             = 0.0;
    double volts_total             = 0.0;
    double amps_total              = 0.0;
    double flow1_total             = 0.0;
    double flow2_total             = 0.0;
    double strain_total            = 0.0;
    double temp_total              = 0.0;
    double power_total             = 0.0;
    bool alarm = false;         // Set to true if ANY records have the alarm set.
    double cumPower_total          = 0.0;
    double ec1WaterL_total         = 0.0;
    double ec1WaterH_total         = 0.0;
    double ec2WaterH_total         = 0.0;
    double ec2WaterL_total         = 0.0;
    double gate_total              = 0.0;
    double head_total              = 0.0;
    double pwrState_total          = 0.0;

    // Iterate over OpHistory and average every NUM_GRAPH_POINTS
    int numRows = m_pOpHistoryModel->rowCount();

    // Default to showing all records.  1 row per interval. 
    int rowsPerInterval = 1;

    // If we have a lot of rows, then split them into NUM_GRAPH_POINT
    // intervals and average the values within that interval. 
    if (numRows > NUM_GRAPH_POINTS * 2)
    {
        rowsPerInterval = numRows / NUM_GRAPH_POINTS;
    }

    // Loop through all records putting them into an output table.
    // Each row of the output table is one interval.  So, intervalRowCounter
    // is the row we are currently writing to in the output table.
    int intervalRowCounter = 0;
    for (int row = 0; row < numRows; ++row)
    {
        // Compute averages if we've iterated over rowsPerInterval 
        // or if we are on the last record in the input set, average
        // whatever values we've been able to read.
        // We use the intervalRowCounter as the denominator, so an interval
        // that doesn't have a complete set of records will still have the 
        // correct average. 
        if ((row > 0 && (intervalRowCounter ==  rowsPerInterval)) || (row+1 == numRows))
        {
            double freq_avg         = freq_total      / double(intervalRowCounter);
            double speed_avg        = speed_total     / double(intervalRowCounter);
            double volts_avg        = volts_total     / double(intervalRowCounter);
            double amps_avg         = amps_total      / double(intervalRowCounter);
            double flow1_avg        = flow1_total     / double(intervalRowCounter);
            double flow2_avg        = flow2_total     / double(intervalRowCounter);
            double strain_avg       = strain_total    / double(intervalRowCounter);
            double temp_avg         = temp_total      / double(intervalRowCounter);
            double power_avg        = power_total     / double(intervalRowCounter);
            double ec1WaterL_avg    = ec1WaterL_total / double(intervalRowCounter);
            double ec1WaterH_avg    = ec1WaterH_total / double(intervalRowCounter);
            double ec2WaterL_avg    = ec2WaterL_total / double(intervalRowCounter);
            double ec2WaterH_avg    = ec2WaterH_total / double(intervalRowCounter);
            double gate_avg         = gate_total      / double(intervalRowCounter);
            double head_avg         = head_total      / double(intervalRowCounter);
            double pwrState_avg     = pwrState_total  / double(intervalRowCounter);

            // Add to graph model
            int graphModelRow = m_pGraphModel->rowCount();
	        m_pGraphModel->insertRow(graphModelRow);
	     
	        m_pGraphModel->setData(graphModelRow, COL_TIMESTAMP,    boost::any(lastTime));
	        m_pGraphModel->setData(graphModelRow, COL_FREQUENCY,    boost::any(freq_avg));
	        m_pGraphModel->setData(graphModelRow, COL_ROTOR_SPEED,  boost::any(speed_avg));
    	    m_pGraphModel->setData(graphModelRow, COL_VOLTS,        boost::any(volts_avg));
    	    m_pGraphModel->setData(graphModelRow, COL_AMPS,         boost::any(amps_avg));
    	    m_pGraphModel->setData(graphModelRow, COL_FLOW1,        boost::any(flow1_avg));
    	    m_pGraphModel->setData(graphModelRow, COL_FLOW2,        boost::any(flow2_avg));
    	    m_pGraphModel->setData(graphModelRow, COL_STRAIN,       boost::any(strain_avg));
    	    m_pGraphModel->setData(graphModelRow, COL_TEMP,         boost::any(temp_avg));
    	    m_pGraphModel->setData(graphModelRow, COL_ALARM,        boost::any(alarm));
    	    m_pGraphModel->setData(graphModelRow, COL_POWER,        boost::any(power_avg));
            m_pGraphModel->setData(graphModelRow, COL_CUMPOWER,     boost::any(cumPower_total)); // cumPower is a running total.
            m_pGraphModel->setData(graphModelRow, COL_EC1WATERL,    boost::any(ec1WaterL_avg));
            m_pGraphModel->setData(graphModelRow, COL_EC1WATERH,    boost::any(ec1WaterH_avg));
            m_pGraphModel->setData(graphModelRow, COL_EC2WATERL,    boost::any(ec2WaterL_avg));
            m_pGraphModel->setData(graphModelRow, COL_EC2WATERH,    boost::any(ec2WaterH_avg));
            m_pGraphModel->setData(graphModelRow, COL_GATE,         boost::any(gate_avg));
            m_pGraphModel->setData(graphModelRow, COL_HEAD,         boost::any(head_avg));
            m_pGraphModel->setData(graphModelRow, COL_PWRSTATE,     boost::any(pwrState_avg));

            freq_total = 0.0;
            speed_total = 0.0;
            volts_total = 0.0;
            amps_total = 0.0;
            flow1_total = 0.0;
            flow2_total = 0.0;
            strain_total = 0.0;
            temp_total = 0.0;
            power_total = 0.0;
            // cumPower_total = 0.0; // Don't reset cumPower.  It accumulates.
            ec1WaterL_total = 0.0;
            ec1WaterH_total = 0.0;
            ec2WaterL_total = 0.0;
            ec2WaterH_total = 0.0;
            gate_total = 0.0;
            head_total = 0.0;
            pwrState_total = 0.0;
            bool alarm = false;
	        intervalRowCounter = 0;
        }

        // Sum values in this interval
	    OpHistoryResult pResult = m_pOpHistoryModel->resultRow(row);
        lastTime        =  pResult->timestamp;
        freq_total      +=  pResult->frequency;
        speed_total     +=  pResult->rotorSpeed;
        volts_total     +=  pResult->volts;
        amps_total      +=  pResult->amps;
        flow1_total     +=  pResult->flow1;
        flow2_total     +=  pResult->flow2;
        strain_total    +=  pResult->strain;
        temp_total      +=  pResult->genTemp;
        power_total     +=  pResult->power;
        cumPower_total  += pResult->cumPower;
        ec1WaterL_total += pResult->ec1WaterL;
        ec1WaterH_total += pResult->ec1WaterH;
        ec2WaterL_total += pResult->ec2WaterL;
        ec2WaterH_total += pResult->ec2WaterH;
        gate_total      += pResult->gate;
        head_total      += pResult->head;
        pwrState_total  += pResult->pwrState;
       
        // Flag alarm if *any* of the records have alarm. 
        if (alarm || pResult->alarm)  
        {
            alarm = true; 
        }
	
	    intervalRowCounter++;
    }

    cout << "CumPower TOTAL:  " << cumPower_total << endl;
    WString displayText("{1}"); 
    cumPowerDisplayText = displayText.arg(cumPower_total);
    m_pGraphModel->sort(COL_TIMESTAMP, Wt::AscendingOrder);
}

void HydrovoltsConnectModel::CreateOpHistoryModel()
{
    // Create a model that is an array of tuples from the database.
    m_pOpHistoryModel  = new Wt::Dbo::QueryModel< Wt::Dbo::ptr<HydrovoltsConnectOpHistory> >();
    m_pOpHistoryModel->setQuery(m_dbSession.find<HydrovoltsConnectOpHistory>());

    // TODO:  Localize second parameter (Column header title)
    m_pOpHistoryModel->addColumn("timestamp",   "Time");
    m_pOpHistoryModel->addColumn("frequency",   "Frequency"); 
    m_pOpHistoryModel->addColumn("rotorSpeed",  "Rotor Speed"); 
    m_pOpHistoryModel->addColumn("volts",       "Volts"); 
    m_pOpHistoryModel->addColumn("amps",        "Amps"); 
    m_pOpHistoryModel->addColumn("flow1",       "Flow 1"); 
    m_pOpHistoryModel->addColumn("flow2",       "Flow 2"); 
    m_pOpHistoryModel->addColumn("strain",      "Strain"); 
    m_pOpHistoryModel->addColumn("genTemp",     "Temp"); 
    m_pOpHistoryModel->addColumn("alarm",       "Alarm"); 
    m_pOpHistoryModel->addColumn("power",       "Power");
    m_pOpHistoryModel->addColumn("cumPower",    "Cumulative Power");
    m_pOpHistoryModel->addColumn("ec1WaterL",   "ec1WaterL");
    m_pOpHistoryModel->addColumn("ec1WaterH",   "ec1WaterH");
    m_pOpHistoryModel->addColumn("ec2WaterL",   "ec2WaterL");
    m_pOpHistoryModel->addColumn("ec2WaterH",   "ec2WaterH");
    m_pOpHistoryModel->addColumn("gate",        "Gate");
    m_pOpHistoryModel->addColumn("head",        "Head");
    m_pOpHistoryModel->addColumn("pwrState",    "Power State");
}

void HydrovoltsConnectModel::CreateGraphModel()
{
    // Create a model that is an array of tuples from the database.
    if (m_pGraphModel != NULL)
    {
        m_pGraphModel->clear();
        delete m_pGraphModel;
    }
    m_pGraphModel  = new Wt::WStandardItemModel();

    InitializeGraphModel();
} 

void HydrovoltsConnectModel::CreateProjectModel()
{
    m_pProjectModel = new Wt::Dbo::QueryModel< Wt::Dbo::ptr<HydrovoltsConnectProject> >();
    m_pProjectModel->setQuery(m_dbSession.find<HydrovoltsConnectProject>());
    
    //m_pProjectModel->addAllFieldsAsColumns();
    m_pProjectModel->addColumn("id", "ID");  // TODO:  Localize "ID"
    m_pProjectModel->addColumn("name", "Name"); // TODO:  Localize "Name"
    m_pProjectModel->addColumn("installDate", "Installed"); 
    m_pProjectModel->addColumn("ipAddress", "Address");
}
