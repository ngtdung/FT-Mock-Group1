################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../test/test_driver/adc/test_adc.cpp 

CPP_DEPS += \
./test/test_driver/adc/test_adc.d 

OBJS += \
./test/test_driver/adc/test_adc.o 


# Each subdirectory must supply rules for building sources it contributes
test/test_driver/adc/%.o: ../test/test_driver/adc/%.cpp test/test_driver/adc/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -I"D:\eclipse-workspace\Test_Cygwin\driver\adc\include" -I"D:\eclipse-workspace\Test_Cygwin\driver\uart\include" -I"D:\eclipse-workspace\Test_Cygwin\stub\driver\uart_stub\include" -I"D:\eclipse-workspace\Test_Cygwin\stub\board" -I"D:\eclipse-workspace\Test_Cygwin\libgtest\include" -I"D:\eclipse-workspace\Test_Cygwin\driver\can\include" -I"D:\eclipse-workspace\Test_Cygwin\driver\gpio\include" -I"D:\eclipse-workspace\Test_Cygwin\driver\lpit\include" -I"D:\eclipse-workspace\Test_Cygwin\driver\port\include" -I"D:\eclipse-workspace\Test_Cygwin\stub\driver\adc_stub\include" -I"D:\eclipse-workspace\Test_Cygwin\stub\driver\can_stub\include" -I"D:\eclipse-workspace\Test_Cygwin\stub\driver\gpio_stub\include" -I"D:\eclipse-workspace\Test_Cygwin\stub\driver\nvic_stub\include" -I"D:\eclipse-workspace\Test_Cygwin\stub\driver\lpit_stub\include" -I"D:\eclipse-workspace\Test_Cygwin\stub\driver\port_stub\include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-test-2f-test_driver-2f-adc

clean-test-2f-test_driver-2f-adc:
	-$(RM) ./test/test_driver/adc/test_adc.d ./test/test_driver/adc/test_adc.o

.PHONY: clean-test-2f-test_driver-2f-adc

