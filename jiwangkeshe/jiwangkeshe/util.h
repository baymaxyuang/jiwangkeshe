#include<stdio.h>
#include<winsock2.h>

#pragma once
#pragma comment(lib,"wsock32.lib")

#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define max_IP_address_text 20 //IP ��󳤶�
#define max_list_file_path_text 200// url ��󳤶�
#define ID_TABLE_SIZE 20 //url-ip �����������
#define DEBUG_OFF 0
#define DEBUG_I 1
#define DEBUG_II 2
#define DNS_PORT 53
#define max_datagram_length 512
#define max_datagram_info_queue_size 500
#define max_time_to_out 10 //���ó�ʱʱ��Ϊ10s
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
	char extern_DNS_server_IP_address[max_IP_address_text];//�մ�˵��û������
	char file_path[200];//�մ�˵��û������
}InitialParameters;

typedef struct Idconvert {
	unsigned short origin_id;
	int expire_time;//��ʱ����
	int have_check;
	SOCKADDR client;
}Idconvert;

typedef struct{
	my_byte data[max_datagram_length];
}DataGram;



typedef struct{
	DataGram datagram;//���ݱ�����
	int datagram_length;
	SOCKADDR from;//���ݱ���Դ�ĵ�ַ
	int addrlen;//���ݱ���ַ�ĳ���
	long long time;//�յ����ݱ���ʱ���
	
}DataGramInfo ;


//���ݰ���Ϣ�������

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
//����Ҫ�洢��Ϣ�Ľṹ�壨���ļӷ����ߵ�ַbulabula��������


Queue Create_Queue(int MaxSize);
void Delete_Queue(Queue Q);
int In_Queue(Queue Q, DataGramInfo datagram_info);
int Out_Queue(Queue Q, DataGramInfo *datagram_info_ptr);
int QIs_full(Queue Q);
int QIs_empty(Queue Q);

//����ͨ�ŵ�ȫ�ֱ�����
int current_event = 0;//�������̺߳͵ڶ��߳�ͨ��


char extern_DNS_server_IP_address[max_IP_address_text] = "202.106.0.20"; //��ԴDNS������IP��ַ
int exception_flag = 0; //�쳣��ǣ����쳣ʱ�ᱻ��1

InitialParameters init;
//�м̹���ʱ��idת����
Idconvert idconvert[ID_TABLE_SIZE];
//������Ϣ�洢��ȫ�ֱ�����
//��ʼʱ����Ķ�Ӧ�����һֱ����
//��̬���µĶ�Ӧ����Ϣ

//���ĺ���Ϣ����
Queue datagram_info_queue_for_user;
Queue datagram_info_queue_for_extern_DNS_server;