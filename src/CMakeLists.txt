#
# © Copyright 2012 Spatial Minds, Inc. All Rights Reserved.
#
cmake_minimum_required (VERSION 2.6)
project (HydrovoltsConnect)


# SOURCE 
set(SRCS 
  HydrovoltsConnect.cpp
  HydrovoltsConnectApp.cpp
  HydrovoltsConnectMainWnd.cpp
  HydrovoltsConnectWidget.cpp
  HydrovoltsConnectWidgetToolbar.cpp
  HydrovoltsConnectProjects.cpp
  HydrovoltsConnectProject.h
  HydrovoltsConnectOpHistory.h
  HydrovoltsConnectProjectsTab.cpp
  HydrovoltsConnectTabs.cpp
  HydrovoltsConnectModel.cpp
  HydrovoltsConnectTableView.cpp
  HydrovoltsConnectChartView.cpp
  HydrovoltsConnectChartToolbar.cpp
  HydrovoltsConnectRestApi.cpp
  HVDatabaseUpdatedResource.cpp
  WCSVFileResource.cpp
  )

# EXTERNAL LIBS
if (Wt_FOUND)
    set (INCLUDE_DIRS ${INCLUDE_DIRS} ${Wt_INCLUDE_DIR})
    set (LINK_LIBS ${LINK_LIBS} ${Wt_LIBRARIES})
endif (Wt_FOUND)

if (Boost_FOUND)
    set (INCLUDE_DIRS ${INCLUDE_DIRS} ${Boost_INCLUDE_DIR})
    set (LINK_LIBS ${LINK_LIBS} ${Boost_LIBRARIES})
    set (LINK_DIRS ${LINK_DIRS} ${Boost_LIBRARY_DIR})
endif (Boost_FOUND)

# BUILD 
include_directories(${INCLUDE_DIRS})
add_executable (hydrovolts-connect.wt ${SRCS})

# LINK
link_directories(${LINK_DIRS})
target_link_libraries(hydrovolts-connect.wt ${LINK_LIBS})
