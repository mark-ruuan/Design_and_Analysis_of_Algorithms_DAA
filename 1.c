#include <stdio.h>
#include <stdlib.h>
 
struct st{
	int min, max;
};
 
struct st d_q(int i, int j, int arr[]){
	struct st new, new1;
	if(i == j){
		new.min = arr[i];
		new.max = arr[j];
		return new;
	}
	if(i == j - 1){
		if(arr[i] < arr[j]){
			new.min = arr[i];
			new.max = arr[j];
		}
		else{
			new.max = arr[i];
			new.min = arr[j];
		}
		return new;
	}
	int mid = (i + j) / 2;
	new = d_q(i, mid, arr);
	new1 =d_q(mid + 1, j, arr);
	if(new.min > new1.min){
		new.min = new1.min;
	}
	if(new.max < new1.max){
		new.max = new1.max;
	}
	return new;
}
 
 
int main(){
	printf("********DIVIDE AND CONQUER ALGORITHM********\n");
	printf("Enter the size of the array\n");
	int n;
	scanf("%d", &n);
	int *arr = (int *)malloc(sizeof(int) * n);
	printf("Enter the elements in the array\n");
	for(int i = 0; i < n; i++)
		scanf("%d", &arr[i]);
	struct st ans = d_q(0, n - 1, arr);
	printf("minimum element of the list is: %d\nmaximum element of the list is: %d", ans.min, ans.max);
	free(arr);
}
