// Name : Hamid Ahmad
// Date: 29/Nov/2023
// Task: Give inverse of matrix.

// it will work for 3 BY 3 matrix
// Approach used to achieve the goal:
    // first we need to find determinent of matrix for which we used same technique for which you can check file of determinent
    // secondly for adjoint:
        // for this we need to find cofactor of each element of matrix for which we used a technique which is similar to technique used in a function in determinent for refrence you can check determinent file to know how it works
        // then we took transport of matrix to get adjoint of matrix

#include<stdio.h>
#define ROWS 3
#define COLS 3



#define ADJROWS 2
#define ADJCOLUMNS 2

// print matrix
void printMatrix(double matrix[ROWS][COLS],int rows,int cols){

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%5.2lf\t", matrix[i][j]);
        }
        printf("\n");
    }

    printf("\n");
}


// get determinent of 2by2matrix
double ajdOfMatrix2By2(double matrix[ADJROWS][ADJCOLUMNS], int rows, int cols){
    double value1=1, value2=1;

    value1=value1*matrix[0][0];
    value1=value1*matrix[1][1];

    value2=value2*matrix[0][1];
    value2=value2*matrix[1][0];
    double determinentOfMatrix= value1-value2;
    return determinentOfMatrix;
}

// determinent of 3By3 matrix
double determinentOfMatrix(double matrix[ROWS][COLS], int rows, int cols, double cofactorsMatrix[ROWS][COLS]){
    double cofactorElements[2][2];
    int countRows=0;
    int countCOl=0;
    double deter=0;
    for(int i=0; i<1; i++){
        for(int j=0; j<cols; j++){         
            countCOl=0;
            countRows=0;
            for(int k=0; k<rows; k++){
                for(int l=0; l<cols; l++){
                    if(k==i || l==j){
                        continue;
                    }else{ 
                        cofactorElements[countRows][countCOl]=matrix[k][l];
                        
                        if(countCOl==1){
                            countRows++;
                            countCOl=0;
                        }else if(countCOl==1 && countRows==1){
                            countCOl=0;
                            countRows=0;
                        }else{
                            countCOl++;

                        }
                    }
                }
                
            }
            double element=ajdOfMatrix2By2(cofactorElements, 2,2);
            static int counter=1;
            if(counter%2==0){
                deter=deter - (matrix[i][j]*element);
                counter++;
            }else{
                deter=deter+ (matrix[i][j]*element);
                counter++;
            }
            cofactorsMatrix[i][j]=element;
        }
    }
    return deter;
}


// this function =>decideCofactor(). decide element to get cofactor of element and pass that element in form of 2By2 matrix to adoint2By2 function and create a new cofactorsMatrix which contain cofactors of original matrix
void decideCofactor(double matrix[ROWS][COLS], int rows, int cols, double cofactorsMatrix[ROWS][COLS]){
    double cofactorElements[2][2];
    int countRows=0;
    int countCOl=0;

    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){           
            countCOl=0;
            countRows=0;
            for(int k=0; k<rows; k++){
                for(int l=0; l<cols; l++){
                    if(k==i || l==j){
                        continue;
                    }else{                       
                        cofactorElements[countRows][countCOl]=matrix[k][l];
                        if(countCOl==1){
                            countRows++;
                            countCOl=0;
                        }else if(countCOl==1 && countRows==1){
                            countCOl=0;
                            countRows=0;
                        }else{
                            countCOl++;

                        }
                    }
                }
            }
            double element=ajdOfMatrix2By2(cofactorElements, 2,2);
            if((i+j)%2!=0){
                element=-element;
            }
            cofactorsMatrix[i][j]=element;
        }
    }
    
}

// this is main function for adjoint of matrix. It gets the cofactorsMatrix and then take element from that matrix and create a newMatrix which is transport to that matrix
void adjointOfMatrix(double cofactorsMatrix[ROWS][COLS], double adjointMatrix[ROWS][COLS], int rows, int cols){
    double element;
    
    // create transport => tranpost of cofactorsOfMatrix is called adjoint matrix
    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){

            element=cofactorsMatrix[i][j];
            adjointMatrix[j][i]=element;
        }
    }
}

// main function for inverse of matrix
void inverseOfMatrix(double matrix[ROWS][COLS],double adjointMatrix[ROWS][COLS],double inverseMatrix[ROWS][COLS],double cofactorsMatrix[ROWS][COLS],int rows, int cols){
    
    decideCofactor(matrix,ROWS,COLS, cofactorsMatrix);
    adjointOfMatrix(cofactorsMatrix, adjointMatrix, ROWS, COLS);
    double determinent = determinentOfMatrix(matrix,ROWS, COLS,cofactorsMatrix);

    // if determinent is zero then it means inverse of this matrix does not exist
    if(determinent==0){
        printf("As determinent is zero so the inverse of this matrix does not exists!\n");
    }else{
        // if determinent is possible then divide each element of ajoint of matrix with determinent to get inverse of matrix
        for(int i=0; i<rows; i++){
            for(int j=0; j<cols; j++){
                inverseMatrix[i][j]=((adjointMatrix[i][j])/determinent);
            }
        }
        // print inverse of matrix
        printf("Inverse of your matrix is:\n");
        printMatrix(inverseMatrix,ROWS, COLS);
    }   
}


// start main function
int main(){

    static double matrix[ROWS][COLS];
    static double cofactorsMatrix[ROWS][COLS];
    double adjointMatrix[ROWS][COLS];
    double inverseMatrix[ROWS][COLS];

    printf("Please enter elements for %d by %d matrix!\n", ROWS, COLS);
    for (int i = 0; i < ROWS; i++) {
        double matrix_element;
        for (int j = 0; j < COLS; j++) {
            printf("Please enter %d element of %d row.\n", (j + 1), (i + 1));
            scanf("%lf", &matrix_element);
            matrix[i][j] = matrix_element;
        }
    }
    printf("Your matrix is:\n");
    printMatrix(matrix,ROWS,COLS);
    inverseOfMatrix(matrix, adjointMatrix,inverseMatrix,cofactorsMatrix, ROWS,COLS);

    return 0;
}
