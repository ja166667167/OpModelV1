#ifndef treeH
#define treeH

#include<iostream>
#include<string>
#include<vector>
#include"U32.h"


class treeNode{
    public:
        treeNode();//empty
        //treeNode(treeNode*); //root
        //treeNode(treeNode*,board*);//next nodes
        treeNode(bool,U32[],int[]);
        virtual ~treeNode(){}

        //treeNode *parent;
        //vector<treeNode*> children;

        //board *nodeBoard;
        U32 piece[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0xFFFFFFFF};
        bool playerColor;
        int numUnrevealPiece[16] = {0,1,2,2,2,2,2,5,1,2,2,2,2,2,5,0};

        int value=0;
        string chosenMove;
        

        void printBoard();
        //void printMoves();
        

};
#endif