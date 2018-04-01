#ifndef __MPU_H
#define __MPU_H	 
#include "xxwsL.h" 


//MPU����ϸ���ù�ϵ���뿴����STM32F7����ֲ�.pdf��
//����ĵ���4.6��,Table 89.
//MPU��������������Զ��壨������stm32f7xx_hal_cortex.h��
//����MPU->RASR�Ĵ���AP[26:24]λ������ֵ
#define  MPU_REGION_NO_ACCESS      	((uint8_t)0x00U)		//�޷��ʣ���Ȩ&�û������ɷ��ʣ�
#define  MPU_REGION_PRIV_RW        	((uint8_t)0x01U) 		//��֧����Ȩ��д����
#define  MPU_REGION_PRIV_RW_URO    	((uint8_t)0x02U)  		//��ֹ�û�д���ʣ���Ȩ�ɶ�д���ʣ�
#define  MPU_REGION_FULL_ACCESS    	((uint8_t)0x03U)  		//ȫ���ʣ���Ȩ&�û����ɷ��ʣ�
#define  MPU_REGION_PRIV_RO        	((uint8_t)0x05U) 		//��֧����Ȩ������
#define  MPU_REGION_PRIV_RO_URO    	((uint8_t)0x06U)		//ֻ������Ȩ&�û���������д��
 
void MPU_Disable(void);
void MPU_Enable(void);
u8 MPU_Convert_Bytes_To_POT(u32 nbytes);
u8 MPU_Set_Protection(u32 baseaddr,u32 size,u32 rnum,u8 ap,u8 sen,u8 cen,u8 ben);
void MPU_Memory_Protection(void);
#endif

















