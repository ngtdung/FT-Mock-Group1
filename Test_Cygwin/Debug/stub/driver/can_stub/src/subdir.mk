################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../stub/driver/can_stub/src/can_stub.c 

C_DEPS += \
./stub/driver/can_stub/src/can_stub.d 

OBJS += \
./stub/driver/can_stub/src/can_stub.o 


# Each subdirectory must supply rules for building sources it contributes
stub/driver/can_stub/src/%.o: ../stub/driver/can_stub/src/%.c stub/driver/can_stub/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	gcc -I"D:\eclipse-workspace\Test_Cygwin\driver\adc\include" -I"D:\eclipse-workspace\Test_Cygwin\stub\driver\uart_stub\include" -I"D:\eclipse-workspace\Test_Cygwin\driver\uart\include" -I"D:\eclipse-workspace\Test_Cygwin\stub\board" -I"D:\eclipse-workspace\Test_Cygwin\libgtest\include" -I"D:\eclipse-workspace\Test_Cygwin\driver\can\include" -I"D:\eclipse-workspace\Test_Cygwin\driver\gpio\include" -I"D:\eclipse-workspace\Test_Cygwin\driver\lpit\include" -I"D:\eclipse-workspace\Test_Cygwin\driver\port\include" -I"D:\eclipse-workspace\Test_Cygwin\stub\driver\adc_stub\include" -I"D:\eclipse-workspace\Test_Cygwin\stub\driver\can_stub\include" -I"D:\eclipse-workspace\Test_Cygwin\stub\driver\gpio_stub\include" -I"D:\eclipse-workspace\Test_Cygwin\stub\driver\nvic_stub\include" -I"D:\eclipse-workspace\Test_Cygwin\stub\driver\lpit_stub\include" -I"D:\eclipse-workspace\Test_Cygwin\stub\driver\port_stub\include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-stub-2f-driver-2f-can_stub-2f-src

clean-stub-2f-driver-2f-can_stub-2f-src:
	-$(RM) ./stub/driver/can_stub/src/can_stub.d ./stub/driver/can_stub/src/can_stub.o

.PHONY: clean-stub-2f-driver-2f-can_stub-2f-src

