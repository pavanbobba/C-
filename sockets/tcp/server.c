#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<dirent.h>
#include<time.h>

#define ERROR -1
#define PORT 54321
#define BUF_SIZE 10000

void * handler(int client_fd)
{
	char buf[BUF_SIZE], name[100];
	int pos;
	DIR *dir = NULL;
	struct dirent * content = NULL;
	struct stat details;
	
	dir = opendir(".");
	if(!dir)
	{
		perror("opendir:");
		return NULL;
	}
	
	while(1)
	{
		memset(buf, '\0', sizeof(buf));
		if(read(client_fd, buf, sizeof(buf)) != ERROR)
		{
			if(!strncmp(buf, "pwd", 3))
			{
				memset(buf, '\0', sizeof(buf));
				if(!getcwd(buf, sizeof(buf)))
				{	
					perror("getcwd:");
					break;
				}
			}
			else if(!strncmp(buf, "ls", 2))
			{
				pos = 0;
				memset(buf, '\0', sizeof(buf));
				memset(&details, 0, sizeof(details));
				memset(&content, 0, sizeof(content));
				while((content = readdir(dir)) != NULL)
				{
					if(stat(content->d_name, &details) != ERROR)
					{
						pos += snprintf(&buf[pos], (strlen(content->d_name) + 1), "%s", content->d_name);
						buf[pos++] = ' ';
						if(content->d_type == DT_DIR)
						{
							pos += snprintf(&buf[pos], 4, "dir");
						}
						else
						{
							pos += snprintf(&buf[pos], 5, "file");
						}
						buf[pos++] = ' ';
						pos += strftime(&buf[pos], 50, "%H:%M:%S %Y-%m-%d", localtime((const time_t *)&details.st_atim));
						buf[pos++] = '\n';
					}
					else
					{
						perror("stat:");
						break;
						break;
					}
				}
			}
			else if(!strncmp(buf, "cd ", 3))
			{
				pos = 3;
				memset(name, '\0', sizeof(name));
				while(buf[pos] != '\n')
				{
					name[pos - 3] = buf[pos++];
				}
				name[pos] = '\0';
				if(!chdir(name))
				{
					memset(buf, '\0', sizeof(buf));
					snprintf(buf, 8, "changed");	
				}
				else
				{
					perror("chdir:");
					break;
				}
			}
			else if(!strncmp(buf, "bye", 3))
			{
				memset(buf, '\0', sizeof(buf));
				snprintf(buf, 17, "please leave...");
				if(write(client_fd, buf, (strlen(buf) + 1)) == ERROR)
				{
					perror("write:");
 				}
				break;
			}
			else
			{
				memset(buf, '\0', sizeof(buf));
				snprintf(buf, 15, "invalid input");
				continue;
			}
			if(write(client_fd, buf, (strlen(buf) + 1)) == ERROR)
			{
				perror("write:");
				break;
			}
		}
		else
		{
			perror("read:");
			break;
		}
	}
	return NULL;
}

int main()
{
	int serv_fd, cli_fd, len;
    struct sockaddr_in serv_addr, cli_addr;
	serv_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(serv_fd != ERROR)
	{
		bzero(&serv_addr, sizeof(serv_addr));

		serv_addr.sin_family = AF_INET;
		serv_addr.sin_port = htons(PORT);
		serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

		if(!bind(serv_fd, (const struct sockaddr *)&serv_addr, sizeof(serv_addr)))
		{
			if(!listen(serv_fd, 10))
			{
				bzero(&cli_addr, sizeof(cli_addr));
				len = sizeof(cli_addr);
				cli_fd = accept(serv_fd, (struct sockaddr *)&cli_addr, (socklen_t *)&len);
				if(cli_fd != ERROR)
				{
					handler(cli_fd);
					close(cli_fd);
				}
				else
				{
					perror("accept:");
				}
			}
			else
			{
				perror("listen:");
			}
		}
		else
		{
			perror("bind:");
		}
	}
	else
	{
		perror("socket:");
	}
		
	return 0;
}
