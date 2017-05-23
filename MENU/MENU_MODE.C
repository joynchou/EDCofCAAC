#include "MENU_MODE.h"
//按键设置pid参数函数
void setAngle(void)
{

	static bit BUTTON1_bit = 0;
	static bit BUTTON2_bit = 0;
	static bit BUTTON3_bit = 0;
	static bit BUTTON4_bit = 0;
	static u8 setAngle1 = 70;
	static u8 setAngle2 = 80;


#ifdef PID_DEBUG	
	if (getButtonState(BUTTON3_GPIO_PIN))
	{
		if (!BUTTON3_bit)
		{
			BUTTON3_bit = 1;



			/*


			 按键处理代码












			*/


			/*
			switch (getMenuNum(FIRST_MEUN_NUM))
			{
			case 1:
			{
				kp += 0.1f;
				setPID_data(KP, kp);
				GUI_PutNum(0, 0, kp);
			};
			break;
			case 2:
			{
				ki += 0.005f;
				setPID_data(KI, ki);
				GUI_PutNum(0, 7, ki);
			};
			break;
			case 3:
			{
				kd += 0.1f;
				setPID_data(KD, kd);
				GUI_PutNum(0, 14, kd);
			};
			break;
			case 4:
			{

				angle += 2;
				GUI_PutNum(0, 7 * 3, angle);
			};
			break;
			case 5:
			{
				leftMotorSpeed += 0.01f;
				setMotorSpeed(LEFT_MOTOR, leftMotorSpeed);
				GUI_PutNum(3, 1, leftMotorSpeed);
			};
			break;
			case 6:
			{
				rightMotorSpeed += 0.01f;
				setMotorSpeed(RIGHT_MOTOR, rightMotorSpeed);
				GUI_PutNum(3, 2, rightMotorSpeed);
			};
			break;
			case 7:
			{
				PWM_ALL_EN;
			};
			break;
			}
			*/
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

			switch (getMenuNum(FIRST_MEUN_NUM))
			{
			case 1:
			{
				kp -= 0.1f;
				setPID_data(KP, kp);
				GUI_PutNum(0, 0, kp);
			};
			break;
			case 2:
			{
				ki -= 0.005f;
				setPID_data(KI, ki);
				GUI_PutNum(0, 1, ki);
			};
			break;
			case 3:
			{
				kd -= 0.1f;
				setPID_data(KD, kd);
				GUI_PutNum(0, 2, kd);
			};
			break;
			case 4:
			{
				angle -= 2;
				GUI_PutNum(0, 3, angle);
			};
			break;
			case 5:
			{

				setMotorSpeed(LEFT_MOTOR, leftMotorSpeed);
				leftMotorSpeed -= 0.01f;
				GUI_PutNum(3, 1, leftMotorSpeed);
			};
			break;
			case 6:
			{
				setMotorSpeed(RIGHT_MOTOR, rightMotorSpeed);
				rightMotorSpeed -= 0.01f;
				GUI_PutNum(3, 2, rightMotorSpeed);
			};
			break;
			case 7:
			{

			};
			break;
			}

		}
	}
	else
	{
		BUTTON4_bit = 0;
	}
#else
	if (getButtonState(BUTTON1_GPIO_PIN))
	{
		if (!BUTTON1_bit)
		{
			BUTTON1_bit = 1;

			switch (getMenuNum(SECOND_MEUN_NUM))
			{
			case 1:
			{	 setAngle1++;
			GUI_PutNum(0, 0, setAngle1);
			};
			break;
			case 2:
			{	 setAngle2++;
			GUI_PutNum(0, 7, setAngle2);
			};
			break;
			case 3:
			{
				OPEN_PWM();
			};
			break;
			case 4:
			{
				GUI_PutNum(0, 7 * 2, angle);
			};
			break;
			case 5:
			{
				GUI_PutNum(3, 7, leftMotorSpeed);
			};
			break;
			case 6:
			{
				GUI_PutNum(3, 7 * 2, rightMotorSpeed);
			};
			break;
			case 7:
			{
			};
			break;
			}
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

			switch (getMenuNum(SECOND_MEUN_NUM))
			{
			case 1:
			{   setAngle1--;
			GUI_PutNum(0, 0, setAngle1);

			};
			break;
			case 2:
			{	 setAngle2--;
			GUI_PutNum(0, 7, setAngle2);
			};
			break;
			case 3:
			{
				CLOSE_PWM();
			};
			break;
			case 4:
			{
				GUI_PutNum(0, 3, angle);
			};
			break;
			case 5:
			{
				GUI_PutNum(3, 1, leftMotorSpeed);
			};
			break;
			case 6:
			{
				GUI_PutNum(3, 2, rightMotorSpeed);
			};
			break;
			case 7:
			{
			};
			break;
			}
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
			BUTTON3_bit = 1;

			if (!getPWM_state())
			{

			}
		}
		else
		{
			BUTTON3_bit = 0;
		}
	}
#endif	
}
