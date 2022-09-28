#include "C:\Users\user\Desktop\0928과제\Common.h"
/*
typedef struct hostent {
  char  *h_name;
  char  **h_aliases;
  short h_addrtype;
  short h_length;
  char  **h_addr_list;
} HOSTENT, *PHOSTENT, *LPHOSTENT;
*/

//도메인 이름을 인자로 받음

int main(int argc, char* argv[])
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	char* host_name = argv[1];
	HOSTENT* hostPtr = gethostbyname(host_name);


	//입력받은 도메인 이름 출력

	printf("입력받은 도메인 이름 : %s\n\n", host_name);

	// 호스트의 별명
	for (int i = 0; hostPtr->h_aliases[i] != NULL; i++)
	{
		printf("%d 번째 별명 %s\n\n",i+1, hostPtr->h_aliases[i]);
	}

	// IPv4 출력
	for (int i = 0; hostPtr->h_addr_list[i] != NULL; i++)
	{
		printf("%d 번째 ipv4주소 %s\n",i+1, inet_ntoa(*(IN_ADDR*)hostPtr->h_addr_list[i]));
	}

	WSACleanup();
	return 0;
}