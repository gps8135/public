#include "C:\Users\user\Desktop\0928����\Common.h"
#define TESTNAME "www.test.com"

/*
struct addrinfo {
   int          ai_flags;           // �߰����� �ɼ��� ���� �� �� �����. ���� flag�� bitwise OR-ing �Ͽ� �ִ´�
   int          ai_family;          // address family�� ��Ÿ��. AF_INET, AF_INET6, AF_UNSPEC
   int          ai_socktype;        // socket type�� ��Ÿ��. SOCK_SREAM, SOCK_DGRAM
   int          ai_protocol;        // IPv4�� IPv6�� ���� IPPROTO_xxx�� ���� ���� ����.
   socklen_t    ai_addrlen;         // socket �ּ��� ai_addr�� ���̸� ��Ÿ��
   char        *ai_canonname;       // ȣ��Ʈ�� canonical name�� ��Ÿ��
   struct sockaddr    *ai_addr;     // socket �ּҸ� ��Ÿ���� ����ü ������
   struct addrinfo    *ai_next;     // �ּ����� ����ü addrinfo�� linked list�̴�. ���� �������� ������
};  
*/

BOOL GetIPAddr6(char* name, IN6_ADDR* addr)
{
	ADDRINFOA hints;
	ADDRINFOA* res;
	ZeroMemory(&hints, sizeof(ADDRINFOA));
	hints.ai_family = AF_INET6;

	int ret = getaddrinfo(TESTNAME, NULL, &hints, &res);
	if (ret != 0)
	{
		printf("getaddrinfo: %s\n", gai_strerrorA(ret));
	}
	memcpy(addr, res->ai_addr, res->ai_addrlen);
	return TRUE;
}

int main(int argc, char* argv[])
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	IN6_ADDR addr;
	if (GetIPAddr6(TESTNAME, &addr))
	{
		char str[128];
		printf("IP �ּ�(��ȯ ��) = %s\n", inet_ntop(AF_INET6, &addr, str, sizeof(str)));
	}

	WSACleanup();
	return 0;
}