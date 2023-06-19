#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
void printBoard(char board[][26],int dims);
void instantiateBoard(char board[][26],int dim);
void loadAllPositions (int white_pos[],int black_pos[],int *whitecount, int *blackcount, char board[][26],int dims);
void findValidMoves(int directions[][2],int *positions,int *moves,char board[][26], int boardsize, char side, int *counter, int *validMoves);
void makeMove(int directions[][2],char board[][26],int pos,int len, char side, char oppside);
void replicateBoard(char board[][26],char tempbord[][26],int dims);
void restoreBoard(char board[][26],char tempbord[][26],int dims);
void setZero(int *arr, int num);
int generateScore(char board[][26],char side,int dims);
bool exists(int *moves,int *len, int val);
int main (void){
int validMovesWhite = 0;
int validMovesBlack= 0;
int *computer_validMoves;
int *player_validMoves;
int *computer_side_pos;
int *player_side_pos;
int *computer_moves = NULL;
int *player_moves = NULL;
int directions[8][2] = {{0, 1}, {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}};
int dims = 0;
int white_pos[676]={0};
int black_pos[676]={0};
int white_moves[1000]={0};
int black_moves[1000]={0};

int num_white_pos=0;
int num_black_pos=0;
int *num_player_pos;
int *num_computer_pos;
char computer_side; char player_side;
bool comp_turn = false;
printf("Enter the board dimension: ");
scanf("%d",&dims);
char board[26][26];
char tempboard[26][26];
char starting_side[2];
instantiateBoard(board,dims);

//asks user which side computer plays
printf("Computer plays (B/W) : ");
fflush(stdin);
char *input_char = fgets(starting_side, 1024, stdin);
scanf("%[^'\n']s",input_char);
computer_side = starting_side[0];

printBoard(board,dims);

if(computer_side=='W'){
    player_side = 'B';
    computer_moves= white_moves;
    player_moves = black_moves;
    computer_validMoves = &validMovesWhite;
    player_validMoves = &validMovesBlack;
    computer_side_pos = white_pos;
    player_side_pos = black_pos;
    num_computer_pos = &num_white_pos;
    num_player_pos = &num_black_pos;
}
else{
    player_side = 'W';
   computer_moves= black_moves;
   player_moves = white_moves;
   computer_validMoves = &validMovesBlack;
   player_validMoves = &validMovesWhite;
   comp_turn = true;
    computer_side_pos = black_pos;
    player_side_pos = white_pos;
    num_computer_pos = &num_black_pos;
    num_player_pos = &num_white_pos;
}


 do{
  setZero(computer_side_pos,*num_computer_pos);
  setZero(player_side_pos,*num_player_pos);
  setZero(player_moves,*player_validMoves);
  setZero(computer_moves,*computer_validMoves);
  *player_validMoves = 0;
  *computer_validMoves = 0;
  *num_computer_pos = 0;
  *num_player_pos = 0;
  loadAllPositions(white_pos,black_pos,&num_white_pos,&num_black_pos,board,dims);

 //clock_t begin = clock();
  findValidMoves(directions,computer_side_pos,computer_moves,board,dims,computer_side,num_computer_pos,computer_validMoves);
  //clock_t end = clock();
 //double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
 findValidMoves(directions,player_side_pos,player_moves,board,dims,player_side,num_player_pos,player_validMoves);
//  for(int i=0;i<*computer_validMoves;i++){
//     printf("++%d++",computer_moves[i]);
// }
//printf("\n==%d,%d==",num_white_pos,num_black_pos);

int best_move = 0;
int computer_score = -2147483647;
 if(comp_turn==true){
     //printf("\n[%d]",*computer_validMoves);
     for(int i=0;i<*computer_validMoves;i++){
         replicateBoard(board,tempboard,dims);
        //printf("??%d??",computer_moves[i]);
         makeMove(directions,board,computer_moves[i],dims,computer_side,player_side);
         int temp_pos = computer_moves[i];
         int temp_score = generateScore(board,computer_side,dims);
         printf("temp_score: %d",temp_score);
         restoreBoard(board,tempboard,dims);

        if(temp_score>computer_score){
            computer_score = temp_score;
            best_move = temp_pos;
        }
        else if(temp_score == computer_score){
            //best move is still 0, you need to set best move to temp pos at the first, 
            if((temp_pos/100)<(best_move/100)){
            computer_score = temp_score;
            best_move = temp_pos;
            //printf("\nBest<%d>",best_move);
            }
            else if((temp_pos/100)==(best_move/100)||i==0){
                if((temp_pos%100)<(best_move%100) || i==0){
                computer_score = temp_score;
                best_move = temp_pos;   
                }
            }
        }
         
     }
     if(*computer_validMoves!=0){
    fflush(stdout);
     printf("Computer places %c at %c%c.\n",computer_side,(best_move/100)+97,(best_move%100)+97);
     makeMove(directions,board,best_move,dims,computer_side,player_side);
    printBoard(board,dims);

    }
     else{
         if(*player_validMoves!=0){
         printf("%c player has no valid move.\n",computer_side);
         }
     }
 }
 else{
 printf("Enter move for colour %c (RowCol): ",player_side);
 char inputtedrow = {'\0'};
 char inputtedcol ={'\0'};
 char player_inputs[3];
 char *input_pos = fgets(player_inputs, 1024, stdin);
 fflush(stdin);
 scanf("%[^'\n']s",input_pos);
 inputtedrow = input_pos[0];
 inputtedcol = input_pos[1];
 fflush(stdin);
 int inputtedmove = (((int)(inputtedrow))-97)*100+((int)(inputtedcol))-97;
 if(exists(player_moves,player_validMoves,inputtedmove)){
     makeMove(directions,board,inputtedmove,dims,player_side,computer_side);
     printBoard(board,dims);

 }
 else if(*player_validMoves==0 && *computer_validMoves!=0){
    printf("%c player has no valid move.\n",player_side);
 }
 else{
     printf("Invalid move.\n");
     printf("%c player wins.",computer_side);
     break;
    }
  }
if(*player_validMoves==0 && *computer_validMoves==0){
    int final_comp_score = generateScore(board,computer_side,dims);
    int final_player_score = generateScore(board,player_side,dims);
    if(final_comp_score>final_player_score){
        printf("%c player wins.",computer_side);  
    }
    else if(final_player_score>final_comp_score){
        printf("%c player wins.",player_side);  
    }
    else{
        printf("Draw!");
        }
                    
        }


 

  comp_turn = (!comp_turn);
 }while(*player_validMoves!=0 || *computer_validMoves!=0);




return 0;
}
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
void instantiateBoard(char board[][26],int dims){
  for(int i=0;i<dims;i++){
    for(int j=0;j<dims;j++){  
        if(((j==(dims/2)-1) && (i ==(dims/2)-1) )||((j==(dims/2))&&(i==(dims/2)))){
            board[i][j]='W';
   

        }
        else if(((j==(dims/2)-1) && i ==(dims/2) )||((j==(dims/2))&&(i==(dims/2)-1))){
            board[i][j]='B';

        }
        else{
            board[i][j]='U';
        }
        

    }
}


}
void loadAllPositions (int white_pos[],int black_pos[],int *whitecount, int *blackcount, char board[][26],int dims){

    for (int i=0;i<dims;i++){
        for(int j=0;j<dims;j++){
            if(board[i][j]=='W'){
            white_pos[*whitecount] =i*100+j;
            (*whitecount)++;
            }
            else if(board[i][j]=='B'){
            black_pos[*blackcount]= i*100+j;
            (*blackcount)++;
            }
        }
    }
}
bool InBounds(int n, int row, int col) {
    return (row<n && row>=0 )&& (col>=0 && col<n);
}
bool exists(int *moves,int *len, int val){
    for(int i=0;i<*len;i++){
        if(val==moves[i]){
            return true;
        }
    }
    return false;

}
void findValidMoves(int directions[][2],int *positions,int *moves,char board[][26], int boardsize, char side, int *counter, int *validMoves){
  char oppside={'\0'};
       if( side =='W'){
           oppside = 'B';
       }
       else{
        oppside='W';
       }
        

    for(int w=0;w<*counter;w++){
        
        for (int g = 0;g<8;g++){
            int num=0;
            int first=0;
            int row = positions[w]/100;
            int col = positions[w]%100;
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
                    if(exists(moves,validMoves,row*100+col)==false){
                    moves[*validMoves]=row*100+col;
                    (*validMoves)++;
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

}
void makeMove(int directions[][2],char board[][26],int pos,int len, char side, char oppside){
board[pos/100][pos%100]=side;
for(int p=0;p<8;p++){
int row = pos/100;
int col = pos%100;
int rowdir= directions[p][1];
int coldir = directions[p][0];
int num=0;
bool continuable = false;
bool has_inbtw = false;
bool has_end = false;
while(InBounds(len,row,col)){
    if(board[row][col]==oppside ){
      continuable = true;
      has_inbtw = true;
    }
    else if(board[row][col]==side && has_inbtw && num!=0){
    has_end = true;
    break;
    }
    else if(board[row][col]==side && has_inbtw==false&&num!=0 ){
    has_end = false;
    break;
    }
    else if(board[row][col]=='U'){
    continuable = false;
    break;
    }

    num++;
    row+=rowdir;
    col+=coldir;

}

if(continuable && has_end){

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
void replicateBoard(char board[][26],char tempbord[][26],int dims){
    for(int i=0;i<dims;i++){
        for(int j=0;j<dims;j++){
            tempbord[i][j] = board[i][j];
        }
    }

}
void restoreBoard(char board[][26],char tempbord[][26],int dims){
    for(int i=0;i<dims;i++){
        for(int j=0;j<dims;j++){
            board[i][j] = tempbord[i][j];
        }
    }

}
int generateScore(char board[][26],char side,int dims){
    int side_score = 0;int opp_score = 0;int empty_sq = 0;
        for(int i=0;i<dims;i++){
        for(int j=0;j<dims;j++){
            if(board[i][j]==side){
                side_score++;
            }
            else if (board[i][j]=='U'){
                empty_sq++;
            }
            else{
                opp_score++;
            }
        }
    }
    return side_score-opp_score;
}
void setZero(int *arr, int num){
    for(int i=0;i<num;i++){
        arr[i]=0;
    }
}

