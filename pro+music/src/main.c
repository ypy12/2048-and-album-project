/***********************************************************
-  Copyright (C), Ksd xiongzh
-  Filename  : main.c
-  Author  :  xiongzh		Date  :  2019-7-31
-  Description  :  主函数的实现文件
				   几个LED灯的宏定义
				   还有全局变量的定义	
				   
-  Others  :  包含了一些所需的头文件
-  Function List  :  
   1. main.c :  整个项目的实现
*************************************************************/

#include <stdio.h>
#include <linux/input.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <pthread.h>
#include "get_xy.h"
#include "list.h"
#include "game_func.h"
#include <dirve.h>
#include <square.h>
#include <pthread.h>

/* 定义个存放音乐名图片的数组 */
char *music_bmp[3] = {"music1.bmp", "music2.bmp", "music2.bmp"};

/* 定义一个指针数组，存放2048游戏中的2~2018图片的路径 */
char *bmp_name[] = {"./2_2048/2.bmp", "./2_2048/4.bmp", "./2_2048/8.bmp", "./2_2048/16.bmp",
					"./2_2048/32.bmp", "./2_2048/64.bmp", "./2_2048/128.bmp", "./2_2048/256.bmp",
					"./2_2048/512.bmp", "./2_2048/1024.bmp", "./2_2048/2048.bmp"};
/* 定义一个指针数组，存放2048游戏中的分数图片路径 */
char *score_bmp[] = {"./score/score0.bmp", "./score/score1.bmp", "./score/score2.bmp", "./score/score3.bmp", "./score/score4.bmp",
					 "./score/score5.bmp", "./score/score6.bmp", "./score/score7.bmp", "./score/score8.bmp", "./score/score9.bmp"};

int flag_music=0;
/* 释放所有堆内存 */
void free_heap(PTO head, SQ_P *sq_buf, TEMP_P temp_head);

		void *play_music(void *arg)
		{      	
			char buf[100] = {0};
			strcpy(buf, (char*)arg);
			
			char buf1[200] = {0};
			sprintf(buf1, "madplay %s", buf); //madplay ./1.mp3
			
			system(buf1);  //system("madplay ./1.mp3");
			flag_music= 0;
		}
