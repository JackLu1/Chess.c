#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int start();
int ins();
void display();
void cmd(int turn);
int checkmate();
int check1(int turn, int x, int y); //choose right piece
int check2(int turn, int x, int y, int x1, int y1); //choose right location/movement
void pmove(int turn, int x, int y);
void check3(int turn, int x, int y); //check if kill black or check
void cboard(int x, int y);
//======================= PIECE MOVEMENTS ========================
void rook(int x, int y);
void knight(int x, int y);
void bishop(int x, int y);
void queen(int x, int y);
void pawn(int turn, int x, int y);
void king(int x, int y);
//================================================================

char * piece[8][8] = {
                {"♖", "♘", "♗", "♕", "♔", "♗", "♘", "♖"},
                {"♙", "♙", "♙", "♙", "♙", "♙", "♙", "♙"},
                {" ", " ", " ", " ", " ", " ", " ", " "},
                {" ", " ", " ", " ", " ", " ", " ", " "},
                {" ", " ", " ", " ", " ", " ", " ", " "},
                {" ", " ", " ", " ", " ", " ", " ", " "},
                {"♟", "♟", "♟", "♟", "♟", "♟", "♟", "♟"},
                {"♜", "♞", "♝", "♛", "♚", "♝", "♞", "♜"}
               };

char * white[6] = {"♜", "♞", "♝", "♛", "♟", "♚"};
char * black[6] = {"♖", "♘", "♗", "♕", "♙", "♔"};
char * wdead[15];
char * bdead[15];
int * movement[8][8];

//===============================================================================================================================================================

int main(){
  int choice = start(), win=0, turn=1;

  if (choice == 1)
   {
    system("clear");
    display();
  }
  if (choice == 2)
    {
    system("clear");
    ins();
    display();
  }

  while (win < 10)
  {
    cmd(turn);
    system("clear");
    display();
    win++;
    turn++;
  }

  return 0;
}
//===============================================================================================================================================================

void cmd(int turn){

  int x, y, x1, y1;
  int correct, correct2;
  char temp1[3];
  char temp2[3];

  if (turn % 2 != 0)
  {
      printf("White's Turn\n");
      printf("Enter the x coordinate of your piece: ");
      scanf("%d", &x);
      printf("Enter the y coordinate of your piece: ");
      scanf("%d", &y);
      correct = check1(turn, x, y);
      while (correct != 1)                                                    //check select correct piece
       {
         printf("Enter a valid x coordinate: ");
         scanf("%d", &x);
         printf("Enter a valid y coordinate: ");
         scanf("%d", &y);
         correct = check1(turn, x, y);
       }
      pmove(turn, x, y);

      printf("\nEnter the x coordinate of your desired location: ");
      scanf("%d", &x1);
      printf("\nEnter the y coordinate of your desired location: ");
      scanf("%d", &y1);
      //==============================
      correct2 = check2(turn, x, y, x1, y1);                                          //check move correct place
      while (correct2 != 1)
       {
         printf("Enter a valid destination: ");
         scanf("%d", &x1);
         printf("Enter a valid destination: ");
         scanf("%d", &y1);
         correct2 = check2(turn, x, y, x1, y1);
       }

      //==============================
      strcpy(temp1, piece[y][x]);
      strcpy(temp2, piece[y1][x1]);
      piece[y1][x1]=(char *)malloc(60*sizeof(char));
      strcpy((piece[y1][x1]), temp1);
      piece[y][x]=(char *)malloc(60*sizeof(char));
      strcpy((piece[y][x]), temp2);
      check3(turn, x, y);
      cboard(x, y);
    }

   else
   {
       printf("Black's Turn\n");
       printf("Enter the x coordinate of your piece: ");
       scanf("%d", &x);
       printf("Enter the y coordinate of your piece: ");
       scanf("%d", &y);
       correct = check1(turn, x, y);
       while (correct != 1)
        {
          printf("Enter a valid x coordinate: ");
          scanf("%d", &x);
          printf("Enter a valid y coordinate: ");
          scanf("%d", &y);
          correct = check1(turn, x, y);
        }

       pmove(turn, x, y);

       printf("\nEnter the x coordinate of your desired location: ");
       scanf("%d", &x1);
       printf("\nEnter the y coordinate of your desired location: ");
       scanf("%d", &y1);
       //==============================
       correct2 = check2(turn, x, y, x1, y1);                                          //check move correct place
       while (correct2 != 1)
        {
          printf("Enter a valid destination: ");
          scanf("%d", &x1);
          printf("Enter a valid destination: ");
          scanf("%d", &y1);
          correct2 = check2(turn, x, y, x1, y1);
        }
       //==============================
       strcpy(temp1, piece[y][x]);
       strcpy(temp2, piece[y1][x1]);
       piece[y1][x1]=(char *)malloc(60*sizeof(char));
       strcpy((piece[y1][x1]), temp1);
       piece[y][x]=(char *)malloc(60*sizeof(char));
       strcpy((piece[y][x]), temp2);
       check3(turn, x, y);
       cboard(x, y);
     }
}
//=======================================================================================================

