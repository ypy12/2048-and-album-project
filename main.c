#include <pthread.h>
#include <stdio.h>
#include <string.h>
int flag = 1;
//线程函数在创建线程之后就不需要你自动调用了
void *play_music(void *arg)
{
	char buf[100] = {0};
	strcpy(buf, (char *)arg);

	char buf1[200] = {0};
	sprintf(buf1, "madplay %s", buf); //madplay ./1.mp3

	system(buf1); //system("madplay ./1.mp3");
	flag = 0;
}

void main()
{
	printf("12345789fadfadfadsf\n");
		pthread_t thread; //保存线程号
	pthread_create(&thread, NULL, play_music, "./1.mp3");
	pthread_detach(thread);

	while (flag);
		
	printf("123456\n");
}
// int music()
// {
// 	pthread_t thread; //保存线程号
// 	pthread_create(&thread, NULL, play_music, "./1.mp3");
// 	pthread_detach(thread);

// 	while (flag)
// 		;
// 	printf("123456\n");
// }