int counter(int board[8][8]);

int counter(int board[8][8]) { //counts black pieces on the board
  int result=0;
  for(int i=0;i<8;i++) {
    for(int j=0;j<8;j++) {
      if(board[i][j] == 1) {
        result++;
      }
    }
  }
  return result;
}
