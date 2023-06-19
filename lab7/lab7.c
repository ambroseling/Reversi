//
// Author: Ambrose Ling
//
// #include "reversi.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define max_instructions 100


void makeMove(int directions[][2],char board[][26],int pos,int len, char side, char oppside);
void loadActualMoves(int actual_moves[],int moves[], int len);
void findValidMoves(int directions[][2],int positions[][2],int moves[1000],char board[][26], int boardsize, bool white, int *whitecount, int *blackcount, int *validMovesWhite, int *validMovesBlack);
void printBoard(char board[][26],int dims);
void sortMoves(int moves[], int *size);
void assignPos (int pos[][3], char board[][26]);
void printValidMoves(int moves[],bool white,int *validMovesWhite, int *validMovesBlack);
bool exists(int moves[1000],int len, int val);
void checMove(int directions[][2],char userinput[3],int white_moves[],int black_moves[],char board[][26],int size, int *validMovesWhite , int *vaidMovesBlack);
void loadAllPositions (int white_pos[][2],int black_pos[][2],int *validMovesWhite, int *validMovesBlack, char board[][26],int dim);


void printBoard(char board[][26],int dims) {
    int ascii_top_row = 97;int ascii_left_col = 97;
    printf("  ");
    for(int i=0;i<dims+1;i++){
        if(i>=1){
            printf("%c ",ascii_left_col);
            ascii_left_col++;
        }
        for(int j=0;j<dims;j++ ){
            if(i==0){
                printf("%c",ascii_top_row);
                ascii_top_row++;
            }
            else{
                printf("%c",board[i-1][j]);
            }
        }
        printf("\n");
    }
}
void assignPos (int pos[][3], char board[][26]){
    for(int i=0;i<100;i++){
        if(pos[i][0]==-31){
            board[pos[i][1]][pos[i][2]]='B';

        }
        else if(pos[i][0]==0&& pos[i][1]==0&&pos[i][2]==0){
            break;
        }
        else{
            board[pos[i][1]][pos[i][2]]='W'; 
  
        }
    }
}

 bool InBounds(int n, int row, int col) {
    return (row<n && row>=0 )&& (col>=0 && col<n);
 }

void findValidMoves(int directions[][2],int positions[][2],int moves[1000],char board[][26], int boardsize, bool white, int *whitecount, int *blackcount, int *validMovesWhite, int *validMovesBlack){
    int validMoveCount=0;
    int counter;
    char side={'\0'};char oppside={'\0'};
    if(white){
        side = 'W';
        oppside='B';
        counter = *whitecount;
    }
    else{
        side = 'B';
        oppside='W';
        counter = *blackcount;
    }

    for(int w=0;w<counter;w++){
        
        for (int g = 0;g<8;g++){
            int num=0;
            int first=0;
            int row = (positions)[w][0];
            int col = (positions)[w][1];
            int rowdir = directions[g][1];
            int coldir = directions[g][0];
            
            while(InBounds(boardsize,row,col)){

            if(board[row][col]==oppside){
            num++;
            }
            else if(board[row][col]==side && first!=0){
                break;
            }
            else if(board[row][col]=='U'){
                 if(num==0){
                    break;
                 }
                 else{
                    if(exists(moves,validMoveCount,row*100+col)==false){
                    moves[validMoveCount]=row*100+col;
                    validMoveCount++;
                    }
                 

                 break;
                 }
                 
                
             }

             first++;
            row+=rowdir;
            col+=coldir;

            
            }
        }
    }
    if(white){
    *validMovesWhite=validMoveCount;
    } 
    else{
    *validMovesBlack=validMoveCount;
    }

}

