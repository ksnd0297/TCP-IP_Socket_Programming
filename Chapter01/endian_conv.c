#include <stdio.h>
#include <arpa/inet.h>

int main(int argc, char* argv[])
{
	unsigned short host_port = 0x3412; // Big Endian
	unsigned short net_port; // Little Endian
	unsigned long host_addr = 0x12345678; // Big Endian
	unsigned long net_addr; // Little Endian

	net_port = ntohs(host_port);
	net_addr = htonl(host_addr);

	printf("Host ordered port : %#x \n", host_port);
	printf("Network ordered port : %#x \n", net_port);
	printf("Host ordered address : %#lx \n", host_addr);
	printf("Network ordered address : %#lx \n", net_addr);
	return 0;
}

