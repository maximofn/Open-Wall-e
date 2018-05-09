/**
  ******************************************************************************
  * File Name          : USART.c
  * Description        : This file provides code for the configuration
  *                      of the USART instances.
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "usart.h"

#include "gpio.h"

/* USER CODE BEGIN 0 */

//#include <stdio.h>
//#include <stdint.h>
//#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "debug.h"

uint8_t debug_bufferRX[2];

T_Ring_Buffer Ring_Buffer_UART_debug;
T_Ring_Buffer Ring_Buffer_UART_VR;

//uint8_t external_debug = 0;
uint8_t parar_programa = 0;

#if DEBUG == 1
	uint8_t external_debug = 1;
#else
	uint8_external_debug = 0
#endif

/* USER CODE END 0 */

UART_HandleTypeDef huart3;
UART_HandleTypeDef huart6;

/* USART3 init function */

void MX_USART3_UART_Init(void)
{

  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  huart3.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart3.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}
/* USART6 init function */

void MX_USART6_UART_Init(void)
{

  huart6.Instance = USART6;
  huart6.Init.BaudRate = 115200;
  huart6.Init.WordLength = UART_WORDLENGTH_8B;
  huart6.Init.StopBits = UART_STOPBITS_1;
  huart6.Init.Parity = UART_PARITY_NONE;
  huart6.Init.Mode = UART_MODE_TX_RX;
  huart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart6.Init.OverSampling = UART_OVERSAMPLING_16;
  huart6.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart6.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart6) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct;
  if(uartHandle->Instance==USART3)
  {
  /* USER CODE BEGIN USART3_MspInit 0 */

  /* USER CODE END USART3_MspInit 0 */
    /* USART3 clock enable */
    __HAL_RCC_USART3_CLK_ENABLE();
  
    /**USART3 GPIO Configuration    
    PD8     ------> USART3_TX
    PD9     ------> USART3_RX 
    */
    GPIO_InitStruct.Pin = STLK_RX_Pin|STLK_TX_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    /* USART3 interrupt Init */
    HAL_NVIC_SetPriority(USART3_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART3_IRQn);
  /* USER CODE BEGIN USART3_MspInit 1 */

  /* USER CODE END USART3_MspInit 1 */
  }
  else if(uartHandle->Instance==USART6)
  {
  /* USER CODE BEGIN USART6_MspInit 0 */

  /* USER CODE END USART6_MspInit 0 */
    /* USART6 clock enable */
    __HAL_RCC_USART6_CLK_ENABLE();
  
    /**USART6 GPIO Configuration    
    PC6     ------> USART6_TX
    PC7     ------> USART6_RX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF8_USART6;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    /* USART6 interrupt Init */
    HAL_NVIC_SetPriority(USART6_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART6_IRQn);
  /* USER CODE BEGIN USART6_MspInit 1 */

  /* USER CODE END USART6_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART3)
  {
  /* USER CODE BEGIN USART3_MspDeInit 0 */

  /* USER CODE END USART3_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART3_CLK_DISABLE();
  
    /**USART3 GPIO Configuration    
    PD8     ------> USART3_TX
    PD9     ------> USART3_RX 
    */
    HAL_GPIO_DeInit(GPIOD, STLK_RX_Pin|STLK_TX_Pin);

    /* USART3 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART3_IRQn);
  /* USER CODE BEGIN USART3_MspDeInit 1 */

  /* USER CODE END USART3_MspDeInit 1 */
  }
  else if(uartHandle->Instance==USART6)
  {
  /* USER CODE BEGIN USART6_MspDeInit 0 */

  /* USER CODE END USART6_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART6_CLK_DISABLE();
  
    /**USART6 GPIO Configuration    
    PC6     ------> USART6_TX
    PC7     ------> USART6_RX 
    */
    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_6|GPIO_PIN_7);

    /* USART6 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART6_IRQn);
  /* USER CODE BEGIN USART6_MspDeInit 1 */

  /* USER CODE END USART6_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */

void UART_Error_Registers_init(void)
{
	UART_debug_ERROR_REGISTER_.DMA_Counter = 0;
	UART_debug_ERROR_REGISTER_.FE_Counter = 0;
	UART_debug_ERROR_REGISTER_.ORE_Counter = 0;
	UART_debug_ERROR_REGISTER_.NE_Counter = 0;
	UART_debug_ERROR_REGISTER_.PE_Counter = 0;

	UART_VR_ERROR_REGISTER_.DMA_Counter = 0;
	UART_VR_ERROR_REGISTER_.FE_Counter = 0;
	UART_VR_ERROR_REGISTER_.ORE_Counter = 0;
	UART_VR_ERROR_REGISTER_.NE_Counter = 0;
	UART_VR_ERROR_REGISTER_.PE_Counter = 0;
}

