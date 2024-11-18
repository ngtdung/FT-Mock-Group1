################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../stub/driver/irq_stub/src/irq_stub.c 

OBJS += \
./stub/driver/irq_stub/src/irq_stub.o 

C_DEPS += \
./stub/driver/irq_stub/src/irq_stub.d 


# Each subdirectory must supply rules for building sources it contributes
stub/driver/irq_stub/src/%.o: ../stub/driver/irq_stub/src/%.c stub/driver/irq_stub/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I"D:\DAPAcademy\unit_test\src\driver\adc\include" -I"D:\DAPAcademy\unit_test\src\driver\adc\include" -I"D:\DAPAcademy\unit_test\stub\driver\adc_stub\include" -I"D:\DAPAcademy\unit_test\stub\board\include" -I"D:\DAPAcademy\unit_test\stub\driver\can_stub\include" -I"D:\DAPAcademy\unit_test\stub\driver\irq_stub\include" -I"D:\DAPAcademy\unit_test\src\driver\can\include" -O0 -g3 -Wall -c -fmessage-length=0 -fprofile-arcs -ftest-coverage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