int check1(turn, x, y){ //ERROR WHITE STILL MOVES BLACK PIECES
  int i;
  if (turn % 2 != 0)  //Check white is moving white piece
    {
      for (i=0; i<6; i++)
      {
      if (strcmp(piece[y][x], black[i]) == 0)
       {
         printf("You cannot move that piece\n");
         return 0;
       }
     }
   }
  else  //checks black is moving black piece
     {
       for (i=0; i<6; i++)
       {
       if (strcmp(piece[y][x], white[i]) == 0)
        {
          printf("You cannot move that piece\n");
          return 0;
        }
      }
    }
  return 1;
}


//=======================================================================================================

int check2(int turn, int x, int y, int x1, int y1){
  int i;

  // char * white[6] = {"♜", "♞", "♝", "♛", "♟", "♚"};
  // char * black[6] = {"♖", "♘", "♗", "♕", "♙", "♔"};
  if (turn % 2 != 0)  //Check white is moving to valid place
    {
      for (i=0; i<5; i++)
        {
          if (strcmp(piece[y1][x1], white[i]) == 0)
            {
              printf("You cannot move to a space occupied by your own piece.\n");
              return 0;
            }
         }
      }
   else         //black
     {
       for (i=0; i<5; i++)
         {
           if (strcmp(piece[y1][x1], black[i]) == 0)
             {
               printf("You cannot move to a space occupied by your own piece.\n");
               return 0;
             }
          }
        }
     return 1;
   }

//=======================================================================================================

void pmove(int turn, int x, int y){
  // char * white[6] = {"♜", "♞", "♝", "♛", "♟", "♚"};
  // char * black[6] = {"♖", "♘", "♗", "♕", "♙", "♔"};

  if (strcmp(piece[y][x], white[0]) == 0 || strcmp(piece[y][x], black[0]) == 0)     //Rook
    {
      rook(x, y);
      system("clear");
      display();
    }
  // if (strcmp(piece[y][x], white[1]) == 0 || strcmp(piece[y][x], black[1]) == 0)     //Knight
  //   {
  //     knight(x, y);
  //     system("clear");
  //     display();
  //   }
  if (strcmp(piece[y][x], white[2]) == 0 || strcmp(piece[y][x], black[2]) == 0)     //Bishop
    {
      bishop(x, y);
      system("clear");
      display();
    }
  if (strcmp(piece[y][x], white[3]) == 0 || strcmp(piece[y][x], black[3]) == 0)     //Queen
    {
      queen(x, y);
      system("clear");
      display();
    }
  if (strcmp(piece[y][x], white[4]) == 0 || strcmp(piece[y][x], black[4]) == 0)     //Pawn
    {
      pawn(turn, x, y);
      system("clear");
      display();
    }
  if (strcmp(piece[y][x], white[5]) == 0 || strcmp(piece[y][x], black[5]) == 0)     //King
    {
      king(x, y);
      system("clear");
      display();
    }
  }
