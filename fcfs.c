#include<stdio.h>


int main()
{
    int at[10];
int bt[10];
int n;



    printf("Enter number of processors \n");
    scanf("%d",&n);
    printf("Enter arrival time and booting time of the processors \n");
    for(int i=0;i<n;i++)
    {
        printf("Process [%d] \n",i+1);
        printf("Enter AT ");
        scanf("%d",&at[i]);
        printf("Enter Bt");
        scanf("%d",&bt[i]);

    }
    for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            if(at[i]>at[j])
            {
                int temp=at[i];
                at[i]=at[j];
                at[j]=at[i];
            }
        }

    }
    int ct[10],tat[10],wt[10];
    int curr_time=0;
    for(int i=0;i<n;i++)
    {
        if(curr_time<at[i])
        {
            curr_time=at[i];
        }
        ct[i]=curr_time+bt[i];
        tat[i]=ct[i]-at[i];
        wt[i]=tat[i]-bt[i];
        curr_time=ct[i];


    }
    float avg_tat,avg_wt;
    float total_tat=0;
    float total_wt=0;
    for(int i=0;i<n;i++)
    {
        total_tat+=tat[i];
        total_wt+=wt[i];

    }
    avg_tat=total_tat/n;
    avg_wt=total_wt/n;


    printf("Process  At Bt Ct Tat Wt \n");
    for(int i=0;i<n;i++)
    {
        printf("%d       %d  %d  %d  %d  %d \n",i+1,at[i],bt[i],ct[i],tat[i],wt[i]);
    }
        printf(" Average tat= %.2f  Average Wt=%.2f",avg_tat,avg_wt);

    return 0;

}




