#ifndef omh
#define omh
#include"ab.h"

extern int const omDptLim;
extern int omDptCount,omNodeCount;

void OmSearch(treeNode*);

treeNode* OmMax(treeNode*);

treeNode* OmMin(treeNode*);

// treeNode* generateMove(treeNode*);
// treeNode* probe(treeNode*);


#endif 