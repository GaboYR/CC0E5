cmake_minimum_required(VERSION 3.10)
project(DHeapTests)
enable_testing()

# Descargar Google Test para pruebas
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        main
)

# Se descarga y se configura Google Test
FetchContent_MakeAvailable(googletest)

# Directorio de inclusión de los archivos de encabezado
include_directories(${CMAKE_SOURCE_DIR})

# Agregar archivos fuente
add_library(main_exec main.cpp)
add_library(funciones func.cpp)
target_link_libraries(main_exec funciones)
# Agregar el ejecutable para las pruebas
add_executable(runTests test/test_main.cpp main.cpp)


# Vincular con GoogleTest
target_link_libraries(runTests gtest gtest_main main_exec)

# Registrar pruebas
add_test(NAME FuncionesTests COMMAND runTests)
