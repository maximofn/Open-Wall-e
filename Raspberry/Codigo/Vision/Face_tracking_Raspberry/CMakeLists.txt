# Nombre del royecto
PROJECT(FaceTracking)

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

# Crear el ejecutable
ADD_EXECUTABLE(FaceTracking 
		src/FaceTracking.cpp 
		src/Librerias_Reconocimiento.cpp 
		src/libreria_Detection.cpp 
		src/raspicam/Utilities.cpp src/RaspiPreview.c 
		src/raspicam/RaspiCLI.c 
		src/raspicam/RaspiCamControl.c 
		src/raspicam/RaspiCamCV.c)

# Enlazar el ejecutable con las librerías
TARGET_LINK_LIBRARIES(FaceTracking 
	/opt/vc/lib/libmmal_core.so 
	/opt/vc/lib/libmmal_util.so 
	/opt/vc/lib/libmmal_vc_client.so 
	/opt/vc/lib/libvcos.so 
	/opt/vc/lib/libbcm_host.so 
	${OpenCV_LIBS})

