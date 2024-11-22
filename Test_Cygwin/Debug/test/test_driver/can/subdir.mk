################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../test/test_driver/can/test_can.cpp 

CPP_DEPS += \
./test/test_driver/can/test_can.d 

OBJS += \
./test/test_driver/can/test_can.o 


# Each subdirectory must supply rules for building sources it contributes
test/test_driver/can/%.o: ../test/test_driver/can/%.cpp test/test_driver/can/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -I"D:\eclipse-workspace\Test_Cygwin\libgtest\include" -I"D:\eclipse-workspace\Test_Cygwin\stub\board" -I"D:\eclipse-workspace\Test_Cygwin\stub\driver\include" -I"D:\eclipse-workspace\Test_Cygwin\driver\can_driver\include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-test-2f-test_driver-2f-can

clean-test-2f-test_driver-2f-can:
	-$(RM) ./test/test_driver/can/test_can.d ./test/test_driver/can/test_can.o

.PHONY: clean-test-2f-test_driver-2f-can

