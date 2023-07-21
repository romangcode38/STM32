/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g0xx_ll_adc.h"
#include "stm32g0xx_ll_rcc.h"
#include "stm32g0xx_ll_bus.h"
#include "stm32g0xx_ll_system.h"
#include "stm32g0xx_ll_exti.h"
#include "stm32g0xx_ll_cortex.h"
#include "stm32g0xx_ll_utils.h"
#include "stm32g0xx_ll_pwr.h"
#include "stm32g0xx_ll_dma.h"
#include "stm32g0xx_ll_usart.h"
#include "stm32g0xx_ll_gpio.h"

#if defined(USE_FULL_ASSERT)
#include "stm32_assert.h"
#endif /* USE_FULL_ASSERT */

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define USER_BTN_Pin LL_GPIO_PIN_13
#define USER_BTN_GPIO_Port GPIOC
#define MCO_Pin LL_GPIO_PIN_0
#define MCO_GPIO_Port GPIOF
#define LED_GREEN_Pin LL_GPIO_PIN_5
#define LED_GREEN_GPIO_Port GPIOA
#define LED_RED1_Pin LL_GPIO_PIN_6
#define LED_RED1_GPIO_Port GPIOA
#define LED_RED2_Pin LL_GPIO_PIN_7
#define LED_RED2_GPIO_Port GPIOA
#define LED_RED3_Pin LL_GPIO_PIN_0
#define LED_RED3_GPIO_Port GPIOB
#define LED_RED3B1_Pin LL_GPIO_PIN_1
#define LED_RED3B1_GPIO_Port GPIOB
#define LED_RED4_Pin LL_GPIO_PIN_11
#define LED_RED4_GPIO_Port GPIOB
#define MOTOR_PIN1_Pin LL_GPIO_PIN_8
#define MOTOR_PIN1_GPIO_Port GPIOA
#define LED_RED4C7_Pin LL_GPIO_PIN_7
#define LED_RED4C7_GPIO_Port GPIOC
#define TMS_Pin LL_GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin LL_GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define MOTOR_PIN4_Pin LL_GPIO_PIN_3
#define MOTOR_PIN4_GPIO_Port GPIOB
#define MOTOR_PIN2_Pin LL_GPIO_PIN_4
#define MOTOR_PIN2_GPIO_Port GPIOB
#define MOTOR_PIN3_Pin LL_GPIO_PIN_5
#define MOTOR_PIN3_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
