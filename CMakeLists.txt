project(kde-contextmenu)

set(KDE_MIN_VERSION "4.3.85") # for the < 4.2 macro
find_package(KDE4 4.3.85 REQUIRED)

include(MacroLibrary)
include(KDE4Defaults)

add_definitions(${QT_DEFINITIONS} ${KDE4_DEFINITIONS})
include_directories(${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR} ${KDE4_INCLUDES})

set(contextmenu_SRCS
    launch.cpp
)

kde4_add_plugin(kde-contextmenu ${contextmenu_SRCS})
target_link_libraries(kde-contextmenu ${KDE4_PLASMA_LIBS} ${KDE4_KIO_LIBS})

install(TARGETS kde-contextmenu DESTINATION ${PLUGIN_INSTALL_DIR})
install(FILES kde-contextmenu.desktop DESTINATION ${SERVICES_INSTALL_DIR})
