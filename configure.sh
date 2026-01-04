#!/bin/bash

# Script de configuración para el proyecto Satellite Maintenance

echo "🛰️  Configurando Sistema de Mantenimiento de Satélites..."

# Detectar la ruta de Qt5
QT5_PATH="/opt/homebrew/opt/qt@5"

if [ ! -d "$QT5_PATH" ]; then
    echo "❌ Error: Qt5 no encontrado en $QT5_PATH"
    echo "Por favor, instala Qt5 con: brew install qt@5"
    exit 1
fi

echo "✅ Qt5 encontrado en: $QT5_PATH"

# Crear directorio build
if [ ! -d "build" ]; then
    mkdir build
    echo "✅ Directorio build creado"
else
    echo "✅ Directorio build existe"
fi

# Configurar con CMake
cd build
echo "🔧 Ejecutando CMake..."
cmake -DCMAKE_PREFIX_PATH="$QT5_PATH" ..

if [ $? -eq 0 ]; then
    echo "✅ Configuración exitosa"
    echo ""
    echo "Para compilar el proyecto, ejecuta:"
    echo "  cd build && make"
    echo ""
    echo "Para ejecutar la aplicación:"
    echo "  ./build/SatelliteMaintenance"
else
    echo "❌ Error en la configuración"
    exit 1
fi
