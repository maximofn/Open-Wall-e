# Nombre del royecto
PROJECT(DisplayImage)

#Minima versión requerida
cmake_minimum_required(VERSION 2.8)


find_package( OpenCV REQUIRED )

#Añadir directorio de fuentes
INCLUDE_DIRECTORIES(${DisplayImage_SOURCE_DIR}/src)

# Crear el ejecutable
ADD_EXECUTABLE(DisplayImage src/DisplayImage.cpp)

# Enlazar el ejecutable con las librerías
TARGET_LINK_LIBRARIES(DisplayImage ${OpenCV_LIBS})
