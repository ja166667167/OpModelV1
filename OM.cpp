#include"OM.h"

using namespace std;


int omNodeCount=0;
int omDptLim=1;
int omDptCount=0;

void OmSearch(treeNode* t){
    treeNode *chosenNode = OmMax(t);
    makeMove(chosenNode->chosenMove);
}
    

treeNode* OmMax(treeNode* thisNode){
    
}
treeNode* OmMin(treeNode*thisNode){
     return AB(thisNode);
}