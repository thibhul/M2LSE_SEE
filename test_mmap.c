#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//open
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
//close
#include <unistd.h>
//error
#include <errno.h>
//mmap
#include <sys/mman.h>


#define FILE_PATH "/root/MAINTAINERS"

int main(int argc, char const *argv[])
{
	struct stat fileinfo;


	if (stat(FILE_PATH, &fileinfo) < 0) {
		perror("stat");
		exit(EXIT_FAILURE);
	}

	int file_size = (int)fileinfo.st_size;
	int fd = open(FILE_PATH, O_RDONLY);
	printf("%d\n", file_size);
	void* address = mmap(NULL, file_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (!address)
	    exit(EXIT_FAILURE);

	if (madvise(address, file_size, MADV_SEQUENTIAL) < 0) {
	    exit(EXIT_FAILURE);
	}

	int i;
	for (i = 0; i < file_size/sizeof(char); i++) {
	    printf("%c", ((char*)address)[i]);
	}

	munmap(address, file_size);
	close(fd);
	exit(EXIT_SUCCESS);
}
