################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include build/CMakeFiles/sample.dir/subdir.mk
-include build/CMakeFiles/sample.dir/Shapes/subdir.mk
-include build/CMakeFiles/subdir.mk
-include build/CMakeFiles/3.1.1/CompilerIdCXX/subdir.mk
-include build/CMakeFiles/3.1.1/CompilerIdC/subdir.mk
-include Shapes/subdir.mk
-include ModelingWindow/subdir.mk
-include ModelingWindow/Shapes/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: 367_p2_LightAndMovement

# Tool invocations
367_p2_LightAndMovement: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	g++  -o"367_p2_LightAndMovement" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C++_DEPS)$(C_DEPS)$(CC_DEPS)$(CPP_DEPS)$(EXECUTABLES)$(CXX_DEPS)$(C_UPPER_DEPS) 367_p2_LightAndMovement
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
