cmake_minimum_required(VERSION 3.5 FATAL_ERROR) ## Minima versión requerida de CMake

project(Simulation) ## Nombre del proyecto

find_package(Geant4 REQUIRED ui_all vis_all) ## paquetes necesarios

include(${Geant4_USE_FILE}) ## files usadas 

file(GLOB_RECURSE HEADER_DIRS
    RELATIVE ${CMAKE_SOURCE_DIR}
    "${CMAKE_SOURCE_DIR}/*/*.hh"
)

foreach(dir ${HEADER_DIRS})
    get_filename_component(dir_path ${dir} PATH)
    list(APPEND ALL_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/${dir_path}")
endforeach()

include_directories(${ALL_INCLUDE_DIRS})

file(GLOB sources
    "${PROJECT_SOURCE_DIR}/*.cc"
    "${CMAKE_SOURCE_DIR}/../construction/*.cc"
)
file(GLOB_RECURSE HEADER_DIRS "${CMAKE_SOURCE_DIR}/../*/*.hh")

add_executable(cerenkov_light sim.cc ${sources} ${HEADER_DIRS}) ## nombre del ejecutable y se corre en el archivo.cc
target_link_libraries(cerenkov_light ${Geant4_LIBRARIES})

add_custom_target(Simulation DEPENDS cerenkov_light)