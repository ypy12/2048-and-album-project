#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
 
#include <sys/mman.h>
 
int * plcd;
//全局变量，代表映射后的首地址
 
/*
函数的功能：在指定的点显示一个指定的颜色
函数参数：
@x:你指定的点的横坐标
@y:你指定的点的纵坐标
@color:你指定的颜色
函数的返回值：无
*/
void lcd_draw_point(int x,int y,int color)
{
	if(x>=800 || y>= 480)
	{
		printf("you point out the lcd\n");
		return ;//仅代表函数结束
	}
	*(plcd+800*y+x) = color;
}
 
//清屏
void lcd_clear(int color)
{
	int x,y;
	for(y=0;y<480;y++)
	{
		for(x=0;x<800;x++)
		{
			lcd_draw_point(x,y,color);
		}
	}
}
 
 
//显示一张指定的图片到指定的位置
/*
name:图片名字
x0,y0:起始位置
w,h:图片的大小
*/
void lcd_draw_bmp(char *name,int x0,int y0)
{
	//打开图片，把图片中的像素数据拿出来，关闭图片
	int fd_bmp = open(name,O_RDWR);
	if(-1 == fd_bmp)
	{
		printf("open bmp error\n");
		return ;
	}
 
	int size;
	int w,h;
	//定位文件的光标
	char buf[4]={0};
	lseek(fd_bmp,0x02,SEEK_SET);
	read(fd_bmp,buf,4);
	size = (buf[0]) | (buf[1]<<8) | (buf[2]<<16) | (buf[3]<<24);
	
	lseek(fd_bmp,0x12,SEEK_SET);
	read(fd_bmp,buf,4);
	w = (buf[0]) | (buf[1]<<8) | (buf[2]<<16) | (buf[3]<<24);
	
	lseek(fd_bmp,0x16,SEEK_SET);
	read(fd_bmp,buf,4);
	h = (buf[0]) | (buf[1]<<8) | (buf[2]<<16) | (buf[3]<<24);
	
	lseek(fd_bmp,0x1C,SEEK_SET);
	read(fd_bmp,buf,2);
	int color_depth = (buf[0]) | (buf[1]<<8);
	
	printf("size = %d,w = %d,h = %d\n",size,w,h);
	printf("color_depth = %d\n",color_depth);
	
	//光标偏移到像素数据处
	lseek(fd_bmp,0x36,SEEK_SET);
	char pixel[w*h*(color_depth/8)];
	read(fd_bmp,pixel,w*h*(color_depth/8));
	close(fd_bmp);
	
	//把像素点数据合成颜色
	char a,b,g,r;
	int color;
	int x,y;
	int i = 0;
	for(y=0;y<abs(h);y++)
	{
		for(x=0;x<w;x++)
		{
			b = pixel[i++];
			g = pixel[i++];
			r = pixel[i++];
			a = (color_depth == 32)?pixel[i++]:0;
			color = (a<<24)|(r<<16) | (g<<8) | b;
			//把颜色显示到屏幕上面
			int dy = (h<0)? (y+y0):(y0+h-1-y);
			
			lcd_draw_point(x+x0,dy,color);
		}
		if(w*(color_depth/8)%4 != 0)
		{
			i+= 4-(w*(color_depth/8)%4);
		}	
	}
	
}

 
int main()
{	
	//打开屏幕
	int fd = open("/dev/fb0",O_RDWR);
	if(-1 == fd)
	{
		printf("open lcd error\n");
		return 0;
	}
	
	//映射内存
	plcd = mmap(NULL,800*480*4, PROT_WRITE | PROT_READ,MAP_SHARED,fd,0);
	if(plcd == MAP_FAILED)
	{
		printf("map error\n");
		return 0;
	}
	//操作屏幕
	lcd_draw_bmp("/pic.bmp",16,16);
	//解映射
	munmap(plcd,800*480*4);
	//关闭
	close(fd);
	return 0;
}