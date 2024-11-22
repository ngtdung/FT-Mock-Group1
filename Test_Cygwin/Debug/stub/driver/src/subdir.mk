################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../stub/driver/src/can_stub.c 

C_DEPS += \
./stub/driver/src/can_stub.d 

OBJS += \
./stub/driver/src/can_stub.o 


# Each subdirectory must supply rules for building sources it contributes
stub/driver/src/%.o: ../stub/driver/src/%.c stub/driver/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	gcc -I"D:\eclipse-workspace\Test_Cygwin\libgtest" -I"D:\eclipse-workspace\Test_Cygwin\stub\board" -I"D:\eclipse-workspace\Test_Cygwin\stub\driver\include" -I"D:\eclipse-workspace\Test_Cygwin\driver\can_driver\include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-stub-2f-driver-2f-src

clean-stub-2f-driver-2f-src:
	-$(RM) ./stub/driver/src/can_stub.d ./stub/driver/src/can_stub.o

.PHONY: clean-stub-2f-driver-2f-src

