################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/libfacerec-0.04/src/colormap.cpp \
../src/libfacerec-0.04/src/decomposition.cpp \
../src/libfacerec-0.04/src/facerec.cpp \
../src/libfacerec-0.04/src/helper.cpp \
../src/libfacerec-0.04/src/lbp.cpp \
../src/libfacerec-0.04/src/main.cpp \
../src/libfacerec-0.04/src/subspace.cpp 

OBJS += \
./src/libfacerec-0.04/src/colormap.o \
./src/libfacerec-0.04/src/decomposition.o \
./src/libfacerec-0.04/src/facerec.o \
./src/libfacerec-0.04/src/helper.o \
./src/libfacerec-0.04/src/lbp.o \
./src/libfacerec-0.04/src/main.o \
./src/libfacerec-0.04/src/subspace.o 

CPP_DEPS += \
./src/libfacerec-0.04/src/colormap.d \
./src/libfacerec-0.04/src/decomposition.d \
./src/libfacerec-0.04/src/facerec.d \
./src/libfacerec-0.04/src/helper.d \
./src/libfacerec-0.04/src/lbp.d \
./src/libfacerec-0.04/src/main.d \
./src/libfacerec-0.04/src/subspace.d 


# Each subdirectory must supply rules for building sources it contributes
src/libfacerec-0.04/src/%.o: ../src/libfacerec-0.04/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include/opencv -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


