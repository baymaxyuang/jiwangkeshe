#define max_IP_address_text 20 //IP地址字符串的最大长度
#define max_list_file_path_text 200//IP地址表路径字符串的最大长度


#define DEBUG_OFF 0
#define DEBUG_I 1
#define DEBUG_II 2

typedef struct {
	int debug_information_level;
	char extern_DNS_server_IP_address[max_IP_address_text];//空串说明没有填入
	char file_path[max_list_file_path_text];//空串说明没有填入

}InitialParameters;


//队列要存储信息的结构体（报文加发信者地址bulabula。。。）