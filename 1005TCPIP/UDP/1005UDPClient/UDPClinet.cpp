#include "C:\Users\com426\Documents\KIM\common.h"
#define SERVERPORT 9000
#define BUFSIZE 1024
char* SERVERIP = (char*)"127.0.0.1";

int main(int argc, char* argv[]) {
	int retval;
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2,2), &wsa) != 0)
		return 1;

	//UDP ���� ����(DGRAM)
	
	SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock == INVALID_SOCKET) err_quit("socket() err");

	//���� �ּ� ����ü
	
	struct sockaddr_in serveraddr,myaddr;
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	inet_pton(AF_INET, SERVERIP, &serveraddr.sin_addr);
	serveraddr.sin_port = htons(SERVERPORT);

	int serverlen;
	serverlen = sizeof(serveraddr);
	//��ź���
	int addrlen;
	struct sockaddr_in peeraddr;
	char buf[BUFSIZE + 1];
	int len;
	getsockname(sock, (struct sockaddr*)&myaddr,&serverlen);
	printf("Port    : %d\n", ntohs(myaddr.sin_port));
	printf("address : %s\n", inet_ntoa(myaddr.sin_addr));

	//���
	while (1) {
		//�Է�
		printf("�Էµ�����\n");
		if (fgets(buf, BUFSIZE + 1, stdin) == NULL)
			break;
		
		len = (int)strlen(buf);
		if (buf[len - 1] == '\n')
			buf[len - 1] = '\0';
		if (strlen(buf) == 0)
			break;

		//������ �۽�

		retval = sendto(sock, buf, (int)strlen(buf), 0, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
		if (retval == SOCKET_ERROR) {
			err_display("snedto() err");
			break;
		}

		printf("%d ����Ʈ �۽�\n", retval);

		//������ ����
		addrlen = sizeof(peeraddr);
		retval = recvfrom(sock, buf, BUFSIZE, 0, (struct sockaddr*) & peeraddr, &addrlen);
		if (retval == SOCKET_ERROR) {
			err_display("recvfrom() err");
			break;
		}
		buf[retval] = '\0';
		printf("%d ����Ʈ ����\n", retval);
		printf("����:%s\n", buf);

		}


	closesocket(sock);
	WSACleanup();
	return 0;
}



