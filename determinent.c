// Name : Hamid Ahmad
// Date: 29/Nov/2023
// Task: Get determinent of matrix.

// it will work for 3 BY 3 matrix
// Approach used to achieve the goal:
// to get determinent of matrix I get the cofactors of first rows then add them and subtract the second to get determinent
    // as we need deter of 2 by 2 to get cofactor so one of the function give us the deter =>determinent2By2() 
    // second function decide and pass the values to first defined function whom determinent we need to get to find cofactor and then that function also responsible to give the determinent


#include<stdio.h>
#define ROWS 3
#define COLS 3



#define ADJROWS 2
#define ADJCOLUMNS 2

// it will print matrix
void printMatrix(double matrix[ROWS][COLS],int rows,int cols){

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%5.1lf\t", matrix[i][j]);
        }
        printf("\n");
    }

    printf("\n");
}

// it will give the determinent 
double determinent2By2(double matrix[ADJROWS][ADJCOLUMNS], int rows, int cols){
    double value1=1, value2=1;

    value1=value1*matrix[0][0];
    value1=value1*matrix[1][1];

    value2=value2*matrix[0][1];
    value2=value2*matrix[1][0];
    double determinentOfMatrix= value1-value2;
    return determinentOfMatrix;
}

//  this function is deciding the elements for adjoint2By2 function and also responsible to send/give determinent of MAtrix
// Approach folloed:
    // first it goes throug matrix(first two loops)
    // then in third and fourth loop => decide which values we need to send and it will skip that element of matrix which are in the same row/column of that element (by using first if condition)
void determinentOfMatrix(double matrix[ROWS][COLS], int rows, int cols, double cofactorsMatrix[ROWS][COLS]){
    double cofactorElements[2][2];
    int countRows=0;
    int countCOl=0;
    float deter=0;

    for(int i=0; i<1; i++){
        for(int j=0; j<cols; j++){         
            countCOl=0;
            countRows=0;
            for(int k=0; k<rows; k++){
                for(int l=0; l<cols; l++){
                    // if element belongs to it's own row/column then stop here and go to next element
                    if(k==i || l==j){
                        continue;
                    }else{ 
                        cofactorElements[countRows][countCOl]=matrix[k][l];
                        
                        // it is telling location of element in that matrix which we passed to adjoint2By2 function
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
            // this variable (element) has cofactor of element 
            double element=determinent2By2(cofactorElements, 2,2);
            static int counter=1;
            // deciding whether we need to add it or subtract
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
    printf("Deter is: %.1f\n",deter);
}


// starts main function
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
    
    // give the determinent of matrix
    determinentOfMatrix(matrix, ROWS,COLS, cofactors);

    return 0;

}
// ends main function