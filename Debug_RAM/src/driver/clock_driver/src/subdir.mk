################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/driver/clock_driver/src/CLOCK.c \
../src/driver/clock_driver/src/Drv_Clock.c 

OBJS += \
./src/driver/clock_driver/src/CLOCK.o \
./src/driver/clock_driver/src/Drv_Clock.o 

C_DEPS += \
./src/driver/clock_driver/src/CLOCK.d \
./src/driver/clock_driver/src/Drv_Clock.d 


# Each subdirectory must supply rules for building sources it contributes
src/driver/clock_driver/src/%.o: ../src/driver/clock_driver/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/driver/clock_driver/src/CLOCK.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


