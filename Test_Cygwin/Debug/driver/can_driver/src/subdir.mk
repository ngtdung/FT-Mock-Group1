################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../driver/can_driver/src/FlexCAN.c 

C_DEPS += \
./driver/can_driver/src/FlexCAN.d 

OBJS += \
./driver/can_driver/src/FlexCAN.o 


# Each subdirectory must supply rules for building sources it contributes
driver/can_driver/src/%.o: ../driver/can_driver/src/%.c driver/can_driver/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	gcc -I"D:\eclipse-workspace\Test_Cygwin\libgtest" -I"D:\eclipse-workspace\Test_Cygwin\stub\board" -I"D:\eclipse-workspace\Test_Cygwin\stub\driver\include" -I"D:\eclipse-workspace\Test_Cygwin\driver\can_driver\include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-driver-2f-can_driver-2f-src

clean-driver-2f-can_driver-2f-src:
	-$(RM) ./driver/can_driver/src/FlexCAN.d ./driver/can_driver/src/FlexCAN.o

.PHONY: clean-driver-2f-can_driver-2f-src

