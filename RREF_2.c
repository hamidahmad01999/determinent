// Name : Hamid Ahmad
// Date: 29/Nov/2023
// Task: This program find rref but in different way that used other file diffence is in finding ref
#include<stdio.h>
#include<stdbool.h>
#define ROWS 4
#define COLS 4

#define ADJROWS 2
#define ADJCOLUMNS 2

int pivotPosition(double matrix[ROWS][COLS],int rowNumber, int cols){
    double element;
    for(int i=0; i<cols; i++){
        element = matrix[rowNumber][i];
        if(element!=0){
            return i;
        }
    }
    return 1000;
}

// check whether matrix is ref or not
bool isREF(double matrix[ROWS][COLS], int rows, int cols){


    for(int i=0; i<rows-1; i++){
        if(pivotPosition(matrix, i, cols)<=pivotPosition(matrix, i+1, cols)){

        }else{
            return false;
        }
    }

    return true;
}



void printMatrix(double matrix[ROWS][COLS],int rows,int cols){

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%5.2lf\t", matrix[i][j]);
        }
        printf("\n");
    }

    printf("\n");
}

void swapRows(double matrix[ROWS][COLS], int rowOne, int rowTwo, int cols){
    int copyOfRowOne[cols];
    // make a copy of row one
    for(int i=0; i<cols; i++){
        copyOfRowOne[i]=matrix[rowOne][i];
    }

    // replace/paste row 2 at position of row 1
    for(int i=0; i<cols; i++){
        matrix[rowOne][i]=matrix[rowTwo][i];
    }

    // now paste row one at position of row Two
    for(int i=0; i<cols; i++){
        matrix[rowTwo][i]=copyOfRowOne[i];
    }

}

void swapRowsWRTPivots(double matrix[ROWS][COLS], int rows, int cols){

    for(int i=0; i<=rows; i++){
        for(int j=0; j<rows; j++){
            if(pivotPosition(matrix, j, cols)>pivotPosition(matrix, j+1, cols)){
                swapRows(matrix,j,j+1, cols);
            }
        }
    }

}

void makePivotsForREF(double matrix[ROWS][COLS], int rows, int cols){
    double factor;
    double copyRow[cols];
    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            if(matrix[i][j]!=0){
                
                factor=matrix[i][j];
                for(int k=0; k<cols; k++){
                    copyRow[k]=matrix[i][k]/factor;
                }
                
                double multipleRow[cols];
                for(int l=i+1; l<rows; l++){
                    double multiple=matrix[l][j];
                    
                    for(int n=0; n<cols; n++){
                        multipleRow[n]=copyRow[n]*(-multiple);
                    }

                    for(int m=0; m<cols; m++){

                        matrix[l][m]=matrix[l][m]+multipleRow[m];
                    }
                    
                }
                break;
            }
        }

    }
    

    

}

void makeREF(double matrix[ROWS][COLS], int rows, int cols){
    swapRowsWRTPivots(matrix, rows, cols);
    makePivotsForREF(matrix, rows, cols);

    // new added condition
    if(isREF(matrix,rows,cols)!=1){
        makeREF(matrix, rows, cols);
    }

    printf("REF of matrix is:\n");
    printMatrix(matrix, rows, cols);
}

void makePivotsForRREF(double matrix[ROWS][COLS],int rows, int cols){
    double element, pivotOne;
    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            pivotOne=matrix[i][j];
            if(pivotOne!=0){
                for(int m=0; m<cols; m++){
                    matrix[i][m]=matrix[i][m]/pivotOne;
                }
            }
            if(matrix[i][j]==1){
                for(int k=0; k<rows; k++){
                    if(k==i){
                        continue;
                    }
                    for(int l=0; l<cols; l++){
                        if(matrix[k][l]==0){
                            continue;
                        }
                        element=-(matrix[k][j]*matrix[i][l]);
                        matrix[k][l]=matrix[k][l]+element;
                    }
                }
                break;
            }
        }
    }

}

void makeRREF(double matrix[ROWS][COLS],int rows, int cols){
    // swapRowsWRTPivots(matrix,rows,cols);
    // makePivotsForREF(matrix, rows, cols);
    makeREF(matrix, ROWS, cols);
    makePivotsForRREF(matrix, rows, cols);
    printf("RREF is:\n");
    printMatrix(matrix, rows,cols);
}



int main(){

    static double matrix[ROWS][COLS];
    static double cofactors[ROWS][COLS];

    printf("Please enter elements for %d by %d matrix!\n", ROWS, COLS);
    for (int i = 0; i < ROWS; i++) {
        double matrix_element;
        for (int j = 0; j < COLS; j++) {
            printf("Please enter %d element of %d row.\n", (j + 1), (i + 1));
            scanf("%lf", &matrix_element);
            matrix[i][j] = matrix_element;
        }
    }
    printf("Matrix you entered is:\n");
    printMatrix(matrix, ROWS, COLS);
    makeRREF(matrix, ROWS, COLS);

    return 0;

}