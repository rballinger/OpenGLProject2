################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Shapes/Cylinder.cpp \
../Shapes/Fan.cpp \
../Shapes/Sphere.cpp \
../Shapes/Torus.cpp 

OBJS += \
./Shapes/Cylinder.o \
./Shapes/Fan.o \
./Shapes/Sphere.o \
./Shapes/Torus.o 

CPP_DEPS += \
./Shapes/Cylinder.d \
./Shapes/Fan.d \
./Shapes/Sphere.d \
./Shapes/Torus.d 


# Each subdirectory must supply rules for building sources it contributes
Shapes/%.o: ../Shapes/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


