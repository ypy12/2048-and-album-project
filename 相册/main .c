#include "lcd.h"
#include "album.h"
int main()
{
	dirpath="./pictures"
	LCD_Init();
	showpicture();
	position=0
	getBmpName(dirPath);
	touch()
	showpicture(bmpPath[position]);
	while(1)
	{
		int move=touch()
		if (bmpPath[position+move]!=NULL)
		{
			position+=move;
			showpicture(bmpPath[position]);
		}
	}
	LCD_Uninit();
	return 0;
}

