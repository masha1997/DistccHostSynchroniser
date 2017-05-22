project(distcc_host_synchroniser)
cmake_minimum_required(VERSION 2.8)


set (BOOST_HOME CACHE STRING "Path to custom boost")
if(BOOST_HOME STREQUAL "")
   message (STATUS "BOOST_HOME is empty. Use system Boost")
else()
  message (STATUS "Use Boost from ${BOOST_HOME}")
  set(BOOST_ROOT ${BOOST_HOME})
  set(BOOST_INCLUDE_DIRS ${BOOST_ROOT}/include/)
  set(BOOST_LIBRARY_DIRS ${BOOST_ROOT}/lib)
endif()

find_package(Boost REQUIRED COMPONENTS system coroutine thread filesystem)

add_subdirectory(Synca)

INCLUDE_DIRECTORIES(
    ${BOOST_INCLUDE_DIRS}
    Synca
    ./
)

message (${Boost_LIBRARIES})
set ( LIBRARIES
    synca
    ${Boost_LIBRARIES}
)

set (SRC_LIST
    main.cpp
    nodes/impl/src/node_db_impl.cc
    nodes/impl/src/node_info.cc
    net/impl/src/client_impl.cc
    net/impl/src/server_impl.cc
    rpc/impl/src/rpc_factory_impl.cc
    rpc/impl/src/add_node_request.cc
    rpc/impl/src/remove_node_request.cc
    rpc/impl/src/out_of_date_notification.cc
    rpc/impl/src/rpc_factory_impl.cc
)

set (CMAKE_CXX_STANDARD 14)
add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} ${LIBRARIES})

