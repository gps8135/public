#include "C:\Users\com426\Documents\KIM\common.h"

#define SERVERPORT 9000
#define BUFSIZE 1024

int main(int argc, char* argv[]) {
	int retval;

	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	//UDP 소켓생성 (DGRAM)
	SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock == INVALID_SOCKET) err_quit("socket() err");

	//bind

	struct sockaddr_in serveraddr;
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = bind(sock, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("bind() err");

	//통신변수

	struct sockaddr_in clientaddr;
	int addrlen;
	char buf[BUFSIZE + 1];
	
	//통신

	while (1) {
		//데이터 수신
		addrlen = sizeof(clientaddr);
		retval = recvfrom(sock, buf, BUFSIZE, 0, (struct sockaddr*)&clientaddr, &addrlen);
		if (retval == SOCKET_ERROR) {
			err_display("recvfrom() err");
			break;
		}
		//수신데이터 출력
		buf[retval] = '\0';
		char addr[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &clientaddr.sin_addr, addr, sizeof(addr));
		printf("%s, %d %s \n", addr, ntohs(clientaddr.sin_port), buf);

		//데이터 송신

		retval = sendto(sock, buf, retval, 0, (struct sockaddr*) & clientaddr, sizeof(clientaddr));
		if (retval == SOCKET_ERROR) {
			err_display("sendto() err");
			break;
		}
	}

	//소켓종료
	closesocket(sock);
	WSACleanup();
	return 0;
}