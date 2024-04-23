################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Thirdparty/croutine.c \
../Thirdparty/event_groups.c \
../Thirdparty/list.c \
../Thirdparty/queue.c \
../Thirdparty/stream_buffer.c \
../Thirdparty/tasks.c \
../Thirdparty/timers.c 

OBJS += \
./Thirdparty/croutine.o \
./Thirdparty/event_groups.o \
./Thirdparty/list.o \
./Thirdparty/queue.o \
./Thirdparty/stream_buffer.o \
./Thirdparty/tasks.o \
./Thirdparty/timers.o 

C_DEPS += \
./Thirdparty/croutine.d \
./Thirdparty/event_groups.d \
./Thirdparty/list.d \
./Thirdparty/queue.d \
./Thirdparty/stream_buffer.d \
./Thirdparty/tasks.d \
./Thirdparty/timers.d 


# Each subdirectory must supply rules for building sources it contributes
Thirdparty/%.o Thirdparty/%.su: ../Thirdparty/%.c Thirdparty/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I"C:/Users/samar/STM32CubeIDE/workspace_1.9.0/CAN_TEST/Thirdparty/portable" -I"C:/Users/samar/STM32CubeIDE/workspace_1.9.0/CAN_TEST/PROJECT" -I"C:/Users/samar/STM32CubeIDE/workspace_1.9.0/CAN_TEST/Thirdparty/portable/GCC/ARM_CM4F" -I"C:/Users/samar/STM32CubeIDE/workspace_1.9.0/CAN_TEST/Thirdparty/portable/MemMang" -I"C:/Users/samar/STM32CubeIDE/workspace_1.9.0/CAN_TEST/Thirdparty/include" -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Thirdparty

clean-Thirdparty:
	-$(RM) ./Thirdparty/croutine.d ./Thirdparty/croutine.o ./Thirdparty/croutine.su ./Thirdparty/event_groups.d ./Thirdparty/event_groups.o ./Thirdparty/event_groups.su ./Thirdparty/list.d ./Thirdparty/list.o ./Thirdparty/list.su ./Thirdparty/queue.d ./Thirdparty/queue.o ./Thirdparty/queue.su ./Thirdparty/stream_buffer.d ./Thirdparty/stream_buffer.o ./Thirdparty/stream_buffer.su ./Thirdparty/tasks.d ./Thirdparty/tasks.o ./Thirdparty/tasks.su ./Thirdparty/timers.d ./Thirdparty/timers.o ./Thirdparty/timers.su

.PHONY: clean-Thirdparty

