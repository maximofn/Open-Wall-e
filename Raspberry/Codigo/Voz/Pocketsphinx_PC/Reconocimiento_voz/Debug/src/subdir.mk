################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Reconocimiento_voz.cpp \
../src/Utilities.cpp 

OBJS += \
./src/Reconocimiento_voz.o \
./src/Utilities.o 

CPP_DEPS += \
./src/Reconocimiento_voz.d \
./src/Utilities.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include/sphinxbase -I/usr/local/include/pocketsphinx -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


