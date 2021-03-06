/************************************************************
* 文件名称: USER.C
* 作者: 周晨阳
* 版本: 1.0
* 日期: 2017/4/29
* 描述: // 用户层的函数文件
* 主要函数及其功能 : // 主要函数及其功能
  1.void setup(void )//初始化函数
  2.void loop(void)//死循环函数，相当于while（1）{}
* 历史修改记录: // 历史修改记录
* <作者> <时间> <版本 > <描述>
* 周晨阳 2017/4/29 添加了此文件说明注释
***********************************************************/
#include "USER.h"
#include "../ANGLE/ANGLE.h"
#include "../MOTOR/MOTOR.h"
#include "../BUTTON/BUTTON.h"
#include "../DISPLAY/DataScope_DP.h"
#include "../DISPLAY/DISPLAY.H"
#include "../ANGLE/ANGLE.H"
#include "USART1.h"
#include "adc.h"
#include "STC15_PWM.H"
#include "UI.h"




//如有调试需要，请到user.h中将相应的宏定义开启
static u8 angle = 50, i = 0;//默认角度
static float kp = 3.0f, ki = 0.02f, kd = 1.0f, leftMotorSpeed = 0.5f, rightMotorSpeed = 0.5f;
void setup(void)//初始化函数
{
	UART1_init(UART1_BANDRATE);    //串口初始化
	GUI_Initialize(); //初始化液晶
	Button_config();//按键初始化
	ADC_config(ANGLE_PIN, ANGLE_Speed);   //adc初始化
	PID_config(kp, ki, kd);//pid算法初始化	
	setMenu_MAXandMIN(7, 1);//菜单级数,最大级数为6
	PWM_config(PWM_2);//pwm初始化
	PWM_config(PWM_4);
	PWM_period(5000);
	PWM_duty(PWM_2, 0.5f); //默认占空比0.5f
	PWM_duty(PWM_4, 0.5f);
	EA = 1;  //总中断开关	
	setPID_data(SET_ANGLE, 70);
	uiDraw();

}
/*************  串口1初始化函数 *****************/
/*************************************************
* 函数名称: void    UART1_init(unsigned long BandRate)
* 描述: 串口1初始化函数
* 输入: unsigned long BandRate ：串口的波特率，请在数值后加字母"L"，防止出问题
* 输出: 调用此函数会发送一段测试语句 “ STC15w4k58s4 UART1 is open ”
* 返回值: 无
* 其他说明: 无
*************************************************/
void    UART1_init(unsigned long BandRate)
{
	COMx_InitDefine     COMx_InitStructure;           
	COMx_InitStructure.UART_Mode = UART_8bit_BRTx;    
	COMx_InitStructure.UART_BRT_Use = BRT_Timer2;     
	COMx_InitStructure.UART_BaudRate = BandRate;      
	COMx_InitStructure.UART_RxEnable = ENABLE;        
	COMx_InitStructure.BaudRateDouble = DISABLE;      
	COMx_InitStructure.UART_Interrupt = ENABLE;       
	COMx_InitStructure.UART_Polity = PolityHigh;      
	COMx_InitStructure.UART_P_SW = UART1_SW_P30_P31;  
	COMx_InitStructure.UART_RXD_TXD_Short = DISABLE;  
	USART_Configuration(USART1, &COMx_InitStructure); 
//    PrintString1("STC15w4k58s4 UART1 is open \r\n");   //串口测试
}

//串口示波器数据发送函数
void sendScopeData(void)
{
	u8 a; //
	u8 Send_Count;

	DataScope_Get_Channel_Data(getPID_data(ERR), 1);  //误差数据
	DataScope_Get_Channel_Data(getPID_data(OUTPUT) + getPID_data(SET_ANGLE), 2);  //实际输出数据
	DataScope_Get_Channel_Data(getPID_data(INTEGRAL), 3);  //积分数据
	DataScope_Get_Channel_Data(getPID_data(SET_ANGLE), 4);  //设定角度
	DataScope_Get_Channel_Data(getAngle(PRESENT_ANGLE), 5);  //实际角度

	Send_Count = DataScope_Data_Generate(5); //
	for (a = 0; a < Send_Count; a++)
	{
		TX1_write2buff(DataScope_OutPut_Buffer[a]); //发送一通道数据到串口示波器
	}

}
