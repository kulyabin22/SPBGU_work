#include <iostream>

using namespace std;

int max_element (int array, int n)
{
  int max = 0;
  for(int i = 0; i < n; i++){
    if(array[i] > max){
        max = array[i];
    }  
  }

  return max;
}
int min_element ( int array,  int n )
{
  int min = 100000000000;
  for(int i = 0; i < n; i++){
    if(array[i] < min){
        min = array[i];
    }  
  }

  return min;
}
int main()
{
    int n;
    cin<< n;
    int x[n];
    int y[n];
    for(i = 0; i < n; i++){
        int kx;
        int ky;
        cin<< kx;
        cin<< ky;
        x[i] = kx;
        y[i] = ky;
    int a;
    int b;
    cin<< a;
    cin<< b;
    int mins = 10000000;
    int sum = 0;
    for(int i = min_element(x, n); i < max_element(x, n)+1 ){
        j = a*i + b
        for(l = 0; l < n; l++){
            d = (i - x[l])*(i - x[l]) + (j - y[l])*(j - y[l]);
            sum = sum + d;
        if(sum < mins){
            mins = sum;
        }
        }
            
        
    }
    }
    cout>> mins;
    
    return 0;
}