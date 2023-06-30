#include<stdlib.h>
#include<iostream>
#include<chrono>
#include<unistd.h>
using namespace std;

void merge(int A[], int low1,int hi1,int low2, int hi2)
{
	int* tmp=new int[hi1-low1+hi2-low2+2];
	int i=low1,j=low2,k=0;
	while((i<=hi1)&&(j<=hi2))
	{
		if(A[i]<A[j])
			tmp[k++]=A[i++];
		else
			tmp[k++]=A[j++];		
	}
	while(i<=hi1) tmp[k++]=A[i++];
	while(j<=hi2) tmp[k++]=A[j++];
	// do nguoc lai
	k=low1;
	int l=0;
	while (k<=hi2)
		A[k++]=tmp[l++];
}
void mergeSort(int A[],int low,int hi)
{
	if(low<hi)
	{
		int mid=(low+hi)/2;
		mergeSort(A,low,mid);
		mergeSort(A,mid+1,hi);
		merge(A,low,mid,mid+1,hi);		
	}
}
void selectionSort(int A[],int low,int hi)
{
	for(int i=low;i<hi;i++)
		for(int j=i+1;j<=hi;j++)
			if(A[j]<A[i])
			{
				int tmp=A[j];
				A[j]=A[i];
				A[i]=tmp;
			}
}
void selectionSortAdv(int A[],int low,int hi)
{
	for(int i=low;i<hi;i++)
	{
		int minIdx=i;
		for(int j=i+1;j<=hi;j++)
			if(A[j]<A[minIdx])
				minIdx=j;
		if(i!=minIdx)
		{
			int tmp=A[i];
			A[i]=A[minIdx];
			A[minIdx]=tmp;
		}		
	}		
}
int partition( int a[], int low, int high ) {
   int left, right;
   int pivot_item;
   pivot_item = a[low];
   int pivot = left = low;
   right = high;
   while ( left < right ) {
     /* Move left while item < pivot */
     while( a[left] <= pivot_item ) left++;
     /* Move right while item > pivot */
     while( a[right] > pivot_item ) right--;
     if ( left < right ) 
     {
         int tmp=a[left];
         a[left]=a[right];
         a[right]=tmp;
     }
         
     }
   /* right is final position for the pivot */
   a[low] = a[right];
   a[right] = pivot_item;
   return right;
   }
void quickSort( int a[], int low, int high )
   {
   int pivot;
   /* Termination condition! */
   if ( high > low )
     {
     pivot = partition( a, low, high );
     quickSort( a, low, pivot-1 );
     quickSort( a, pivot+1, high );
     }
   }
int main(void)
{
	// generate very big arrays
	int *A=new int[100001];
	int *B=new int[100001];
	int *C=new int[100001];
	int D[]={10,8,6,7};
	for(int i=0;i<100001;i++)
	{
		A[i]=B[i]=C[i]=rand();	
	}
	// test selection sort
	auto start = chrono::steady_clock::now(); 	
	selectionSort(A,0,100000);	
	auto end = chrono::steady_clock::now(); 	
	cout << "Selection sort: "
        << chrono::duration_cast<chrono::microseconds>(end - start).count()
        << " µs" << endl;
	// test merge sort
	start = chrono::steady_clock::now(); 	
	mergeSort(B,0,100000);
	end = chrono::steady_clock::now(); 	
	cout << "Merge sort: "
        << chrono::duration_cast<chrono::microseconds>(end - start).count()
        << " µs" << endl;   
	// test quick sort
	start = chrono::steady_clock::now(); 	
	quickSort(D,0,3);
	end = chrono::steady_clock::now(); 	
	cout << "Quick sort: "
        << chrono::duration_cast<chrono::microseconds>(end - start).count()
        << " µs" << endl;   	 
	return 0;
}