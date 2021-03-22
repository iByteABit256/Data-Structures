#include <stdio.h>
#include <stdlib.h>
#include "btreeTypes.h"
#include "queue.h"
#define max(a,b) a > b? a : b

/*
Note:
I use a dummy node for the binary tree, for safety and easier deletion of the tree.
The root of the tree is the right node of the dummy node and the left node is null, so is the item.
The drawback is that there have to be two null checks, in case the given BT node is the dummy node.
*/

BTTree BTcreateTree(int maxelem){
	BTTree dummy = malloc(sizeof(struct btnode));
	dummy->left = NULL;
	dummy->right = NULL;
	dummy->parent = dummy;
	return dummy;
}

int BTisEmpty(BTTree tree){
	if(tree == NULL) return 1;
	else if(tree == tree->parent && tree->right == NULL) return 1;
	else return 0;
}

int BTHeightRec(BTTree tree, int row){
	if(tree->parent == tree) tree = tree->right;
	int r, l;
	if(tree->right == NULL){
		r = row;
	}else{
		r = BTHeightRec(tree->right,row+1);
	}	
	if(tree->left == NULL){
		l = row;
	}else{
		l = BTHeightRec(tree->left,row+1);
	}	
	return max(r,l);	
}

int BTHeight(BTTree tree){
	BTHeightRec(tree, 1);
}

int BTSize(BTTree tree){
	if(tree->parent == tree) tree = tree->right;
	static int n = 0;
	if(tree->right != NULL){
		n++;
		BTSize(tree->right);
	}
	if(tree->left != NULL){
		n++;
		BTSize(tree->left);
	}
	return n+1;
}

BTNode BTgetRoot(BTNode node){
	if(node == NULL) return NULL;
	if(node->parent == node) return node->right;
	if(node == NULL) return NULL;
	while(node->parent->parent != node->parent) node = node->parent;
	return node;
}

BTNode BTgetParent(BTTree tree, BTNode node){
	if(node != NULL){
		if(node->parent == node) node = node->right;
		if(node == NULL) return NULL;
		if(node == BTgetRoot(node)) printf("Error: root has no parents\n");
		return node->parent;
	}
	return NULL;
}

BTNode BTgetLeft(BTTree tree, BTNode node){
	if(node != NULL){
		if(node->parent == node) node = node->right;
		if(node == NULL) return NULL;
		return node->left;
	}
	return NULL;
}

BTNode BTgetRight(BTTree tree, BTNode node){
	if(node != NULL){
		if(node->parent == node) node = node->right;
		if(node == NULL) return NULL;
		return node->right;
	}
	return NULL;
}

int BTisNil(BTTree tree, BTNode node){
	if(node != NULL && node->parent == node) node = node->right;
	if(node == NULL) return 1;
	return 0;
}

BTItem BTgetItem(BTTree tree, BTNode node){
	if(node == NULL){
		printf("Error: NULL node\n");	
		return 0;
	} 
	if(node->parent == node) node = node->right;
	if(node == NULL){
		printf("Error: NULL node\n");	
		return 0;
	} 
	else return node->item;
}

BTTree BTinsertRoot(BTTree tree, BTItem item){
	if(tree->parent != tree){
		printf("Error: tree not empty\n");
		return tree;
	} 
	else{	
		BTTree root = malloc(sizeof(struct btnode));
		root->right = NULL;
		root->left = NULL;
		root->item = item;
		root->parent = tree;
		tree->right = root;
		return tree;
	}
}

BTTree BTinsertLeft(BTTree tree, BTNode node, BTItem item){
	if(node->parent == node) node = node->right;
	if(node->left != NULL){
		printf("Error: left child exists\n");
	}else{
		node->left = BTcreateTree(0);	
		node->left->item = item;
		node->left->parent = node;
	}
	return tree;
}

BTTree BTinsertRight(BTTree tree, BTNode node, BTItem item){
	if(node->parent == node) node = node->right;
	if(node->right != NULL){
		printf("Error: right child exists\n");
	}else{
		node->right = BTcreateTree(0);	
		node->right->item = item;
		node->right->parent = node;
	}
	return tree;
}

void BTRemove(BTTree tree, BTNode node){
	if(node->parent == node) node = node->right;
	if(node->left == NULL && node->right == NULL){	
		BTNode parent = node->parent;
		if(parent->left == node) parent->left = NULL;
		if(parent->right == node) parent->right = NULL;
		free(node);
	}else{
		printf("Error: can't remove node with children\n");
	}
}

BTTree BTChange(BTTree tree, BTNode node, BTItem item){
	if(node != NULL){
		if(node->parent == node) node = node->right;
		if(tree == NULL) return tree;
		node->item = item;
	}
	return tree;
}

void BTPreOrder(BTTree tree, void (*visit)(BTTree tree, BTNode node)){
	if(tree == NULL) return;
	if(tree->parent == tree) tree = tree->right;
	if(tree == NULL) return;
	visit(tree, tree);
	BTPreOrder(tree->left, visit);
	BTPreOrder(tree->right, visit);
}

void BTInOrder(BTTree tree, void (*visit)(BTTree tree, BTNode node)){
	if(tree == NULL) return;
	if(tree->parent == tree) tree = tree->right;
	if(tree == NULL) return;
	BTInOrder(tree->left, visit);
	visit(tree, tree);
	BTInOrder(tree->right, visit);
}

void BTPostOrder(BTTree tree, void (*visit)(BTTree tree, BTNode node)){
	if(tree == NULL) return;
	if(tree->parent == tree) tree = tree->right;
	if(tree == NULL) return;
	BTPostOrder(tree->right, visit);
	BTPostOrder(tree->left, visit);
	visit(tree, tree);
}

void BTLevelOrder(BTTree tree, void (*visit)(BTTree tree, BTNode node)){
	//printf("tree = %d\n", tree->item);
	if(tree == NULL) return;
	if(tree->parent == tree) tree = tree->right;
	//printf("tree 2 = %d\n", tree->item);
	//printf("left = %d\n", tree->left->item);
	//printf("right = %d\n", tree->right->item);
	if(tree == NULL) return;
	queueptr q = createQ();
	enqueue(q, BTgetRoot(tree));	
	//printf("tree 3 = %d\n", tree->item);
	//printf("left = %d\n", tree->left->item);
	//printf("right = %d\n", tree->right->item);
	while(!(empty(q))){
		//printf("q front = %d\n", q->front->value->item);
		BTNode *nodeptr = malloc(sizeof(struct btnode));
		dequeue(q, nodeptr);
		//printf("nodeptr = %d\n", (*nodeptr)->item);
		visit(tree, *nodeptr);
		//if(BTgetLeft(*nodeptr, *nodeptr) != NULL) printf("left = %d\n", (*nodeptr)->left->item);
		//if(BTgetRight(*nodeptr, *nodeptr) != NULL) printf("right = %d\n", (*nodeptr)->right->item);
		if(BTgetLeft(*nodeptr, *nodeptr) != NULL) enqueue(q, BTgetLeft(*nodeptr, *nodeptr));
		if(BTgetRight(*nodeptr, *nodeptr) != NULL) enqueue(q, BTgetRight(*nodeptr, *nodeptr));
	}
}

void BTDestroy(BTTree tree){
	if(tree->parent == tree) tree = tree->right;
	BTPostOrder(tree, BTRemove);
}
