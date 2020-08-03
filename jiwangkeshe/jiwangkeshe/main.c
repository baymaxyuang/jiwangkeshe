#include"util.h"
#include<windows.h>   //创建线程函数需要操作系统函数
#include<process.h>   //创建线程函数头文件


int main(int argc, char* argv[])
{
	//服务器初始化部分：
	//对控制台参数进行预处理
	//根据控制台参数做出反应，包括设置调试信息等级，设置外源DNS服务器IP地址，读入
	Access_info(argc, argv, &init);

	for (int i = 0; i < ID_TABLE_SIZE; i++)
	{
		idconvert[i].origin_id = 0;
		idconvert[i].have_check = TRUE;
		idconvert[i].expire_time = 0;
		memset(&(idconvert[i].client), 0, sizeof(SOCKADDR_IN));
	}

	WSAStartup(MAKEWORD(2, 2), &wsaData);			//初始化ws2_32.dll动态链接库
	local_socket = socket(AF_INET, SOCK_DGRAM, 0);
	extern_socket = socket(AF_INET, SOCK_DGRAM, 0);

	int non_block = 1;
	ioctlsocket(local_socket, FIONBIO, (u_long FAR*)&non_block);
	ioctlsocket(extern_socket, FIONBIO, (u_long FAR*)&non_block);

	if (local_socket < 0)
	{
		if (init.debug_information_level >= 1)
			printf("Create local socket failed.\n");
		exit(1);
	}

	//初始化两个套接字，分别用于和用户以及外源DNS服务器通信
	local_name.sin_family = AF_INET;            /* Set the family as AF_INET (TCP/IP) */
	local_name.sin_addr.s_addr = INADDR_ANY;    /* Set to any */
	local_name.sin_port = htons(DNS_PORT);      /* Set the port as DNS port (53) */

	extern_name.sin_family = AF_INET;                         /* Set the family as AF_INET (TCP/IP) */
	extern_name.sin_addr.s_addr = inet_pton(init.extern_DNS_server_IP_address);   /* Set to the IP of extern DNS server */
	extern_name.sin_port = htons(DNS_PORT);

	int reuse = 1;
	setsockopt(local_socket, SOL_SOCKET, SO_REUSEADDR, (const char*)&reuse, sizeof(reuse));//设置套接字的选项,避免出现本地端口被占用情况
	//绑定本地套接字

	if (bind(local_socket, (struct sockaddr*) & local_name, sizeof(local_name)) < 0)
	{
		if (init.debug_information_level >= 1)
			printf("Bind socket port failed.\n");
		exit(1);
	}

	printf("Bind socket port successfully.\n");
	//初始化报文和信息队列，用于缓存从外源DNS服务器收到的报文及相关信息
	//初始化报文和信息队列，用于缓存从用户收到的报文以及用户的地址等相关信息
	datagram_info_queue_for_extern_DNS_server = Create_Queue(max_datagram_info_queue_size);
	datagram_info_queue_for_user = Create_Queue(max_datagram_info_queue_size);

	HANDLE Thread2 = 0;       //线程的访问句柄
	unsigned ThreadID = 1;
	//线程标识号,不用变量赋值，则只能为NULL
	Thread2 = _beginThreadex(NULL, 0, Serve_for_ThreadII, NULL, 0, &ThreadID);
    //开启第二线程，保证来自用户和外源DNS服务器的的报文和数据可以及时收到，且受到后会有相应的标记
	
	WaitForSingleObject(Thread2, INFINITE);//等待线程结束
	CloseHandle(Thread2);//无须控制线程时删除此句柄，可防止内核对象泄露。
	
	int event = 0;
	
	//dns服务器的主协议部分：
	while (exception_flag == 0)//无异常
	{
		//event = Wait_for_enent();
		//从事件等待器中接受事件信息，预设的信息类型有：收到外源DNS服务器报文，收到用户报文，外源DNS服务器超时等等

		switch (event)
		{
		default:
			break;
		}
		//对不同情况分别处理


		//最后对对应表做维护
		//Update_data();


	}		
	

	

	return 0;

}


void Serve_for_ThreadII()
{


}

//int Wait_for_enent()
//{
//	int event = 0;
//	
//	
//	
//	return event;
//}
