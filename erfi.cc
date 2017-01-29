#include <iostream>
#include<cmath>
#include <kv/defint.hpp>
#include<kv/constants.hpp>
#include <kv/complex.hpp>
typedef kv::interval<double> itv;
typedef kv::complex< kv::interval<double> > cp;
#define b 0.2 // imaginary part of z
using namespace std;
// verification program for the imaginary error function
struct Func1 {
	template <class T> T operator() (const T& x) {
	  return exp(x*x)*cos(2*b*x);
	}
};

struct Func2 {
	template <class T> T operator() (const T& x) {
	  return exp(x*x)*sin(2*b*x);
	}
};

struct Func3 {
	template <class T> T operator() (const T& y) {
	  return exp(-y*y);
	}
};
int main(){
  cout.precision(17);
  itv a,bb,reGauss,re,im,imGauss1,imGauss2,ReErf,ImErf;
  a=0.1; // real part of z
  bb=b; // imaginary part of z
  // calculating Gaussian integral
  reGauss=kv::defint(Func1(), (itv)0., (itv)a, 10, 10);
  imGauss1=kv::defint(Func2(), (itv)0., (itv)a, 10, 10);
  imGauss2=kv::defint(Func3(), (itv)0., (itv)bb, 10, 10);
  re=exp(-b*b)*reGauss;
  im=imGauss2+exp(-b*b)*imGauss1;
  // calculating the error function
  ReErf=2*re/sqrt(kv::constants<itv>::pi());
  ImErf=2*im/sqrt(kv::constants<itv>::pi());
  cp res;
  res=cp(ReErf, ImErf); 
  cout<<res<<"\n";

}
