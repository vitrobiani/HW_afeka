#ifndef PICTURELINES
#define PICTURELINES
#define ROWS 50
#define COLS 50

void addLines();

int getLine(int row, int col, int* px1 , int* py1 , int* px2 , int* py2);

void insertLine(int row , int col , int x1 , int y1 , int x2 , int y2 , int* mat);

void printEMat(int row , int col , const int* mat);

void getEffectiveSize(int* row, int* col);

int checkIfLineIntercepts(int row, int col, int x1, int y1, int x2, int y2, int *mat);

#endif // !PICTURELINES

