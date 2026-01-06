# 🛰️ Sistema de Mantenimiento de Satélites

Aplicación con interfaz gráfica (Qt5) para gestionar el mantenimiento de satélites mediante formularios interactivos, cálculo automático del estado general y generación de reportes PDF.

## 📋 Características

- **Formulario de Registro**: Captura información completa del satélite (nombre, serie, código, estado, componentes, observaciones)
- **Búsqueda de Observaciones**: Base de datos de observaciones comunes con filtrado en tiempo real
- **Cálculo de Condición General**: Algoritmo que evalúa el estado del satélite en porcentaje
- **Generación de Reportes PDF**: Exportación profesional de reportes técnicos
- **Interfaz Moderna**: Diseño con pestañas, colores dinámicos y estilos CSS

## 🔧 Requisitos del Sistema

- **Compilador C++**: C++17 o superior
- **CMake**: 3.10 o superior
- **Qt5**: Componentes necesarios:
  - Qt5Core
  - Qt5Widgets
  - Qt5PrintSupport

### Instalación de Qt5

#### macOS
```bash
brew install qt@5
```

#### Ubuntu/Debian
```bash
sudo apt-get install qt5-default qtbase5-dev libqt5printsupport5
```

#### Windows
Descargar e instalar desde [Qt Official Website](https://www.qt.io/download)

## 🏗️ Compilación

### 1. Clonar el repositorio
```bash
git clone <repository-url>
cd x-satellite
```

### 2. Crear directorio de compilación
```bash
mkdir build
cd build
```

### 3. Configurar con CMake
```bash
cmake ..
```

Si Qt5 no se encuentra automáticamente, especifica la ruta:
```bash
cmake -DCMAKE_PREFIX_PATH=/path/to/Qt5 ..
```

### 4. Compilar
```bash
make
```

O para compilación paralela:
```bash
make -j$(nproc)
```

### 5. Ejecutar
```bash
./SatelliteMaintenance
```

## 📖 Uso

### 1. Pestaña "Formulario"
- Complete los campos básicos: nombre, número de serie, código
- Seleccione el estado del satélite: Bueno / Regular / Malo / Fatal
- Marque si los componentes están completos
- Ingrese observaciones técnicas

### 2. Pestaña "Búsqueda de Observaciones"
- Use la barra de búsqueda para filtrar observaciones comunes
- Haga clic en una observación de la lista
- Presione "Agregar" para incluirla en el formulario

### 3. Panel de Estado General
- Visualice el porcentaje de condición del satélite en tiempo real
- El color cambia según el nivel de salud:
  - **Verde** (80-100%): Bueno
  - **Naranja** (60-79%): Regular
  - **Naranja oscuro** (40-59%): Malo
  - **Rojo** (0-39%): Crítico

### 4. Generar Reporte PDF
- Complete el formulario
- Presione "Generar Reporte PDF"
- Elija la ubicación y nombre del archivo
- El PDF incluye toda la información estructurada

## 🧮 Algoritmo de Cálculo de Estado

El porcentaje de condición se calcula basándose en:

1. **Estado Base**:
   - Bueno: 100%
   - Regular: 70%
   - Malo: 40%
   - Fatal: 15%

2. **Penalizaciones**:
   - Componentes faltantes: -15%
   - Observaciones críticas detectadas: -10%

3. **Palabras clave críticas**:
   - falla, crítico, grave, severo
   - daño, roto, destruido, pérdida
   - inoperante, no funciona, error fatal

## 📁 Estructura del Proyecto

```
x-satellite/
├── src/
│   ├── main.cpp                 # Punto de entrada
│   ├── MainWindow.cpp/.h        # Ventana principal
│   ├── SatelliteForm.cpp/.h     # Formulario de datos
│   ├── SearchWidget.cpp/.h      # Widget de búsqueda
│   ├── ReportGenerator.cpp/.h   # Generador de PDF
│   └── SatelliteReport.cpp/.h   # Modelo de datos
├── resources/
│   ├── icons/                   # Íconos (opcional)
│   └── qss/                     # Estilos CSS (opcional)
├── tests/                       # Tests unitarios (futuro)
├── CMakeLists.txt              # Configuración CMake
├── README.md                   # Este archivo
└── SATELLITE_MAINTENANCE.md    # Especificaciones del proyecto
```

## 🎯 Casos de Uso

- **Entrenamiento técnico** en gestión de satélites
- **Soporte operativo** en mantenimiento preventivo
- **Proyectos universitarios** de ingeniería aeroespacial
- **Documentación** confiable para archivos técnicos

## 🔮 Futuras Mejoras

- [ ] Base de datos SQLite para historial de reportes
- [ ] Gráficos de tendencia temporal
- [ ] Exportación a otros formatos (Excel, JSON)
- [ ] Sistema de alertas y notificaciones
- [ ] Modo multi-satélite con dashboard
- [ ] Integración con APIs de telemetría real

## 👨‍💻 Desarrollo

### Agregar nuevas observaciones
Edite el método `loadCommonObservations()` en `src/SearchWidget.cpp`

### Modificar algoritmo de cálculo
Edite el método `calcularEstado()` en `src/SatelliteReport.cpp`

### Personalizar estilos
Los estilos CSS están embebidos en cada widget. Para centralizar:
1. Cree un archivo `resources/qss/style.qss`
2. Cárguelo en `MainWindow::applyStyles()`

## 📄 Licencia

Este proyecto es de código abierto y está disponible para fines educativos.

## 🤝 Contribuciones

Las contribuciones son bienvenidas. Por favor:
1. Fork el proyecto
2. Cree una rama para su feature (`git checkout -b feature/AmazingFeature`)
3. Commit sus cambios (`git commit -m 'Add some AmazingFeature'`)
4. Push a la rama (`git push origin feature/AmazingFeature`)
5. Abra un Pull Request

## 📧 Contacto

Para preguntas o sugerencias sobre el proyecto, abra un issue en el repositorio.

---

**Sistema desarrollado para optimizar procesos de mantenimiento aeroespacial** 🚀
