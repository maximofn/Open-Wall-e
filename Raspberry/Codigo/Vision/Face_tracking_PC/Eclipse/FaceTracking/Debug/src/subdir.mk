################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/FaceTracking.cpp \
../src/Librerias_Reconocimiento.cpp \
../src/Utilities.cpp \
../src/libreria_Detection.cpp 

OBJS += \
./src/FaceTracking.o \
./src/Librerias_Reconocimiento.o \
./src/Utilities.o \
./src/libreria_Detection.o 

CPP_DEPS += \
./src/FaceTracking.d \
./src/Librerias_Reconocimiento.d \
./src/Utilities.d \
./src/libreria_Detection.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include/opencv -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


