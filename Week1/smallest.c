#include <stdio.h>
int main (){
    int n,key;
    printf("enter the number of elements ");
    scanf("%d",&n);
    int arr[n];
    printf("enter the elements");
    for (int i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }
    int min=arr[0],pos;
    for(int i=0;i<n;i++){
        if(arr[i]<min){
            min=arr[i];
            pos=i+1;
        }
    }
    printf("The smallest number is %d and is at position %d",min,pos);

}
