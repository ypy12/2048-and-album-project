/***********************************************************
-  Copyright (C), Ksd xiongzh
-  Filename  : dirve.c
-  Author  :  xiongzh		Date  :  2019-7-31
-  Description  : 
				  1、封装了整个驱动模块的函数
-  Others  :  none
-  Function List  :  
   1.  dirve_led_beff()  ：驱动beef和led
   2.  close_all_led()	 ：关闭所有led
   3.  while_led()	     ：流水灯的线程函数
*************************************************************/

#include "dirve.h"
#include <pthread.h>

/* 关闭所有led */
void close_all_led(int fd3)
{
	ioctl(fd3,LED1,1);
	ioctl(fd3,LED2,1);
	ioctl(fd3,LED3,1);
	ioctl(fd3,LED4,1);
}

void *while_led(void *arg)
{
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,NULL);
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,NULL);
	pthread_detach(pthread_self());
	int fd3 = *((int *)arg);
	while(1)
	{
		ioctl(fd3,LED1,0);
		usleep(250000);
		ioctl(fd3,LED1,1);
		usleep(250000);
		ioctl(fd3,LED2,0);
		usleep(250000);
		ioctl(fd3,LED2,1);
		usleep(250000);
		ioctl(fd3,LED3,0);
		usleep(250000);
		ioctl(fd3,LED3,1);
		usleep(250000);
		ioctl(fd3,LED4,0);
		usleep(250000);
		ioctl(fd3,LED4,1);
	}
}

/***********************************************************
-  Description  :  驱动led和beef
-  Calls  :  show_bmp.c->show_bmp_no_effect()、get_xy.c->get_xy()、ioctl()
			 sleep()
-  Iuput :  1~6、坐标地址 7~8、led和beef的设备文件描述符
-  Return  :  返回节点结构体指针
-  Others  :  none
*************************************************************/
void dirve_led_beff(int *x,int *y,int fd2,int fd3)
{
	int k = 0;
	pthread_t tid;
	show_bmp_no_effect(0,0,"./led_beef.bmp");
	while(1)
	{
		get_xy(x,y);
		/* 1、led1 */
		if(*x  > 32 && *x < 203 && *y > 14 && *y < 106)
		{
			pthread_cancel(tid);
			close_all_led(fd3);
			show_bmp_no_effect(475,143,"./led.bmp");
			sleep(3);
			ioctl(fd3,LED1,1);
			show_bmp_no_effect(0,0,"./led_beef.bmp");
		} 
		/* 2、led2 */
		if(*x > 32 && *x < 203 && *y > 113 &&  *y < 206)
		{
			pthread_cancel(tid);
			close_all_led(fd3);
			for(k=0;k<3;k++)
			{
				ioctl(fd3,LED2,0);
				show_bmp_no_effect(475,143,"./led.bmp");
				sleep(1);
				ioctl(fd3,LED2,1);
				show_bmp_no_effect(0,0,"./led_beef.bmp");
			}
		} 
		//3、led3
		if(*x > 32 && *x < 203 && *y > 212 && *y < 305)
		{
			pthread_cancel(tid);
			close_all_led(fd3);
			for(k=0;k<20;k++)
			{
				ioctl(fd3,LED3,0);
				show_bmp_no_effect(475,143,"./led.bmp");
				usleep(50000);
				ioctl(fd3,LED3,1);
				show_bmp_no_effect(0,0,"./led_beef.bmp");
			}
		} 
		//4、led4
		if(*x > 32 && *x < 203 && *y >309  && *y < 402)
		{
			show_bmp_no_effect(475,143,"./led.bmp");
			pthread_create(&tid, NULL, while_led, (void *)&fd3);
		}
		
		/* 5、蜂鸣器响 */
		if(*x > 583 && *x < 729 && *y >300  && *y < 387)
		{
			pthread_cancel(tid);
			close_all_led(fd3);
			ioctl(fd2,0,1); //响
			show_bmp_no_effect(475,143,"./beef.bmp");
			sleep(1);
			ioctl(fd2,1,1); //不响
			show_bmp_no_effect(0,0,"./led_beef.bmp");
		}
		/* 返回上一界面 */
		if(*x >329 && *x < 453 && *y > 327 && *y < 389)
		{
			pthread_cancel(tid);
			close_all_led(fd3);
			break;
		}	
	}
}