qt_add_library(backend
    backend.h
    backend.cpp
)

add_library(SpotifyQt::backend ALIAS backend)

target_include_directories(backend PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(backend PUBLIC
    Qt6::Core
    Qt6::WebSockets
    SpotifyQT::network
    SpotifyQt::utils
)