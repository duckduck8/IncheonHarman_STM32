#include "main.h"
#include "mylib.h"

extern UART_HandleTypeDef huart2; //소스가 여러개 있어도 모두 모여서 하나의 실행파일로 만들어진다.

mybuf buf;


int __io_putchar(int ch)
{
	HAL_UART_Transmit(&huart2, &ch, 1, 10);
	return ch;
}

int __io_getchar(void)
{
	char ch;
	/*
	while(1)
	{
		int r = HAL_UART_Receive(&huart2, &ch, 1, 10);
		if(r == HAL_OK) break;
	}
	*/
	while(HAL_UART_Receive(&huart2, &ch, 1, 10) != HAL_OK);
	HAL_UART_Transmit(&huart2, &ch, 1, 10);	// echo
	if(ch == '\r') HAL_UART_Transmit(&huart2, "\n", 1, 10);
	return ch;
}

void Dump(int n)  //1,2,4... (byte)
{
	int max_row=20;
	int max_col=16/n;
	char str[10];
	sprintf(str, "%%0%dx ", n*2);  //%%='%'
	for(int i=0; i<max_row; i++)  //row index
	{
		for(int j=0; j<max_col; j++)  //column index
		{
			unsigned int v= (n==1) ? buf.v0[i*16+j]:
					        (n==2) ? buf.v1[i*8+j]:
							(n==4) ? buf.v2[i*4+j]: -1;
			printf(str, v);
	  		if(j==8/n-1) printf("   ");
		}
	  		printf("\r\n");
	}

}




void cls()
{
	printf("\033[2J\n");

	printf("\033[2J\033[1;1H\n");
}

void Wait()
{
	while(HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) != 0);
}

void ProgramStart(char *name)
{
	printf("\033[2J\033[1;1H\n"); // [y;xH : move cur to (x,y)
	printf("Program(%s) started... Blue button to start\r\n", name);
	Wait(); //while(HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) != 0);
}
