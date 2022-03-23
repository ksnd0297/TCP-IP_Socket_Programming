#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30
void error_handling(char* message);

int main(int argc, char* argv[])
{
	int serv_sd, clnt_sd;
	FILE* fp;
	char buf[BUF_SIZE];
	int read_cnt;

	struct sockaddr_in serv_adr, clnt_adr;
	socklen_t clnt_adr_sz;

	if(argc != 2) {
		printf("Usage : %s <port> \n", argv[0]);
		exit(1);
	}

	fp = fopen("file_server.c", "rb"); // file_server.c 의 파일 디스크립터
	serv_sd = socket(PF_INET, SOCK_STREAM, 0); // server Socket 생성

	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_adr.sin_port = htons(atoi(argv[1]));

	bind(serv_sd, (struct sockaddr*)&serv_adr, sizeof(serv_adr));
	listen(serv_sd, 5);

	clnt_adr_sz = sizeof(clnt_adr);
	clnt_sd = accept(serv_sd, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);
	// client 소켓을 받아들임 clnt_adr 구조체에 값을 넣음

	while(1)
	{
		read_cnt = fread((void*)buf, sizeof(char), BUF_SIZE, fp);
		printf("read_cnt : %d, BUF_SIZE : %d \n", read_cnt, BUF_SIZE); // 마지막 11Byte
		if(read_cnt < BUF_SIZE) // 마지막 문단은 BUF_SIZE보다 작음
		{
			write(clnt_sd, buf, read_cnt);
			break;
		}
		write(clnt_sd, buf, BUF_SIZE); // 마지막 문단 외에는 BUF_SIZE와 같을 수 있음
	}

	shutdown(clnt_sd, SHUT_WR); // 출력 스트림 종료 EOF 전달
	read(clnt_sd, buf, BUF_SIZE);
	printf("Message from client : %s \n", buf);

	fclose(fp);
	close(clnt_sd); close(serv_sd);
	return 0;
}

void error_handling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
