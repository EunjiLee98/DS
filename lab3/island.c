#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {

	void * buffer ;
	int unit ;
	int capacity ;
	int front ;
	int rear ;
	int full ;

} queue ;

typedef struct {

	bool visited;
	int land;

} cell;

typedef struct {

	int x;
	int y;
} pos;

queue * create_queue (int capacity, int unit) 
{
	queue * que = malloc(sizeof(queue)) ;
	que->capacity = capacity ;
	que->unit = unit ;
	que->buffer = calloc(capacity, unit) ;
	que->front = 0 ;
	que->rear = 0 ;
	que->full = 0 ;
	return que ;
}

void delete_queue (queue * que) 
{
	if (que->buffer != 0x0)
		free(que->buffer) ;
	free(que) ;
}

int enqueue (queue * que, void * elem)
{
	if (is_full(que))
		return 1 ;

	memcpy(que->buffer + ((que->rear) * (que->unit)), elem, que->unit) ;
	que->rear = (que->rear + 1) % que->capacity ;

	if (que->rear == que->front)
		que->full = 1 ;

	return 0 ;
}

int dequeue (queue * que, void * elem)
{
	if (is_empty(que)) 
		return 1 ;

	memcpy(elem, que->buffer + que->front * que->unit, que->unit) ;
	que->front = (que->front + 1) % que->capacity ;	
	que->full = 0 ;

	return 0;
}

int is_empty (queue * que) 
{
	return (que->front == que->rear) && (que->full == 0) ;
}

int is_full (queue * que) 
{
	return que->full ;
}

/*void print_queue (queue * que, void (* print_element)(void * elem)) 
{
	int i ;
	if (que->front == que->rear && que->full == 0)
		return ;

	for (i = que->front ; i != que->rear ; i = (i + 1) % (que->capacity)) {
		printf("[") ;
		print_element(que->buffer + i * que->unit) ;
		printf("] ") ;
	}
	printf("\n") ;
}

void print_int (void * p)
{
	int * elem = (int *) p ; 
	printf("%d", *elem) ;
}

void print_array (cell (*arr)[8], int h, int w)
{
	for(int i=0; i<h; i++)
	{
		for(int j=0; j<w; j++)
		{
			printf("%d ",arr[i][j].land);
		}
		printf("\n");
	}
}*/
const int d[4][2] = {{0,-1}, {-1,0}, {0,1}, {1,0}} ;

int main()
{
	int height,width;
	int island_size = 0;
	int count = 0;
	int max_size = 0, min_size = 100;

	scanf("%d %d\n",&width,&height);

	cell island[height][width];

	for(int i=0; i<height; i++)
	{
		for(int j=0; j<width; j++)
		{
			scanf("%d ",&island[i][j].land);
			island[i][j].visited = false;
		}
	
		scanf("\n");
	}

//	print_array(island,height,width);

	queue * que;
	que = create_queue((height * width), sizeof(pos));

	for(int i=0; i<height; i++)
	{
		for(int j=0; j<width; j++)
		{
			if(island[i][j].land == 1 && island[i][j].visited == false)
			{
			
				island_size = 0; 
				count += 1;
				pos cur;
				cur.x = j;
				cur.y = i;
				enqueue(que, &cur);
				island[i][j].visited = true;
				while(!dequeue(que,&cur))
				{
					island_size += 1;
					for(int z = 0; z < 4; z++)
					{
						int y = cur.y + d[z][0];
						int x = cur.x + d[z][1];

						if( 0 <= y && y < height &&
							0 <= x && x < height )
						{
							if(island[y][x].land == 1 && 
							   island[y][x].visited == false){
								pos newPos;
								newPos.x = x;
								newPos.y = y;
								enqueue(que, &newPos);
								island[y][x].visited = true;
							}	
						}
					}
				}
				if(island_size > max_size)
					max_size = island_size;

				if(island_size < min_size)
					min_size = island_size;
			
			}
		}
	}
	printf("%d %d %d\n",count, min_size, max_size);
//	print_queue(que, print_int) ;

	delete_queue(que) ;
	return 0 ;
}
