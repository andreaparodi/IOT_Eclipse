/*
 * print_out.h
 *
 *  Created on: 13 feb 2018
 *      Author: andre
 */

#ifndef PRINT_OUT_H_
#define PRINT_OUT_H_

#include "main.h"

/**
  * @brief Sends a single character
  * @param USARTx: specifies the USART to use
  */
void UU_PutChar(USART_TypeDef* USARTx, uint8_t ch);

/**
  * @brief Sends a string
  * @param USARTx: specifies the USART to use
  */
void UU_PutString(USART_TypeDef* USARTx, uint8_t* message);

/**
  * @brief Converts an unsigned 32 integer to characters and then
  *	   sends it character by character. Please note that the maximum
  *	   value is 4,294,967,295 which equals 0xFFFFFFFF. Any number
  *	   greater than this number will be turncated.
  * @param USARTx: specifies the USART to use
  */
void UU_PutNumber(USART_TypeDef* USARTx, uint32_t x);

#endif /* PRINT_OUT_H_ */
