#include <stdio.h>

// 素数
#define N 2999

int A[N];

// *p と *q の値を入れ替える関数
void swap(int *p, int *q){
  int tmp;
  tmp = *p;
  *p = *q;
  *q = tmp;
}

int quick_select(int A[], int n, int k){
    int i, j, pivot, eq;

    pivot = A[n/2];
    A[n/2] = A[0];
    A[0] = pivot;
    for(i = j = eq = 1; i < n; i++){
        if(A[i] < pivot){
            swap(A+i, A+j);
            j++;
        }
        if(A[i] == pivot){
            swap(A+i, A+eq);
            swap(A+i, A+j);
            j++;
            eq++;
        }
    }
    
    if((j - eq < k+1) && (k+1 <= j)) return pivot;
    else if(j < k+1) return quick_select(A+j, n-j, k-j);
    else return quick_select(A+eq, j-eq, k);
}

int median_of_median(int A[], int n, int k){
    int a = n/5 + 1;
    int B[a];
    int i, j, pivot, eq;
    
    if(n <= 5) return quick_select(A,n,n/2-1);
    else{
        for(i = 0; i < a; i++){
            if(i < a-1) B[i] = quick_select(A+5*i,5,2);
            else B[a-1] = quick_select(A+5*(a-1),n-5*(a-1)+1,(n+5*(a-1))/2-1);
        }
    }
    pivot = quick_select(B,a,a/2-1);
    for(i = 0; i < n; i++){
        if(A[i] == pivot){
            A[i] = A[0];
            break;
        }
    }
    A[0] = pivot;
    for(i = j = eq = 1; i < n; i++){
        if(A[i] < pivot){
            swap(A+i, A+j);
            j++;
        }
        if(A[i] == pivot){
            swap(A+i, A+eq);
            swap(A+i, A+j);
            j++;
            eq++;
        }
    }
    if((j - eq < k+1) && (k+1 <= j)) return pivot;
    else if(j < k+1) return median_of_median(A+j, n-j, k-j);
    else return median_of_median(A+eq, j-eq, k);
}

int main(){
  int i;
  A[0] = 0;
  A[1] = 17; //原始元
  for(i=2;i<N;i++){
    A[i] = (long long int) A[i-1] * A[1] % N;
  }
  for(i=0;i<N;i++){
    if(quick_select(A, N, i) != i) printf("ERROR %d %d\n", i, quick_select(A, N, i));
//    printf("%d th element is %d\n", i, quick_select(A, N, i))
  }
}
