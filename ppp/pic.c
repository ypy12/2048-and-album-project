#include "lcd.h"
#include "album.h"
int main()
{
	char dirpath="\\pictures\\"
	LCD_Init();
	showpicture();
	int position=0
	getBmpName(dirPath);
	touch()
	showpicture(bmpPath[position]);
	while(1)
	{
		int move=touch()
		if (position+move<curBmpNum)&(position+move>=0)
		{
			position+=move;
			showpicture(bmpPath[position]);
		}
	}
	LCD_Uninit();
	return 0;
}