void UART_Ring_Buffer_init(void)
{
	Ring_Buffer_UART_debug.WR_Ptr = Ring_Buffer_UART_debug.Buffer_Recv;
	Ring_Buffer_UART_debug.Read_Flag = 0;
	Ring_Buffer_UART_debug.End_Of_Buffer_Flag = 0;
	Ring_Buffer_UART_debug.Buffer_size_used = UART_DEBUG_BUFFER_SIZE;
	Ring_Buffer_UART_debug.huart = &huart3;
	HAL_UART_Receive_IT(Ring_Buffer_UART_debug.huart, &Ring_Buffer_UART_debug.Byte_Recv, 1);

	Ring_Buffer_UART_VR.WR_Ptr = Ring_Buffer_UART_VR.Buffer_Recv;
	Ring_Buffer_UART_VR.Read_Flag = 0;
	Ring_Buffer_UART_VR.End_Of_Buffer_Flag = 0;
	Ring_Buffer_UART_VR.Buffer_size_used = UART_VR_BUFFER_SIZE;
	Ring_Buffer_UART_VR.huart = &huart6;
	HAL_UART_Receive_IT(Ring_Buffer_UART_VR.huart, &Ring_Buffer_UART_VR.Byte_Recv, 1);
}

void UART_Ring_Buffer_WR(T_Ring_Buffer *Ring_Buffer, uint8_t Data)
{
	*Ring_Buffer->WR_Ptr = Data;
	if(Ring_Buffer->WR_Ptr < &Ring_Buffer->Buffer_Recv[Ring_Buffer->Buffer_size_used])
	{
		Ring_Buffer->WR_Ptr++;
	}
	else
	{
		Ring_Buffer->WR_Ptr = Ring_Buffer->Buffer_Recv;
		Ring_Buffer->End_Of_Buffer_Flag = 1;
	}
	Ring_Buffer->Read_Flag = 1;
	//imprimir  (" FLAG\n\r", QUIET, CODIGO_ANSI_ERROR);

}

uint32_t UART_Ring_Buffer_RD(T_Ring_Buffer *Ring_Buffer, uint8_t *Buffer)
{
	uint32_t size1; //variable auxiliar
	uint32_t size2; //variable auxiliar
	uint32_t size = 0;


	__HAL_UART_DISABLE_IT(Ring_Buffer->huart, UART_IT_RXNE);

	if(Ring_Buffer->Read_Flag == 1) // hay algo que leer
	{
		//imprimir  (" ALGO QUE LEER\n\r", QUIET, CODIGO_ANSI_ERROR);

			if(Ring_Buffer->End_Of_Buffer_Flag == 0 )
			{
				size1 = Ring_Buffer->WR_Ptr - Ring_Buffer->Buffer_Recv;
				memcpy(Buffer, Ring_Buffer->Buffer_Recv, size1);
				//safe_memcpy(Buffer, size1, Ring_Buffer->Buffer_Recv, size1, size1);
				size = size1;
				//sprintf (bufferTX, "Ring_Buffer->End_Of_Buffer_Flag == 0 ==> (size = %i) \n\r", size); DEBUG(bufferTX);
			}
			else if(Ring_Buffer->End_Of_Buffer_Flag == 1 && Ring_Buffer->WR_Ptr == Ring_Buffer->Buffer_Recv)
			{
				memcpy(Buffer, Ring_Buffer->Buffer_Recv, Ring_Buffer->Buffer_size_used);
				size =  Ring_Buffer->Buffer_size_used;
				//sprintf (bufferTX, "Ring_Buffer->End_Of_Buffer_Flag == 1 && Ring_Buffer->WR_Ptr == Ring_Buffer->Buffer_Recv ==> (size = %i) \n\r", size); DEBUG(bufferTX);
			}
			else if(Ring_Buffer->End_Of_Buffer_Flag == 1 && Ring_Buffer->WR_Ptr != Ring_Buffer->Buffer_Recv)
			{
				size1 = &Ring_Buffer->Buffer_Recv[Ring_Buffer->Buffer_size_used] - Ring_Buffer->WR_Ptr;
				memcpy(Buffer, Ring_Buffer->WR_Ptr, size1);

				size2 = Ring_Buffer->WR_Ptr - Ring_Buffer->Buffer_Recv;
				memcpy(Buffer + size1, Ring_Buffer->Buffer_Recv, size2);

				size = size1 + size2;
				//sprintf (bufferTX, "Ring_Buffer->End_Of_Buffer_Flag == 1 && Ring_Buffer->WR_Ptr != Ring_Buffer->Buffer_Recv ==> (size = %i) \n\r", size); DEBUG(bufferTX);
			}

	}
	else
	{
		//imprimir  (" NADA QUE LEER\n\r", QUIET, CODIGO_ANSI_ERROR);
	}

	Ring_Buffer->WR_Ptr = Ring_Buffer->Buffer_Recv;
	Ring_Buffer->End_Of_Buffer_Flag = 0;
	Ring_Buffer->Read_Flag = 0;

	__HAL_UART_ENABLE_IT(Ring_Buffer->huart, UART_IT_RXNE);

	return size;
}


