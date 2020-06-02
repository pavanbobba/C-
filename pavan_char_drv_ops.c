#include<stdio.h>
#include<string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "/home/pavan/C/drivers/include/pavan_chrdev_ioctl.h"

#define MY_DEV_FILE_NAME "/dev/pavan_char_dev1"
int main()
{
	int fd = -1;int ret = 0;
	char buf_write[50] = "hi ra how are you?";
	char buf_read[50];
	
	memset(buf_read, '\0', sizeof(buf_read));
	fd = open(MY_DEV_FILE_NAME, O_RDWR);
	if(fd != -1)
	{
		ret = write(fd, buf_write, sizeof(buf_write));
		printf("write returned %d\n", ret);
		ret = lseek(fd, 0, SEEK_SET);
		printf("lseek returned %d\n", ret);
		ret = read(fd, buf_read, sizeof(buf_read));
		printf("data from buffer: %s\n", buf_read);
		printf("fread returned %d\n", ret);
		//ioctl
		ret = 0;
		ioctl(fd, ERASE_BUF);//erasing kernel buffer
		ioctl(fd, GET_FILE_POS, &ret);
		printf("file position returned is %d\n", ret);
		
		close(fd);
	}
	else
		perror("open:");
	return 0;
}
