#include "stm32g0xx_hal.h"
#include "main.h"

void GPIO_PA4_Init();
void setupTimer3Base();
void setupTimer14Base();
TIM_HandleTypeDef tim3 = {0};
TIM_HandleTypeDef tim14 = {0};

int main()
{
  HAL_Init();
  setupTimer3Base();
  setupTimer14Base();
  GPIO_PA4_Init();

  while (1)
  {
    HAL_Delay(100);
  }
  return 0;
}

uint32_t last = 0;
uint32_t diff = 0;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM3)
  {
    uint32_t current = HAL_GetTick();
    diff = current - last;
    last = current;
  }
  else if (htim->Instance == TIM14)
  {
    volatile uint16_t kk = 0;
  }
}
void setupTimer3Base()
{
  __HAL_RCC_TIM3_CLK_ENABLE();

  tim3.Instance = TIM3;
  tim3.Init.Prescaler = 1599;
  tim3.Init.Period = 19999;
  HAL_TIM_Base_Init(&tim3);
  HAL_NVIC_SetPriority(TIM3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(TIM3_IRQn);

  HAL_TIM_Base_Start_IT(&tim3);
}

void setupTimer14Base()
{
  __HAL_RCC_TIM14_CLK_ENABLE();

  tim14.Instance = TIM14;
  tim14.Init.Prescaler = 15999;
  tim14.Init.Period = 0xfff;

  HAL_TIM_Base_Init(&tim14);

  TIM_OC_InitTypeDef sConfigOC = {0};
  sConfigOC.OCMode = TIM_OCMODE_TOGGLE; // Toggle mode
  sConfigOC.Pulse = 100;                // CCR value (toggle at half the period)
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  HAL_TIM_OC_ConfigChannel(&tim14, &sConfigOC, TIM_CHANNEL_1);
  HAL_TIM_OC_Start(&tim14, TIM_CHANNEL_1);
}

void GPIO_PA4_Init()
{
  __HAL_RCC_GPIOA_CLK_ENABLE();
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin = GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF4_TIM14;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}
