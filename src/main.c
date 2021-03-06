/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/

#include "main.h"

#include <string.h>

int main(void)
{
	HAL_Init();
	MX_USART2_UART_Init();
	//lettura training
	//training vero e proprio

	/*
	char *c1 = "Acceleration\t\t";
	char *c2 = "Speed\t\t";
	char *c3 = "Direction\r\n";
*/

	//float *media;
	//float *varianza;

	float vettore1[10]={45,4,5,7,2,1,8,66,8,12};
	int vectorLength = sizeof(vettore1)/sizeof(vettore1[0]);
	float tempMedia1 = calculateMean(vettore1, vectorLength);
	float tempVarianza1 = calculateVar(vettore1, tempMedia1, vectorLength);
	//deviazione standard
	float tempStdDev1=sqrt(tempVarianza1);

	int media1 = (int)tempMedia1;
	int varianza1 = (int)tempVarianza1;
	int stdDev1=(int)tempStdDev1;

	float vettore2[10]={2,5,3,4,3,7,99,12,8,4};
	//stessa lunghezza perch� immaginiamo che i vettori siano lunghi uguali
	float tempMedia2 = calculateMean(vettore2, vectorLength);
	float tempVarianza2 = calculateVar(vettore2, tempMedia2, vectorLength);
	//deviazione standard
	float tempStdDev2=sqrt(tempVarianza2);

	int media2 = (int)tempMedia2;
	int varianza2 = (int)tempVarianza2;
	int stdDev2=(int)tempStdDev2;
	float tempCorrIndex = calculateCorr(vettore1, vettore2, vectorLength, media1, media2, stdDev1, stdDev2);
	int corrIndex = (int)tempCorrIndex;
	char *newline = "\n\r";

	char test[100];
	char buffer[100];
	//int prova = 124;

	for(;;)
		{

// \r serve a far "rientrare"

		//HAL_StatusTypeDef HAL_UART_Transmit(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout)


		/*
			HAL_UART_Transmit(&huart2, (uint8_t*)c1, strlen(c1), 0xFFFF);
			HAL_Delay(100);
			HAL_UART_Transmit(&huart2, (uint8_t*)c2, strlen(c2), 0xFFFF);
			HAL_Delay(100);
			HAL_UART_Transmit(&huart2, (uint8_t*)c3, strlen(c3), 0xFFFF);
*/
		//HAL_UART_Transmit(&huart2, (uint8_t*)test, strlen(test), 0xFFFF);
/*
			HAL_UART_Transmit(&huart2, (uint8_t*)&media, numOfDigits(media), 0xFFFF);
			HAL_UART_Transmit(&huart2, (uint8_t*)newline, strlen(newline), 0xFFFF);
			HAL_Delay(100);
			HAL_UART_Transmit(&huart2, (uint8_t*)&varianza, numOfDigits(varianza), 0xFFFF);
			HAL_UART_Transmit(&huart2, (uint8_t*)newline, strlen(newline), 0xFFFF);
			HAL_UART_Transmit(&huart2, (uint8_t*)newline, strlen(newline), 0xFFFF);
			HAL_Delay(100);
			HAL_Delay(1000);
			*/
			//char test[] = "Media:\t\t\t"
			*test = "Media1:\t\t\t";
    		HAL_UART_Transmit(&huart2, (uint8_t*)test, strlen(test), 0xFFFF);
			snprintf(buffer, sizeof buffer, "%d", media1);
			HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 0xFFFF);
			HAL_UART_Transmit(&huart2, (uint8_t*)newline, strlen(newline), 0xFFFF);

			//char test2[] = "Varianza: \t\t";
			*test = "Varianza1: \t\t";
			HAL_UART_Transmit(&huart2, (uint8_t*)test, strlen(test), 0xFFFF);
			snprintf(buffer, sizeof buffer, "%d", varianza1);
			HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 0xFFFF);
	    	HAL_UART_Transmit(&huart2, (uint8_t*)newline, strlen(newline), 0xFFFF);
	    	HAL_Delay(1000);

			//char test3[] = "Corr: \t\t";
	    	*test = "Corr: \t\t";
	    	HAL_UART_Transmit(&huart2, (uint8_t*)test, strlen(test), 0xFFFF);
	    	snprintf(buffer, sizeof buffer, "%d", corrIndex);
	    	HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 0xFFFF);
	    	HAL_UART_Transmit(&huart2, (uint8_t*)newline, strlen(newline), 0xFFFF);
	    	HAL_Delay(1000);
		}

}
//inizializzazione della seriale
void MX_USART2_UART_Init(void)
{
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 9600;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	HAL_UART_Init(&huart2);
}
//configurazione dei pin per comunicazione
void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  if(huart->Instance==USART2)
  {
    __GPIOA_CLK_ENABLE();
    __USART2_CLK_ENABLE();

    /**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
  }
}

