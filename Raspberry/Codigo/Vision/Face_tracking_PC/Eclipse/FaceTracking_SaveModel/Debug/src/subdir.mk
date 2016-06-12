################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/FaceTracking_SaveModel.cpp \
../src/Libreria_SaveLoadModel.cpp \
../src/Librerias_Reconocimiento.cpp \
../src/Utilities.cpp 

OBJS += \
./src/FaceTracking_SaveModel.o \
./src/Libreria_SaveLoadModel.o \
./src/Librerias_Reconocimiento.o \
./src/Utilities.o 

CPP_DEPS += \
./src/FaceTracking_SaveModel.d \
./src/Libreria_SaveLoadModel.d \
./src/Librerias_Reconocimiento.d \
./src/Utilities.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include/opencv -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


