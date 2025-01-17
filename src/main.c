#include "stm32g0xx_hal.h"

void GPIO_PA4_Init();
void GPIO_PA4_TIM_OC_Init();
void example1();
void example2();
void example3();
void example4();

TIM_HandleTypeDef htim3 = {0};
TIM_HandleTypeDef htim14 = {0};

int main()
{
  HAL_Init();

  //Recommendation: test examples one at a time (comment in others) instead of all in a row
  
  example1();
  HAL_Delay(10000);

  GPIO_PA4_Init();
  example2();
  HAL_Delay(10000);

  GPIO_PA4_TIM_OC_Init();
  example3();
  HAL_Delay(10000);

  GPIO_PA4_TIM_OC_Init();
  example4();
  HAL_Delay(10000);


  while (1)
  {
    HAL_Delay(100);
  }
  return 0;
}

void GPIO_PA4_Init()
{
  __HAL_RCC_GPIOA_CLK_ENABLE();
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin = GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void GPIO_PA4_TIM_OC_Init()
{
  __HAL_RCC_GPIOA_CLK_ENABLE();
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin = GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Alternate = GPIO_AF4_TIM14;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void example1()
{
    HAL_TIM_Base_Stop(&htim3);
    HAL_TIM_Base_DeInit(&htim3);
    __HAL_RCC_TIM3_CLK_ENABLE();

    htim3.Instance = TIM3;
    htim3.Init.Prescaler = 16000 - 1;
    htim3.Init.Period = 6000 - 1;
    htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
    HAL_TIM_Base_Init(&htim3);
    HAL_TIM_Base_Start(&htim3);
}

void example2()
{
    HAL_TIM_Base_Stop(&htim3);
    HAL_TIM_Base_DeInit(&htim3);
    __HAL_RCC_TIM3_CLK_ENABLE();

    htim3.Instance = TIM3;
    htim3.Init.Prescaler = 16000 - 1;
    htim3.Init.Period = 2000 - 1;

    HAL_TIM_Base_Init(&htim3);
    HAL_NVIC_SetPriority(TIM3_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM3_IRQn);
    HAL_TIM_Base_Start_IT(&htim3);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM3)
    {
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_4);
    }
}

void example3()
{
    HAL_TIM_Base_Stop(&htim14);
    HAL_TIM_Base_DeInit(&htim14);
    __HAL_RCC_TIM14_CLK_ENABLE();

    htim14.Instance = TIM14;
    htim14.Init.Prescaler = 16000 - 1;
    htim14.Init.Period = 5000 - 1;
    HAL_TIM_OC_Init(&htim14);

    TIM_OC_InitTypeDef htimOcConfig = {0};
    htimOcConfig.OCMode = TIM_OCMODE_TOGGLE;
    htimOcConfig.Pulse = 2500;
    HAL_TIM_OC_ConfigChannel(&htim14, &htimOcConfig, TIM_CHANNEL_1);
    HAL_TIM_OC_Start(&htim14, TIM_CHANNEL_1);
}

void example4()
{
    HAL_TIM_Base_Stop(&htim14);
    HAL_TIM_Base_DeInit(&htim14);
    __HAL_RCC_TIM14_CLK_ENABLE();

    htim14.Instance = TIM14;
    htim14.Init.Prescaler = 16 - 1; //downclock timer to 1 MHz
    htim14.Init.Period = 1000 - 1;  //count to 1000

    TIM_OC_InitTypeDef htimOcConfig = {0};
    htimOcConfig.OCMode = TIM_OCMODE_PWM1;
    htimOcConfig.Pulse = 500;       //startup duty cycle - 50% (500/1000)

    HAL_TIM_PWM_ConfigChannel(&htim14, &htimOcConfig, TIM_CHANNEL_1);
    HAL_TIM_PWM_Init(&htim14);
    HAL_TIM_PWM_Start(&htim14, TIM_CHANNEL_1);

    while (1)
    {
        htimOcConfig.Pulse = htimOcConfig.Pulse + 50;
        if (htimOcConfig.Pulse >= 1000)
        {
            htimOcConfig.Pulse = 0;
        }
        HAL_TIM_PWM_ConfigChannel(&htim14, &htimOcConfig, TIM_CHANNEL_1);
        HAL_Delay(100);
    }
}
