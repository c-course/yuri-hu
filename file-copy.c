#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#define SIZE 1024

int main(int args, char *argv[])
{
	char buf[SIZE];
	int fd, f;
	const char *fin = "a.txt";
	const char *fout = "b.txt";
	
	fd = open(fin, O_RDONLY);
	if (fd < 0) {
		perror(fin);
		exit(1);
	}

	f = open(fout, O_CREAT | O_WRONLY, S_IRWXU);
	if (f < 0) {
		perror(fout);
		exit(1);
	}
	
	while (read(fd, buf, 1) > 0)
		write(f, buf, 1);

	close(fd);
	close(f);

	return 0;
}
