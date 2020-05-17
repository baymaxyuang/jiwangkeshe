#include "util.h"


// 通用的各种工具函数放在util.c里


//记时的函数





//建立队列的的函数和处理队列的若干函数函数
//




//处理初始化参数的函数
void Access_info(int argc, char* argv[], InitialParameters* initial_parameters)
{
	int customize_dns = 0, customize_file = 0;
	if (argc > 1 && argv[1][0] == '-')
	{
		if (argv[1][1] == 'd')
			initial_parameters->debug_information_level = 1; /* Debug level to 1 */
		if (argv[1][2] == 'd')
			initial_parameters->debug_information_level = 2; /* Debug level to 2 */
		if (argc > 2)
		{
			customize_dns = 1; /* If user set the dns server ip address */
			strcpy(initial_parameters->extern_DNS_server_IP_address, argv[2]);
		}
	}

	//使用默认的dns地址
	if (argc == 1 || argc == 2)
		strcpy(initial_parameters->extern_DNS_server_IP_address, "202.106.0.20");

	if (argc > 3)
	{
		customize_file = 1;
		strcpy(initial_parameters->file_path, argv[3]);
	}
	else
		strcpy(initial_parameters->file_path, "dnsrelay.txt");

	printf("Debug level : %d\n", initial_parameters->debug_information_level);
	printf("DNS server : %s\n", initial_parameters->extern_DNS_server_IP_address);
	printf("配置文件 : %s\n", initial_parameters->file_path);
}


//读入对应表的函数
//void Read_data(列表数据结构的地址, char* path)
//{
//
//}
//
////更新对应表的函数，过时的就不要了
//void Update_data()
//{
//	
//}
//
//
////封装好发报函数，（因为socket自己那个函数参数太多了）
////输入：socket、dns报文
////然后就会发报
//
////封装好的接受报文的函数
////输入：队列地址
////就会把收到的存起来
//
//
//
//
//
//
//
//
//
////向控制台输出调试信息的函数
//
//void lprintf()//带时间的日志打印函数，可以套一下链路层那个
//{
//
//}
//
//void Print_debug_info()
//{
//
//}
