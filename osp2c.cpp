#include <pthread.h>
#include <iostream>

using namespace std;

/**************************
     Thread Methods
**************************/
void *row_check(void *arg);
void *col_check(void *arg);
void *box_check(void *arg);

/***************************
          Sudoku Class
 *************************/
class Sudoku{

  int puzzle[9][9];

public:

Sudoku()
  {
    int temp, ii, jj;
    for(ii=0; ii<9; ii++)
      {
	for(jj=0; jj<9; jj++)
	  {
	    cin >> puzzle[ii][jj];
	  }
      }
  }
  
  int get_val(int row, int col)
  {
    if(row > 8 || row < 0 || col > 8 || col < 0)
      return -1;

    return puzzle[row][col];
  }

  void set_val(int row, int col, int val)
  {
    if(row > 8 || row < 0 || col > 8 || col < 0
       || val < 1 || val > 9)
      return;

    puzzle[row][col] = val;
  }

  void print()
  {
    int ii, jj;
    for(ii = 0; ii < 9; ii++)
    {
      for(jj = 0; jj < 9; jj++)
	{
	  cout << to_string(get_val(ii,jj)) << " " ;
	}
      cout << endl;
    }
  
  }

};

/*************************************************/

/*****************************
     Global Return Variabls
******************************/
bool row_status, col_status, box_status;

/******************************
     Main
*******************************/
int main(int args, char* argv[])
{
  Sudoku sud = Sudoku();
  int ii, jj;
  pthread_t row_t, col_t, box_t;

  pthread_create(&row_t, NULL, row_check, &sud);
  pthread_create(&col_t, NULL, col_check, &sud);
  pthread_create(&box_t, NULL, box_check, &sud);
  pthread_join(row_t, NULL);
  pthread_join(col_t, NULL);
  pthread_join(box_t, NULL);

  
  if(row_status && box_status && col_status)
    {
      cout << "1" << endl;
    }
  else
    {
      cout << "0" << endl;
    }
  
}

void *row_check(void *arg)
{
  Sudoku *sud = static_cast<Sudoku *>(arg);
  int ii, jj, kk;
  bool found[9];
  
  
  for(ii = 0; ii < 9; ii++)
    {
        for(kk = 0; kk < 9; kk++)
	  found[kk] = false;
	
      for(jj = 0; jj<9; jj++)
	{
	  if(found[sud->get_val(ii,jj) - 1])
	    {
	      row_status = false;
	      pthread_exit(&row_status);
	    }
	  else
	    {
	      found[sud->get_val(ii,jj) - 1] = true;
	    }
	}
    }
  row_status = true;
  pthread_exit(&row_status);
}


void *col_check(void *arg)
{
  Sudoku *sud = static_cast<Sudoku *>(arg);
  int ii, jj, kk;
  bool found[9];
  
  
  for(jj = 0; jj < 9; jj++)
    {
        for(kk = 0; kk < 9; kk++)
	  found[kk] = false;
	
      for(ii = 0; ii<9; ii++)
	{
	  if(found[sud->get_val(ii,jj) - 1])
	    {
	      col_status = false;
	      pthread_exit(&col_status);
	    }
	  else
	    {
	      found[sud->get_val(ii,jj) - 1] = true;
	    }
	}
    }
  col_status = true;
  pthread_exit(&col_status);

}

void *box_check(void *arg)
{
 Sudoku *sud = static_cast<Sudoku *>(arg);
 int ii, jj, kk, mm;
  bool found[9];
  
  
  for(ii = 0; ii < 9; ii+=3)
    {
      for(jj = 0; jj<9; jj+=3)
	{
	  for(kk = 0; kk < 9; kk++)
	    found[kk] = false;
	
	  for(kk = 0; kk < 3; kk++)
	    {
	      for(mm = 0; mm < 3; mm++)
		{
		  if(found[sud->get_val(ii+kk,jj+mm) - 1])
		    {
		      box_status = false;
		      pthread_exit(&box_status);
		    }
		  else
		    {
		      found[sud->get_val(ii+kk,jj+mm) - 1] = true;
		    }
		}
	    }
	}
    }
  box_status = true;
  pthread_exit(&box_status);

}
