#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
	int status;
	pid_t pid = fork();

	if(pid == 0)
	{
//		sleep(30);
		return 3;
	}
	else {
		wait(&status);
		if(WIFEXITED(status))
			printf("Child Send : %d \n", WEXITSTATUS(status));
	}
	return 0;
}

