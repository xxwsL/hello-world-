#include "sys.h"
#include "commom.h"
#include "string.h"
#include "usart3.h"
int main(void)
{	xxwsL;
//	memset(USART3_RX_BUF,0,sizeof(USART3_RX_BUF));
	
	while (1)
	{	
		run;
//  	atk_8266_send_cmd("AT+CIPSTATUS","",200);

	}	
}









































#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

