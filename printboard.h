void printboard(int board[8][8]);

void printboard(int board[8][8]) { //prints the board visually using the 2d array to know content of each square
  int i, j;
  printf("   --- --- --- --- --- --- --- ---\n");
  for(i=0;i<8;i++) {
    printf("%d |", i+1);
    for(j=0;j<8;j++) { //for lines that board contents are printed in, each square is printed seperatly based on the corresponding value of the board[][] array
      if(board[i][j] == 0) { //if square is blank
        printf("   |");
      }
      if(board[i][j] == 1) { //if square has a black piece on it
        printf(" B |");
      }
      if(board[i][j] == 2) { //if square has a white piece on it
        printf(" W |");
      }
    }
    printf("\n   --- --- --- --- --- --- --- ---\n");
  }
  printf("    a   b   c   d   e   f   g   h\n");
}
