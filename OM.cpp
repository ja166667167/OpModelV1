#include"OM.h"

using namespace std;


int omNodeCount=0;
int const omDptLim=3;
int omDptCount=0;

void OmSearch(treeNode* root){
    root = OmMax(root);
    //cout<<"Move= "<<root->chosenMove<<endl;
    makeMove(root->chosenMove);
}
    

treeNode* OmMax(treeNode* thisNode){
    //cout<<"in"<<endl;
    omNodeCount++;
    omDptCount++;
    if(omDptCount==omDptLim){
        omDptCount--;
        thisNode->value=chessTypeValue(thisNode);
        return thisNode;
    }
        else{

//generate move
        thisNode->refreshBlack();
        thisNode->refreshOccupied();
        thisNode->refreshRed();
        U32 dest;
//eat and spread
        if (!thisNode->playerColor)
        {
            for (int i = 1; i < 8; i++)
            {
                U32 p = thisNode->piece[i];
                while (p > 0)
                {
                    U32 mask = LS1B(p);
                    p ^= mask;
                    U32 src = U32toInt(mask);
                    if (i == 1)
                    {
                        dest = pMove[src] & ((thisNode->black^    thisNode->piece[14])|  thisNode->piece[0]) ;
                        //printf("%d\n",i);
                    }
                    else if (i == 2)
                    {
                        dest = pMove[src] & (thisNode->black^    thisNode->piece[8]);
                        dest = dest|(pMove[src]&  thisNode->piece[0]);
                        // printf("i:%d,mask:%x,src:%d\n",i,mask,src);
                    }
                    else if (i == 3)
                    {
                        dest = pMove[src] & ((thisNode->black^    thisNode->piece[8] ^    thisNode->piece[9])|  thisNode->piece[0]);
                        //printf("i:%d,src:%d\n",i,src);
                    }
                    else if (i == 4)
                    {
                        dest = pMove[src] & ((   thisNode->piece[11] |    thisNode->piece[12] |    thisNode->piece[13] |    thisNode->piece[14])|  thisNode->piece[0]);
                        //printf("i:%d,src:%d\n",i,src);
                    }
                    else if (i == 5)
                    {
                        dest = pMove[src] & ((   thisNode->piece[12] |    thisNode->piece[13] |    thisNode->piece[14])|  thisNode->piece[0]);
                        //printf("i:%d,src:%d\n",i,src);
                    }
                    else if (i == 6)
                    {

                        dest = thisNode->generateCMove(mask) & thisNode->black;
                        dest = dest|(pMove[src]&  thisNode->piece[0]);
                    }
                    else if (i == 7)
                    {
                        dest = pMove[src] & (   thisNode->piece[8] |    thisNode->piece[14]);
                        dest = dest|(pMove[src]&  thisNode->piece[0]);
                    }
                    else
                    {
                        dest = 0;
                    }

                    while (dest)
                    {
                        string result("\0");
                        U32 mask2 = LS1B(dest);
                        dest ^= mask2;
                        result.append(U32toString(mask));
                        result.append(1, '-');
                        result.append(U32toString(mask2));
                        //cout<<result<<endl;

//generate board with move
                        if (result.empty())
                        {
                            cout << "unusable move string" << endl;
                            exit(1);
                        }
                        if ( result[2] == '-'){   
                            treeNode *newNode = new treeNode(!thisNode->playerColor,thisNode->piece,thisNode->numUnrevealPiece);
                            int srcP = result[0] - 96 + (result[1] - 49) * 4;
                            int destP = result[3] - 96 + (result[4] - 49) * 4;
                            U32 src = InttoU32(srcP);
                            U32 dest = InttoU32(destP);
                            for (int i = 0; i < 16; i++)
                            {
                                if (( newNode->piece[i] != 0) & (( newNode->piece[i] | src) ==  newNode->piece[i]))
                                {

                                    newNode->piece[i] =  newNode->piece[i] ^ src;
                                    newNode->piece[0] =  newNode->piece[0] | src;
                                    for (int j = 0; j < 16; j++)
                                    {
                                        if (( newNode->piece[j] != 0) & (( newNode->piece[j] | dest) ==  newNode->piece[j]))
                                        {
                                            newNode->piece[j] =  newNode->piece[j] ^ dest;
                                        }
                                    }
                                    newNode->piece[i] =  newNode->piece[i] | dest;
                                }
                            }
//next level                            
                            //depthCount++;
                            newNode=OmMin(newNode);
                            if(newNode->value>thisNode->value){
                                thisNode->value=newNode->value;
                                
                                if(omDptCount==1){
                                    
                                    thisNode->chosenMove=result;
                                    thisNode->chosenNode=newNode;
                                    
                                }
                            }
                            if(omDptCount!=1)delete newNode;
                            

                            
                        }
                        else{
                            cout << "child setting ERROR!!!!!!!!!!!!!!!" << endl;
                        }
                    
                    }
                }
            }
        }
        else if (thisNode->playerColor)
        {
            for (int i = 8; i < 15; i++)
            {
                U32 p =    thisNode->piece[i];
                while (p)
                {
                    U32 mask = LS1B(p);
                    p ^= mask;
                    U32 src = U32toInt(mask);
                    if (i == 8){
                        dest = pMove[src] & (thisNode->red^thisNode->piece[7]);
                        dest = dest|(pMove[src]&  thisNode->piece[0]);
                    }
                    else if (i == 9){
                        dest = pMove[src] & (thisNode->red^    thisNode->piece[1]);
                        dest = dest|(pMove[src]&  thisNode->piece[0]);
                    }
                    else if (i == 10)
                        dest = pMove[src] & (thisNode->red^    thisNode->piece[1] ^    thisNode->piece[1]);
                    
                    else if (i == 11){
                        dest = pMove[src] & (   thisNode->piece[4] |    thisNode->piece[5] |    thisNode->piece[6] |    thisNode->piece[7]);
                        dest = dest|(pMove[src]&  thisNode->piece[0]);
                    }
                    else if (i == 12)
                    {
                        dest = pMove[src] & (   thisNode->piece[5] |    thisNode->piece[6] |    thisNode->piece[7]);
                        dest = dest|(pMove[src]&  thisNode->piece[0]);
                        //printf("p=%llu,src=%llu,dest=%llu\n",p,src,dest);
                    }

                    
                    else if (i == 13)
                    {
                        dest = thisNode->generateCMove(mask) &thisNode->red;
                        dest = dest|(pMove[src]&  thisNode->piece[0]);
                    }
                    else if (i == 14){
                        dest = pMove[src] & (   thisNode->piece[1] |    thisNode->piece[7]);
                        dest = dest|(pMove[src]&  thisNode->piece[0]);
                    }
                    else
                        dest = 0;

                    while (dest)
                    {
                        //printf("i=%d,red=%x,   thisNode->piece[1]=%x\n", i, red,    thisNode->piece[1]);
                        string result("\0");
                        U32 mask2 = LS1B(dest);
                        dest ^= mask2;
                        result.append(U32toString(mask));
                        result.append(1, '-');
                        result.append(U32toString(mask2));
                        //eatMove.push_back(result);
                        //cout<<result<<endl;
//generate board with move
                        if (result.empty())
                        {
                            cout << "unusable move string" << endl;
                            exit(1);
                        }
                        if ( result[2] == '-'){   
                            treeNode *newNode = new treeNode(!thisNode->playerColor,thisNode->piece,thisNode->numUnrevealPiece);
                            int srcP = result[0] - 96 + (result[1] - 49) * 4;
                            int destP = result[3] - 96 + (result[4] - 49) * 4;
                            U32 src = InttoU32(srcP);
                            U32 dest = InttoU32(destP);
                            for (int i = 0; i < 16; i++)
                            {
                                if (( newNode->piece[i] != 0) & (( newNode->piece[i] | src) ==  newNode->piece[i]))
                                {

                                    newNode->piece[i] =  newNode->piece[i] ^ src;
                                    newNode->piece[0] =  newNode->piece[0] | src;
                                    for (int j = 0; j < 16; j++)
                                    {
                                        if (( newNode->piece[j] != 0) & (( newNode->piece[j] | dest) ==  newNode->piece[j]))
                                        {
                                            newNode->piece[j] =  newNode->piece[j] ^ dest;
                                        }
                                    }
                                    newNode->piece[i] =  newNode->piece[i] | dest;
                                }
                            }
//next level                            
                            //depthCount++;
                            newNode=OmMin(newNode);
                            if(newNode->value>thisNode->value){
                                thisNode->value=newNode->value;
                                if(omDptCount==1){
                                    thisNode->chosenMove=result;
                                    
                                    thisNode->chosenNode=newNode;
                                    
                                }
                            }
                            if(omDptCount!=1)delete newNode;                            
                        }
                        else{
                            cout << "child setting ERROR!!!!!!!!!!!!!!!" << endl;
                        }
                    
                    }
                }
            }
        }
//reveal        
        U32 reveal = thisNode->piece[15];
        U32 mask;
        while (reveal)
        {
            string result("\0");
            mask = LS1B(reveal);
            reveal ^= mask;
            result.append("R(");
            result.append(U32toString(mask));
            result.append(")");
            //cout<<result<<endl;
//generate board with move
            if (result.empty())
            {
                cout << "unusable move string" << endl;
                exit(1);
            }
            else if( result[0]=='R'){
                int revP =     result[2] - 96 + (    result[3] - 49) * 4;
                U32 rev = InttoU32(revP);
                for (int a = 1; a < 15; a++){

                    if (thisNode->numUnrevealPiece[a] != 0)//此棋種還有位翻開的棋
                    {
                        treeNode *newNode = new treeNode(!thisNode->playerColor,thisNode->piece,thisNode->numUnrevealPiece);
                        newNode->piece[15] =  newNode->piece[15] ^ rev;
                        newNode->piece[a] =  newNode->piece[a] | rev;
                        newNode->numUnrevealPiece[a]--;
//next level             
                        //depthCount++;
                            newNode=OmMin(newNode);
                            if(newNode->value>thisNode->value){
                                thisNode->value=newNode->value;
                                if(omDptCount==1){

                                    cout<<"value= "<<thisNode->value<<endl;
                                    thisNode->chosenMove=result;
                                    thisNode->chosenNode=newNode;
                                    
                                }
                            }
                            if(omDptCount!=1)delete newNode;
                        
                    }
                
                }
            }
            
            else{
                cout << "child setting ERROR!!!!!!!!!!!!!!!" << endl;
            }
        
        }

    }    
    omDptCount--;
    return thisNode;

}
treeNode* OmMin(treeNode*thisNode){
    //cout<<"min in\n";
    omNodeCount++;
    omDptCount++;
    if(omDptCount==omDptLim){
        thisNode->playerColor=!thisNode->playerColor;
        omDptCount--;
        thisNode->value=chessTypeValue(thisNode);
        return thisNode;
    }
    else{
        thisNode=AB(thisNode);
        //cout<<"AB result= "<<thisNode->chosenMove<<endl;
        thisNode->chosenNode->printBoard();  
    
    treeNode* newNode = OmMax(thisNode->chosenNode);
    cout<<"ab value= "<<thisNode->value<<endl;
    thisNode->value=newNode->value;
    cout<<"max value="<<thisNode->value<<endl;
    //exit(1);
    omDptCount--;
    return thisNode;
    }
}
