################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../ModelingWindow/Car.cpp \
../ModelingWindow/StreetLight.cpp \
../ModelingWindow/Tire.cpp \
../ModelingWindow/main.cpp 

OBJS += \
./ModelingWindow/Car.o \
./ModelingWindow/StreetLight.o \
./ModelingWindow/Tire.o \
./ModelingWindow/main.o 

CPP_DEPS += \
./ModelingWindow/Car.d \
./ModelingWindow/StreetLight.d \
./ModelingWindow/Tire.d \
./ModelingWindow/main.d 


# Each subdirectory must supply rules for building sources it contributes
ModelingWindow/%.o: ../ModelingWindow/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