//=======================================================================================================
void rook(int x, int y){
  int i;
  for (i=x; i>=0; i--)
    {
      if (strcmp(piece[i][x], " ") == 0)
        {
        piece[i][x]=(char *)malloc(60*sizeof(char));
        strcpy(piece[i][x], "_");
        }
      if (strcmp(piece[y][i], " ") == 0)
        {
        piece[y][i]=(char *)malloc(60*sizeof(char));
        strcpy(piece[y][i], "_");
        }
    }
  for (i=x; i<8; i++)
    {
      if (strcmp(piece[i][x], " ") == 0)
        {
        piece[i][x]=(char *)malloc(60*sizeof(char));
        strcpy(piece[i][x], "_");
        }
      if (strcmp(piece[y][i], " ") == 0)
        {
        piece[y][i]=(char *)malloc(60*sizeof(char));
        strcpy(piece[y][i], "_");
        }
    }

  }
//=======================================================================================================
void knight(int x, int y){

 if (y+1<8 && x+2<8)             //++
  {
    if (strcmp(piece[y+1][x+2], " ") == 0)
      {
        piece[y+1][x+2]=(char *)malloc(60*sizeof(char));
        strcpy(piece[y+1][x+2], "_");
      }
   }
//  if (y+1 < 8 && x-2 < 8)         //+-
//  {
//    if (strcmp(piece[y+1][x-2], " ") == 0)
//      {
//        piece[y+1][x+3]=(char *)malloc(60*sizeof(char));
//        strcpy(piece[y+1][x-2], "_");
//      }
//   }
// if (y-1 < 8 && x+2 < 8)         //-+
// {
//   if (strcmp(piece[y-1][x+2], " ") == 0)
//     {
//       piece[y-1][x+2]=(char *)malloc(60*sizeof(char));
//       strcpy(piece[y-1][x+2], "_");
//     }
//  }
//  if (y-1 < 8 && x-2 < 8)        //--
//  {
//    if (strcmp(piece[y-1][x-2], " ") == 0)
//      {
//        piece[y-1][x-2]=(char *)malloc(60*sizeof(char));
//        strcpy(piece[y-1][x-2], "_");
//      }
//   }
}

//=======================================================================================================

void bishop(int x, int y){
  int i, j, k, l;

   for (i=0; i+x<8 && i+y<8; i++)
   {
     if (strcmp(piece[y+i][x+i], " ") == 0)
       {
         piece[y+i][x+i]=(char *)malloc(60*sizeof(char));
         strcpy(piece[y+i][x+i], "_");
       }
     }
   for (j=0; x-j>-1 && y-j>-1; j++)
   {
     if (strcmp(piece[y-j][x-j], " ") == 0)
       {
         piece[y-j][x-j]=(char *)malloc(60*sizeof(char));
         strcpy(piece[y-j][x-j], "_");
       }
     }
   for (k=0; x+k<8 && y-k>-1; k++)
   {
     if (strcmp(piece[y-k][x+k], " ") == 0)
       {
         piece[y-k][x+k]=(char *)malloc(60*sizeof(char));
         strcpy(piece[y-k][x+k], "_");
       }
     }
   for (l=0; x-l>0 && y+l<8; l++)
   {
     if (strcmp(piece[y+l][x-l], " ") == 0)
       {
         piece[y+l][x-l]=(char *)malloc(60*sizeof(char));
         strcpy(piece[y+l][x-l], "_");
       }
     }
   }



//=======================================================================================================

void pawn(int turn, int x, int y){
  if (turn % 2 != 0)
    {
      if (strcmp(piece[y-1][x], " ") == 0)
        {
          piece[y-1][x]=(char *)malloc(60*sizeof(char));
          strcpy(piece[y-1][x], "_");
        }
      }
  else
    {
      if (strcmp(piece[y+1][x], " ") == 0)
        {
          piece[y+1][x]=(char *)malloc(60*sizeof(char));
          strcpy(piece[y+1][x], "_");
        }
      }
    }

//=======================================================================================================

