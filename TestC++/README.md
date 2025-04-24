# Guia para realizar las pruebas en C++ usando Google Test

## 1. Instalación de Google Test mediante el CMakeLists.txt

```cmake
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

```

## 2. Estructura de carpetas

Agregamos la siguiente estructura de carpetas para organizar el proyecto:

add_library("nombre de la libreria(lo escogemos nosotros)" "nombre del archivo.cpp")
add_library("nombre de la libreria" "nombre del archivo.h")

target_link_libraries("nombre de la libreria" "nombre de la libreria que queremos usar")
add_executable("nombre del ejecutable" "nombre del archivo.cpp")

## 3. Compilación y ejecución de pruebas

Para compilar y ejecutar las pruebas, sigue estos pasos:
Ejecuta el script que contiene el archivo script.sh

Captura de la salida:

![image](/TestC++/image/captura.png)

Dirigete a la carpeta `build` y ejecuta el comando `./runTests` para ejecutar las pruebas.
