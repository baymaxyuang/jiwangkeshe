#include<stdio.h>
#include"util.h"

//用于通信的全局变量：
int current_event = 0;//用于主线程和第二线程通信

int debug_information_level = DEBUG_OFF;//调试信息等级
char extern_DNS_server_IP_address[max_IP_address_text]="202.106.0.20"; //外源DNS服务器IP地址
int exception_flag = 0; //异常标记，有异常时会被置1


//用于信息存储的全局变量：
//初始时读入的对应表，这个一直保留
//动态更新的对应表信息



int main(int argc, char* argv[])
{
	//服务器初始化部分：

	//对控制台参数进行预处理


	//根据控制台参数做出反应，包括设置调试信息等级，设置外源DNS服务器IP地址，读入

	//初始化两个套接字，分别用于和用户以及外源DNS服务器通信
	
	//初始化报文和信息队列，用于缓存从外源DNS服务器收到的报文及相关信息

	//初始化报文和信息队列，用于缓存从用户收到的报文以及用户的地址等相关信息

	//开启第二线程，保证来自用户和外源DNS服务器的的报文和数据可以及时收到，且受到后会有相应的标记
	//这个主要是为第一线程提供“接受事件信息”的

	
	int event = 0;
	
	//dns服务器的主协议部分：
	while (exception_flag == 0)//无异常
	{
		event = Wait_for_enent();
		//从事件等待器中接受事件信息，预设的信息类型有：收到外源DNS服务器报文，收到用户报文，外源DNS服务器超时等等

		switch (event)
		{
		default:
			break;
		}
		//对不同情况分别处理


		//最后对对应表做维护
		Update_data();


	}
	

	return 0;

}


void Serve_for_ThreadII(两个套接字，两个队列的地址)
{

}

int Wait_for_enent()
{
	int event = 0;
	
	
	
	return event;
}