#include "lcd.h"
#include "album.h"
int main()
{
	LCD_Init();
	showpicture();
	int position=0;
	getBmpName("./pictures");
	touch();
	showpicture(bmpPath[position]);
	while(1)
	{
		int move=touch();
		if (move==0)
			break;
		if ((position+move<curBmpNum)&&(position+move>=0))
		{
			position+=move;
			showpicture(bmpPath[position]);
		}
	}
	LCD_Uninit();
	return 0;
}

