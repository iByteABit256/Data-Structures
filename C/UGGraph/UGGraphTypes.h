#include "lists.h"
#include "htInterface.h"

struct ugvertex{
	char *value;
	Listptr adjacent;
};

typedef struct ugvertex *UGVertex;

/*struct uggraph{
	int size;
	UGVertex *vertices;
};*/

typedef HTHash UGGraph;
