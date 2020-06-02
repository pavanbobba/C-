#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct my_list{
	int data;
	struct my_list * next;
};
//To create loop condition if required
static int loop_node_var = 0;
static struct my_list * head = NULL;

void PrintList(void)
{
	struct my_list * tmp = NULL;
	
	if(head)
	{
		tmp = head;
		while(tmp)
		{
			printf("%d ", tmp->data);
			tmp = tmp->next;
		}
		printf("\n");
	}
	else
		printf("list is empty\n");
}

void InsertAtEnd(int data)
{
	struct my_list * tmp, * node = NULL;
	if(head)
	{
		tmp = head;
		node = (struct my_list *)malloc(sizeof(struct my_list));
		if(node)
		{
			node->data = data;
			if(!loop_node_var)
				node->next = NULL;
			else
			{
				node->next = head->next->next;
			}
			
			while(tmp->next)
				tmp = tmp->next;
			tmp->next = node;
		}
		else
		{
			perror("malloc:");
		}
	}
	else
	{
		head = (struct my_list *)malloc(sizeof(struct my_list));
		if(head)
		{
			head->data = data;
			head->next = NULL;
		}
		else
		{
			perror("malloc");
		}
	}
	if(!loop_node_var)
		PrintList();
}

void InsertAtHead(int data)
{
	struct my_list *node = NULL;
	if(head)
	{
		node = (struct my_list *)malloc(sizeof(struct my_list));
		if(node)
		{
			node->data = data;
			node->next = head;
			head = node;
		}
		else
		{
			perror("malloc");
		}
		
	}
	else
	{
		head = (struct my_list *)malloc(sizeof(struct my_list));
		if(head)
		{
			head->data = data;
			head->next = NULL;
		}
		else
		{
			perror("malloc");
		}
	}
	PrintList();
}

void DeleteAtEnd(void)
{
	struct my_list * tmp = NULL, *prev = NULL;
	if(head)
	{
		tmp = head;
		while(tmp->next)
		{
			prev = tmp;
			tmp = tmp->next;
		}
		free(tmp);
		if(prev)
			prev->next = NULL;
		else
		{
			head = NULL;
		}
		tmp = NULL;
		PrintList();
	}
	else
	{
		printf("list is empty\n");
	}
}

void DeleteAtHead(void)
{
	struct my_list * tmp = NULL;

	if(head)
	{
		tmp = head;
		free(head);
		head = tmp->next;

		PrintList();
	}
	else
	{
		printf("list is empty\n");
	}	
}

void ReverseList(void)
{
	struct my_list *prev = NULL, *tmp = NULL, *next = NULL;

	if(head)
	{
		tmp = head;
		while(tmp)
		{
			next = tmp->next;
			tmp->next = prev;
			prev = tmp;
			tmp = next;
		}
		head = prev;
		PrintList();
	}
	else
	{
		printf("list is empty\n");
	}
}

void CleanList(void)
{
	struct my_list * tmp = NULL;

	while(head)
	{
		tmp = head;
		free(head);
		head = tmp->next;
	}
	
	PrintList();
}
//creating bugging condition
void CreateLoop()
{
	int loop_node;
	if(head)
	{
		printf("enter node to create loop\n");
		scanf("%d", &loop_node);

		loop_node_var = 1;
		InsertAtEnd(loop_node);
		loop_node_var = 0;
		printf("loop got created\n");
	}
	else
	{
		printf("list empty\n");;
	}
	
}

void RemoveLoop()
{
	struct my_list *ptr = NULL, *ptr_jump = NULL;
	bool loop = false;

	if(head)
	{
		ptr = head;
		ptr_jump = head;

		while((ptr->next) && (ptr_jump->next))
		{
			ptr = ptr->next;
			ptr_jump = ptr_jump->next->next;

			if(ptr == ptr_jump)
			{
				printf("found the loop at the node %d\n", ptr->data);
				loop = true;
				ptr_jump = head;
				while(ptr->next != ptr_jump->next)
				{
					ptr = ptr->next;
					ptr_jump = ptr_jump->next;
				}
				ptr->next = NULL;
				printf("loop got removed\n");
				break;
			}
		}
		if(!loop)
			printf("there is no loop\n");
	}
	else
	{
		printf("list is empty\n");
	}
}

int main()
{
	int opt, node;
	while(1)
	{
		printf("enter the option\n"
			"1.Insert node at end\n"
			"2.Insert node at head\n"
			"3.Delete node at end\n"
			"4.Delete node at head\n"
			"5.Reverse list\n"
			"6.Print list\n"
			"7.Clear list\n"
			"8.Create loop\n"
			"9.Remove loop\n"
			"10.Exit\n");
			
		scanf("%d", &opt);
		switch(opt)
		{
			case 1: printf("enter node\n");
					scanf("%d", &node);
					InsertAtEnd(node);
					break;
			case 2: printf("enter node\n");
					scanf("%d", &node);
					InsertAtHead(node);
					break;
			case 3: DeleteAtEnd();
					break;
			case 4: DeleteAtHead();
					break;
			case 5: ReverseList();
					break;
			case 6: PrintList();
					break;
			case 7: CleanList();
					break;
			case 8: CreateLoop();
					break;
			case 9: RemoveLoop();
					break;
			case 10: CleanList();
					return 0;

			default: printf("invalid option...try again\n");
		}
		
	}
	return 0;
}
