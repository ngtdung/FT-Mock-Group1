################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/driver/port_driver/src/PORT_Driver.c 

OBJS += \
./src/driver/port_driver/src/PORT_Driver.o 

C_DEPS += \
./src/driver/port_driver/src/PORT_Driver.d 


# Each subdirectory must supply rules for building sources it contributes
src/driver/port_driver/src/%.o: ../src/driver/port_driver/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/driver/port_driver/src/PORT_Driver.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


