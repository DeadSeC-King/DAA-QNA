#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

void multiply(ll *A, ll *B, ll *C, int n) {
    if (n <= 32) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                for (int k = 0; k < n; k++)
                    C[i*n+j] += A[i*n+k] * B[k*n+j];
        return;
    }

    int h = n / 2;
    int sz = h * h;

    ll *a = calloc(sz * 18, sizeof(ll));
    if (!a) exit(1);

    ll *A11=a, *A12=a+sz, *A21=a+2*sz, *A22=a+3*sz;
    ll *B11=a+4*sz, *B12=a+5*sz, *B21=a+6*sz, *B22=a+7*sz;
    ll *M1=a+8*sz, *M2=a+9*sz, *M3=a+10*sz, *M4=a+11*sz;
    ll *M5=a+12*sz, *M6=a+13*sz, *M7=a+14*sz;
    ll *X=a+15*sz, *Y=a+16*sz;

    for(int i=0;i<h;i++)
        for(int j=0;j<h;j++) {
            A11[i*h+j]=A[i*n+j];
            A12[i*h+j]=A[i*n+j+h];
            A21[i*h+j]=A[(i+h)*n+j];
            A22[i*h+j]=A[(i+h)*n+j+h];

            B11[i*h+j]=B[i*n+j];
            B12[i*h+j]=B[i*n+j+h];
            B21[i*h+j]=B[(i+h)*n+j];
            B22[i*h+j]=B[(i+h)*n+j+h];
        }

    #define ADD(P,Q,R) for(int t=0;t<sz;t++) R[t]=P[t]+Q[t]
    #define SUB(P,Q,R) for(int t=0;t<sz;t++) R[t]=P[t]-Q[t]

    ADD(A11,A22,X); ADD(B11,B22,Y);
    multiply(X,Y,M1,h);

    ADD(A21,A22,X);
    multiply(X,B11,M2,h);

    SUB(B12,B22,Y);
    multiply(A11,Y,M3,h);

    SUB(B21,B11,Y);
    multiply(A22,Y,M4,h);

    ADD(A11,A12,X);
    multiply(X,B22,M5,h);

    SUB(A21,A11,X); ADD(B11,B12,Y);
    multiply(X,Y,M6,h);

    SUB(A12,A22,X); ADD(B21,B22,Y);
    multiply(X,Y,M7,h);

    for(int i=0;i<h;i++)
        for(int j=0;j<h;j++) {
            int p=i*h+j;
            C[i*n+j]=M1[p]+M4[p]-M5[p]+M7[p];
            C[i*n+j+h]=M3[p]+M5[p];
            C[(i+h)*n+j]=M2[p]+M4[p];
            C[(i+h)*n+j+h]=M1[p]-M2[p]+M3[p]+M6[p];
        }

    free(a);
}

int main() {
    int n, size=1;
    scanf("%d",&n);

    while(size<n) size*=2;

    ll *A=calloc((size_t)size*size,sizeof(ll));
    ll *B=calloc((size_t)size*size,sizeof(ll));
    ll *C=calloc((size_t)size*size,sizeof(ll));

    if(!A || !B || !C) return 1;

    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            scanf("%lld",&A[i*size+j]);

    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            scanf("%lld",&B[i*size+j]);

    multiply(A,B,C,size);

    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            if(j) printf(" ");
            printf("%lld",C[i*size+j]);
        }
        printf("\n");
    }

    free(A);
    free(B);
    free(C);

    return 0;
}