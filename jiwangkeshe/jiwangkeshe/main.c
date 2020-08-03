#include"util.h"
#include<windows.h>   //�����̺߳�����Ҫ����ϵͳ����
#include<process.h>   //�����̺߳���ͷ�ļ�


int main(int argc, char* argv[])
{
	//��������ʼ�����֣�
	//�Կ���̨��������Ԥ����
	//���ݿ���̨����������Ӧ���������õ�����Ϣ�ȼ���������ԴDNS������IP��ַ������
	Access_info(argc, argv, &init);

	for (int i = 0; i < ID_TABLE_SIZE; i++)
	{
		idconvert[i].origin_id = 0;
		idconvert[i].have_check = TRUE;
		idconvert[i].expire_time = 0;
		memset(&(idconvert[i].client), 0, sizeof(SOCKADDR_IN));
	}

	WSAStartup(MAKEWORD(2, 2), &wsaData);			//��ʼ��ws2_32.dll��̬���ӿ�
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

	//��ʼ�������׽��֣��ֱ����ں��û��Լ���ԴDNS������ͨ��
	local_name.sin_family = AF_INET;            /* Set the family as AF_INET (TCP/IP) */
	local_name.sin_addr.s_addr = INADDR_ANY;    /* Set to any */
	local_name.sin_port = htons(DNS_PORT);      /* Set the port as DNS port (53) */

	extern_name.sin_family = AF_INET;                         /* Set the family as AF_INET (TCP/IP) */
	extern_name.sin_addr.s_addr = inet_pton(init.extern_DNS_server_IP_address);   /* Set to the IP of extern DNS server */
	extern_name.sin_port = htons(DNS_PORT);

	int reuse = 1;
	setsockopt(local_socket, SOL_SOCKET, SO_REUSEADDR, (const char*)&reuse, sizeof(reuse));//�����׽��ֵ�ѡ��,������ֱ��ض˿ڱ�ռ�����
	//�󶨱����׽���

	if (bind(local_socket, (struct sockaddr*) & local_name, sizeof(local_name)) < 0)
	{
		if (init.debug_information_level >= 1)
			printf("Bind socket port failed.\n");
		exit(1);
	}

	printf("Bind socket port successfully.\n");
	//��ʼ�����ĺ���Ϣ���У����ڻ������ԴDNS�������յ��ı��ļ������Ϣ
	//��ʼ�����ĺ���Ϣ���У����ڻ�����û��յ��ı����Լ��û��ĵ�ַ�������Ϣ
	datagram_info_queue_for_extern_DNS_server = Create_Queue(max_datagram_info_queue_size);
	datagram_info_queue_for_user = Create_Queue(max_datagram_info_queue_size);

	HANDLE Thread2 = 0;       //�̵߳ķ��ʾ��
	unsigned ThreadID = 1;
	//�̱߳�ʶ��,���ñ�����ֵ����ֻ��ΪNULL
	Thread2 = _beginThreadex(NULL, 0, Serve_for_ThreadII, NULL, 0, &ThreadID);
    //�����ڶ��̣߳���֤�����û�����ԴDNS�������ĵı��ĺ����ݿ��Լ�ʱ�յ������ܵ��������Ӧ�ı��
	
	WaitForSingleObject(Thread2, INFINITE);//�ȴ��߳̽���
	CloseHandle(Thread2);//��������߳�ʱɾ���˾�����ɷ�ֹ�ں˶���й¶��
	
	int event = 0;
	
	//dns����������Э�鲿�֣�
	while (exception_flag == 0)//���쳣
	{
		//event = Wait_for_enent();
		//���¼��ȴ����н����¼���Ϣ��Ԥ�����Ϣ�����У��յ���ԴDNS���������ģ��յ��û����ģ���ԴDNS��������ʱ�ȵ�

		switch (event)
		{
		default:
			break;
		}
		//�Բ�ͬ����ֱ���


		//���Զ�Ӧ����ά��
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
