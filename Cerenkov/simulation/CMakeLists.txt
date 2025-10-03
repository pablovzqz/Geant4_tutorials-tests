cmake_minimum_required(VERSION 2.6 FATAL_ERROR) ## Minima versión requerida de CMake

project(Simulation) ## Nombre del proyecto

find_package(Geant4 REQUIRED ui_all vis_all) ## paquetes necesarios

include(${Geant4_USE_FILE}) ## files usadas 

file(GLOB sources ${PROJECT_SOURCE_DIR}/*.cc) ## buscar todos los codigos fuente de este path
file(GLOB headers ${PROJECT_SOURCE_DIR}/*.hh) ## buscar todos los headers de este path

add_executable(cerenkov_light sim.cc ${sources} ${headers}) ## nombre del ejecutable y se corre en el archivo.cc
target_link_libraries(cerenkov_light ${Geant4_LIBRARIES})

add_custom_target(Simulation DEPENDS cerenkov_light)