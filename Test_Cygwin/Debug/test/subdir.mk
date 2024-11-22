################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../test/main.cpp 

CPP_DEPS += \
./test/main.d 

OBJS += \
./test/main.o 


# Each subdirectory must supply rules for building sources it contributes
test/%.o: ../test/%.cpp test/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -I"D:\eclipse-workspace\Test_Cygwin\libgtest\include" -I"D:\eclipse-workspace\Test_Cygwin\stub\board" -I"D:\eclipse-workspace\Test_Cygwin\stub\driver\include" -I"D:\eclipse-workspace\Test_Cygwin\driver\can_driver\include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-test

clean-test:
	-$(RM) ./test/main.d ./test/main.o

.PHONY: clean-test

