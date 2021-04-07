bool isValid(int colour, int board[8][8], int i, int j);

bool isValid(int colour, int board[8][8], int i, int j) { //if move is valid, updates board appropriately and return true, otherwise return false
  //variables for 8 directions, value of 1 meaning they should be checked for a valid pattern of pieces, useful as some directions may be ruled out easily due to the move being too close to the edge
  //of the board. For example pieces placed on square a1 or b2 can only capture pieces to their right, bottom right, and below them. In general, being on or immediately next to an edge rules out
  //3 directions, and corners rule out 5 directions.
  int top=1, topRight=1, right=1, botRight=1, bot=1, botLeft=1, left=1, topLeft=1, oppositeColour, x, y;
  bool valid=false;
  if(board[i][j] != 0) { //if is not empty, move is invalid
    return false;
  }

  if(colour == 1) { //if colour is black, opposite colour is white or vise vera
    oppositeColour=2;
  } else {
    oppositeColour=1;
  }

  if(i<2) { //if move is on the 1st or 2nd row, dont check above
    top=0;
    topLeft=0;
    topRight=0;
  }
  if(i>5) { //if move is on the 7th or 8th row, dont check below
    bot=0;
    botLeft=0;
    botRight=0;
  }
  if(j<2) { //if move is on the 1st or 2nd column, dont check to the left
    left=0;
    topLeft=0;
    botLeft=0;
  }
  if(j>5) { //if move is on the 7th or 8th column, dont check to the right
    right=0;
    topRight=0;
    botRight=0;
  }

  //checks appropriate directions for sequence of opposite colour pieces followed by same colour piece (the comments below apply to all 8 directions, and each section of code is labeled with the direction being searched)
  // Top ///////////////////////////////////////////////////////////////////////
  if(top=1 && board[i-1][j] == oppositeColour) { // if direction should be checked and square immediately in that direction has oppisite colour piece on it
    for(y=i-1;y>=0;y--) { //check squares in that direction until...
      if(board[y][j] == 0) { //empty square is found
        break; //check next direction
      }
      if(board[y][j] == colour) { //same colour piece is found
        valid=true; //move is valid
        //go back and replace all the oppisite colour pieces checked with the current colour
        y += 1;
        while(y<i) {
          board[y][j]=colour;
          y++;
        }
        break; //check next direction
      }
    }
  }

  // Top Right /////////////////////////////////////////////////////////////////
  if(topRight=1 && board[i-1][j+1] == oppositeColour) {
    x=j+1;
    for(y=i-1;y>=0;y--) {
      if(x>7) {
        break;
      }
      if(board[y][x] == 0) {
        break;
      }
      if(board[y][x] == colour) {
        valid=true;
        x -= 1;
        y += 1;
        while(y<i) {
          board[y][x]=colour;
          x--;
          y++;
        }
        break;
      }
      x++;
    }
  }

  // Right /////////////////////////////////////////////////////////////////////
  if(right=1 && board[i][j+1] == oppositeColour) {
    for(x=j+1;x<=7;x++) {
      if(board[i][x] == 0) {
        break;
      }
      if(board[i][x] == colour) {
        valid=true;
        x -= 1;
        while(x>j) {
          board[i][x]=colour;
          x--;
        }
        break;
      }
    }
  }

  // Bottom Right //////////////////////////////////////////////////////////////
  if(botRight=1 && board[i+1][j+1] == oppositeColour) {
    x=j+1;
    for(y=i+1;y<=7;y++) {
      if(x>7) {
        break;
      }
      if(board[y][x] == 0) {
        break;
      }
      if(board[y][x] == colour) {
        valid=true;
        x -= 1;
        y -= 1;
        while(y>i) {
          board[y][x]=colour;
          x--;
          y--;
        }
        break;
      }
      x++;
    }
  }

  // Bottom ////////////////////////////////////////////////////////////////////
  if(bot=1 && board[i+1][j] == oppositeColour) {
    for(y=i+1;y<=7;y++) {
      if(board[y][j] == 0) {
        break;
      }
      if(board[y][j] == colour) {
        valid=true;
        y -= 1;
        while(y>i) {
          board[y][j]=colour;
          y--;
        }
        break;
      }
    }
  }

  // Bottom Left ///////////////////////////////////////////////////////////////
  if(botLeft=1 && board[i+1][j-1] == oppositeColour) {
    x=j-1;
    for(y=i+1;y<=7;y++) {
      if(x<0) {
        break;
      }
      if(board[y][x] == 0) {
        break;
      }
      if(board[y][x] == colour) {
        valid=true;
        x += 1;
        y -= 1;
        while(y>i) {
          board[y][x]=colour;
          x++;
          y--;
        }
        break;
      }
      x--;
    }
  }

  // Left //////////////////////////////////////////////////////////////////////
  if(left=1 && board[i][j-1] == oppositeColour) {
    for(x=j-1;x>=0;x--) {
      if(board[i][x] == 0) {
        break;
      }
      if(board[i][x] == colour) {
        valid=true;
        x += 1;
        while(x<j) {
          board[i][x]=colour;
          x++;
        }
        break;
      }
    }
  }

  // Top Left //////////////////////////////////////////////////////////////////
  if(topLeft=1 && board[i-1][j-1] == oppositeColour) {
    x=j-1;
    for(y=i-1;y>=0;y--) {
      if(x<0) {
        break;
      }
      if(board[y][x] == 0) {
        break;
      }
      if(board[y][x] == colour) {
        valid=true;
        x += 1;
        y += 1;
        while(y<i) {
          board[y][x]=colour;
          x++;
          y++;
        }
        break;
      }
      x--;
    }
  }

  return valid;
}