void king(int x, int y){

    if (x+1 < 8)
        {
          if (strcmp(piece[y][x+1], " ") == 0)
          {
          piece[y][x+1]=(char *)malloc(60*sizeof(char));
          strcpy(piece[y][x+1], "_");
        }
      }
    if (x-1 < 8)
        {
          if (strcmp(piece[y][x-1], " ") == 0)
          {
          piece[y][x-1]=(char *)malloc(60*sizeof(char));
          strcpy(piece[y][x-1], "_");
        }
      }
    if (x+1 < 8)
        {
          if (strcmp(piece[y][x+1], " ") == 0)
          {
          piece[y][x+1]=(char *)malloc(60*sizeof(char));
          strcpy(piece[y][x+1], "_");
        }
      }
    if (y+1 < 8)
        {
          if (strcmp(piece[y+1][x], " ") == 0)
          {
          piece[y+1][x]=(char *)malloc(60*sizeof(char));
          strcpy(piece[y+1][x], "_");
        }
      }
    if (y-1 < 8)
        {
          if (strcmp(piece[y-1][x], " ") == 0)
          {
          piece[y-1][x]=(char *)malloc(60*sizeof(char));
          strcpy(piece[y-1][x], "_");
        }
      }

    if (x+1 < 8 && y+1 < 8)
        {
          if (strcmp(piece[y+1][x+1], " ") == 0)
          {
          piece[y+1][x+1]=(char *)malloc(60*sizeof(char));
          strcpy(piece[y+1][x+1], "_");
        }
      }
    if (x+1 < 8 && y-1 < 8)
        {
          if (strcmp(piece[y-1][x+1], " ") == 0)
          {
          piece[y-1][x+1]=(char *)malloc(60*sizeof(char));
          strcpy(piece[y-1][x+1], "_");
        }
      }
    if (x-1 < 8 && y-1 < 8)
        {
          if(strcmp(piece[y-1][x-1], " ") == 0)
          {
          piece[y-1][x-1]=(char *)malloc(60*sizeof(char));
          strcpy(piece[y-1][x-1], "_");
        }
      }
    if (x-1 < 8 && y+1 < 8)
        {
          if (strcmp(piece[y+1][x-1], " ") == 0)
          {
          piece[y+1][x-1]=(char *)malloc(60*sizeof(char));
          strcpy(piece[y+1][x-1], "_");
        }
      }
    }

void queen(int x, int y){
  int n;
  for (n=x; n>=0; n--)
    {
      if (strcmp(piece[n][x], " ") == 0)
        {
        piece[n][x]=(char *)malloc(60*sizeof(char));
        strcpy(piece[n][x], "_");
        }
      if (strcmp(piece[y][n], " ") == 0)
        {
        piece[y][n]=(char *)malloc(60*sizeof(char));
        strcpy(piece[y][n], "_");
        }
    }
  for (n=x; n<8; n++)
    {
      if (strcmp(piece[n][x], " ") == 0)
        {
        piece[n][x]=(char *)malloc(60*sizeof(char));
        strcpy(piece[n][x], "_");
        }
      if (strcmp(piece[y][n], " ") == 0)
        {
        piece[y][n]=(char *)malloc(60*sizeof(char));
        strcpy(piece[y][n], "_");
        }
    }
    int i, j, k, l;

     for (i=0; i+x<8 && i+y<8; i++)
     {
       if (strcmp(piece[y+i][x+i], " ") == 0)
         {
           piece[y+i][x+i]=(char *)malloc(60*sizeof(char));
           strcpy(piece[y+i][x+i], "_");
         }
       }
     for (j=0; x-j>0 && y-j>0; j++)
     {
       if (strcmp(piece[y-j][x-j], " ") == 0)
         {
           piece[y-j][x-j]=(char *)malloc(60*sizeof(char));
           strcpy(piece[y-j][x-j], "_");
         }
       }
     for (k=0; x+k<8 && y-k>0; k++)
     {
       if (strcmp(piece[y-k][x+k], " ") == 0)
         {
           piece[y-k][x+k]=(char *)malloc(60*sizeof(char));
           strcpy(piece[y-k][x+k], "_");
         }
       }
     for (l=0; x-l>0 && y+l<8; l++)
     {
       if (strcmp(piece[y+l][x-l], " ") == 0)
         {
           piece[y+l][x-l]=(char *)malloc(60*sizeof(char));
           strcpy(piece[y+l][x-l], "_");
         }
       }

   }

//=======================================================================================================

void cboard(int x, int y){
 int i, j;
 for (i=0; i<8; i++)
  {
    for (j=0; j<8; j++)
      {
        if (strcmp(piece[i][j], "_") == 0)
          {
            piece[i][j]=(char *)malloc(60*sizeof(char));
            strcpy(piece[i][j], " ");
          }
        }
      }
    }

