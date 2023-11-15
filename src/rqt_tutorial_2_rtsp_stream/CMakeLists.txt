cmake_minimum_required(VERSION 3.5)

project(rqt_tutorial_2_rtsp_stream)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/")

# Default to C++17
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(rqt_gui_cpp REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)
find_package(Qt5MultimediaWidgets REQUIRED)

set(rqt_tutorial_2_rtsp_stream_SRCS src/tutorial_2.cpp)

set(rqt_tutorial_2_rtsp_stream_HDRS include/rqt_tutorial_2_rtsp_stream/tutorial_2.hpp)

file(GLOB QWT_INCLUDE_DIR "/usr/include/qwt")
file(GLOB QWT_LIBRARIES "/usr/lib/libqwt*")

set(rqt_tutorial_2_rtsp_stream_UIS resources/rtsp.ui)

include_directories(include)

qt5_wrap_cpp(rqt_tutorial_2_rtsp_stream_MOCS ${rqt_tutorial_2_rtsp_stream_HDRS})
qt5_wrap_ui(rqt_tutorial_2_rtsp_stream_UIS_H ${rqt_tutorial_2_rtsp_stream_UIS})
qt5_add_resources(QT_RESOURCES_CPP ${PRO_RESOURCES_DIR})

add_library(
  ${PROJECT_NAME} SHARED
  ${rqt_tutorial_2_rtsp_stream_SRCS} ${rqt_tutorial_2_rtsp_stream_MOCS} ${rqt_tutorial_2_rtsp_stream_UIS_H}
  ${rqt_tutorial_2_rtsp_stream_IMG} ${QT_RESOURCES_CPP} ${PRO_RESOURCES_DIR})

set(library_name ${PROJECT_NAME})

set(dependencies tf2_geometry_msgs rqt_gui_cpp)

ament_target_dependencies(${library_name} ${dependencies})
target_include_directories(
  ${library_name}
  PRIVATE ${GST_INCLUDE_DIRS}
  PUBLIC ${Qt5Widgets_INCLUDE_DIRS} ${OGRE_INCLUDE_DIRS})

# Install Directory
install(
  TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}
  ARCHIVE DESTINATION lib/${PROJECT_NAME}
  LIBRARY DESTINATION lib/${PROJECT_NAME}
  RUNTIME DESTINATION bin/${PROJECT_NAME}
  INCLUDES
  DESTINATION include)


include_directories(include/ ${CMAKE_CURRENT_BINARY_DIR} ${QWT_INCLUDE_DIR})

install(DIRECTORY include/ DESTINATION include)


install(FILES plugin.xml DESTINATION share/${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} 
Qt5::Widgets 
${QWT_LIBRARIES}
Qt5::MultimediaWidgets
)

install(TARGETS ${PROJECT_NAME} DESTINATION lib/${PROJECT_NAME})

pluginlib_export_plugin_description_file(rqt_gui "plugin.xml")

ament_export_include_directories(include)

ament_package()
