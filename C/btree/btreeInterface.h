#include <stdio.h>
#include <stdlib.h>
#include "btreeTypes.h"

BTTree BTcreateTree(int maxelem);

int BTisEmpty(BTTree tree);

int BTHeightRec(BTTree tree, int row);

int BTHeight(BTTree tree);

int BTSize(BTTree tree);

BTNode BTgetRoot(BTTree tree);

BTNode BTgetParent(BTTree tree, BTNode node);

BTNode BTgetLeft(BTTree tree, BTNode node);

BTNode BTgetRight(BTTree tree, BTNode node);

int BTisNil(BTTree tree, BTNode node);

BTItem BTgetItem(BTTree tree, BTNode node);

BTTree BTinsertRoot(BTTree tree, BTItem item);

BTTree BTinsertLeft(BTTree tree, BTNode node, BTItem item);

BTTree BTinsertRight(BTTree tree, BTNode node, BTItem item);

void BTRemove(BTTree tree, BTNode node);

BTTree BTChange(BTTree tree, BTNode node, BTItem item);

void BTPreOrder(BTTree tree, void (*visit)(BTTree tree, BTNode node));

void BTInOrder(BTTree tree, void (*visit)(BTTree tree, BTNode node));

void BTPostOrder(BTTree tree, void (*visit)(BTTree tree, BTNode node));

void BTLevelOrder(BTTree tree, void (*visit)(BTTree tree, BTNode node));

void BTDestroy(BTTree tree);

void printNode(BTTree tree, BTNode node);
