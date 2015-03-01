################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Ground.cpp \
../Sphere.cpp \
../StreetLamp.cpp \
../UFO.cpp \
../Wheel.cpp \
../main.cpp 

OBJS += \
./Ground.o \
./Sphere.o \
./StreetLamp.o \
./UFO.o \
./Wheel.o \
./main.o 

CPP_DEPS += \
./Ground.d \
./Sphere.d \
./StreetLamp.d \
./UFO.d \
./Wheel.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