void HAL_UART_RxCpltCallback (UART_HandleTypeDef *huart)
{

	// USART 3 --> Debug
	if(huart->Instance == UART_DEBUG)
	{

		UART_Ring_Buffer_WR(&Ring_Buffer_UART_debug, Ring_Buffer_UART_debug.Byte_Recv);

		//sprintf(bufferTX, " Ring_Buffer_UART_debug.Byte_Recv = %X\n\r", Ring_Buffer_UART_debug.Byte_Recv); imprimir  (bufferTX, QUIET, CODIGO_ANSI_NORMAL);

		__HAL_UNLOCK(Ring_Buffer_UART_debug.huart);

		HAL_UART_Receive_IT(Ring_Buffer_UART_debug.huart, &Ring_Buffer_UART_debug.Byte_Recv, 1);

		if (Ring_Buffer_UART_debug.Byte_Recv == 'r' || Ring_Buffer_UART_debug.Byte_Recv == 'R') // Si se recibe una 'r' o una 'R' se resetea
		{
#if EXTERNAL_RESET == 1
			traza  ("\n\r ----------------- RESET ----------------- \n\r");
			NVIC_SystemReset();
#endif
		}
		else if (Ring_Buffer_UART_debug.Byte_Recv == 'p' || Ring_Buffer_UART_debug.Byte_Recv == 'P')
		{
			if (parar_programa)
			{
				traza  (" ----------------- REANUDAR PROGRAMA ----------------- \n\r");
				parar_programa = 0;
			}
			else
			{
				traza  (" ----------------- PARAR PROGRAMA ----------------- \n\r");
				parar_programa = 1;
			}
		}
		else if (Ring_Buffer_UART_debug.Byte_Recv == 'd' || Ring_Buffer_UART_debug.Byte_Recv == 'D')
		{
			if (external_debug)
			{
				traza  (" ----------------- DISABLE DEBUG ----------------- \n\r");
				external_debug = 0;
			}
			else
			{
				traza  (" ----------------- ENABLE DEBUG ----------------- \n\r");
				external_debug = 1;
			}
		}
		else if (Ring_Buffer_UART_debug.Byte_Recv == 'h' || Ring_Buffer_UART_debug.Byte_Recv == 'H')
		{
			traza  (" ----------------- COMANDOS CONSOLA ----------------- \n\r");
			traza  ("  * r - Reset \n\r");
			traza  ("  * p - Parar programa \n\r");
			traza  ("  * d - Enable/disable debug \n\r");
			traza  ("  * h - Help \n\r");
		}
		else if(Ring_Buffer_UART_debug.Byte_Recv != '\r' && Ring_Buffer_UART_debug.Byte_Recv != '\n') // dato recibido distinto de 'enter'
		{
			debug_bufferRX [0] = Ring_Buffer_UART_debug.Byte_Recv;	// se añade el dato al buffer
			HAL_UART_Transmit ( Ring_Buffer_UART_debug.huart, debug_bufferRX, 1, 0xFF);				// Eco
		}
		else						// dato recibido 'enter'
		{
			debug_bufferRX [0] = '\r';
			debug_bufferRX [1] = '\n';
			HAL_UART_Transmit (Ring_Buffer_UART_debug.huart, debug_bufferRX, 2, 0xFF);		// Eco
			//Transfer_complete = 1; // transfer complete, se puede leer el buffer
		}
	}

	// USART 6 --> VR
	if(huart->Instance == UART_VR)
	{

		UART_Ring_Buffer_WR(&Ring_Buffer_UART_VR, Ring_Buffer_UART_VR.Byte_Recv);

		//sprintf(bufferTX, " Ring_Buffer_UART_VR.Byte_Recv = %X\n\r", Ring_Buffer_UART_VR.Byte_Recv); imprimir  (bufferTX, QUIET, CODIGO_ANSI_NORMAL);

		__HAL_UNLOCK(Ring_Buffer_UART_VR.huart);

		HAL_UART_Receive_IT(Ring_Buffer_UART_VR.huart, &Ring_Buffer_UART_VR.Byte_Recv, 1);
	}

	else
	{

	}
}




int traza(const char* format, ...)
{
	int ret = 0;
#if DEBUG == 1

	va_list ap;
	static char buf[200];
	//char buf[128];
	va_start (ap, format);



	// Print to the local buffer
	ret = vsnprintf (buf, sizeof(buf), format, ap);

	if (ret > 0)
	{
		//HAL_UART_Transmit_IT(&huart2,(uint8_t*)buf, (size_t)ret);
		HAL_UART_Transmit(Ring_Buffer_UART_debug.huart,(uint8_t*)buf, (size_t)ret, 0xFF);
		//HAL_Delay(4);
	}

	va_end (ap);
#endif
	return ret;
}

/* USER CODE END 1 */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
