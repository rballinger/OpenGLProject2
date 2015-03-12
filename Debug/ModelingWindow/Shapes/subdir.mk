################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../ModelingWindow/Shapes/Cylinder.cpp \
../ModelingWindow/Shapes/Sphere.cpp \
../ModelingWindow/Shapes/Torus.cpp 

OBJS += \
./ModelingWindow/Shapes/Cylinder.o \
./ModelingWindow/Shapes/Sphere.o \
./ModelingWindow/Shapes/Torus.o 

CPP_DEPS += \
./ModelingWindow/Shapes/Cylinder.d \
./ModelingWindow/Shapes/Sphere.d \
./ModelingWindow/Shapes/Torus.d 


# Each subdirectory must supply rules for building sources it contributes
ModelingWindow/Shapes/%.o: ../ModelingWindow/Shapes/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


