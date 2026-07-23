qt_add_library(network
    ApiClient/apiclient.cpp ApiClient/apiclient.h
    SpotifyAuth/spotifyauth.cpp SpotifyAuth/spotifyauth.h
)

add_library(SpotifyQT::network ALIAS network)

target_include_directories(network PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(network PUBLIC
    Qt6::Core
    Qt6::Network
    Qt6::NetworkAuth
)