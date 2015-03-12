################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Arm.cpp \
../Car.cpp \
../Island.cpp \
../StreetLight.cpp \
../Tire.cpp \
../UFO.cpp \
../VaneSwivel.cpp \
../WeatherVaneBase.cpp 

CC_SRCS += \
../animation.cc 

OBJS += \
./Arm.o \
./Car.o \
./Island.o \
./StreetLight.o \
./Tire.o \
./UFO.o \
./VaneSwivel.o \
./WeatherVaneBase.o \
./animation.o 

CC_DEPS += \
./animation.d 

CPP_DEPS += \
./Arm.d \
./Car.d \
./Island.d \
./StreetLight.d \
./Tire.d \
./UFO.d \
./VaneSwivel.d \
./WeatherVaneBase.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

%.o: ../%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


