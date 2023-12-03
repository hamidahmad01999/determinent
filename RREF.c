// Name : Hamid Ahmad
// Date: 29/Nov/2023
// Task: Covert matrix into RREF.

#include<stdio.h>
#include<stdbool.h>

#define ROWS 3
#define COLS 3



// 1:swaping rows 
    // main function in swapping is =>swapRowsWRTPivots() it swaps the rows this function first check the positons of pivots with the help of function =>pivotPostion() and if main function finds that it needs to change the position of rows it swaps the rows with the help of function =>swapRows()

// this function tells us the postion of pivot on which postion pivot is
// if position is 0 => it means pivot is on left most side or we can say the first element in row is pivot
// if position is 1000=> it means the provided row is a zero row
// this function gets matrix, rowNumber(the row whom pivot we want to know), and column
int pivotPosition(double matrix[ROWS][COLS],int rowNumber, int cols){

    double element;
    for(int i=0; i<cols; i++){
        element = matrix[rowNumber][i];
        // if element is not zero it means this is pivot so return it's index(for 1=index is 0. because indexing is starting from 0)
        if(element!=0){
            return i;
        }
    }

    // if given row is zero then return 1000 as index.
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



// Approach used to achieve the goal:
// First convert matrix into REF then converted into RREF
// For REF:
    // first arrange rows in matrix with respect to the positions of pivots in rows
        // and zero row will come at the end of matrix
    // secondly as matrix is arranged WRT positions of pivot so now we have to apply some matrix operation, I applied row operations in second step and by this we are getting REF 
    // one more thing in this code pivot value of REF is one not a random number

// Now for RREF:
    // As we already got the REF of a matrix in which pivots has value one so according to the definition of RREF I only need to make zero below and above the pivots of RREF but our REF function already made zero below the pivots so now we only need to make zero entry below pivot



#define ADJROWS 2
#define ADJCOLUMNS 2

// printing the matrix
void printMatrix(double matrix[ROWS][COLS],int rows,int cols){

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%5.1lf\t", matrix[i][j]);
        }
        printf("\n");
    }

    printf("\n");
}

// pivotPositions()function was here which is now moved to upward 

// this function swapRows swap two rows with each other
    // this functions gets matrix, number of rowOne and rowTwo, and number of columns in matrix
    // and then it change the position of rowOne with rowTwo
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

// this is main function to controll swapping
void swapRowsWRTPivots(double matrix[ROWS][COLS], int rows, int cols){

    // here i used the bubble sorting method to move the row of highest pivot to last row in matrix and row which has lowest pivot will come at first
    for(int i=0; i<=rows; i++){
        for(int j=0; j<rows; j++){

            // if the pivot position of row1 is greater than row2 then exchange it's position with second row
            if(pivotPosition(matrix, j, cols)>pivotPosition(matrix, j+1, cols)){
                swapRows(matrix,j,j+1, cols);
            }
        }
    }

}


// till now we swapped rows WRT to the pivots now we need to apply row operations(Actually this was most difficult task for me:) )
// Approacah Used:
    // first of all first loop(firs two loops) go through the matrix if at any postion it find an element it means it is pivots 
        // so divide the whole row with one to make pivot in that row 1 (value of pivot is stored in variable factor) =>third loop is used for this purpose
        // now we need to make zeros under that pivot for this first mulitple current row with the pivot of row below it(one by one) and then subtract current row with that row to make zero in that row below pivot. =>Fourth loop is used for this purpose 
        // after making zeros under pivot in current row we break the 2nd loop to enter in next row to apply same operations in next rows to get REF
void makePivotsForREF(double matrix[ROWS][COLS], int rows, int cols){
    double factor;
    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            if(matrix[i][j]!=0){
                factor=matrix[i][j];
                for(int k=0; k<cols; k++){
                    matrix[i][k]=matrix[i][k]/factor;
                }

                // this code is commented please don't uncomment this
                // for(int l=i+1; l<rows; l++){
                    
                //     double element=matrix[i][j]*(-matrix[l][j]);
                //     matrix[l][j]=matrix[l][j]+element;
                //     static int count=0;
                //     printf("count :%d\n",count);
                //     count++;
                // }
                // commenting code end here

                for(int l=i+1; l<rows; l++){
                    for(int k=0; k<cols; k++){
                        double element=matrix[i][k]*(-matrix[l][j]);
                        matrix[l][k]=matrix[l][k]+element;
                        static int count=0;
                        printf("count :%d\n",count);
                        count++;
                    }

                }
                break;
            }
        }

    }
   

}

// tell here we got REF so now we only need to get RREF
    // for this we only need to make enteries zero above pivot
    // because in previous function =>makePivotsForREF(). we made pivot one and make entries zero below pivots
    // to make enteries above the pivots zero (but in this function we suppsed that enteries below pivot is not zero. If REF function failed to make enteries below pivot zero so it will make them zero) 
        // in first two loop we go through matrix and where we find pivot(element/matrix[i][j]==1). we try to make entries above/below pivots zero by multiplying that current row with the values above/below of pivot and then subtract current row with the row of that element 
            // in second if condition loop will skip the current row to apply operations
            // in third if, if already entries below pivots are zero so it will not apply operations
    // in fourth loop by knowing which value we have to make zero we multiply that value with current row which has pivot 1. And then subtract current row with that row which eventually make that row entry zero(0).
    // After making entries below and above pivots zero we break the second loop and go to next row to apply these same operations
void makePivotsForRREF(double matrix[ROWS][COLS],int rows, int cols){

    double element;
    for(int i=1; i<rows; i++){
        for(int j=1; j<cols; j++){

            if(matrix[i][j]==1){
                for(int k=0; k<rows; k++){

                    // skip to apply operations on current row
                    if(k==i){
                        continue;
                    }

                    for(int l=0; l<cols; l++){
                        if(matrix[k][l]==0){
                            // break loop if entry already zero
                            continue;
                        }
                        // multiply element with current row and then subtract current row with that emelment's row to make zero in that entry
                        element=-(matrix[k][j]*matrix[i][l]);
                        matrix[k][l]=matrix[k][l]+element;
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


// this is controlling function for RREF it calls all function which we need to make a matrix RREF and it prints the RREF matrix
void makeRREF(double matrix[ROWS][COLS],int rows, int cols){


    makeREF(matrix, rows, cols);

    makePivotsForRREF(matrix, rows, cols);
    printf("RREF is:\n");
    // print RREF matrix
    printMatrix(matrix, rows,cols);

}

// start main function
int main(){
    // declaring 2D array to store matrix
    static double matrix[ROWS][COLS];
    printf("Please enter elements for %d by %d matrix!\n", ROWS, COLS);

    // ask user to enter entries
    for (int i = 0; i < ROWS; i++) {
        double matrix_element;
        for (int j = 0; j < COLS; j++) {
            printf("Please enter %d element of %d row.\n", (j + 1), (i + 1));
            scanf("%lf", &matrix_element);
            matrix[i][j] = matrix_element;
        }
    }
    printf("Your matrix is:\n");
    printMatrix(matrix, ROWS, COLS);


    // call RREF function
    makeRREF(matrix,ROWS, COLS);

    return 0;
}
// ends main function