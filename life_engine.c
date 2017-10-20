#include "life_engine.h"

/* A game-of-life configuration is stored as a life_board structure.
 * See life_engine.h for more explanation.
 */

/********************************************************************
 * read_board_from_file - reads a given file for the board
 ********************************************************************/
void read_board_from_file(char *filename, life_board *board)
{
  FILE *fp = fopen(filename, "r");
  char lines[MAX_ROWS][MAX_COLS];
  if (NULL==fp) {
    fprintf(stderr, "Cannot open file %s\n, killing self.", filename);
    exit(-1);
  }
  // Guarded against fopen failures
  int row_count = 0;
  int col_count = -1;
  while (!feof(fp) &&
        fgets(lines[row_count], MAX_COLS, fp)) {
    // poor man's trim
    char *line = lines[row_count];
    while (line[strlen(line)-1]=='\n' || line[strlen(line)-1]==' ')
      line[strlen(line)-1]=0;

    int this_col_count = strlen(line);
    if (col_count>0 && this_col_count!=col_count) {
      fprintf(stderr, "Uneven number of columns!\n killing self.");
      exit(-2);
    }
    col_count = this_col_count;
    row_count++;
  }
  DEBUG("num_rows=%d, num_cols=%d\n", row_count, col_count);
  board->num_rows = row_count;
  board->num_cols = col_count;

  size_t nbytes = row_count*col_count*sizeof(unsigned char);
  board->cells = (unsigned char *) malloc(nbytes);

  for (int row=0;row<board->num_rows;++row) {
    for (int col=0;col<board->num_cols;++col) {
      if (lines[row][col]=='*')
        set_alive(*board, row, col);
      else
        set_dead(*board, row, col);
    }
  }
}

/********************************************************************
 * get_index - returns the index into the 1d array
 *    corresponding to the cell location (row, col).
 ********************************************************************/
int get_index(life_board board, int row, int col)
{
  int index = board.num_cols*row+col;
	return index; // TODO: implement me
}
/********************************************************************
 * set_alive - set the given cell to alive
 ********************************************************************/
void set_alive(life_board board, int row, int col)
{
  board.cells[get_index(board, row, col)] = 1;
}

/********************************************************************
* set_dead - set the given cell to dead
********************************************************************/
void set_dead(life_board board, int row, int col)
{
  board.cells[get_index(board, row, col)] = 0;
}


/********************************************************************
 * print_board - prints the board to stdout.
 *    a . indicates an empty square; a * indicates a "live" cell.
 *******************************************************************/
 void print_board(life_board board)
 {
   for (int row=0;row<board.num_rows;++row) {
     for (int col=0;col<board.num_cols;++col) {
       char cell_marker = (board.cells[get_index(board,row,col)]==0)?'.':'*';
       printf("%c", cell_marker);
     }
     printf("\n");
   }
 }

/***********************************************************************
 * is_in_range - returns 0 or 1 indicating whether the given location is
 *    a valid location on this board, assuming 0-indexing.
 ***********************************************************************/
int is_in_range(life_board board, int row, int col)
{
  if(row >= 0 && col >= 0 && row < board.num_rows && col < board.num_cols){
    return 1;
  }
	return 0; // TODO: implement me
}

/***********************************************************************
 * is_alive - returns 1 if whether a given cell is alive and 0 otherwise.
 *    moreover, it will return 0 if the given location is out of range.
 ***********************************************************************/
int is_alive(life_board board, int row, int col)
{
  if(board.cells[get_index(board,row,col)] == 1 && is_in_range(board,row,col) == 1){
    return 1;
  }
	return 0; // TODO: implement me
}

/***********************************************************************
 * count_live_nbrs - returns the number of alive neighbors that a cell
 *    has by adding together the result of is_alive for all 8 directions.
 ***********************************************************************/
int count_live_nbrs(life_board board, int row, int col)
{
  int liveNeighbors = 0;
  //North
  if(is_alive(board,row,col+1) == 1){
    liveNeighbors++;
  }
  //South
  if(is_alive(board,row,col-1) == 1){
    liveNeighbors++;
  }
  //West
  if(is_alive(board,row-1,col) == 1){
    liveNeighbors++;
  }
  //East
  if(is_alive(board,row+1,col) == 1){
    liveNeighbors++;
  }
  //NorthWest
  if(is_alive(board,row-1,col+1) == 1){
    liveNeighbors++;
  }
  //NorthEast
  if(is_alive(board,row+1,col+1) == 1){
    liveNeighbors++;
  }
  //SouthWest
  if(is_alive(board,row-1,col-1) == 1){
    liveNeighbors++;
  }
  //SouthEast
  if(is_alive(board,row+1,col-1) == 1){
    liveNeighbors++;
  }

	return liveNeighbors; // TODO: implement me
}

/***********************************************************************
 * make_next_board - takes the current board and produces (by calling
 *    set_alive, set_dead) the next-generation board according to the
 *    rules of game of life.
 ***********************************************************************/
void make_next_board(life_board current, life_board next)
{
  for(int i=0;i<current.num_rows;i++){
    for(int j=0;j<current.num_cols;j++){
      if(is_alive(current,i,j)){
        //If a cell is alive and has 2 or 3 live neighbors, it will remain alive in the next generation.
        if(count_live_nbrs(current,i,j)==2 || count_live_nbrs(current,i,j)==3){
          set_alive(next,i,j);
        }
        // for case with fewer than 2 neighbors, or more than 3; set_dead
        else {
          set_dead(next,i,j);
        }
      }else{
        // If a cell is dead and has exactly 3 live neighbors, new org will be born
        // so set_alive. Else, it remains dead.
        if(count_live_nbrs(current,i,j)==3){
          set_alive(next,i,j);
        }
        //remains dead so no need to set_dead again???
        // else{
        //   set_dead(next,i,j);
        // }
      }
    }
  }
	// return 0; // TODO: implement me
}