int main(void) {
int white_pos[100][2] = {{0,0}};
int black_pos[100][2] = {{0,0}};
int validMovesWhite = 0;
int validMovesBlack= 0;

int whitecount = 0;//number of positions occupied by white
int blackcount = 0;//number of  positions occupied by black
int directions[8][2] = {{0, 1}, {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}};
char mod_input[100]={'\0'};
char input[100]={'\0'};
int pos[100][3]={{0}};
int white_moves[1000]={0};
int black_moves[1000]={0};

  int dim=0 ;
  printf("Enter the board dimension: ");
  scanf("%d",&dim);
  fflush(stdin);
  char board[26][26]={{'\0'}};

printBoard(board,dim);

printf("Enter board configuration:\n");
int count=0;int count2=0;
char userinput[10]={'\0'};
scanf("%[^!]s",input);

for(int p=0;p<100;p++){
    
    if(input[p]=='\0'){
        break;
    }
    else if(input[p]!='\n'){
        mod_input[p]=input[p];
        
        pos[count/3][count2-(3*(count/3))]=(int)(input[p])-97;

        count++;
        count2++;
    }
        
}
assignPos(pos,board);
loadAllPositions(white_pos,black_pos,&whitecount,&blackcount,board,dim);

fflush(stdin);
printBoard(board,dim);

findValidMoves(directions,white_pos,white_moves,board,dim,true,&whitecount,&blackcount,&validMovesWhite,&validMovesBlack);

findValidMoves(directions,black_pos,black_moves,board,dim,false,&whitecount,&blackcount,&validMovesWhite,&validMovesBlack);

sortMoves(white_moves,&validMovesWhite);
sortMoves(black_moves,&validMovesBlack);
 printValidMoves(white_moves,true,&validMovesWhite,&validMovesBlack);
 printValidMoves(black_moves,false,&validMovesWhite,&validMovesBlack);
printf("Enter a move:\n");
char *inputline = fgets(userinput, 1024, stdin);
scanf("%[^'\n']s",inputline);



fflush(stdin);
checMove(directions,userinput,white_moves,black_moves,board,dim,&validMovesWhite,&validMovesBlack);
return 0;
}
void printValidMoves(int moves[],bool white,int *validMovesWhite, int *validMovesBlack){
    int movenum = 0;
    char sidename='\0';
    if(white){
        movenum = *validMovesWhite;
        sidename='W';
    }
    else{
        movenum = *validMovesBlack;
        sidename='B';
    }

    printf("Available moves for %c:\n",sidename);
    for(int i=0;i<movenum;i++){
       printf("%c%c",((moves[i]/100)+97),(moves[i]%100)+97);
            printf("\n");
           
            
           }
    }


void sortMoves(int moves[], int *size){
    int num=0;
    for(int i=0;i<*size-1;i++){
           for(int j=0;j<*size-1-i;j++){
          if(moves[j]>moves[j+1]){
            num = moves[j];
            moves[j]=moves[j+1];
            moves[j+1]=num;
        }
    } 
    }

}
void checMove(int directions[][2],char userinput[3],int white_moves[],int black_moves[],char board[][26],int size, int *validMovesWhite , int *vaidMovesBlack){
   bool found = false;
   
    if(userinput[0]=='W'){
    
        for(int i=0;i<*validMovesWhite;i++){
            int pos = ((int)(userinput[1])-97)*100+((int)(userinput[2])-97);
            if(pos==white_moves[i]){
                found=true;
                printf("Valid move.\n");

                makeMove(directions,board,pos,size,'W','B');
                 printBoard(board,size);
                 break;
            }
        }
        if(found==false){
            printf("Invalid move.\n");
            printBoard(board,size);
        }
    }
    else{
         for(int i=0;i<*vaidMovesBlack;i++){
            int pos = ((int)(userinput[1])-97)*100+((int)(userinput[2])-97);
            if(pos==black_moves[i]){
                found=true;
                printf("Valid move.\n");
                makeMove(directions,board,pos,size,'B','W');
                 printBoard(board,size);
                 break;
            }
        }
        if(found==false){
            printf("Invalid move.\n");
            printBoard(board,size);
        }

    }
}
//need to fix 0s appearing in the array mistaken as a validMove
//need to change the board correctly when a move is made
 bool exists(int moves[1000],int len, int val){
    for(int i=0;i<len;i++){
        if(val==moves[i]){
            return true;
        }
    }
    return false;

}
void makeMove(int directions[][2],char board[][26],int pos,int len, char side, char oppside){
board[pos/100][pos%100]=side;


for(int p=0;p<8;p++){
int row = pos/100;
int col = pos%100;
int rowdir= directions[p][1];
int coldir = directions[p][0];
int num=0;
bool flip = false;
while(InBounds(len,row,col)){
    if(board[row][col]==oppside){
      flip = true;
    }
    else if(board[row][col]==side && num!=0 ){
    break;
    }
    else if(board[row][col]=='U'){
    flip = false;
    break;
    }
    if((row==len-1 || col==len-1)&& board[row][col]!=side){
    flip=false;
}
    num++;
    row+=rowdir;
    col+=coldir;

}

if(flip){
    int a = pos/100;
    int b = pos%100;
    while(a!=row || b!=col){
        a+=rowdir;
        b+=coldir;
        board[a][b]=side;
    }
}
}
}
void loadAllPositions (int white_pos[][2],int black_pos[][2],int *whitecount, int *blackcount, char board[][26],int dim){
    for (int i=0;i<dim;i++){
        for(int j=0;j<dim;j++){
            if(board[i][j]=='W'){
            white_pos[*whitecount][0] =i;
            white_pos[*whitecount][1] = j;
            (*whitecount)++;
            }
            else if(board[i][j]=='B'){
            black_pos[*blackcount][0] = i;
            black_pos[*blackcount][1]=j;
            (*blackcount)++;
            }
        }
    }
}