//=======================================================================================================

void check3(int turn, int x, int y){

  int i;
  char blank[4] = " ";

  if (turn % 2 != 0)  //check if white is killing black piece
    {
      for (i=0; i<5; i++)
        {
          if (strcmp(piece[y][x], black[i]) == 0)
            {
              piece[y][x]=(char *)malloc(60*sizeof(char));
              strcpy(piece[y][x], blank);
            }
          }
      // if (strcmp(piece[y][x], black[5]) == 0)
      //   {
      //     checkmate( );
      //   }
    }
   else
   {
     for (i=0; i<5; i++)
       {
         if (strcmp(piece[y][x], white[i]) == 0)
           {
             piece[y][x]=(char *)malloc(60*sizeof(char));
             strcpy(piece[y][x], blank);
           }
         }
        //  if (strcmp(piece[y][x], black[5]) == 0)
        //    {
        //      checkmate( );
        //    }
   }
  }

//==============================================================================================================

int start(){
  int choice;
  system("clear");
  printf("\n                 WELCOME TO CHESS                         \n\n");
  printf("                 To Start: Press 1 \n");
  printf("               Instructions: Press 2 \n\n");
  printf("> ");
  scanf("%d", &choice);
  return choice;
}

//================================================================================================================

int ins(){
  int choice;
  printf("\nThis is a chess game between 2 players, since making AI is too hard.\n");
  printf("To Move a piece, enter its x coordinate, then its y coordinate.\n");
  printf("Then, enter the square of a valid spot to move there.\n\n");
  printf("White is filled in.\n");
  printf("Black is outlined.\n\n");
  printf("♚ / ♔ = KING\n");
  printf("♛ / ♕ = QUEEN\n");
  printf("♜ / ♖ = ROOK\n");
  printf("♞ / ♘ = KNIGHT\n");
  printf("♝ / ♗ = BISHOP\n");
  printf("♟ / ♙ = PAWN\n\n");
  printf("Once you are done, enter 1 to begin playing.\n");
  scanf("%d", &choice);
  system("clear");
  return choice;
}

//===============================================================================================================================================================

void display(){
  printf("\n\n");
  printf("     0     1     2     3     4     5     6     7\n");
  printf("  .................................................\n");
  printf("0 |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  | 0\n", piece[0][0], piece[0][1], piece[0][2], piece[0][3], piece[0][4], piece[0][5], piece[0][6], piece[0][7]);
  printf("  .................................................\n");
  printf("1 |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  | 1\n", piece[1][0], piece[1][1], piece[1][2], piece[1][3], piece[1][4], piece[1][5], piece[1][6], piece[1][7]);
  printf("  .................................................\n");
  printf("2 |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  | 2\n", piece[2][0], piece[2][1], piece[2][2], piece[2][3], piece[2][4], piece[2][5], piece[2][6], piece[2][7]);
  printf("  .................................................\n");
  printf("3 |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  | 3\n", piece[3][0], piece[3][1], piece[3][2], piece[3][3], piece[3][4], piece[3][5], piece[3][6], piece[3][7]);
  printf("  .................................................\n");
  printf("4 |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  | 4\n", piece[4][0], piece[4][1], piece[4][2], piece[4][3], piece[4][4], piece[4][5], piece[4][6], piece[4][7]);
  printf("  .................................................\n");
  printf("5 |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  | 5\n", piece[5][0], piece[5][1], piece[5][2], piece[5][3], piece[5][4], piece[5][5], piece[5][6], piece[5][7]);
  printf("  .................................................\n");
  printf("6 |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  | 6\n", piece[6][0], piece[6][1], piece[6][2], piece[6][3], piece[6][4], piece[6][5], piece[6][6], piece[6][7]);
  printf("  .................................................\n");
  printf("7 |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  | 7\n", piece[7][0], piece[7][1], piece[7][2], piece[7][3], piece[7][4], piece[7][5], piece[7][6], piece[7][7]);
  printf("  .................................................\n");
  printf("     0     1     2     3     4     5     6     7\n");
}
