cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(Tutorial)

# ── Find Geant4 ───────────────────────────────────────────────────────────────
if(NOT Geant4_DIR AND DEFINED ENV{Geant4_DIR})
    set(Geant4_DIR "$ENV{Geant4_DIR}")
endif()
if(NOT Geant4_DIR)
    set(Geant4_DIR "/home/harnoor-singh/geant4/geant4-v11.4.1-install/lib/cmake/Geant4")
endif()

message(STATUS "Geant4_DIR: ${Geant4_DIR}")
find_package(Geant4 REQUIRED ui_all vis_all)
message(STATUS "Geant4 version: ${Geant4_VERSION}")

include(${Geant4_USE_FILE})

# ── C++ Standard ─────────────────────────────────────────────────────────────
# Set BEFORE defining targets so it applies globally
if(NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 17)          # Geant4 11.x recommends C++17
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)       # Prefer -std=c++17 over -std=gnu++17
endif()

# ── Sources ───────────────────────────────────────────────────────────────────
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)

add_executable(sim sim.cc ${sources})

target_include_directories(sim PRIVATE ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(sim PRIVATE ${Geant4_LIBRARIES})

# ── Copy macro files to build dir ─────────────────────────────────────────────
file(GLOB mac_files macros/*.mac)
foreach(_mac ${mac_files})
    configure_file(${_mac} ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
endforeach()

# ── Convenience alias ─────────────────────────────────────────────────────────
add_custom_target(Tutorial DEPENDS sim)