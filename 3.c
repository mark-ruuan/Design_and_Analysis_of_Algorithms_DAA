#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
typedef struct
{
	int src, dest, weight;
}Edge;

typedef struct
{
	int v,e;
	Edge* edge;
}Graph;

Graph* createGraph(int v, int e)
{
	Graph* graph = (Graph*)malloc(sizeof(Graph));
	graph->v = v;
	graph->e = e;
	graph->edge = (Edge*)malloc(e*sizeof(Edge));
	return graph;
}



void bellmanFord(Graph *graph, int src)
{
	int v = graph->v;
	int e = graph->e;
	int i;
	int *dist = (int *)malloc(v*sizeof(int));
	int flag  = 0;
	for(int i =0; i < v; ++i)
		dist[i] = INT_MAX;
	
	dist[src] = 0;
	for( i = 1; i <= v-1; ++i)
	{
		
		flag = 0;
		for(int j = 0; j < e; ++j)
		{
			int src = graph->edge[j].src;
			int dest = graph->edge[j].dest;
			int weight = graph->edge[j].weight;
			if(dist[src] != INT_MAX && dist[src] + weight < dist[dest])
			{
				dist[dest] = dist[src] + weight;
				flag = 1;	
			}
			
			
		}
		if(!flag)
			break;
	}
	flag = 0;
    if(i == v-1)
    {
    	for (int i = 0; i < e; i++) 
   	 	{ 
			int src = graph->edge[i].src;
			int dest = graph->edge[i].dest;
			int weight = graph->edge[i].weight;			
        	if (dist[src] != INT_MAX && dist[src] + weight < dist[dest])
        	{ 
            	flag = 1;
            	break;
            }
    	} 
    }   
    if(!flag)
    {
    	printf("Source    Destination  \t\tDistance\n");
    	for(int i = 0; i < v; ++i)
    	{
    		if(dist[i] != INT_MAX)
    			printf("%d\t\t%d\t\t%d\n",src+1,i+1,dist[i]);
    		else
    			printf("%d\t\t%d\t\t-\n",src+1,i+1);    		
    	}	 
    }
    else
    	printf("There is a negative weight cycle\n");
    free(dist);
}
int main()
{
	int v,e;
	printf("Enter the no of vertex: ");
	scanf("%d",&v);
	while(v < 2){
		printf("The no of vertices should be atlest 2\n");
		printf("Enter the no of vertex: ");
		scanf("%d", &v);
	}
	printf("Enter the no of edges: ");
	scanf("%d",&e);
	while(e < 0 || e > v * v - v){
		printf("No of edges must be positive and maximum no of edges must be %d\n", v * v - v);
		printf("Enter the no of edges: ");
		scanf("%d",&e);
	}
	Graph* graph = createGraph(v,e);
	int src, dest, weight;

	for(int i = 0; i < e; )
	{
		int chk = 0;
		int u,t,w;
		printf("Enter the source : ");
		scanf("%d",&u);
		//printf("%d\n", u);
		printf("Enter the destination : ");
		scanf("%d",&t);
		//printf("%d\n", t);
		if( u >= 1 && u <=v && t >= 1 && t <= v)
		{
			
			graph->edge[i].src = u-1;
			graph->edge[i].dest = t-1;
			
			
			for(int j = 0; j < i; ++j)
			{
				if(graph->edge[i].src == graph->edge[j].src && graph->edge[i].dest == graph->edge[j].dest)
				{
					chk = 1;
					break;	
				}
			}
			if(chk)
				printf("Duplicate edge entered, please re-enter\n");
			else
			{
				printf("Enter the weight: ");
				scanf("%d",&graph->edge[i].weight );
				//printf("%d\n", graph->edge[i].weight);
				i++;	
			}
		}
		else
			printf("Invalid vertex enterd \n");

	}
	printf("\nEnter the source vertex:");
	scanf("%d",&src);
	//printf("%d\n", src);
	printf("\n");
	bellmanFord(graph,src-1);
	free(graph);
	

}
