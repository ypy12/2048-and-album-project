#include "lcd.h"
#include "album.h"
#include <pthread.h>
#include "xiangce.h"

int flag = 1;
void *play_music1(void *arg)
{
    char buf[100] = {0};
    strcpy(buf, (char *)arg);

    char buf1[200] = {0};
    sprintf(buf1, "madplay %s", buf); //madplay ./1.mp3

    system(buf1); //system("madplay ./1.mp3");
    flag = 0;
}

int xiangce(int *flag_home)
{
    int x, y;
    LCD_Init();
    int position = 0;

    getBmpName("./pictures");
    touch();
    showpicture(bmpPath[position]);
    printf("xiangce");
    while (1)
    {
        pthread_t thread; //保存线程号
        pthread_create(&thread, NULL, play_music1, "./1.mp3");
        pthread_detach(thread);
        printf("%d", &position);
        int move = touch();
        if (move == 0)
            break;
        if ((position + move < curBmpNum) && (position + move >= 0))
        {
            position += move;
            showpicture(bmpPath[position]);

            get_xy(&x, &y);
            //返回上一级
            if (x > 0 && x < 160 * 1.28 && y > 400 * 1.28 && y < 480 * 1.25)
            {
                showpicture("./picture/7.bmp");
                //flag = 0;
                system("pkill madplay"); //system("killall madplay")
                break;
            }
            //返回主界面
            if (x > 640 * 1.28 && x < 800 * 1.28 && y > 400 * 1.25 && y < 480 * 1.25)
            {

                showpicture("./picture/8.bmp");
                //退出游戏，回到主页面
                system("pkill madplay"); //system("killall madplay")
                flag_home=1;
                break;
            }
        }
    }
    LCD_Uninit();
    return 0;
}