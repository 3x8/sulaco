#include <stdbool.h>
#include <stdint.h>
#include <math.h>

#include "platform.h"

#include "common/maths.h"

#include "drivers/audio.h"

static DAC_HandleTypeDef hdac;
static TIM_HandleTypeDef handle;
static DAC_ChannelConfTypeDef sConfig;

void audioSetupIO(void)
{
    __HAL_RCC_DAC_CLK_ENABLE();
    __HAL_RCC_TIM6_CLK_ENABLE();

    hdac.Instance = DAC;
    HAL_DAC_Init(&hdac);

    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = GPIO_PIN_4;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void audioGenerateWhiteNoise(void)
{
    // TIM6 runs on APB2 at 42Mhz
    handle.Instance = TIM6;
    handle.Init.Period = 0xFF;
    handle.Init.Prescaler = 0;

    handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    handle.Init.CounterMode = TIM_COUNTERMODE_UP;
    handle.Init.RepetitionCounter = 0;
    HAL_TIM_Base_Init(&handle);

    TIM_MasterConfigTypeDef sMasterConfig;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_ENABLE;
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
    HAL_TIMEx_MasterConfigSynchronization(&handle, &sMasterConfig);

    HAL_TIM_Base_Start(&handle);

    sConfig.DAC_Trigger = DAC_TRIGGER_T6_TRGO;
    sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;
    HAL_DAC_ConfigChannel(&hdac, &sConfig, DAC_CHANNEL_1);

    HAL_DACEx_NoiseWaveGenerate(&hdac, DAC_CHANNEL_1, DAC_LFSRUNMASK_BITS10_0);
    HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_L, 0xcd00);

    HAL_DAC_Start(&hdac, DAC_CHANNEL_1);
}

#define TONE_SPREAD 8

void audioPlayTone(uint8_t tone)
{
    handle.Init.Period = 64 + (MAX(TONE_MIN,MIN(tone, TONE_MAX)) * TONE_SPREAD);
    TIM_Base_SetConfig(handle.Instance, &handle.Init);
}

void audioSilence(void)
{
    HAL_DAC_Stop(&hdac, DAC_CHANNEL_1);
    HAL_TIM_Base_Stop(&handle);
}
