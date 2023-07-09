################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Source/Src/AdcDrv.c \
../Source/Src/ButtonDrv.c \
../Source/Src/CircularBuffer.c \
../Source/Src/EcuM.c \
../Source/Src/LedDrv.c \
../Source/Src/Test.c \
../Source/Src/TheAPP.c \
../Source/Src/USARTDrv.c \
../Source/Src/USART_CommunicationProtocol.c 

OBJS += \
./Source/Src/AdcDrv.o \
./Source/Src/ButtonDrv.o \
./Source/Src/CircularBuffer.o \
./Source/Src/EcuM.o \
./Source/Src/LedDrv.o \
./Source/Src/Test.o \
./Source/Src/TheAPP.o \
./Source/Src/USARTDrv.o \
./Source/Src/USART_CommunicationProtocol.o 

C_DEPS += \
./Source/Src/AdcDrv.d \
./Source/Src/ButtonDrv.d \
./Source/Src/CircularBuffer.d \
./Source/Src/EcuM.d \
./Source/Src/LedDrv.d \
./Source/Src/Test.d \
./Source/Src/TheAPP.d \
./Source/Src/USARTDrv.d \
./Source/Src/USART_CommunicationProtocol.d 


# Each subdirectory must supply rules for building sources it contributes
Source/Src/%.o Source/Src/%.su Source/Src/%.cyclo: ../Source/Src/%.c Source/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DSTM32G071xx -DUSE_FULL_LL_DRIVER -DUSE_HAL_DRIVER -c -I../Core/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -I"D:/Embeded/NUCLEO_G071RB/LED_BLINK/Source/Inc" -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Source-2f-Src

clean-Source-2f-Src:
	-$(RM) ./Source/Src/AdcDrv.cyclo ./Source/Src/AdcDrv.d ./Source/Src/AdcDrv.o ./Source/Src/AdcDrv.su ./Source/Src/ButtonDrv.cyclo ./Source/Src/ButtonDrv.d ./Source/Src/ButtonDrv.o ./Source/Src/ButtonDrv.su ./Source/Src/CircularBuffer.cyclo ./Source/Src/CircularBuffer.d ./Source/Src/CircularBuffer.o ./Source/Src/CircularBuffer.su ./Source/Src/EcuM.cyclo ./Source/Src/EcuM.d ./Source/Src/EcuM.o ./Source/Src/EcuM.su ./Source/Src/LedDrv.cyclo ./Source/Src/LedDrv.d ./Source/Src/LedDrv.o ./Source/Src/LedDrv.su ./Source/Src/Test.cyclo ./Source/Src/Test.d ./Source/Src/Test.o ./Source/Src/Test.su ./Source/Src/TheAPP.cyclo ./Source/Src/TheAPP.d ./Source/Src/TheAPP.o ./Source/Src/TheAPP.su ./Source/Src/USARTDrv.cyclo ./Source/Src/USARTDrv.d ./Source/Src/USARTDrv.o ./Source/Src/USARTDrv.su ./Source/Src/USART_CommunicationProtocol.cyclo ./Source/Src/USART_CommunicationProtocol.d ./Source/Src/USART_CommunicationProtocol.o ./Source/Src/USART_CommunicationProtocol.su

.PHONY: clean-Source-2f-Src

