################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/ssd1306/ssd1306.c \
../Drivers/ssd1306/ssd1306_fonts.c \
../Drivers/ssd1306/ssd1306_tests.c 

OBJS += \
./Drivers/ssd1306/ssd1306.o \
./Drivers/ssd1306/ssd1306_fonts.o \
./Drivers/ssd1306/ssd1306_tests.o 

C_DEPS += \
./Drivers/ssd1306/ssd1306.d \
./Drivers/ssd1306/ssd1306_fonts.d \
./Drivers/ssd1306/ssd1306_tests.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/ssd1306/%.o: ../Drivers/ssd1306/%.c Drivers/ssd1306/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Drivers/74hc595 -I../Drivers/ssd1306 -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-ssd1306

clean-Drivers-2f-ssd1306:
	-$(RM) ./Drivers/ssd1306/ssd1306.d ./Drivers/ssd1306/ssd1306.o ./Drivers/ssd1306/ssd1306_fonts.d ./Drivers/ssd1306/ssd1306_fonts.o ./Drivers/ssd1306/ssd1306_tests.d ./Drivers/ssd1306/ssd1306_tests.o

.PHONY: clean-Drivers-2f-ssd1306

