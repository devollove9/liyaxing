//   test driver for heap, ignores index 0
/*------------------------------------------------------
 * CSE 331
 * Yaxing Li
 * HomeWork 4 
----------------------------------------------------------*/
#include <iostream>
#include <math.h>
#include <sys/time.h>
#include <stdlib.h>

using namespace std;
int HeapSort(int * ,int);

void heapify(int *  , int,int );
void buildheap( int *,int);
// short integer random number generator from stdlib
int rand(void); 

int main()
{ 
  int size;
  cout << endl << "How many elements in the input array ";  cin >> size;
  int* dataArray = new int [size + 1];   // get array of right size (with invisible 0th element)
 
  // fill array -- fill 0th element but don't show it.
  for (int k=0; k< size+1 ; k++)  dataArray[k] = rand();
  cout<<"Input array:\n";
  for (int k=1; k<size+1; k++)
    cout<<dataArray[k]<<" ";
  cout<<endl;
  int dataArray2[]={1,7,2,5,6,4,10,20,8,11,9};
  // ============= implement your code here or call it as a function======
  // you may assume that the variable size is the correct size of the array
  // (even though it's not) for heap-building purposes
  // build a heap for dataArray
  HeapSort(dataArray,size);    
  
  
  //show heap (but not ignored 0th element)
  cout<<"Heap built from the input array:\n";
  for (int k=1; k<size+1; k++)
    cout<<dataArray[k]<<" ";
  cout<<endl;

}

int HeapSort(int* H,int size)
{
    int i;
    int length=size;
    buildheap(H,size);
    if (length>1)
    {
        for (i=length;i>1;i--)
        {
                swap(H[1],H[i]);
                length--;
                heapify(H,1,length);
        }
    }
}

void heapify( int *H  , int i,int size)
{
    
    int left=2*i, right = 2*i+1,smallest;

    if (left<size && H[left]<H[i]) smallest=left; 
    else smallest=i;
    if (right<size && H[right]<H[smallest]) smallest=right;
    
    if (smallest!=i)
    {
        swap(H[i],H[smallest]);
        heapify(H,smallest,size);
    }
    
}

void buildheap( int *H,int size)
{
    int i=1,s;
    cout<<size<<endl;
    s=size+1;
    for(i=(s/2)-1;i>=1;i--)
    {
        heapify(H,i,size);
    }   
}