# Ejecucion del script de pruebas:

# !/bin/bash

# Si el directorio de compilación ya existe, lo eliminamos
if [ -d "build" ]; then
    rm -rf build
fi
# Crear el directorio de compilación 
mkdir build
cd build
cmake ..
make
ctest