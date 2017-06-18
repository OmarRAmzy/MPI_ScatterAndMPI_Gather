#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include <assert.h>

int main(int argc , char** argv)
{
    int rank , size , *arr , i , data , *subarr , ps ,n  ;
    float * avgs ;

    MPI_Init(&argc , &argv);


    MPI_Comm_rank(MPI_COMM_WORLD , &rank);
    MPI_Comm_size(MPI_COMM_WORLD , &size);



    if(rank==0)
    {
        printf("Enter Array size: ");
        scanf("%d" , &n);
        arr=malloc(n * sizeof(int));

        for(i=0 ; i< n ;i++)
            scanf("%d" , &arr[i]);

       ps=n/size;
    }

    subarr=malloc(ps * sizeof(int));
    avgs= malloc(ps * sizeof(float));
    MPI_Scatter(arr , ps , MPI_INT , subarr , ps , MPI_INT, 0 , MPI_COMM_WORLD );

    float sum=0 , avg=0;
    for(i=0 ;i<ps ;i++)
        sum+=subarr[i];

    avg=sum/ps ;

    MPI_Gather(&avg , 1 , MPI_FLOAT , avgs , 1 , MPI_FLOAT , 0 , MPI_COMM_WORLD );

    if(rank==0)
    {
        for(i=0 ;i<ps ;i++)
            printf("%f \n" , avgs[i]);
    }

    printf("Rank # %d has data= %d \n" , rank , data);


    MPI_Finalize();


    return 0;
}
