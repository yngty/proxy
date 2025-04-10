cmake_minimum_required(VERSION 3.8...3.20)

# determine whether it's main/root project
# or being built under another project.
if (NOT DEFINED BOOST_REDIS_MAIN_PROJECT)
  set(BOOST_REDIS_MAIN_PROJECT OFF)
  if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(BOOST_REDIS_MAIN_PROJECT ON)
  endif()
endif()

project(boost_redis VERSION "${BOOST_SUPERPROJECT_VERSION}" LANGUAGES CXX)

# Library
add_library(boost_redis INTERFACE)
add_library(Boost::redis ALIAS boost_redis)
target_include_directories(boost_redis INTERFACE include)
target_compile_features(boost_redis INTERFACE cxx_std_17)

# Dependencies
if (BOOST_REDIS_MAIN_PROJECT)
  # TODO: Understand why we have to list all dependencies below
  # instead of
  #set(BOOST_INCLUDE_LIBRARIES redis)
  #set(BOOST_EXCLUDE_LIBRARIES redis)
  #add_subdirectory(../.. boostorg/boost EXCLUDE_FROM_ALL)

  set(deps
    system
    assert
    config
    throw_exception
    asio
    variant2
    mp11
    winapi
    predef
    align
    context
    core
    static_assert
    pool
    date_time
    smart_ptr
    exception
    integer
    move
    type_traits
    algorithm
    utility
    io
    lexical_cast
    numeric/conversion
    mpl
    range
    tokenizer
    tuple
    array
    bind
    concept_check
    function
    iterator
    regex
    unordered
    preprocessor
    container
    conversion
    container_hash
    detail
    optional
    function_types
    fusion
    intrusive
    describe
    typeof
    functional
    test
    json
    endian
  )

  foreach(dep IN LISTS deps)
    add_subdirectory(../${dep} boostorg/${dep})
  endforeach()

  find_package(Threads REQUIRED)
  find_package(OpenSSL REQUIRED)
  target_link_libraries(boost_redis
    INTERFACE
      Boost::system
      Boost::asio
      Threads::Threads
      OpenSSL::Crypto
      OpenSSL::SSL
  )
else()
  # If we're in the superproject or called from add_subdirectory,
  # Boost dependencies should be already available.
  # If other dependencies are not found, we bail out
  find_package(Threads)
  if(NOT Threads_FOUND)
    message(STATUS "Boost.Redis has been disabled, because the required package Threads hasn't been found")
    return()
  endif()
  find_package(OpenSSL)
  if(NOT OpenSSL_FOUND)
    message(STATUS "Boost.Redis has been disabled, because the required package OpenSSL hasn't been found")
    return()
  endif()

  # This is generated by boostdep
  target_link_libraries(boost_redis
    INTERFACE
      Boost::asio
      Boost::assert
      Boost::core
      Boost::mp11
      Boost::system
      Boost::throw_exception
      Threads::Threads
      OpenSSL::Crypto
      OpenSSL::SSL
  )
endif()

# Enable testing. If we're being called from the superproject, this has already been done
if (BOOST_REDIS_MAIN_PROJECT)
  include(CTest)
endif()

# Most tests require a running Redis server, so we only run them if we're the main project
if(BOOST_REDIS_MAIN_PROJECT AND BUILD_TESTING)
  # Tests and common utilities
  add_subdirectory(test)

  # Benchmarks. Build them with tests to prevent code rotting
  add_subdirectory(benchmarks)

  # Examples
  add_subdirectory(example)
endif()
