################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/driver/uart_driver/src/DRV_LPUART.c 

OBJS += \
./src/driver/uart_driver/src/DRV_LPUART.o 

C_DEPS += \
./src/driver/uart_driver/src/DRV_LPUART.d 


# Each subdirectory must supply rules for building sources it contributes
src/driver/uart_driver/src/%.o: ../src/driver/uart_driver/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/driver/uart_driver/src/DRV_LPUART.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


