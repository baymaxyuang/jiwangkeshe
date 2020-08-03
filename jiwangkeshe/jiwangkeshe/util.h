#include<stdio.h>
#include<winsock2.h>

#pragma once
#pragma comment(lib,"wsock32.lib")

#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define max_IP_address_text 20 //IP 最大长度
#define max_list_file_path_text 200// url 最大长度
#define ID_TABLE_SIZE 20 //url-ip 表中最大行数
#define DEBUG_OFF 0
#define DEBUG_I 1
#define DEBUG_II 2
#define DNS_PORT 53
#define max_datagram_length 512
#define max_datagram_info_queue_size 500
#define max_time_to_out 10 //设置超时时间为10s
#define RECEIVE_DATAGRAM_FROM_USERS 1
#define RECEIVE_DATAGRAM_FROM_EXTERN 2


typedef char my_byte;


typedef struct table{
	char* ip;
	char* url;
}table;
table local_table[ID_TABLE_SIZE];

typedef struct InitialParameters {
	int debug_information_level;
	char extern_DNS_server_IP_address[max_IP_address_text];//空串说明没有填入
	char file_path[200];//空串说明没有填入
}InitialParameters;

typedef struct Idconvert {
	unsigned short origin_id;
	int expire_time;//超时处理
	int have_check;
	SOCKADDR client;
}Idconvert;

typedef struct{
	my_byte data[max_datagram_length];
}DataGram;



typedef struct{
	DataGram datagram;//数据报内容
	int datagram_length;
	SOCKADDR from;//数据报来源的地址
	int addrlen;//数据报地址的长度
	long long time;//收到数据报的时间戳
	
}DataGramInfo ;


//数据包信息缓存队列

typedef struct QNode* PtrToQNode;
struct QNode {
	DataGramInfo datagram_info;
	PtrToQNode Next;
};
typedef struct queue* Queue;
struct queue{
	PtrToQNode Front, Rear;
	int MaxSize;
	int CurrentSize;
};



void Access_info(int argc, char* argv[], InitialParameters* initial_parameters);
void Serve_for_ThreadII();
WSADATA wsaData;
SOCKET local_socket, extern_socket;
SOCKADDR_IN local_name, extern_name;
//队列要存储信息的结构体（报文加发信者地址bulabula。。。）


Queue Create_Queue(int MaxSize);
void Delete_Queue(Queue Q);
int In_Queue(Queue Q, DataGramInfo datagram_info);
int Out_Queue(Queue Q, DataGramInfo *datagram_info_ptr);
int QIs_full(Queue Q);
int QIs_empty(Queue Q);

//用于通信的全局变量：
int current_event = 0;//用于主线程和第二线程通信


char extern_DNS_server_IP_address[max_IP_address_text] = "202.106.0.20"; //外源DNS服务器IP地址
int exception_flag = 0; //异常标记，有异常时会被置1

InitialParameters init;
//中继功能时的id转换表
Idconvert idconvert[ID_TABLE_SIZE];
//用于信息存储的全局变量：
//初始时读入的对应表，这个一直保留
//动态更新的对应表信息

//报文和信息队列
Queue datagram_info_queue_for_user;
Queue datagram_info_queue_for_extern_DNS_server;