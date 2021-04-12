cmake_minimum_required(VERSION 3.10)

# set the project name
project(Notification)

set(NOTFYSRC
  receiver.cpp
  notify.cpp
  broadcaster.cpp
  )
# add the executable
add_executable(NotificationLocalReceiver ${NOTFYSRC} local_posture_perfection_example.cpp)
add_executable(NotificationBroadcast ${NOTFYSRC} broadcast_example.cpp)

set(CMAKE_CXX_STANDARD 11)



