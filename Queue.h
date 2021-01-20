 
typedef struct{  
	int pid;
	int time;
}Task;


typedef struct node{    
	Task *Task;
	struct node * next;
}Node;

typedef struct{  
	Node *head;
	Node *tail;
}Queue;

int sizeOf(Queue *queue) 
{
  int size = 0;
  if(queue->head == NULL){
    return 0;
  }
  else{
    Node *node = queue->head;
    while(node != NULL){
		  size=size + 1;
      node = node->next;	
	  }	  
    return size; 
  }
}

Task *makeTask(int pid, int time)     
{
	Task * task;
  task = (Task*)malloc(sizeof(Task));
	task->pid = pid;
	task->time = time;
	return task;
}

Node *makeNode(Task *Task)
{
	Node * node;
  node = (Node*)malloc(sizeof(Node));
	node->Task = Task;
	node->next = NULL;
	return node;
}

Queue *makeQueue()  
{
	Queue * queue;
  queue = (Queue*)malloc(sizeof(Queue));
	queue->tail = NULL;
	queue->head = NULL;
	return queue;
}

void enqueue(Queue *queue, Task *Task) 
{
	if(sizeOf(queue) == 0)
	{
		queue->head = makeNode(Task);
		queue->tail = queue->head;	
	}	
	else
	{
		queue->tail->next = makeNode(Task);
		queue->tail = queue->tail->next;	
	}
}

Task *dequeue(Queue *queue)  
{
  if(sizeOf(queue) == 0)
	{
		return NULL;	
	}	
	else
	{
		Node *node = queue->head;
		Task *Task = node->Task;
		queue->head = node->next;
		free(node);
		return Task;	
	}
}


