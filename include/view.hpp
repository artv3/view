#ifndef __VIEW_HPP__
#define __VIEW_HPP__

#include <iostream>
// declaration
template<size_t...> struct layout; 

// specialization of layout for zero template args
template<>
struct layout<> 
{
  static size_t get(){return 0;}
};

//specialization for 1 or more tempalte args
template<size_t Stride0, size_t... Strides>
struct layout<Stride0, Strides...> : layout<Strides...> 
{
  static size_t get() 
  {
    return Stride0;
  }
};



template<typename T, size_t Stride0,  size_t... Strides>
struct myView
{

private:
  T * data;

  template<typename IDX>
  IDX indexcalc() const
  {
    std::cout<<"no stride"<<std::endl;
    return 0;
  }

  template<typename IDX>
  IDX indexcalc(IDX idx) const
  {
    //std::cout<<"no stride"<<std::endl;
    return idx;
  }

  template<typename IDX, typename... IDXS>
  IDX indexcalc(IDX idx, IDXS... idxs) const
  {
    return idx; 
  }

  //basecase
  template<size_t Str0, typename IDX>
  IDX indexcalc(IDX idx) const
  {
    return idx*layout<Str0>::get();
  }

  template<size_t Str0, size_t... Strs, typename IDX, typename... IDXS>
  IDX indexcalc(IDX idx, IDXS... ids) const
  {   
    return layout<Str0, Strs...>::get()*(idx + indexcalc<Strs...>(ids...));
  }

public:
  myView(T * dptr) : data(dptr) {};
  
  template<typename IDX, typename... IDXS>
  size_t operator() (IDX idx, IDXS... ids) const
  {
    return data[idx + indexcalc<Stride0,Strides...>(ids...)];
  }

};
#endif
