################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../test_src/test_driver/can/test_can_driver.cpp 

OBJS += \
./test_src/test_driver/can/test_can_driver.o 

CPP_DEPS += \
./test_src/test_driver/can/test_can_driver.d 


# Each subdirectory must supply rules for building sources it contributes
test_src/test_driver/can/%.o: ../test_src/test_driver/can/%.cpp test_src/test_driver/can/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"D:\DAPAcademy\unit_test\libgtest\include" -I"D:\DAPAcademy\unit_test\stub\driver\adc_stub\include" -I"D:\DAPAcademy\unit_test\src\driver\adc\include" -I"D:\DAPAcademy\unit_test\src\driver\can\include" -I"D:\DAPAcademy\unit_test\stub\board\include" -I"D:\DAPAcademy\unit_test\stub\driver\can_stub\include" -I"D:\DAPAcademy\unit_test\stub\driver\irq_stub\include" -I"D:\DAPAcademy\unit_test\test_src\test_driver\can" -I"D:\DAPAcademy\unit_test\test_src\test_driver\adc" -O0 -g3 -Wold-style-cast -c -fmessage-length=0 -fprofile-arcs -ftest-coverage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


