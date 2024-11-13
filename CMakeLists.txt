cmake_minimum_required(VERSION 3.14)

project(Remind LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core LinguistTools Multimedia)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core LinguistTools Multimedia)
set(TS_FILES Remind_zh_CN.ts)

add_executable(Remind
  main.cpp
  ${TS_FILES}
  playmusicthread.h playmusicthread.cpp
  readme.md

)
target_link_libraries(Remind Qt${QT_VERSION_MAJOR}::Core Qt6::Multimedia)

if(COMMAND qt_create_translation)
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

include(GNUInstallDirs)
install(TARGETS Remind
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
