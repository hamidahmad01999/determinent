// Name : Hamid Ahmad
// Date: 29/Nov/2023
// Task: Get determinent of matrix. This program use ref of matrix to calculate determinent
// This program can only find determinent for square matrixes.
#include<stdio.h>
#include<stdbool.h>
#define ROWS 5
#define COLS 5
#define ADJROWS 2
#define ADJCOLUMNS 2

static int noOfzeroRows=0;
void zeroRows(double matrix[ROWS][COLS], int rows, int cols){

    for(int i=0; i<rows; i++){
        
        for(int j=0; j<cols; j++){
            double element=matrix[i][j];
            // printf("%lf\t",element);
            if(element!=0){
                break;
            }else if(j==cols-1 && element==0){
                noOfzeroRows++;
            }
        }

    }

}

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

// check pivot positions and change row positions according to pivots positon
void swapRowsWRTPivots(double matrix[ROWS][COLS], int rows, int cols){

    for(int i=0; i<=rows; i++){
        for(int j=0; j<rows; j++){
            if(pivotPosition(matrix, j, cols)>pivotPosition(matrix, j+1, cols)){
                swapRows(matrix,j,j+1, cols);
            }
        }
    }

}

// first make pivot of current row zero and copy it don't apply these changes on matrix
// and that copied row multipy with the number under the pivot and subtract that row to make that number under the pivot zero

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


void determinent(double matrix[ROWS][COLS], int rows, int cols){
    makeREF(matrix, rows,cols);
    zeroRows(matrix, rows, cols);
    double deter=1,element;
    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            element = matrix[i][j];
            
            // but zeros row can be present at last in this case element can be zero 
            if(j==cols-1 && i>=rows-noOfzeroRows && element==0){
                deter = deter*element;  
            }

            // if element is not zero it means it is pivot as pivot can't be zero
            if(element!=0){
                deter = deter*element;
                break;
            }
        }
    }
    printf("Deter is: %.1lf", deter);
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
    
    
    determinent(matrix, ROWS,COLS);

    return 0;

}