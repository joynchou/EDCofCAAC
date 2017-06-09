/************************************************************
* 组织名称：电子大赛小组
* 文件名称: MODE.C
* 作者: 周晨阳
* 版本 beta 1.1
* 日期: 5/26
* 描述: 用来选择模式和执行模式程序的文件
* 历史修改记录: // 历史修改记录
* <作者> <时间> <版本 > <描述>
* 周晨阳 17/5/28 1.0			增加了模式一
* 周晨阳	 17/6/6  1.1    增加了模式二
***********************************************************/

#include "MODE.H"
#include "timer.h" //包含定时器头文件
#include "../RTOS/OS.h"
#include "../USER/delay.h"
#include "../USER/USART1.h"
#include <math.h>
  static u8 mode=0; //默认模式0，开机后请用按键选择模式
//按键检测，4个按键对应4个模式

void modeSelect(void)
{
	static bit BUTTON1_bit = 0;  //按键按下标志位
	static bit BUTTON2_bit = 0;  //同上
	static bit BUTTON3_bit = 0;
	static bit BUTTON4_bit = 0;

	if (getButtonState(BUTTON1_GPIO_PIN))
	{
		if (!BUTTON1_bit)
		{
			mode=1;
			BUTTON1_bit = 1;
		
		}

	}
	else
	{
		BUTTON1_bit = 0;
	}

	if (getButtonState(BUTTON2_GPIO_PIN))
	{
		if (!BUTTON2_bit)
		{
			BUTTON2_bit = 1;

		  mode=2;

		}
	}
	else
	{
		BUTTON2_bit = 0;
	}
		if (getButtonState(BUTTON3_GPIO_PIN))
	{
		if (!BUTTON3_bit)
		{
			mode=3;
			BUTTON3_bit = 1;
		
		}

	}
	else
	{
		BUTTON3_bit = 0;
	}

	if (getButtonState(BUTTON4_GPIO_PIN))
	{
		if (!BUTTON4_bit)
		{
			BUTTON4_bit = 1;

		  mode=4;

		}
	}
	else
	{
		BUTTON4_bit = 0;
	}

	
}
//不同模式对应的程序。
void modeStart(void)
{  
	 switch(mode)
	 {
		 case 1://模式1
		 {
			 	static bit step1=0;//模式一步骤1标志位
				static bit step2=0; //步骤2 标志位
				static bit step3=0;  //步骤三标志位

			 if(step1)//步骤一已经完成
			 {
				 
				  if(step2) //如果步骤2已完成
					{
						  if(step3) //如果步骤三已经完成
							{
								  //模式一已经完成 ，蜂鸣器开始叫
								mode=0;//初始化模式
								step1=0;
								step2=0;
								step3=0;
								
							}
							else//如果步骤三没有完成
							{
								stopMotor();
								step3=OK;
								PrintString1("step3 is ok\n");
								
							}
						
					}
					else //如果步骤二没有完成
					{
					setTimeout(Timer1,5000); //设置定时器定时长度 ,5秒
		//////////////////////定时器////////////////////////////////////////
					if(isExpiredTimer(Timer1))   //如果达到定时时间
					{
						
						  setMotorSpeed(LEFT_MOTOR,0.01f);
						  setMotorSpeed(RIGHT_MOTOR,0.99f);
							stopMotor();
							step2=OK;
						  PrintString1("step2 is ok\n");
					}
					else//如果未达到定时时间或定时器未启动
					{ 
						
						if(isStopped(Timer1)) //只有当定时器是停止状态时才启动定时器。
						{
							restartTimer(Timer1);
							
						}
					}
		////////////////////////////////////////////////////////////////		   
					
					}
			 }
			 else //如果步骤一没有完成
			 {
				 setPID_data(SET_ANGLE,100); //设定稳定角度
				 setTimeout(Timer1,5000); //设置定时器定时长度 ,3秒
				 startMotor();//电机开始工作
				 if(abs(getPID_data(ERR))<2.0f)//当误差小于2°时，认为达到稳定,定时器就开始计时
				{
		//////////////////////定时器////////////////////////////////////////
					if(isExpiredTimer(Timer1))   //如果达到定时时间
					{
						 stopTimer(Timer1);//达到定时时间后关闭定时器
						 step1=OK; //步骤一完成 ，已经达到稳定状态，蜂鸣器响一下
						 PrintString1("step1 is ok\n");
					}
					else//如果未达到定时时间或定时器未启动
					{ 
						
						if(isStopped(Timer1)) //只有当定时器是停止状态时才启动定时器。
						{
							restartTimer(Timer1);
							
						}
					}
		////////////////////////////////////////////////////////////////		 
				}
			 }
			 
			 
		 };
		 break;
		 case 2://模式二
		 {

			 static unsigned int mode2_ERR_times = 0;//���������
			 static bit mode2_step1 = 0;//����1��ʶλ
			 static bit mode2_step2 = 0;//����2��ʶλ
			 static bit mode2_step3 = 0;//����3��ʶλ
			 static unsigned int mode2_time = 0;//ģʽִ�д���
			 static float mode2_Sta_angle = 0.0f;//���ֵ����
			 setTimeout(Timer1,10);//�趨��ʱ��
			 if(mode2_step1)//�жϲ���1�Ƿ����
			 {
				 if(mode2_step2)//�жϲ���2�Ƿ����
				 {
					 if(mode2_step3)//�жϲ���3�Ƿ����
					 {
						  // PrintString1("mode_step3 is ok\n");
						 mode=0;
						 stopMotor();
					 }
					 else
					 {
////////////////////����3///////////////////////////

						 mode2_time++;//ģʽ2ִ�д����ۼ�
						
						 if(mode2_time >= 3)//��ģʽ2����3�κ���ֹͣ����
						 {
							 mode2_time=0;
							 setMotorSpeed(LEFT_MOTOR,0.05f);
							 setMotorSpeed(RIGHT_MOTOR,0.90f);
							 mode2_step3 = 1;	
							 //PrintString1("mode_step3 is ok\n");							 
						 }
						 else
						 {
							 mode2_step1 = 0;//����ģʽ2��һ��
							 mode2_step2 = 0;//����ģʽ2�ڶ���
							 mode2_step3 = 0;//����ģʽ2����
						 }
					 }
////////////////////����2///////////////////////////
				 }
				 else
				 {
					 setPID_data(SET_ANGLE,110);//�趨Ҫ����ĵڶ���Ƕ�
					 if(getPID_data(ERR) < 2.0f)//�ж��Ƿ����������
					 {
						 if(isExpiredTimer(Timer1))//�ж��Ƿ񵽴ﶨʱ��ʱ��
						 { 
							 stopTimer(Timer1);
							 mode2_ERR_times++;//�������ۼ�
							 mode2_Sta_angle += abs(getPID_data(ERR));//����ۼ�
							 if(mode2_ERR_times >= 30)//����ۼƴ����Ƿ񵽴�50��
							 {
								 mode2_Sta_angle /= mode2_ERR_times;//����ƽ�����
								 mode2_ERR_times = 0;//����ۼƼ������ʼ��
								 if(abs(mode2_Sta_angle) < 6.0f)//�ж��Ƿ񵽴��ȶ�
								 {
									 mode2_step2 = 1;//���벽��3
								 }
								 mode2_Sta_angle=0;
							 }
						 }
						 else
						 {
							 restartTimer(Timer1);
						 }
					 }
				 }
////////////////////////����1//////////////////////////
			 }
			 else
			 {
				 setPID_data(SET_ANGLE,70);//�趨Ҫ�ﵽ�ĵ�һ��Ƕ�
				 startMotor();//����
				 if(getPID_data(ERR) < 2.0f)//�ж��Ƿ�ʼ����������
				 {
					 if(isExpiredTimer(Timer1))//�ж϶�ʱ���Ƿ񵽴�ָ��ʱ��

					 {
						 stopTimer(Timer1);
						 mode2_ERR_times++;

						 mode2_Sta_angle += abs(getPID_data(ERR));//����ۼ�
						 if(mode2_ERR_times >= 30)//�Ƿ��¼��50�����
						 {
							 mode2_Sta_angle /= mode2_ERR_times;//ȡ���ƽ��ֵ
							 mode2_ERR_times = 0;//������������
							 if(abs(mode2_Sta_angle) < 6.0f)//�ж��Ƿ񵽴��ȶ�״̬��������벽��2
							 {
								 mode2_step1 = 1;

							 }
							 mode2_Sta_angle=0;
						 }
					 }
					 else
					 {


						 restartTimer(Timer1);//���ʱ��
					 }
				 }
			 }
			 
		
		 };
		 break;
		 case 3: //ģʽ3
		 {

		 };
		 break;
		 case 4:  //模式4
		 {
			 
			 
		 };
		 break;
    
		 default:
		break;		 
	 }
	
}
