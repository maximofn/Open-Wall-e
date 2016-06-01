################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/libfacerec-0.04/test/test_facerecognizers.cpp \
../src/libfacerec-0.04/test/test_helper.cpp \
../src/libfacerec-0.04/test/test_lbp.cpp \
../src/libfacerec-0.04/test/test_lda.cpp \
../src/libfacerec-0.04/test/test_main.cpp \
../src/libfacerec-0.04/test/test_subspace.cpp 

OBJS += \
./src/libfacerec-0.04/test/test_facerecognizers.o \
./src/libfacerec-0.04/test/test_helper.o \
./src/libfacerec-0.04/test/test_lbp.o \
./src/libfacerec-0.04/test/test_lda.o \
./src/libfacerec-0.04/test/test_main.o \
./src/libfacerec-0.04/test/test_subspace.o 

CPP_DEPS += \
./src/libfacerec-0.04/test/test_facerecognizers.d \
./src/libfacerec-0.04/test/test_helper.d \
./src/libfacerec-0.04/test/test_lbp.d \
./src/libfacerec-0.04/test/test_lda.d \
./src/libfacerec-0.04/test/test_main.d \
./src/libfacerec-0.04/test/test_subspace.d 


# Each subdirectory must supply rules for building sources it contributes
src/libfacerec-0.04/test/%.o: ../src/libfacerec-0.04/test/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include/opencv -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


