#include <stdio.h>
int main()

{
 int n  ;
 scanf("%d",&n);
 int a[n][n] ;
 for(int i  =0;i<n;i++)
 {
    for(int j  =0;j<n;j++)
    {
        scanf("%d",&a[i][j]);
    }

 }
  for(int i  =0;i<n;i++)
 {
    for(int j  =0;j<n;j++)
    {
        printf("%d ",a[i][j]);
    }
    printf("\n");

 }
 int rowSum = 0;
 int colSum  =0;
  for(int i  =0;i<n;i++)
 {
    colSum = rowSum = 0;
    for(int j  =0;j<n;j++)
    {
       rowSum +=  a[i][j];
        colSum +=  a[j][i];
    }
    printf("\n%d rowsum : %d",i,rowSum);
    printf("\n%d colsum : %d",i,colSum);

 }
}