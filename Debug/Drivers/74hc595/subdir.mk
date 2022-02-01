################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/74hc595/74hc595.c 

OBJS += \
./Drivers/74hc595/74hc595.o 

C_DEPS += \
./Drivers/74hc595/74hc595.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/74hc595/%.o: ../Drivers/74hc595/%.c Drivers/74hc595/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Drivers/74hc595 -I../Drivers/ssd1306 -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-74hc595

clean-Drivers-2f-74hc595:
	-$(RM) ./Drivers/74hc595/74hc595.d ./Drivers/74hc595/74hc595.o

.PHONY: clean-Drivers-2f-74hc595

