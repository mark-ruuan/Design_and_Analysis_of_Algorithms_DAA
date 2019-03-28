#include<stdio.h>
#include<stdlib.h>

typedef struct 
{
	int id;
	int sz;
	char name[20];
	int rt;
}job;

void merge(int arr[], job ptr[], int l, int m, int r){
	int i, j, k;
	int n1 = m - l + 1, n2 = r - m;
	int *L = (int *)malloc(n1 * sizeof(int));
	int *R = (int *)malloc(n2 * sizeof(int));
	for(i = 0; i < n1; i++) L[i] = arr[l + i];
	for(i = 0; i < n2; i++) R[i] = arr[m + 1  + i];
	i = 0, j = 0, k = l;
	while(i < n1 && j < n2){
		if(ptr[L[i]].sz <= ptr[R[j]].sz){
			arr[k++] = L[i++];
		}
		else{
			arr[k++] = R[j++];
		}
	}
	while(i < n1){
		arr[k++] = L[i++];
	}
	while(j < n2){
		arr[k++] = R[j++];
	}	
	free(L);
	free(R);
}

void merge_sort(int arr[], job ptr[], int l, int r){
	if(l < r){
		int m = (l + r) / 2;
		merge_sort(arr, ptr, l, m);
		merge_sort(arr, ptr, m + 1, r);
		merge(arr, ptr, l, m, r);
	}
}

int main()
{
    int T, n, i, j;
    int avgrt = 0;
    printf("Enter the no of tape(s): ");
    scanf("%d", &T);
    printf("Enter the no of  job(s): ");
    scanf("%d", &n);
    job *ptr = (job *)malloc(n * sizeof(job));
	for(i = 0; i < n; ){

		printf("\nEnter the Job size: ");
		scanf("%d", &ptr[i].sz);
		if(ptr[i].sz > 0){
			ptr[i].id = i;
			printf("Enter the Job Name: ");
			scanf ("%s", ptr[i].name);
			i++;
		}
		else{
			printf("Job size must be greater than 0, please re-enter\n");
		}
	}
    if(n <= T){
    	int sum = 0;
    	for(i  = 0; i < n; ++i){
    		printf("\nID of Job(s) stored on Tape %d: %d \n", i+1, i+1);
    		ptr[i].rt = ptr[i].sz;
    		sum += ptr[i].sz;
    	}
        printf("\nJobID\tJobName\tJobsz\tRetrievalTime\n");
        for(j = 0; j < n; j++)
        	printf("%d\t%s\t%d\t%d\n",ptr[j].id+1, ptr[j].name, ptr[j].sz, ptr[j].rt);	
    	printf("\nAvg Retrievel Time = %.2f\n", (double)sum / n); 
    }
    else{
   		int *arr = (int *)malloc(n*sizeof(int));
    	for(i = 0; i < n; ++i) arr[i]=i;   		
    	merge_sort(arr, ptr, 0, n - 1);
	   	int r = T, c;
		c = (n + T - 1) / T;
		int *a = (int *)malloc(r * c * sizeof(int)); 
		int k = 0;	
   		for (i = 0; i <  c; i++) {
      		for (j = 0; j < r; j++) {
         		if(k < n){
         			a[j*c + i] = arr[k]  ;
         			k++;
         			if(i == 0){
         				ptr[a[j*c + i]].rt = ptr[a[j*c + i]].sz;
         				avgrt+=ptr[a[j*c + i]].rt;
         			}
         			else{
         				ptr[a[j*c + i]].rt = ptr[a[j*c + i]].sz + ptr[a[j*c + (i-1)]].rt;
         				avgrt+=ptr[a[j*c + i]].rt;
         			}
         		} 
         		else
         			a[j*c + i]  = -1;	
         	}
        }
        for(i = 0; i < r; ++i){
        	printf("\nID of Job(s) stored on Tape %d : ",i+1);
        	for(j  = 0; j < c; j++){
        		if(a[i*c + j] != -1)
        			printf("%d  ",a[i*c + j]+1);					
        		else
        			printf("-");
        	}
        	printf("\n");
        }
        printf("\nJobID\tJobName\tJobsz\tRetrievalTime\n");
        for(j = 0; j < n; j++){
        	printf("%d\t%s\t%d\t%d\n",ptr[j].id+1, ptr[j].name, ptr[j].sz, ptr[j].rt);
        		
        }
        printf("\nAvg Retrievel Time = %.2f\n", (double)avgrt / n);
        free(a);
        free(arr);  
    }
	free(ptr);
    return 0;
}
