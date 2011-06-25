/* 

Game of life, written just for kicks
cl3mens 2011-06-19
updated 2011-06-23

*/

#include <stdio.h>

int dispField[24][80];
int workField[24][80];
int arrXLen=80; /*sizeof(workField[0])/sizeof(int);*/
int arrYLen=24; /*(sizeof(workField)/sizeof(int))/arrXLen;*/
int active=0;
int empty=0;
int stale=0;
int alone=0;
int overcrowd=0;
int born=0;
int gen=0;

/* We need a better function for this */
int fillRow() {
  int row;
  for(row=0;row<arrYLen;row++) {
    int col;
    for(col=0;col<arrXLen;col++) {
      dispField[row][col] = rand() %2;
    }
  }
}

/* Copy the current field to workField and read values from there. Write the
   new row to dispField */

int copyField() {
  int row;
  for(row=0;row<arrYLen;row++) {
    int col;
    for(col=0;col<arrXLen;col++) {
      workField[row][col] = dispField[row][col];
    }
  }
}

int studyRow(row) {
  int overRow=row-1;
  int underRow=row+1;

  /* Make the row wrap-around happen */
  if(row==arrYLen-1) {
    /* Last row */
    underRow=0;
  } else if(row==0) {
    /* First row */
    overRow=arrYLen-1;
  }

  int col;
  for(col=0;col<arrXLen;col++) {
    int leftCol=col-1;
    int rightCol=col+1;
    int flanders=0;

    /* Make col wrap-around happen */
    if(col==0) {
      /* First col */
      leftCol=arrXLen-1;
    } else if(col==arrXLen-1) {
      /* Last col */
      rightCol=0;
    } 
    
    /* How many neighbours? */
    if(workField[overRow][leftCol]==1) {
      flanders++;
    }
    if(workField[overRow][col]==1) {
      flanders++;
    }
    if(workField[overRow][rightCol]==1) {
      flanders++;
    }
    if(workField[row][leftCol]==1) {
      flanders++;
    }
    if(workField[row][rightCol]==1) {
      flanders++;
    }
    if(workField[underRow][leftCol]==1) {
      flanders++;
    }
    if(workField[underRow][col]==1) {
      flanders++;
    }
    if(workField[underRow][rightCol]==1) {
      flanders++;
    }

    if(workField[row][col]==1) {
      active++;
      
      if(flanders<2) {
	alone++;
	dispField[row][col]=0;
      } else if(flanders==2 || flanders==3) {
	stale++;
      } else {
	overcrowd++;
	dispField[row][col]=0;
      }
    } else {
      empty++;
      
      if(flanders==3) {
	born++;
	dispField[row][col]=1;
      }
    }
    /* Uncomment for debug
    printf("%d,%d: %d\n",row,col,flanders);
    */
  }
}

int calcField() {
  int row;
  for(row=0;row<arrYLen;row++) {
    studyRow(row);
  }
}

int printField() {
  int row;
  for(row=0;row<arrYLen;row++) {
    int col;
    for(col=0;col<arrXLen;col++) {
      if(dispField[row][col]==1) {
	printf("*");
      } else {
	printf(" ");
      }
    }
    printf("\n");
  }
}


int main(int argc, char *argv[]) {
  fillRow();

  while(main) {
    system("clear");
    gen++;
    printf("Generation %d\n",gen);
    printField();
    copyField();
    calcField();
    sleep(1);
  }

  /* Uncomment for debug...
  printf("%d fields active\n",active);
  printf("%d fields empty\n",empty);
  printf("%d fields alone\n",alone);
  printf("%d fields stale\n",stale);
  printf("%d fields overcrowded\n",overcrowd);
  printf("%d fields born\n",born);
  */
}
