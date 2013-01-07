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
#include "WCSVFileResource.h"
#include <string>

using namespace std;

    WCSVFileResource::WCSVFileResource (HydrovoltsConnectModel* pModel,
                                        const string& mimeType, 
                                        const string& fileName, 
                                        WObject *parent) 
    : m_pModel(pModel), WFileResource(mimeType, fileName, parent) {}
    
    WCSVFileResource::~WCSVFileResource () {}


    void WCSVFileResource::handleRequest(const Wt::Http::Request& request, 
                                               Wt::Http::Response &  response )
    {
        response.setMimeType("text/csv");

        // Iterate over model and output to CSV.
        OpHistoryModelType* pOpHistoryModel = m_pModel->OpHistoryModel();
       
        // Output headers 
        response.out() << "Project ID";
        response.out() << ",Timestamp";
        response.out() << ",Frequency";
        response.out() << ",Rotor Speed";
        response.out() << ",Volts";
        response.out() << ",Amps";
        response.out() << ",Flow 1";
        response.out() << ",Flow 2";
        response.out() << ",Strain";
        response.out() << ",Gen Temp";
        response.out() << ",Alarm";
        response.out() << ",Power";
        response.out() << endl; 
        
        int rowCount = pOpHistoryModel->rowCount();
        for (int row=0; row < rowCount; row++)
        {
            OpHistoryResult result = pOpHistoryModel->resultRow(row);
            response.out() << result->projectId                 << ",";
            response.out() << result->timestamp.toString()      << ",";
            response.out() << result->frequency                 << ",";
            response.out() << result->rotorSpeed                << ",";
            response.out() << result->volts                     << ",";
            response.out() << result->amps                      << ","; 
            response.out() << result->flow1                     << ",";
            response.out() << result->flow2                     << ",";
            response.out() << result->strain                    << ",";
            response.out() << result->genTemp                   << ",";
            response.out() << result->alarm                     << ",";
            response.out() << result->power                     << endl;
        }
    }
