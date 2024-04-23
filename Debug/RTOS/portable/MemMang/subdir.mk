################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../RTOS/portable/MemMang/heap_4.c 

OBJS += \
./RTOS/portable/MemMang/heap_4.o 

C_DEPS += \
./RTOS/portable/MemMang/heap_4.d 


# Each subdirectory must supply rules for building sources it contributes
RTOS/portable/MemMang/%.o RTOS/portable/MemMang/%.su: ../RTOS/portable/MemMang/%.c RTOS/portable/MemMang/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I"C:/Users/samar/STM32CubeIDE/workspace_1.9.0/CAN_TEST/RTOS" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-RTOS-2f-portable-2f-MemMang

clean-RTOS-2f-portable-2f-MemMang:
	-$(RM) ./RTOS/portable/MemMang/heap_4.d ./RTOS/portable/MemMang/heap_4.o ./RTOS/portable/MemMang/heap_4.su

.PHONY: clean-RTOS-2f-portable-2f-MemMang

