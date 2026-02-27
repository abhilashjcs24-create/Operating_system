#include <stdio.h>
int main(){
    int n,key;
    printf("enter the number of elements ");
    scanf("%d",&n);
    int arr[n];

    printf("enter the elements");
    for (int i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }
    printf("Enter the num to find");
    scanf("%d",&key);
    int pos=-1;
    int low =0,high=n-1,mid;
    while(low<=high){
        mid=(low+high)/2;
        if(key==arr[mid]){
            pos=mid;
            break;
        }else if(key<arr[mid]){
            high =mid-1;
        }
        else{
            low=mid+1;
        }
    }
    if(pos==-1){
        printf("the number was not found");

    }else{
        printf("the number is found in the %d position",(pos+1));
    }
}
