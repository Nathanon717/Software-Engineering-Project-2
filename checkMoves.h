bool checkMoves(int colour, int testBoard[8][8]);

bool checkMoves(int colour, int testBoard[8][8]) { //verifies if an attempt to pass is valid by checking for legal moves
  //checks each square of the board one by one to see if current colour can legally go there, returns false after first legal move is found
  for(int i=0;i<8;i++) {
    for(int j=0;j<8;j++) {
      if(isValid(colour, testBoard, i, j)) {
        return false;
      }
    }
  }
  return true; //returns true if no square on the board can be played as a legal move, ie pass is valid
}
