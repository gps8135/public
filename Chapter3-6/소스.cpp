#include "C:\Users\user\Desktop\0928����\Common.h"
/*
typedef struct hostent {
  char  *h_name;
  char  **h_aliases;
  short h_addrtype;
  short h_length;
  char  **h_addr_list;
} HOSTENT, *PHOSTENT, *LPHOSTENT;
*/

//������ �̸��� ���ڷ� ����

int main(int argc, char* argv[])
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	char* host_name = argv[1];
	HOSTENT* hostPtr = gethostbyname(host_name);


	//�Է¹��� ������ �̸� ���

	printf("�Է¹��� ������ �̸� : %s\n\n", host_name);

	// ȣ��Ʈ�� ����
	for (int i = 0; hostPtr->h_aliases[i] != NULL; i++)
	{
		printf("%d ��° ���� %s\n\n",i+1, hostPtr->h_aliases[i]);
	}

	// IPv4 ���
	for (int i = 0; hostPtr->h_addr_list[i] != NULL; i++)
	{
		printf("%d ��° ipv4�ּ� %s\n",i+1, inet_ntoa(*(IN_ADDR*)hostPtr->h_addr_list[i]));
	}

	WSACleanup();
	return 0;
}