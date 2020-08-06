#include "util.h"

// ͨ�õĸ��ֹ��ߺ�������util.c��

//��ʱ�ĺ���

void Set_time_out(Idconvert* idconvert, int ttl)
{
	idconvert->expire_time = time(NULL) + ttl;
}

int Whether_Expired(Idconvert* idconvert) {
	
	if (idconvert->expire_time > 0 && time(NULL) > idconvert->expire_time)
	{
		return 1;
	}return 0;
}

//�������еĵĺ����ʹ�����е����ɺ�������
//

//�����ʼ�������ĺ���
void Access_info(int argc, char* argv[],
	InitialParameters* initial_parameters)
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

	//ʹ��Ĭ�ϵ�dns��ַ
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
	printf("�����ļ� : %s\n", initial_parameters->file_path);
}

//�����Ӧ��ĺ���
void read_data(const InitialParameters* initial_parameters)
{
	FILE* file;
	int i = 0;
	if ((file = fopen("dnsrelay.txt", "r")) == NULL)
	{
		printf("Failed! Reading file\n");
		return;
	}
		
	char url[max_list_file_path_text], ip[max_IP_address_text];
	while (fscanf(file, "%s %s", ip, url) > 0)
	{
		if (initial_parameters->debug_information_level >= 1)
			printf("Read from 'dnsrelay.txt Url: %s, IP: %s\n", url, ip);
		local_table[i].ip = ip;
		local_table[i].url = url;
		i++;
	}

	fclose(file);

	printf("Read dnsrelay.txt successfully\n");
}
//
////���¶�Ӧ��ĺ�������ʱ�ľͲ�Ҫ��
// void Update_data()
//{
//
//}
//
//
////��װ�÷�������������Ϊsocket�Լ��Ǹ���������̫���ˣ�
////���룺socket��dns����
////Ȼ��ͻᷢ��
//
////��װ�õĽ��ܱ��ĵĺ���
////���룺���е�ַ
////�ͻ���յ��Ĵ�����
//
//
//
//
//
//
//
//
//
////�����̨���������Ϣ�ĺ���
//
// void lprintf()//��ʱ�����־��ӡ������������һ����·���Ǹ�
//{
//
//}
//
// void Print_debug_info()
//{
//
//}

void Add_to_cache(char* url, char* ip) //��cache�и��£�LRU���֣�
{
}

//��ȡ��ǰʱ��
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
	datagram_length = recvfrom(sock, (char*)(&datagram_temp),
		max_datagram_length, 0, &from, &addrlen);
	datagraminfo_temp.addrlen = addrlen;
	datagraminfo_temp.datagram = datagram_temp;
	datagraminfo_temp.datagram_length = datagram_length;
	datagraminfo_temp.from = from;
	datagraminfo_temp.time = get_current_time();
}

int Receive_datagram_to_queue(MyQueue Q, SOCKET sock)
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
