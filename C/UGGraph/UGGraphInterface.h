#include "UGGraphTypes.h"
UGGraph UGCreate(void);
void UGAddVertex(UGGraph, char *);
void UGRemoveVertex(UGGraph, char *);
void UGAddEdge(UGGraph, char *, char *);
void UGRemoveEdge(UGGraph, char *, char *);
void UGDestroy(UGGraph);
Listptr UGShortestPath(UGGraph, char *, char *);
UGVertex UGGetVertex(UGGraph, char *);
char *UGGetValue(UGVertex);
Listptr UGGetAdjacent(UGGraph, char *);
