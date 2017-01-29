#include <iostream>
#include<cmath>
#include <kv/defint.hpp>
#include<kv/constants.hpp>
#include <kv/complex.hpp>
typedef kv::interval<double> itv;
typedef kv::complex< kv::interval<double> > cp;
#define b 0.2 // imaginary part of z
using namespace std;
// verification program for the Dawson function
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
  // calculating integral
  reGauss=kv::defint(Func1(), (itv)0., (itv)a, 10, 10);
  imGauss1=kv::defint(Func2(), (itv)0., (itv)a, 10, 10);
  imGauss2=kv::defint(Func3(), (itv)0., (itv)bb, 10, 10);
  re=exp(-b*b)*reGauss;
  im=imGauss2+exp(-b*b)*imGauss1;

  cp gi,res,z;
  z=cp(a,bb);
  gi=cp(re, im); 
  res=exp(-z*z)*gi;
  cout<<res<<"\n";

}
