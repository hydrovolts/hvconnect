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

#include <Wt/WDate>
#include <Wt/Dbo/Dbo>
#include <Wt/Dbo/WtSqlTraits>
#include <Wt/Dbo/QueryModel>

#include <string>

namespace dbo = Wt::Dbo;
using namespace Wt;
using namespace std;

class HydrovoltsConnectOpHistory {
    public:
        HydrovoltsConnectOpHistory (){};
        virtual ~HydrovoltsConnectOpHistory (){};
        template<class Action> void persist(Action& a)
        {
            
            dbo::field(a, timestamp,    "timestamp");
            dbo::field(a, frequency,    "frequency");
            dbo::field(a, rotorSpeed,   "rotorSpeed");
            dbo::field(a, volts,        "volts");
            dbo::field(a, amps,         "amps");
            dbo::field(a, flow1,        "flow1");
            dbo::field(a, flow2,        "flow2");
            dbo::field(a, strain,       "strain");
            dbo::field(a, genTemp,      "genTemp");
            dbo::field(a, alarm,        "alarm");
            dbo::field(a, power,        "power");
            dbo::field(a, cumPower,     "cumPower");
            dbo::field(a, ec1WaterL,    "ec1WaterL");
            dbo::field(a, ec1WaterH,    "ec1WaterH");
            dbo::field(a, ec2WaterL,    "ec2WaterL");
            dbo::field(a, ec2WaterH,    "ec2WaterH");
            dbo::field(a, gate,         "gate");
            dbo::field(a, head,         "head");
            dbo::field(a, pwrState,     "pwrState");
        }

        // C++ Variable         SQLite Schema         Example                
        // id                   //integer id          4142                  
        // version              //integer version                         
        int       projectId;    //numeric turbineId;  1                     
        WDateTime timestamp;    //text timeStamp;     2012-29-03 21:47:33 
        double    frequency;    //numeric frequency;  28.5                 
        double    rotorSpeed;   //numeric rotoSpeed;  419                 
        double    volts;        //numeric volts;      467.74               
        double    amps;         //numeric amps;       15.25                
        double    flow1;        //numeric flow1;      12                    
        double    flow2;        //numeric flow2;      12                     
        double    strain;       //numeric strain;     0                     
        double    genTemp;      //numeric genTemp;    0.118                    
        bool      alarm;        //numeric alarm;      0                    
        double    power;        //real    power
        double    cumPower;     //real
        double    ec1WaterL;    //real
        double    ec1WaterH;    //real
        double    ec2WaterL;    //real
        double    ec2WaterH;    //real
        double    gate;         //real
        double    head;         //real
        double    pwrState;     //real

    private:
        /* data */
};

typedef Wt::Dbo::ptr<HydrovoltsConnectOpHistory> OpHistoryResult;
typedef Wt::Dbo::QueryModel<OpHistoryResult> OpHistoryModelType;
