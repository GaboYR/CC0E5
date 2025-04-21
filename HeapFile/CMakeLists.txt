cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto
project(DHeapTests)

# Configuración de Google Test
enable_testing()

# Descargar Google Test automáticamente con FetchContent
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
add_library(dheap DHeap.cpp)  # Aquí agregamos el archivo fuente DHeap.cpp

# Agregar el ejecutable para las pruebas
add_executable(runTests test-DHeap.cpp)  # El archivo que contiene las pruebas

# Linkear Google Test y la biblioteca DHeap
target_link_libraries(runTests gtest gtest_main dheap)

# Añadir pruebas
add_test(NAME DHeapTests COMMAND runTests)
