#include <iostream>
#include<cmath>
#include <kv/defint.hpp>
#include <kv/complex.hpp>
typedef kv::interval<double> itv;
typedef kv::complex< kv::interval<double> > cp;
using namespace std;
// verification program for the Gaussian integral
struct Func1 {
	template <class T> T operator() (const T& x) {
	  double b;
	  b=0.2; // imaginary part of z
	  return exp(-x*x)*cos(2*b*x);
	}
};

struct Func2 {
	template <class T> T operator() (const T& x) {
	  double b;
	  b=0.2; // imaginary part of z
	  return exp(-x*x)*sin(2*b*x);
	}
};

struct Func3 {
	template <class T> T operator() (const T& y) {
	  return exp(y*y);
	}
};
int main(){
  cout.precision(17);
  itv a,b,reGauss,re,im,imGauss1,imGauss2;
  a=0.1; // real part of z
  b=0.2; // imaginary part of z
  reGauss=kv::defint(Func1(), (itv)0., (itv)a, 10, 10);
  imGauss1=kv::defint(Func2(), (itv)0., (itv)a, 10, 10);
  imGauss2=kv::defint(Func3(), (itv)0., (itv)b, 10, 10);
  re=exp(b*b)*reGauss;
  im=imGauss2-exp(b*b)*imGauss1;
 cp res;
  res=cp(re, im); 
  cout<<res<<"\n";
}
