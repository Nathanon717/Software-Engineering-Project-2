#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "printboard.h"
#include "isValid.h"
#include "counter.h"
#include "checkMoves.h"

#define MAX 100

int main() {

  char name1[MAX], name2[MAX], winner[MAX], move[3];
  int i, j, turns=4, blackScore=2, whiteScore=2, testBoard[8][8], passCount=0;
  //2d integer array to represent board where 0 is a blank space, 1 is a black piece and 2 is a white piece. Also used for testing purposes such and manually setting certain positions to test code behaviour
  int board[8][8] = { {0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 2, 1, 0, 0, 0},
                      {0, 0, 0, 1, 2, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0}
                    };

  //intro/name input and colour assignment
  printf("***  Welcome to Othello!  ***\n");
  printf("\nEnter name of Player 1 (Black): ");
  scanf("%s", &name1);
  printf("\nEnter name of Player 2 (White): ");
  scanf("%s", &name2);

  //main game loop
  while(turns<65) {

    // Black ///////////////////////////////////////////////////////////////////
    printf("\n\nScore: %s (Black) %d:%d %s (White)\n", name1, blackScore, whiteScore, name2); //print info on current position
    printboard(board); //print current board
    printf("\nBlack's move: "); //request move from black
    scanf("%s", &move);

    while(true) { //loops if/until black enters a valid move or passes when there are none
      if(move[0] == 'p') {
        //if player attempted to pass, copy contents of current board to another 2d array to perserve current game state, and check for valid moves using that array
        for(i=0;i<8;i++) {
          for(j=0;j<8;j++) {
            testBoard[i][j] = board[i][j];
          }
        }
        if(checkMoves(1, testBoard)) { //if black (represented by the integer 1) has no valid moves in this position
          passCount++; //used to tell if both players passed consecutavely, as that would end the game
          break; //end turn
        } else {
          printf("\nYou can't pass when you have 1 or more valid moves\n");
        }
      }
      j=move[0]-97; //converts deciaml representation of 'a'-'h' to integers 0-7
      i=move[1]-49; //converts deciaml representation of '1'-'8' to integers 0-7
      if(isValid(1, board, i, j)) { //if current board allows for a black piece in that square
        passCount=0;
        break;
      }
      //if move/pass attempt was invalid, request another move
      printf("Enter a valid move: ");
      scanf("%s", &move);
    }

    if(passCount == 0) { //if move was valid
      board[i][j]=1; //update board with move
      turns++; // used to count pices on the board for score calculation
      blackScore=counter(board); //function that counts black pieces on current board ie black's score
      whiteScore=turns-blackScore; //pieces on the board that aren't black must be white ie white's score
    }
    if(passCount == 2 || blackScore == 0 || whiteScore == 0) { //if 2 passes happened in a row or either player has no counters left on the board
      break; //end the game
    }


    // White ///////////////////////////////////////////////////////////////////
    printf("\n\nScore: %s (Black) %d:%d %s (White)\n", name1, blackScore, whiteScore, name2);
    printboard(board);
    printf("\nWhite's move: ");
    scanf("%s", &move);

    while(true) {
      if(move[0] == 'p') {
        for(i=0;i<8;i++) {
          for(j=0;j<8;j++) {
            testBoard[i][j] = board[i][j];
          }
        }
        if(checkMoves(2, testBoard)) { //integer 2 represents white
          passCount++;
          break;
        } else {
          printf("\nYou can't pass when you have 1 or more valid moves\n");
        }
      }
      j=move[0]-97;
      i=move[1]-49;
      if(isValid(2, board, i, j)) {
        passCount=0;
        break;
      }
      printf("Enter a valid move: ");
      scanf("%s", &move);

    }

    if(passCount == 0) {
      board[i][j]=2;
      turns++;
      blackScore=counter(board);
      whiteScore=turns-blackScore;
    }
    if(passCount == 2 || blackScore == 0 || whiteScore == 0) {
      break;
    }

  }

  if(blackScore>whiteScore) { //black wins
    strcpy(winner, name1); //winner variable used for printing result to .txt file
    printf("************************************\n");
    printf("Winner: %s\n", winner);
    printf("\nScore: %s (Black) %d:%d %s (White)\n", name1, blackScore, whiteScore, name2);
    printf("Final board:\n");
    printboard(board);
    printf("************************************\n");
  }
  if(blackScore<whiteScore) { //white wins
    strcpy(winner, name2);
    printf("************************************\n");
    printf("Winner: %s\n", winner);
    printf("\nScore: %s (Black) %d:%d %s (White)\n", name1, blackScore, whiteScore, name2);
    printf("Final board:\n");
    printboard(board);
    printf("************************************\n");
  }
  if(blackScore==whiteScore) { //tie
    strcpy(winner, "Tie");
    printf("************************************\n");
    printf("Tie\n");
    printf("\nScore: %s (Black) %d:%d %s (White)\n", name1, blackScore, whiteScore, name2);
    printf("Final board:\n");
    printboard(board);
    printf("************************************\n");
  }

  //set date and time
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);

  FILE *fp;
  fp = fopen ("othello-results.txt", "a"); //create/open .txt file in append mode and write result to it
  fprintf(fp, "Winner: %s | Score: %s (Black) %d:%d %s (White) | %d-%02d-%02d %02d:%02d:%02d\n", winner, name1, blackScore, whiteScore, name2, tm.tm_year+1900, tm.tm_mday, tm.tm_mon+1, tm.tm_hour, tm.tm_min, tm.tm_sec);

}
