################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include test/test_driver/port/subdir.mk
-include test/test_driver/lpit/subdir.mk
-include test/test_driver/gpio/subdir.mk
-include test/test_driver/can/subdir.mk
-include test/test_driver/adc/subdir.mk
-include test/subdir.mk
-include stub/driver/port_stub/src/subdir.mk
-include stub/driver/nvic_stub/src/subdir.mk
-include stub/driver/lpit_stub/src/subdir.mk
-include stub/driver/gpio_stub/src/subdir.mk
-include stub/driver/can_stub/src/subdir.mk
-include stub/driver/adc_stub/src/subdir.mk
-include driver/port/src/subdir.mk
-include driver/lpit/src/subdir.mk
-include driver/gpio/src/subdir.mk
-include driver/can_driver/src/subdir.mk
-include driver/adc/src/subdir.mk
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++M_DEPS)),)
-include $(C++M_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(CCM_DEPS)),)
-include $(CCM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXXM_DEPS)),)
-include $(CXXM_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := Test_Cygwin
BUILD_ARTIFACT_EXTENSION := exe
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: main-build

# Main-build Target
main-build: Test_Cygwin.exe

# Tool invocations
Test_Cygwin.exe: $(OBJS) $(USER_OBJS) makefile $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cygwin C++ Linker'
	g++ -L"D:\eclipse-workspace\Test_Cygwin\libgtest\lib" -o "Test_Cygwin.exe" $(OBJS) $(USER_OBJS) $(LIBS) -lpthread -lgtest
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) Test_Cygwin.exe
	-@echo ' '

.PHONY: all clean dependents main-build

-include ../makefile.targets
