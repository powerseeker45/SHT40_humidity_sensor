################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User\ Defined/driver_sht4x.c 

OBJS += \
./User\ Defined/driver_sht4x.o 

C_DEPS += \
./User\ Defined/driver_sht4x.d 


# Each subdirectory must supply rules for building sources it contributes
User\ Defined/driver_sht4x.o: ../User\ Defined/driver_sht4x.c User\ Defined/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H723xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I"E:/parikshit/CANSAT/OBC/humidity_sensor/humidity_sensor/User Defined" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"User Defined/driver_sht4x.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-User-20-Defined

clean-User-20-Defined:
	-$(RM) ./User\ Defined/driver_sht4x.cyclo ./User\ Defined/driver_sht4x.d ./User\ Defined/driver_sht4x.o ./User\ Defined/driver_sht4x.su

.PHONY: clean-User-20-Defined

