################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../PROJECT/CAN.c \
../PROJECT/HMI.c 

OBJS += \
./PROJECT/CAN.o \
./PROJECT/HMI.o 

C_DEPS += \
./PROJECT/CAN.d \
./PROJECT/HMI.d 


# Each subdirectory must supply rules for building sources it contributes
PROJECT/%.o PROJECT/%.su: ../PROJECT/%.c PROJECT/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I"C:/Users/samar/STM32CubeIDE/workspace_1.9.0/CAN_TEST/Thirdparty/portable" -I"C:/Users/samar/STM32CubeIDE/workspace_1.9.0/CAN_TEST/PROJECT" -I"C:/Users/samar/STM32CubeIDE/workspace_1.9.0/CAN_TEST/Thirdparty/portable/GCC/ARM_CM4F" -I"C:/Users/samar/STM32CubeIDE/workspace_1.9.0/CAN_TEST/Thirdparty/portable/MemMang" -I"C:/Users/samar/STM32CubeIDE/workspace_1.9.0/CAN_TEST/Thirdparty/include" -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-PROJECT

clean-PROJECT:
	-$(RM) ./PROJECT/CAN.d ./PROJECT/CAN.o ./PROJECT/CAN.su ./PROJECT/HMI.d ./PROJECT/HMI.o ./PROJECT/HMI.su

.PHONY: clean-PROJECT

