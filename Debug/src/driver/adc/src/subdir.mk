################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/driver/adc/src/adc_driver.c 

OBJS += \
./src/driver/adc/src/adc_driver.o 

C_DEPS += \
./src/driver/adc/src/adc_driver.d 


# Each subdirectory must supply rules for building sources it contributes
src/driver/adc/src/%.o: ../src/driver/adc/src/%.c src/driver/adc/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I"D:\DAPAcademy\unit_test\src\driver\adc\include" -I"D:\DAPAcademy\unit_test\src\driver\adc\include" -I"D:\DAPAcademy\unit_test\stub\driver\adc_stub\include" -I"D:\DAPAcademy\unit_test\stub\board\include" -I"D:\DAPAcademy\unit_test\stub\driver\can_stub\include" -I"D:\DAPAcademy\unit_test\stub\driver\irq_stub\include" -I"D:\DAPAcademy\unit_test\src\driver\can\include" -O0 -g3 -Wall -c -fmessage-length=0 -fprofile-arcs -ftest-coverage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


