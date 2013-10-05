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

#include "HydrovoltsConnectProject.h"
#include "HydrovoltsConnectOpHistory.h"

#include <Wt/WStandardItemModel>
#include <Wt/Dbo/backend/Sqlite3>

class HydrovoltsConnectModel {
public:
    HydrovoltsConnectModel ();
    virtual ~HydrovoltsConnectModel ();

    // Project Table Operations
    ProjectModelType* ProjectModel();
    void SetActiveProject(int projectId);
    int ActiveProject();

    // OpHistory Table Operations
    OpHistoryModelType* OpHistoryModel();

    WStandardItemModel* GraphModel();

    void SetDates(WDate beginDate, WDate endDate);

    WDate BeginDate();
    void SetBeginDate(WDate beginDate);

    WDate EndDate();
    void SetEndDate(WDate endDate);

    void Refresh() {SetOpHistoryFilter();};

    WString cumPowerDisplayText;

    enum OpHistoryCol { 
                        COL_TIMESTAMP = 0,    // 0
                        COL_FREQUENCY = 1,    // 1
                        COL_ROTOR_SPEED = 2,  // 2
                        COL_VOLTS = 3,        // 3
                        COL_AMPS = 4,         // 4
                        COL_FLOW1 = 5,        // 5
                        COL_FLOW2 = 6,        // 6
                        COL_STRAIN = 7,       // 7
                        COL_TEMP = 8,         // 8
                        COL_ALARM = 9,        // 9
                        COL_POWER = 10,       // 10
                        COL_CUMPOWER = 11,    // 11
                        COL_EC1WATERL = 12,   // 12
                        COL_EC1WATERH = 13,   // 13
                        COL_EC2WATERL = 14,   // 14
                        COL_EC2WATERH = 15,   // 15
                        COL_GATE = 16,        // 16
                        COL_HEAD = 17,        // 17
                        COL_PWRSTATE = 18     // 18
    };
private:
        int NUM_GRAPH_POINTS;
        static const int NUM_COLUMNS = 19;
        
    
        // Increment NUM_COLUMNS if additional columns are added 
        // data
        Wt::Dbo::backend::Sqlite3 sqlite3;
        Wt::Dbo::Session m_dbSession;
        ProjectModelType* m_pProjectModel; 
        OpHistoryModelType* m_pOpHistoryModel;
        WStandardItemModel*  m_pGraphModel;
        int m_activeProjectId;
        WDateTime m_begin;
        WDateTime m_end;

        // methods 
	    void InitializeGraphModel();
        void CreateProjectModel();
        void CreateOpHistoryModel();
        void CreateGraphModel();
        void PopulateGraphModel();
        void SetTooltip(int row, int col);

        void SetOpHistoryFilter(/*project id, start date, end date*/);
};
