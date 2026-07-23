qt_add_library(utils
    PlayerTracker/playertracker.cpp PlayerTracker/playertracker.h
)

add_library(SpotifyQt::utils ALIAS utils)

target_include_directories(utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(utils PUBLIC
    Qt6::Core
    Qt6::Quick
)