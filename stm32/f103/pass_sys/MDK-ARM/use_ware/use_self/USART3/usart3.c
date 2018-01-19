#include "sys.h" 


//���ڽ��ջ����� 	
uint8_t USART3_RX_BUF[USART3_MAX_RECV_LEN]=""; 				//���ջ���,���USART3_MAX_RECV_LEN���ֽ�.
uint8_t  USART3_TX_BUF[USART3_MAX_SEND_LEN]=""; 			//���ͻ���,���USART3_MAX_SEND_LEN�ֽ�

//ͨ���жϽ�������2���ַ�֮���ʱ������10ms�������ǲ���һ������������.
//���2���ַ����ռ������10ms,����Ϊ����1����������.Ҳ���ǳ���10msû�н��յ�
//�κ�����,���ʾ�˴ν������.
//���յ�������״̬
//[15]:0,û�н��յ�����;1,���յ���һ������.
//[14:0]:���յ������ݳ���

uint8_t usart_msg_action(void)
{
	if(USART3_RX_STA&0X8000)
	return true;
	else
	return false;		
}


	
vuint16_t USART3_RX_STA=0;
void USART3_IRQHandler(void)
{
	uint8_t res;	      
	if(USART3->SR&(1<<5))//���յ�����
	{	 
		res=USART3->DR; 			 
		if((USART3_RX_STA&(1<<15))==0)//�������һ������,��û�б�����,���ٽ�����������
		{ 
			if(USART3_RX_STA<USART3_MAX_RECV_LEN)	//�����Խ�������
			{
				TIM7->CNT=0;         				//��������� 
				if(USART3_RX_STA==0) 				//ʹ�ܶ�ʱ��7���ж� 
				{
					TIM7->CR1|=1<<0;     			//ʹ�ܶ�ʱ��7
				}
				USART3_RX_BUF[USART3_RX_STA++]=res;	//��¼���յ���ֵ	 
			}else 
			{
				USART3_RX_STA|=1<<15;				//ǿ�Ʊ�ǽ������
			} 
		}
	}  				 											 
}   
//��ʼ��IO ����3
//pclk1:PCLK1ʱ��Ƶ��(Mhz)
//bound:������ 
void usart3_init(uint32_t pclk1,uint32_t bound)
{  	 
	RCC->APB2ENR|=1<<3;   	//ʹ��PORTB��ʱ��  
 	GPIOB->CRH&=0XFFFF00FF;	//IO״̬����
	GPIOB->CRH|=0X00008B00;	//IO״̬���� 
	
	RCC->APB1ENR|=1<<18;  	//ʹ�ܴ���ʱ�� 	 
	RCC->APB1RSTR|=1<<18;   //��λ����3
	RCC->APB1RSTR&=~(1<<18);//ֹͣ��λ	
	//����������
 	USART3->BRR=(pclk1*1000000)/(bound);// ����������	 
	USART3->CR1|=0X200C;  	//1λֹͣ,��У��λ.
	//ʹ�ܽ����ж� 
	USART3->CR1|=1<<5;    	//���ջ������ǿ��ж�ʹ��	    	
	MY_NVIC_Init(0,1,USART3_IRQn,2);//��2
	TIM7_Int_Init(1000-1,7200-1);	//100ms�ж�
	TIM7->CR1&=~(1<<0);		//�رն�ʱ��7
	USART3_RX_STA=0;		//����
}

//����3,printf ����
//ȷ��һ�η������ݲ�����USART3_MAX_SEND_LEN�ֽ�
void u3_printf(char* fmt,...)  
{  
	uint16_t i,j; 
	va_list ap; 
	va_start(ap,fmt);
	vsprintf((char*)USART3_TX_BUF,fmt,ap);
	va_end(ap);
	i=strlen((const char*)USART3_TX_BUF);		//�˴η������ݵĳ���
	for(j=0;j<i;j++)							//ѭ����������
	{
		while((USART3->SR&0X40)==0);			//ѭ������,ֱ���������   
		USART3->DR=USART3_TX_BUF[j];  
	} 
}



































