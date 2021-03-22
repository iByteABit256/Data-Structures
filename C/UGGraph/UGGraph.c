#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "UGGraphInterface.h"
#define inf 100000
#define maxWord 40

char *UGGetValue(UGVertex v){
	if(v == NULL) return NULL;
	return ((UGVertex)v)->value;
}

Listptr UGGetAdjacent(UGGraph graph, char *vertex){
	UGVertex *v = malloc(sizeof(UGVertex));
	if(!HTGet(graph, vertex, (HTItem *)v)) return NULL;
	Listptr adjacent = ((UGVertex)*v)->adjacent;
	free(v);
	return adjacent;
}

UGVertex UGGetVertex(UGGraph graph, char *vertex){
	UGVertex *v = malloc(sizeof(UGVertex));
	if(!HTGet(graph, vertex, (HTItem *)v)) return NULL;
	UGVertex res = (UGVertex)*v;
	free(v);
	return res;
}

UGGraph UGCreate(void){
	UGGraph graph = HTCreate();
	return graph;
}

void UGAddVertex(UGGraph graph, char *vertex){
	UGVertex ver = malloc(sizeof(struct ugvertex));	
	ver->value = vertex;	
	ver->adjacent = ListCreate();
	if(HTInsert(graph, vertex, ver) == NULL) free(ver);
}

void UGRemoveVertex(UGGraph graph, char *vertex){
	UGVertex *ver = malloc(sizeof(UGVertex));
	if(HTGet(graph, vertex, (HTItem *)ver)){
		ListDestroy(((UGVertex)*ver)->adjacent);
		free(*ver);
		HTRemove(graph, vertex);
	}
	free(ver);
}

void UGAddEdge(UGGraph graph, char *vertex1, char *vertex2){
	UGVertex *v1 = malloc(sizeof(UGVertex));
	UGVertex *v2 = malloc(sizeof(UGVertex));
	if(!HTGet(graph, vertex1, (HTItem *)v1) || !HTGet(graph, vertex2, (HTItem *)v2)) return;
	
	if(ListSearch(((UGVertex)*v1)->adjacent, *v2) == NULL) 
		ListInsertLast(((UGVertex)*v1)->adjacent, *v2); 	
	if(ListSearch(((UGVertex)*v2)->adjacent, *v1) == NULL) 
		ListInsertLast(((UGVertex)*v2)->adjacent, *v1); 
	free(v1);
	free(v2);
}

void UGRemoveEdge(UGGraph graph, char *vertex1, char *vertex2){
	UGVertex *v1 = malloc(sizeof(UGVertex));
	UGVertex *v2 = malloc(sizeof(UGVertex));
	if(!HTGet(graph, vertex1, (HTItem *)v1) || !HTGet(graph, vertex2, (HTItem *)v2)) return;

	Listptr l = ListSearch(((UGVertex)*v1)->adjacent, *v2);
	if(l != NULL){
		ListDelete(l->head, l);
	}

	l = ListSearch(((UGVertex)*v2)->adjacent, *v1);
	if(l != NULL){
		ListDelete(l->head, l);
	}
	free(v1);
	free(v2);
}

void UGVisitAdjacent(UGGraph graph, char *vertex, void (*visit)(UGGraph, char *)){
	Listptr l = UGGetAdjacent(graph, vertex);
	if(l == NULL) return;
	for(l = l->head->next; l != l->tail; l = l->next){
		visit(graph, ((UGVertex)l->value)->value);
	}
}

void HTVisitLinked(HTHash hash, int i, void (*visit)(UGGraph, char *)){
	Listptr l = hash->ht[i];
	for(l = l->head->next; l != l->tail;){
		Listptr temp = l->next;
		visit(hash, ((UGVertex)l->value)->value);
		l = temp;
	}
}

void UGDestroy(UGGraph graph){
	int size = graph->curSize;
	for(int i = size-1; i >= 0; i--){
		HTVisitLinked(graph, i, UGRemoveVertex); 
	}
	HTDestroy(graph);
}

