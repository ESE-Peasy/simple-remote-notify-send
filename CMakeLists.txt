cmake_minimum_required(VERSION 3.10)
include(GNUInstallDirs)

project(RemoteNotification)

set(REMOTENOTIFYSRC
  RemoteNotify.cpp
  RemoteNotifyReceive.cpp
  RemoteNotifyBroadcast.cpp
  )
# add the executable
add_executable(PosturePerfectionReceiver ${REMOTENOTIFYSRC} PosturePerfection_receiver.cpp)
add_executable(PosturePerfectionTestBroadcast ${REMOTENOTIFYSRC} PosturePerfection_test_broadcast.cpp)

set(CMAKE_CXX_STANDARD 11)

add_library (RemoteNotify STATIC RemoteNotify.cpp)
add_library (RemoteNotifyBroadcast STATIC RemoteNotifyBroadcast.cpp)
TARGET_LINK_LIBRARIES(RemoteNotifyBroadcast RemoteNotify)
add_library (RemoteNotifyReceive STATIC RemoteNotifyReceive.cpp)
TARGET_LINK_LIBRARIES(RemoteNotifyReceive RemoteNotify)
set_target_properties(RemoteNotify PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
set_target_properties(RemoteNotifyBroadcast PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
set_target_properties(RemoteNotifyReceive PROPERTIES POSITION_INDEPENDENT_CODE TRUE)

set_target_properties(RemoteNotify PROPERTIES
  PUBLIC_HEADER RemoteNotify.h)
 set_target_properties(RemoteNotifyBroadcast PROPERTIES
  PUBLIC_HEADER RemoteNotifyBroadcast.h)
set_target_properties(RemoteNotifyReceive PROPERTIES
  PUBLIC_HEADER RemoteNotifyReceive.h)

install(TARGETS RemoteNotify RemoteNotifyBroadcast RemoteNotifyReceive
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

