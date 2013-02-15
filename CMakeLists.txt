cmake_minimum_required (VERSION 2.8.0)
project (picmi)

if (NOT CMAKE_BUILD_TYPE)
   set(CMAKE_BUILD_TYPE Release)
endif ()

set(Boost_USE_MULTITHREADED ON)
set(QT_USE_QTXML TRUE)

set(picmi_VERSION_MAJOR 1)
set(picmi_VERSION_MINOR 3)
set(picmi_VERSION_PATCH 5)
set(picmi_FILEPREFIX \"${CMAKE_INSTALL_PREFIX}/share/picmi/\")

configure_file(
	"${PROJECT_SOURCE_DIR}/src/config.h.in"
	"${PROJECT_BINARY_DIR}/config.h"
)

find_package(Qt4 REQUIRED)
find_package(SFML 2 COMPONENTS graphics system window REQUIRED)
find_package(Boost COMPONENTS thread system REQUIRED)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Wextra -O3 -pedantic -fPIC -std=c++0x")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -Wall -Wextra -pedantic -fPIC -std=c++0x")

include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

set(picmi_FORMS
	${CMAKE_SOURCE_DIR}/src/f_qthelp.ui
	${CMAKE_SOURCE_DIR}/src/f_qtmainwindow.ui
	${CMAKE_SOURCE_DIR}/src/f_qtsettings.ui
)
qt4_wrap_ui(picmi_FORMS_HEADERS ${picmi_FORMS})

set(picmi_QTHEADERS
	${CMAKE_SOURCE_DIR}/src/f_qtmainwindow.h
	${CMAKE_SOURCE_DIR}/src/f_qthelp.h
	${CMAKE_SOURCE_DIR}/src/f_qtsettings.h
	${CMAKE_SOURCE_DIR}/src/f_qtpicthread.h
)
qt4_wrap_cpp(picmi_QTHEADERS_MOC ${picmi_QTHEADERS})


include_directories(
	"${CMAKE_SOURCE_DIR}/src/"
	${Boost_INCLUDE_DIRS}
	${SFML_INCLUDE_DIR}
	${CMAKE_CURRENT_BINARY_DIR}
)
aux_source_directory(src/ sources)

add_executable(picmi
	${sources}
	${picmi_FORMS_HEADERS}
	${picmi_QTHEADERS_MOC}
)

target_link_libraries(picmi
	${Boost_LIBRARIES}
	${SFML_LIBRARIES}
	${QT_LIBRARIES}
)

install(TARGETS picmi DESTINATION bin)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/gfx DESTINATION share/picmi)