int main(int argc, char **argv)
{
	/* 判断主函数是否传参，参数为相册图片目录路径名 */
	if (argc != 2)
	{
		printf("Usage: %s <dir>\n", argv[0]);
		exit(1);
	}

	pthread_t music_tid; // 定义一个线程id

	int x, y; // 定义触摸获取的坐标值

	signal(SIGINT, black_lcd);


	int i, j, k; // 定义几个循环要用到的整数
	/* 定义四个用来标志的整数 */
	int flag = 1, flag1 = 0, flag2 = 0, flag3 = 0;

	/* 把相片名存入链表 */
	PTO head = NULL;
	head = get_pto(head, &argv[1]); // from getpto.c
	PTO pos=head;

	//  /* 把音乐名存入链表 */
	// char *mus_dir = "./music/";
	//  MUS mus_head = NULL;
	//  mus_head = get_mus(mus_head, &mus_dir); // from getpto.c
	//  MUS mus_temp = NULL;					// 定义一个音乐链表中间节点变量
	//  mus_temp = mus_head;
	//  char buf[20]; // 定义一个system指令缓冲区
	//  bzero(buf, 20); 
	//  /* 定义一个中间变量节点指向存储照片的链表头*/

	int fd = open("./1.txt",O_RDWR | O_CREAT);
	/* 初始化方阵 */
	
	SQ_P bmp_head = square_init(); // from square.c

	// /*从文件中读取数据存入sq方阵中,如果不是空文件返回1 */
	// if (read_sq_from_file(bmp_head, fd4))
	// {
	// 	/* 文件不为空就给一些标志位赋值，用于后面的随机图片是否可以产生 */
	// 	flag = 0;
	// 	flag3 = 1;
	// }
	/* 初始化一条中间方阵链表,用来保存2048上一步 */
	TEMP_P temp_head = init_temp_list(); // from square.c

	/* 为了提高产生随机值时查找插入的效率而定义的结构体数组 */
	SQ_P sq_buf[] = {sq_1, sq_2, sq_3, sq_4,
					 sq_5, sq_6, sq_7, sq_8,
					 sq_9, sq_10, sq_11, sq_12,
					 sq_13, sq_14, sq_15, sq_16};

	PTO temp = calloc(1, sizeof(pto)); // 定义一个结构体，为了保存相册进度

	while (1)
	{
		show_bmp_no_effect(0, 0, "./thouch1.bmp");
		printf('dddd');
		/* 获取触摸屏的坐标 */
		get_xy(&x, &y); // from get_xy.c
        

			pthread_t thread;	//保存线程号
			pthread_create(&thread, NULL, play_music, "./1.mp3");
			pthread_detach(thread);
			
			while(flag_music);
			printf("123456899342\n");
		
		
		/* 进入相册 */
		if (321 > x && x > 111 && y > 41 && y < 183)
		{
			
		
			pthread_t thread;	//保存线程号
			pthread_create(&thread, NULL, play_music, "./1.mp3");
			pthread_detach(thread);
			
			while(flag_music);
			printf("123456\n");
			
			/* 进来先读取进度 */
			  
			int ret = read(fd, temp, sizeof(pto));
			if (ret == 0)
			{
				// 如果进度文件是空的，就不读取
				temp = head;
			}
			else
			{
				/* 找到保存的是哪一张图片 */
				while (pos->next != head)
				{
					if (!strcmp(temp->pname, pos->pname))
					{
						temp = pos;
						flag2 = 1;
						break;
					}
					pos = pos->next;
				}
				if (flag2 == 0)
					temp = pos;
			}
			/* 显示相册背景 */
			show_bmp_no_effect(0, 0, "./touch1.bmp");

			/* 显示照片 */
			show_bmp(65, 30, temp->pname);
			while (1)
			{
				/* 每次滑屏或者，点击按键后都写入文件一次 */
				lseek(fd, 0, SEEK_SET);
				write(fd, temp, sizeof(pto));

				get_xy(&x, &y);

				/* 存放相片的一个双向循环链表，切换时只需要让中间变量指向当前的前或后节点就ok */
				/* 下一张 */
				if ((x > 650 && x < 800) && (y > 0 && y < 83))
				{
					temp = temp->next;
					show_bmp(65, 30, temp->pname);
				}
				/* 上一张 */
				if ((x > 650 && x < 800) && (y > 205 && y < 283))
				{
					temp = temp->bef;
					show_bmp(65, 30, temp->pname);
				}
				/* 返回主界面 */
				if ((x > 650 && x < 800) && (y > 394 && y < 480))
				{
					break;
				}
			}
		}

		/* 退出程序 */
		if (x > 486 && x < 678 && y > 387 && y < 458)
		{
			black_lcd(); // from show_bmp.c
			break;
		}
	}
	//释放堆空间
	free_heap(head, sq_buf, temp_head);
	bmp_head = NULL;
	return 0;
}
void free_heap(PTO head, SQ_P *sq_buf, TEMP_P temp_head)
{
	int i, j, k;
	PTO p = NULL;
	PTO pos = NULL;
	/* 释放相片链表堆内存 */
	for (p = head->bef, pos = p->bef; pos != head; pos = pos->bef, p = pos->next)
	{
		free(p);
		p = NULL;
	}
	free(p);
	free(pos);
	head = NULL;
	/* 释放方阵堆内存 */
	for (i = 0; i < 16; i++)
	{
		free(sq_buf[i]->name);
		free(sq_buf[i]);
	}
	/* 释放中间链表堆内存 */
	TEMP_P p1 = NULL;
	TEMP_P pos1 = NULL;
	for (p1 = temp_head, pos1 = p1->next; p1->next != NULL; pos1 = p1->next)
	{
		p1->next = pos1->next;
		free(pos1->name);
		free(pos1);
	}
	free(p1);
}