project(plasma-containmentactions-favorites)

set(KDE_MIN_VERSION "4.3.85") # for the < 4.2 macro
find_package(KDE4 4.3.85 REQUIRED)

include(MacroLibrary)
include(KDE4Defaults)

add_definitions(${QT_DEFINITIONS} ${KDE4_DEFINITIONS})
include_directories(${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR} ${KDE4_INCLUDES})

set(favorites_SRCS
    launch.cpp
)

kde4_add_plugin(plasma_containmentactions_favorites ${favorites_SRCS})
target_link_libraries(plasma_containmentactions_favorites ${KDE4_PLASMA_LIBS} ${KDE4_KIO_LIBS})

install(TARGETS plasma_containmentactions_favorites DESTINATION ${PLUGIN_INSTALL_DIR})
install(FILES plasma-containmentactions-favorites.desktop DESTINATION ${SERVICES_INSTALL_DIR})
