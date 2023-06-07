################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Source/Src/ButtonDrv.c \
../Source/Src/EcuM.c \
../Source/Src/LedDrv.c 

OBJS += \
./Source/Src/ButtonDrv.o \
./Source/Src/EcuM.o \
./Source/Src/LedDrv.o 

C_DEPS += \
./Source/Src/ButtonDrv.d \
./Source/Src/EcuM.d \
./Source/Src/LedDrv.d 


# Each subdirectory must supply rules for building sources it contributes
Source/Src/%.o Source/Src/%.su Source/Src/%.cyclo: ../Source/Src/%.c Source/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DSTM32G071xx -DUSE_FULL_LL_DRIVER -DHSE_VALUE=8000000 -DHSE_STARTUP_TIMEOUT=100 -DLSE_STARTUP_TIMEOUT=5000 -DLSE_VALUE=32768 -DEXTERNAL_CLOCK_VALUE=12288000 -DHSI_VALUE=16000000 -DLSI_VALUE=32000 -DVDD_VALUE=3300 -DPREFETCH_ENABLE=1 -DINSTRUCTION_CACHE_ENABLE=1 -DDATA_CACHE_ENABLE=1 -c -I../Core/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -I"D:/Embeded/NUCLEO_G071RB/LED_BLINK/Source/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Source-2f-Src

clean-Source-2f-Src:
	-$(RM) ./Source/Src/ButtonDrv.cyclo ./Source/Src/ButtonDrv.d ./Source/Src/ButtonDrv.o ./Source/Src/ButtonDrv.su ./Source/Src/EcuM.cyclo ./Source/Src/EcuM.d ./Source/Src/EcuM.o ./Source/Src/EcuM.su ./Source/Src/LedDrv.cyclo ./Source/Src/LedDrv.d ./Source/Src/LedDrv.o ./Source/Src/LedDrv.su

.PHONY: clean-Source-2f-Src

