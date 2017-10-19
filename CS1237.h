#ifndef __CS1237__h__
#define __CS1237__h__
#include <stdio.h>
#include <wiringPi.h>
#define SCK 1
#define DOUT 4
#define SCK_LOW digitalWrite(SCK,0)
#define SCK_HIGN digitalWrite(SCK,1)
//树莓派wiring引脚对应关系如下

//AD转换数值与实际重量的增益
// #include <Python.h>



//初始化
void CS1237Init()
{
	wiringPiSetup();
	pinMode(SCK,OUTPUT);
	pinMode(DOUT,INPUT);
	pullUpDnControl(DOUT,PUD_UP);
	SCK_LOW;
}
//是否转换完毕
int CS1237isReady()
{
	if(digitalRead(DOUT)==0)
	{
		return 1;
	}
	return 0;
}
//配置函数
void CS1237Config()
{
	//no op
}
//一次上升沿
void CS1237ClockUp()
{
	SCK_LOW;
	delayMicroseconds(10);
	SCK_HIGN;
	delayMicroseconds(10);
}
//读数据
int CS1237Read()
{
	int tmp=0;
	int now=0;
	int i;
	int num=100;
	while(!CS1237isReady())
	{
		;
	}
	//SCK_LOW;
	for(i=0;i<23;i++)
	{
		CS1237ClockUp();
		now = digitalRead(DOUT);
		SCK_LOW;		
		//printf("%d,",now );
		tmp *=2;
		tmp = tmp+now;
		
		
	}

	SCK_LOW;
	CS1237ClockUp();
	CS1237ClockUp();
	CS1237ClockUp();
	SCK_LOW;




		return tmp;
}

//得到平均立波得到实际数值
//num：采样次数
int getValue(int num)
{
	int i=0;
	int tmp=0;
	long weight = 0;
	for(i=0;i<num;i++)
	{
		tmp = CS1237Read();
		weight =weight + tmp;
	}
	return weight/num;
}
int getHelp(int num)
{
	return num*3;
}
// PyObject * wrap_getValue(PyObject *self,PyObject *args)
// {
// 	int num;
// 	int weight;
// 	if(!PyArg_ParseTuple(args,"i:getValue",&num))
// 		return NULL;
// 	weight = getValue(num);
// 	return Py_BuildValue("i",weight);
// }
// PyObject * wrap_getHelp(PyObject *self,PyObject *args)
// {
// 	int num;
// 	int weight;
// 	if(!PyArg_ParseTuple(args,"i:getValue",&num))
// 		return NULL;
// 	weight = getHelp(num);
// 	return Py_BuildValue("i",weight);
// }
// static PyMethodDef CS1237Methods[]=
// {
// 	{"getValue",wrap_getValue,METH_VARARGS,"get weignt adc valie"},
// 	{"getHelp",wrap_getHelp,METH_VARARGS,"get help adc valie"},
// 	{NULL,NULL}
// };

// void initCS1237()
// {
// 	PyObject *m;
// 	m = Py_InitModule("CS1237",CS1237Methods);
// }
#endif