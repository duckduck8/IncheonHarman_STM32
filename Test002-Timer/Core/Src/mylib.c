/*
 * mylib.c
 *
 *  Created on: Jul 4, 2024
 *      Author: user
 */

#include "main.h"

extern UART_HandleTypeDef huart2;  //huart2 타입이 main.c에 있어서 extern 선언을 해줘야한대

int __io_putchar(int ch)  //1문자단위로 포트로 출력
{
	HAL_UART_Transmit(&huart2, &ch, 1, 10);
	return ch;
}
int __io_getchar(void)
{
	char ch;
	while(HAL_UART_Receive(&huart2, &ch, 1, 10) != HAL_OK);
	HAL_UART_Transmit(&huart2, &ch, 1, 10);
	if(ch=='\r') HAL_UART_Transmit(&huart2, "\n", 1, 10);
	return ch;
}

void Wait()
{
	while(HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) !=0);

}

void ProgramStart(char *name)
{
	printf("\033[2J\033[1;1H\n");  //y;xH (x,y) 위치로 커서 옮기기
	printf("Program(%s) ready. Press Blue button to start\r\n", name);
	Wait(); //while(HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) !=0);  bl핀이 눌리면 0 -> 0==0이니까 while문 거짓됨 -> while문 탈출
}
