cmake_minimum_required(VERSION 3.17)
project(1000)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_PREFIX_PATH "/usr/local/Cellar/qt/5.15.2/lib/cmake")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT_VERSION 5)
set(REQUIRED_LIBS Core Gui Widgets)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets)

find_package(Boost 1.75.0)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

add_executable(${PROJECT_NAME} main.cpp gui/HandView.cpp gui/HandView.h gui/MainWindow.cpp gui/MainWindow.h models/Deal.cpp models/Deal.h models/State.cpp models/State.h gui/DealPresenter.cpp gui/DealPresenter.h gui/DealView.cpp gui/DealView.h gui/CardView.cpp gui/CardView.h models/thousand/ThousandState.cpp models/thousand/ThousandState.h models/thousand/ThousandDeal.cpp models/thousand/ThousandDeal.h gui/SetDealDialog.cpp gui/SetDealDialog.h gui/SetDealDialog.ui solvers/ThousandSolver.h solvers/ThousandSolver.cpp)

if (NOT CMAKE_PREFIX_PATH)
    message(WARNING "CMAKE_PREFIX_PATH is not defined, you may need to set it "
            "(-DCMAKE_PREFIX_PATH=\"path/to/Qt/lib/cmake\" or -DCMAKE_PREFIX_PATH=/usr/include/{host}/qt{version}/ on Ubuntu)")
endif ()

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})
