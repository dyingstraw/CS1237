
#include "CS1237.h"
static double CS1237P = 0.0078742;
int main()
{
	int tmp,Orign;
	printf("hello rasp  %s\n","dsc" );
	//初始化CS1237
	CS1237Init();
	//得到初试点（0点校正）
	Orign = getValue(200);
	printf("Orign value is %d\n", Orign);
	while(1)
	{
		tmp = getValue(100);
		printf("now is %lf\n", (tmp-Orign)*CS1237P);
		delay(500);
	}
}


