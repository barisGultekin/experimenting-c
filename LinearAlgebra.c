#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Matrix {
    int row;
    int column;
    double *data;
};

struct Vector {
    int length;
    double *data;
};

int isZero(double input) {
    if(input < 2.22e-16 && input > -(2.22e-16)){
        return 1;
    } else {
        return 0;
    }
}

void matrixInit(struct Matrix *M) {
    printf("Row: ");
    scanf("%i", &M->row);
    printf("Column: ");
    scanf("%i", &M->column);
    M->data = malloc(sizeof(double) * M->row * M->column);
    
    for(int i=0; i<M->row; i++) {
        for(int j=0; j<M->column; j++){
            printf("A[%i][%i]: ",i,j);
            scanf("%lf", (M->data + M->column * i + j));
        }
    }
}

void nPrint(struct Matrix M) {
    printf("\n");
    for(int i=0; i<M.row; i++) {
        printf("[");
        for(int j=0; j<M.column; j++){
            printf("%lf", *(M.data + M.column * i + j));
            j == M.column-1 ? printf("") : printf(", ");
        }
        printf("]\n");
    }
}

void swapRows(struct Matrix *M, int rowA, int rowB) {
    const size_t rowLength = sizeof(double) * M->column;
    double *tempData = malloc(rowLength);
    memcpy(tempData, M->data + M->column * rowA, rowLength);
    memcpy(M->data + M->column * rowA, M->data + M->column * rowB, rowLength);
    memcpy(M->data + M->column * rowB, tempData, rowLength);
    free(tempData);
}


void matrixAdd(struct Matrix *M1, struct Matrix *M2, struct Matrix *res) {
    if(M1->row == M2->row && M1->column == M2->column) {
        res->row = M1->row;
        res->column = M1->column;
        res->data = malloc(sizeof(double) * M1->column * M2->column);
        for(int i=0 ; i < res->row ; i++) {
            for(int j=0 ; j < res->column ; j++) {
                *(res->data + res->column * i + j) = *(M1->data + M1->column * i + j) + *(M2->data + M2->column * i + j);
            }
        }
    } else {
        printf("Can't add those matrices!");
    }
}
    
void matrixMult(struct Matrix *M1, struct Matrix *M2, struct Matrix *res) {
    if(M1->column == M2->row) {
        int inner = M1->column;
        
        res->row = M1->row;
        res->column = M2->column;
        
        res->data = malloc(sizeof(double) * res->column * res->row);
        
        for(int i=0 ; i < res->row ; i++) {
            for(int j=0 ; j < res->column ; j++) {
                for (int k=0 ; k < inner ; k++){
                    *(res->data + res->column * i + j) += *(M1->data + M1->column * i + k) * *(M2->data + M2->column * k + j);
                }
            }
        }
    } else {
        printf("Can't multiply those matrices!");
    }
}

void fillZero(struct Matrix *M){
    
}

void rowCoefMult(struct Matrix *M, int row, int k){
    for(int i=0; i<M->column; i++) {
        *(M->data + M->column * row + i) *= k;
    }
}

void rowAdd(struct Matrix *M, int rowA, int rowB){
    for(int i=0; i<M->column; i++) {
    }
}

//*(M->data + M->column * pivot + pivot)
void gaussianElimination(struct Matrix *M, struct Vector *b) {
    for(int pivot=0 ; pivot < M->column ; pivot++) {
        int k=0;
        while(isZero(*(M->data + M->column * pivot + pivot))){
            if(!isZero(*(M->data + M->column * pivot + pivot))){
                swapRows(M, k, pivot);
            }
            k++;
        }
        if(*(M->data + M->column * pivot + pivot) != 1) {
            rowCoefMult(M, pivot, 1/(*(M->data + M->column * pivot + pivot)));
        }
        for(int m=0 ; m < M->row ; m++){
            if(!isZero(*(M->data + M->column * m + pivot)) || m != pivot){
                struct Matrix tempRow;
                tempRow.data = malloc(sizeof(double) * M->column * M->column);
                fillZero(&tempRow);
                for(int multIndex=0 ; multIndex < M->column ; multIndex++) {
                    *(tempRow.data + tempRow.column * m + multIndex) = *(M->data + M->column * pivot + multIndex);
                }
                rowCoefMult(&tempRow, m, -(*(M->data + M->column * m + pivot)));
            }
        }
    }
}

int main(void){
    struct Matrix A;
    struct Matrix B;
    struct Matrix res;

    matrixInit(&A);
    matrixInit(&B);

    nPrint(A);
    nPrint(B);
    
    matrixMult(&A, &B, &res);
    
    nPrint(res);
    
    free(A.data);
    free(B.data);
    free(res.data);
    return 0;
}
