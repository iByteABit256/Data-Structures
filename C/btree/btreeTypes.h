#ifndef BT
#define BT

typedef void *BTItem;

#ifdef btree

typedef BTItem *BTTree;
typedef int BTNode;

#else

struct btnode{
	BTItem item;
	struct btnode *left, *right, *parent;
};

typedef struct btnode *BTNode;
typedef BTNode BTTree;
#endif

#endif
