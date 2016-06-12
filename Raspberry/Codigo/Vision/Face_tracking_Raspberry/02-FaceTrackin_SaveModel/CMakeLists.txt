# Nombre del royecto
PROJECT(FaceTracking_SaveModel)

#Minima versión requerida
cmake_minimum_required(VERSION 2.8)

# SET(COMPILE_DEFINITIONS -Werror)

find_package( OpenCV REQUIRED )

#Añadir directorio de fuentes
INCLUDE_DIRECTORIES(/opt/vc/include)
INCLUDE_DIRECTORIES(/opt/vc/include/interface/vcos)
INCLUDE_DIRECTORIES(/opt/vc/include/interface/vcos/pthreads)
INCLUDE_DIRECTORIES(/opt/vc/include/interface/vmcs_host/linux)
INCLUDE_DIRECTORIES(.)
#INCLUDE_DIRECTORIES(${FaceTracking_SOURCE_DIR}/src)

# Crear el ejecutable
ADD_EXECUTABLE(FaceTracking_SaveModel
		src/FaceTracking_SaveModel.cpp 
		src/Librerias_Reconocimiento.cpp 
		src/Libreria_SaveLoadModel.cpp 
		src/Utilities.cpp 
		Resources/Resources.cpp
		Resources/raspicam/RaspiPreview.c 
		Resources/raspicam/RaspiCLI.c 
		Resources/raspicam/RaspiCamControl.c 
		Resources/raspicam/RaspiCamCV.c)

# Enlazar el ejecutable con las librerías
TARGET_LINK_LIBRARIES(FaceTracking_SaveModel /opt/vc/lib/libmmal_core.so /opt/vc/lib/libmmal_util.so /opt/vc/lib/libmmal_vc_client.so /opt/vc/lib/libvcos.so /opt/vc/lib/libbcm_host.so ${OpenCV_LIBS})


# Enlazar el ejecutable con las librerías
TARGET_LINK_LIBRARIES(FaceTracking_SaveModel ${OpenCV_LIBS})