char *minKey(UGGraph graph, HTHash shortest, HTHash visited){
	int min = inf;
	char *res = malloc(sizeof(char *));
	for(int i = 0; i < graph->curSize; i++){
		for(Listptr l = graph->ht[i]->next; l != l->tail; l = l->next){
			int *temp = malloc(sizeof(int *));
			int *vis = malloc(sizeof(int *));
			HTGet(shortest, UGGetValue(l->value), (HTItem *)temp);
			HTGet(visited, UGGetValue(l->value), (HTItem *)vis);
			if(*vis){
				free(vis);
				free(temp); 
				continue;
			}
			free(vis);
			if(*temp <= min){
				min = *temp;
				strcpy(res, UGGetValue(l->value));
			}
			free(temp);
		}
	}
	return res;
}

Listptr UGShortestPath(UGGraph graph, char *vertex1, char *vertex2){
	//printf("[Debug] Graph size = %d\n", graph->curSize);
	clock_t start = clock();
	Listptr shortestPath = ListCreate();
	HTHash visited = HTCreate();
	HTHash shortest = HTCreate();
	HTHash previous = HTCreate();
	for(int i = 0; i < graph->curSize; i++){
		for(Listptr l = graph->ht[i]->next; l != l->tail; l = l->next){
			HTInsert(visited, UGGetValue(l->value), (HTItem)0);
			HTInsert(shortest, UGGetValue(l->value), (HTItem)inf);
			HTInsert(previous, UGGetValue(l->value), (HTItem)NULL);
		}
	}
	HTInsert(shortest, vertex1, (HTItem)0);

	clock_t end = clock();
	//printf("[Debug] Time taken for creation of hashtables = %3.5f\n", ((double)end-start)/CLOCKS_PER_SEC);
	
	start = clock();
	//printf("[Debug] -DIJKSTRA BEGINS-\n");
	char *minkey = (char *)malloc(sizeof(char)*maxWord);
	int loops = 0;
	double time = 0;
	while(1){
		clock_t looptime = clock();
		minkey = (char *)minKey(graph, shortest, visited);	
		if(!strcmp(minkey, vertex2)) break;
		HTInsert(visited, minkey, (HTItem)1);	
		Listptr adj = UGGetAdjacent(graph, minkey);
		for(adj = adj->next; adj != adj->tail; adj = adj->next){
			int *vis = malloc(sizeof(int *));
			HTGet(visited, UGGetValue(adj->value), (HTItem *)vis);
			if(*vis){
				free(vis);
				continue;
			}
			free(vis);
			int *minsh = malloc(sizeof(int *));
			int *adjsh = malloc(sizeof(int *));
			HTGet(shortest, UGGetValue(adj->value), (HTItem *)adjsh);	
			HTGet(shortest, minkey, (HTItem *)minsh);	
			if(*minsh+1 < *adjsh){
				HTInsert(shortest, UGGetValue(adj->value), (HTItem)(*minsh+1));
				HTInsert(previous, UGGetValue(adj->value), (HTItem)(minkey));
			}
			free(minsh);
			free(adjsh);
		}
		clock_t looptime_end = clock();
		time += ((double)looptime_end-looptime)/CLOCKS_PER_SEC;
		loops++;
	}
	//printf("[Debug] Loop time = %3.5f\n", time/(double)loops);
	//printf("[Debug] Loops = %d\n", loops);
	free(minkey);

	end = clock();
	//printf("[Debug] -DIJKSTRA ENDS-\n");
	//printf("[Debug] Time taken for Djikstra = %3.5f\n", ((double)end-start)/CLOCKS_PER_SEC);

	start = clock();
	ListInsertLast(shortestPath, vertex2);
	char **pr = malloc(sizeof(char *));
	char *str = malloc(maxWord*sizeof(char));
	strcpy(str, vertex2);
	HTGet(previous, str, (HTItem *)pr);
	while(*pr != NULL){
		ListInsertLast(shortestPath, *pr);
		strcpy(str, *pr);
		HTGet(previous, str, (ItemType)pr);
	} 
	free(pr);
	free(str);

	end = clock();
	//printf("[Debug] Time taken for creation of shortest path = %3.5f\n", ((double)end-start)/CLOCKS_PER_SEC);

	start = clock();
	HTDestroy(visited);
	HTDestroy(shortest);
	HTDestroy(previous);

	end = clock();
	//printf("[Debug] Time taken for deletion of hash tables = %3.5f\n", ((double)end-start)/CLOCKS_PER_SEC);
	return shortestPath;
}
