#include "util.h"


// 通用的各种工具函数放在util.c里


//记时的函数

void Set_time_out()



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
void read_data()
{
	FILE* file;
	int i = 0;
	if ((file = fopen("dnsrely.txt", "r")) == NULL)
		return;
	char url[max_list_file_path_text], ip[max_IP_address_text];
	while (fscanf(file, "%s %s", ip, url) > 0) {
		if (debug_information_level >= 1)
			printf("Read from 'dnsrelay.txt Url: %s, IP: %s\n", url, ip);
		local_table[i].ip = ip;
		local_table[i].url = url;
		i++;
	}
	fclose(file);
}
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

void Add_to_cache(string* url, string* ip) //向cache中更新（LRU部分）
{

}

//信息队列相关操作,共六个

Queue Create_Queue(int MaxSize)
{
	Queue Q = (Queue)malloc(sizeof(struct queue));
	Q->Front = Q->Rear = NULL;
	Q->MaxSize = MaxSize;
	Q->CurrentSize = 0;
}

void Delete_Queue(Queue Q)
{
	DataGramInfo temp;
	while (!QIs_empty(Q))
	{
		Out_Queue(Q, &temp);
	}
	free(Q);
}

int In_Queue(Queue Q, DataGramInfo datagram_info)
{
	if (QIs_full(Q))
	{
		return 0;//表示入队失败
	}
	else
	{
		PtrToQNode temp = (PtrToQNode)malloc(sizeof(struct QNode));
		temp->datagram_info = datagram_info;
		temp->Next = NULL;
		Q->CurrentSize += 1;
		
		if (QIs_empty(Q))
		{
			Q->Front = temp;
			Q->Rear = temp;
			
		}
		else
		{
			Q->Rear->Next = temp;
			Q->Rear = temp;
		}
		return 1;
	}

}
int Out_Queue(Queue Q,DataGramInfo *datagram_info_ptr)
{
	if (QIs_empty(Q))
	{
		return 0;//表示出队失败
	}
	else
	{
		*datagram_info_ptr = Q->Front->datagram_info;
		Q->CurrentSize -= 1;
		if (Q->Front == Q->Rear)
		{
			free(Q->Front);
			Q->Front = Q->Rear = NULL;		
		}
		else
		{
			PtrToQNode temp = Q->Front;
			Q->Front = Q->Front->Next;
			free(temp);
		}
		return 1;
	}
}

int QIs_full(Queue Q)
{
	return (Q->CurrentSize == Q->MaxSize) ? 1 : 0;
}

int QIs_empty(Queue Q)
{
	return (Q->Front == NULL) ? 1 : 0;
}

//获取当前时间
long long get_current_time()
{




	return 0;
}

DataGramInfo Receive_datagram(SOCKET sock)
{
	DataGramInfo datagraminfo_temp;
	DataGram datagram_temp;
	int datagram_length;
	SOCKADDR from;
	int addrlen;
	datagram_length = recvfrom(sock, (char *)(&datagram_temp), max_datagram_length, 0, &from, &addrlen);
	datagraminfo_temp.addrlen = addrlen;
	datagraminfo_temp.datagram = datagram_temp;
	datagraminfo_temp.datagram_length = datagram_length;
	datagraminfo_temp.from = from;
	datagraminfo_temp.time = get_current_time();
}




int Receive_datagram_to_queue(Queue Q, SOCKET sock)
{
	if (QIs_full(Q))
	{
		return 0;
	}
	else
	{
		DataGramInfo datagraminfo_temp;
		datagraminfo_temp = Receive_datagram(sock);
		In_Queue(Q, datagraminfo_temp);
	}
}
