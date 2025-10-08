cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(Simulation)

# Geant4
find_package(Geant4 REQUIRED ui_all vis_all)
include(${Geant4_USE_FILE})

# Copiar macros
file(GLOB MACRO_FILES "${PROJECT_SOURCE_DIR}/*.mac")
file(COPY ${MACRO_FILES} DESTINATION ${PROJECT_BINARY_DIR})

# Copiar datos
file(GLOB DAT_FILES "${PROJECT_SOURCE_DIR}/*.dat")
file(COPY ${DAT_FILES} DESTINATION ${PROJECT_BINARY_DIR})

# Incluir todos los headers de subcarpetas
file(GLOB_RECURSE HEADERS "${PROJECT_SOURCE_DIR}/*/*.hh")
set(ALL_INCLUDE_DIRS "")
foreach(h ${HEADERS})
    get_filename_component(dir_path ${h} PATH)
    list(APPEND ALL_INCLUDE_DIRS ${dir_path})
endforeach()
include_directories(${ALL_INCLUDE_DIRS})

# Incluir todos los sources de subcarpetas
file(GLOB_RECURSE SOURCES "/Users/pablovazquez/Geant4_tutorials-tests/Cerenkov/*/*.cc")

# Agregar ejecutable
add_executable(cerenkov_light sim.cc ${SOURCES})
target_link_libraries(cerenkov_light ${Geant4_LIBRARIES})

# Target custom
add_custom_target(Simulation DEPENDS cerenkov_light)
