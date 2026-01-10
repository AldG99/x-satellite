cmake_minimum_required(VERSION 3.10)
project(SatelliteMaintenance VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Find Qt5
find_package(Qt5 REQUIRED COMPONENTS
    Core
    Widgets
    PrintSupport
)

# Source files
set(SOURCES
    src/main.cpp
    src/MainWindow.cpp
    src/SatelliteForm.cpp
    src/SearchWidget.cpp
    src/ReportGenerator.cpp
    src/SatelliteReport.cpp
)

# Header files
set(HEADERS
    src/MainWindow.h
    src/SatelliteForm.h
    src/SearchWidget.h
    src/ReportGenerator.h
    src/SatelliteReport.h
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Link Qt5 libraries
target_link_libraries(${PROJECT_NAME}
    Qt5::Core
    Qt5::Widgets
    Qt5::PrintSupport
)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE src)

# Copy resources to build directory
file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR})
