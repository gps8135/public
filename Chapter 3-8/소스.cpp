#include "C:\Users\user\Desktop\0928과제\Common.h"
#define TESTNAME "www.test.com"

/*
struct addrinfo {
   int          ai_flags;           // 추가적인 옵션을 정의 할 때 사용함. 여러 flag를 bitwise OR-ing 하여 넣는다
   int          ai_family;          // address family를 나타냄. AF_INET, AF_INET6, AF_UNSPEC
   int          ai_socktype;        // socket type을 나타냄. SOCK_SREAM, SOCK_DGRAM
   int          ai_protocol;        // IPv4와 IPv6에 대한 IPPROTO_xxx와 같은 값을 가짐.
   socklen_t    ai_addrlen;         // socket 주소인 ai_addr의 길이를 나타냄
   char        *ai_canonname;       // 호스트의 canonical name을 나타냄
   struct sockaddr    *ai_addr;     // socket 주소를 나타내는 구조체 포인터
   struct addrinfo    *ai_next;     // 주소정보 구조체 addrinfo는 linked list이다. 다음 데이터의 포인터
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
		printf("IP 주소(변환 후) = %s\n", inet_ntop(AF_INET6, &addr, str, sizeof(str)));
	}

	WSACleanup();
	return 0;
}