# Nombre del royecto
PROJECT( Hello_world )

#Minima versión requerida
cmake_minimum_required(VERSION 2.8)

include_directories(/usr/local/lib)
INCLUDE_DIRECTORIES(${pocketsphinx_SOURCE_DIR}/src)

#find_package( sphinxbase pocketsphinx REQUIRED )
#find_package( pocketsphinx REQUIRED )

# Crear el ejecutable
add_executable( Hello_world Hello_world.cpp )


target_link_libraries( Hello_world ${sphinxbase_LIBS} ${pocketsphinx_LIBS})



#find_package( OpenCV REQUIRED )
