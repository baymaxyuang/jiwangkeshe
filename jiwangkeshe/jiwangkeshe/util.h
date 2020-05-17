#pragma comment(lib,"wsock32.lib")
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define max_IP_address_text 20 //IP地址字符串的最大长度
#define max_list_file_path_text 200//IP地址表路径字符串的最大长度
#define ID_TABLE_SIZE 20
#define DEBUG_OFF 0
#define DEBUG_I 1
#define DEBUG_II 2
#define DNS_PORT 53

#include<stdio.h>
#include<winsock2.h>

typedef struct InitialParameters {
	int debug_information_level;
	char extern_DNS_server_IP_address[max_IP_address_text];//空串说明没有填入
	char file_path[max_list_file_path_text];//空串说明没有填入
}InitialParameters;
typedef struct Idconvert {
	unsigned short origin_id;
	int expire_time;//超时处理
	int have_check;
	SOCKADDR client;
}Idconvert;

void Access_info(int argc, char* argv[], InitialParameters* initial_parameters);

WSADATA wsaData;
SOCKET local_socket, extern_socket;
SOCKADDR_IN local_name, extern_name;
//队列要存储信息的结构体（报文加发信者地址bulabula。。。）
