#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <arpa/inet.h>
#include<string.h>
#include<unistd.h>

#define ERROR -1
#define PORT 54321

void handler(int client_fd)
{
	char buf[10000];
	
	while(1)
	{
		// printf("server supports 4 commands\t"
		//                 "pwd -> to get present working directory of server\t"
		// 				"ls -> to get the list of contents of directory where server running\t"
		// 				"cd <dir> -> to instruct the server to enter into a directory\t"
		// 				"bye -> to exit the session\n");

		memset(buf, '\0', sizeof(buf));
		printf("message to server:\n\n");
		fgets(buf, sizeof(buf), stdin);
		if(buf != NULL)
		{
			if(write(client_fd, buf, sizeof(buf)) != ERROR)
			{
				printf("\n\nmessage from server:\n\n");
				if(read(client_fd, buf, sizeof(buf)) != ERROR)
				{
					printf("%s\n\n", buf);
					if(!strncmp(buf, "please", 6))
						break;
				}
				else
				{
					perror("read:");
					break;
				}
			}
			else
			{
				perror("write:");
				break;
			}
		}
		else
		{
			perror("fgets:");
			break;
		}
	}
}

int main()
{
	int cli_fd;
    struct sockaddr_in cli_addr;
	cli_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(cli_fd != ERROR)
	{
		bzero(&cli_addr, sizeof(cli_addr));

		cli_addr.sin_family = AF_INET;
		cli_addr.sin_port = htons(PORT);
		cli_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

        if(!connect(cli_fd, (const struct sockaddr *)&cli_addr, sizeof(cli_addr)))
		{
			handler(cli_fd);
			close(cli_fd);
		}
		else
		{
			perror("connect:");
		}
	}
	else
	{
		perror("socket:");
	}
		
	return 0;
}
