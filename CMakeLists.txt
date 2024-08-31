cmake_minimum_required(VERSION 3.28)
Set(CMAKE_CXX_COMPILER_ID "GNU")
project(NSEProject)

set(CMAKE_CXX_STANDARD 17)

option(FORCE_STATIC_LINK "FORCE static linking with Boost" OFF)

find_package(Boost QUIET COMPONENTS system thread)

if(Boost_FOUND AND NOT FORCE_STATIC_LINK)
    message(STATUS "Using system-installed Boost.")
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
    set(BOOST_LIBRARIES ${Boost_LIBRARIES})
else()
    message(WARNING "System Boost not found.")

    set(BOOST_INCLUDEDIR "${CMAKE_SOURCE_DIR}/libs/boost")
    set(BOOST_LIBRARYDIR "${CMAKE_SOURCE_DIR}/libs/lib")

    include_directories(${BOOST_INCLUDEDIR})

    file(GLOB BOOST_LIBRARIES "${BOOST_LIBRARYDIR}/*.a")

    link_directories(${BOOST_LIBRARYDIR})

endif()

include_directories(include)

add_executable(NSEProject main.cpp
        include/nse/NSEMessageType.h
        src/util/CommandLineParser.cpp
        include/util/CommandLineParser.h
        src/util/ConfigParser.cpp
        include/util/ConfigParser.h
        src/security/ProofofWork.cpp
        include/security/ProofofWork.h
        src/security/RSI.cpp
        include/security/RSI.h
        include/gossip/GossipMessageType.h
        src/nse/NSEAlgorithm.cpp
        include/nse/NSEAlgorithm.h
        src/nse/NSEServer.cpp
        include/nse/NSEServer.h
        src/gossip/GossipClient.cpp
        include/gossip/GossipClient.h
        src/nse/NSEProtocoll.cpp
        include/nse/NSEProtocoll.h
        src/MainProtocol.cpp
        include/MainProtocol.h
)

target_link_libraries(NSEProject ${BOOST_LIBRARIES})
