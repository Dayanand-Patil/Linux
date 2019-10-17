/* File descriptor test */

#include <stdio.h>
#include <fcntl.h>

int main()
{
	int fd;
        size_t size, 
	printf("Pid : %d\n", getpid());
	getchar();

	perror("can u seem me\n ");
	close(2);
	perror("Stderr: can u see me\n");
	printf("stderr closed\n");
	getchar();

	close(1);
	printf("can you see this\n");
	getchar();

	fd = open("./linux.mp4", O_RDONLY);
	perror("OPEN: \n");
	printf("%s:  file descriptor no %d\n", __func__,fd);
	getchar(); 

}
