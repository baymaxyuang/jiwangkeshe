#define max_IP_address_text 20 //IP��ַ�ַ�������󳤶�
#define max_list_file_path_text 200//IP��ַ��·���ַ�������󳤶�


#define DEBUG_OFF 0
#define DEBUG_I 1
#define DEBUG_II 2

typedef struct {
	int debug_information_level;
	char extern_DNS_server_IP_address[max_IP_address_text];//�մ�˵��û������
	char file_path[max_list_file_path_text];//�մ�˵��û������

}InitialParameters;


//����Ҫ�洢��Ϣ�Ľṹ�壨���ļӷ����ߵ�ַbulabula��������