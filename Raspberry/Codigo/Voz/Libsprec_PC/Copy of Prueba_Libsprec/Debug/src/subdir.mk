################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/flac_encoder.c \
../src/recognize.c \
../src/simple.c \
../src/wav.c \
../src/web_client.c 

OBJS += \
./src/flac_encoder.o \
./src/recognize.o \
./src/simple.o \
./src/wav.o \
./src/web_client.o 

C_DEPS += \
./src/flac_encoder.d \
./src/recognize.d \
./src/simple.d \
./src/wav.d \
./src/web_client.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


