#ifndef ABh
#define ABh

#include<iostream>
#include<vector>
#include<fstream>
#include"treeNode.h"
#include"evaluation.h"

#define RedColor "\033[31m"
#define RESET "\033[0m"
extern string outPut;
extern int depthCount;
extern int const depthLimit;
extern unsigned long long nodeCount;


treeNode* AB(treeNode*);

treeNode* max(treeNode*,int,int);
treeNode* min(treeNode*,int,int);





void makeMove(string);



// treeNode* generateMove(treeNode*);
// treeNode* maxNext(treeNode*);
// treeNode* minNext(treeNode*);

#endif