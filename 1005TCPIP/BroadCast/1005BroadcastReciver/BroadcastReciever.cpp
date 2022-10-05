#include "C:\Users\com426\Documents\KIM\common.h"
#define LOCALPORT 9000
#define BUFSIZE 512

int main(int argc, char* argv[]) {
	int retval;
	WSAData wsa;
	if(WSAStartup(MAKEWORD(2,2), &wsa)!=0)
		return 0;


	SOCKET sock= socket(AF_INET, SOCK_DGRAM,0);
	if(sock==INVALID_SOCKET) err_quit("SOCKET ERR");

	struct sockaddr_in localaddr;
	memset(&localaddr,0,sizeof(localaddr));
	localaddr.sin_family=AF_INET;
	localaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	localaddr.sin_port = htons(LOCALPORT);
	retval = bind(sock, (struct sockaddr*)&localaddr, sizeof(localaddr));
	if (retval == SOCKET_ERROR) err_quit("bind err");


	struct sockaddr_in peeraddr;
	int addrlen;
	char buf[BUFSIZE + 1];

	while (1) {
		addrlen = sizeof(peeraddr);
		retval = recvfrom(sock, buf,BUFSIZE, 0, (struct sockaddr*)&peeraddr, &addrlen);
		if (retval == SOCKET_ERROR) {
			err_display("RECVFROM ERR");
			break;
		}
		buf[retval] = '\0';
		char addr[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &peeraddr.sin_addr, addr, sizeof(addr));
		printf("%s, %d  %s\n", addr, ntohs(peeraddr.sin_port), buf);

	}


	closesocket(sock);
	WSACleanup();
	return 0;
}
