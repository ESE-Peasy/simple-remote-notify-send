cmake_minimum_required(VERSION 3.10)
include(GNUInstallDirs)

project(RemoteNotification)

set(CMAKE_CXX_STANDARD 11)

add_library (RemoteNotifyBroadcast STATIC RemoteNotifyBroadcast.cpp)
add_library (RemoteNotifyReceive STATIC RemoteNotifyReceive.cpp)
set_target_properties(RemoteNotifyBroadcast PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
set_target_properties(RemoteNotifyReceive PROPERTIES POSITION_INDEPENDENT_CODE TRUE)

 set_target_properties(RemoteNotifyBroadcast PROPERTIES
  PUBLIC_HEADER RemoteNotifyBroadcast.h)
set_target_properties(RemoteNotifyReceive PROPERTIES
  PUBLIC_HEADER RemoteNotifyReceive.h)

install(TARGETS RemoteNotifyBroadcast RemoteNotifyReceive
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

