#include "view.hpp"
#include <iostream>

//-------[View AKA Array Wrapper]-----
// Wraps a raw pointer and overloads the () operator
// to simplify multi-dimensional indexing. 

int main(int argc, char* argv[])
{

  const int Dim1 = 2; 
  const int Dim2 = 3;
  const int Dim3 = 4;
  const int NSTR  = Dim1*Dim2*Dim3;

  int * data = new int[NSTR];

  for(int i=0; i<NSTR; ++i) { data[i] = i; };


  //-----[View with 2 indices]-----------------
  myView<int,Dim1> view2(data);  
  auto loop_body2 =
    [=](int i, int j) { std::cout<<i + Dim1*j<<" : "<<view2(i,j)<<std::endl;};
                                              
  for(int j=0; j<Dim2; ++j)
    for(int i=0; i<Dim1; ++i)
      {
        loop_body2(i,j);
      }

  std::cout<<" \n \n "<<std::endl;
  //------[View with 3 indices and lambda]-----  
  myView<int,Dim1,Dim2> view3(data);
  auto loop_body3 =
    [=](int i, int j, int k) { std::cout<<i + Dim1*(j + Dim2*k)<<" : "<<view3(i,j,k)<<std::endl;};
  
  for(int k=0; k<Dim3; ++k)
    for(int j=0; j<Dim2; ++j)
      for(int i=0; i<Dim1; ++i)
        {
          loop_body3(i,j,k);
        }


  //... code works with arbitrary indices.
  
  delete [] data;

  return 0;
}
