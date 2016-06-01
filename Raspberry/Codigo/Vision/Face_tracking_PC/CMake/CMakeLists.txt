# Nombre del royecto
PROJECT(FaceTracking)

#Minima versión requerida
cmake_minimum_required(VERSION 2.8)


find_package( OpenCV REQUIRED )

#Añadir directorio de fuentes
INCLUDE_DIRECTORIES(${FaceTracking_SOURCE_DIR}/src)

# Crear el ejecutable
ADD_EXECUTABLE(FaceTracking src/FaceTracking.cpp)

# Enlazar el ejecutable con las librerías
TARGET_LINK_LIBRARIES(FaceTracking ${OpenCV_LIBS})
