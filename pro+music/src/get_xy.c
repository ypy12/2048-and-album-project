/***********************************************************
-  Copyright (C), Ksd xiongzh
-  Filename  : get_xy.c
-  Description  : 
				  1、获取坐标
-  Others  :  none
-  Function List  :  
   1.  get_xy() : 获取坐标，以及获取滑屏时的起始坐标和结束坐标
*************************************************************/

#include "get_xy.h"
#include <stdio.h>
#include <fcntl.h>	
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <linux/input.h>
#include <sys/mman.h>

/***********************************************************
-  Description  :  获取坐标
-  Calls  :  open()、read()、
-  Iuput :  需要获取的坐标值的地址
-  Return  :  none
-  Others  :  需要注意的事，没按一下屏幕是会读取8次时间，也就是循环八次
*************************************************************/
void get_xy(int* x,int* y)
{
	int num_x,num_y;
    struct input_event ev;
	int touch_fd = open("/dev/input/event0", O_RDONLY);
		if(touch_fd < 0)
		{
			perror("fail");
		}
		while(1)
		{
			read(touch_fd, &ev, sizeof(ev));
			if(ev.type == EV_ABS && ev.code == ABS_X)
				num_x = ev.value;
			else if(ev.type == EV_ABS && ev.code == ABS_Y)
				num_y = ev.value;	

			if(ev.type == EV_KEY && ev.code == BTN_TOUCH)
				if(ev.value == 1)
					printf("press\n");
				else
				{
					*x =num_x;
					*y =num_y;
					break;
				}
			
		}	
		printf("(%d,%d)\n",num_x,num_y);
		close(touch_fd);

}
