#include <iostream>
#include<cmath>
#include <kv/defint.hpp>
#include<kv/constants.hpp>
#include <kv/complex.hpp>
#include <kv/gamma.hpp>
typedef kv::interval<double> itv;
typedef kv::complex< kv::interval<double> > cp;
using namespace std;
# define n 3
# define a 0.1 // real part of z
# define b 0.2 // imaginary part of z
# define r sqrt(a*a+b*b)
// verification program for the super error function
// reference
// Souichiro Ikebe
// Graphics Library of Special Functions
// http://math-functions-1.watson.jp/sub1_spec_070.html#section030
struct Func1 {
  template <class T> T operator() (const T& x) {
    return exp(-pow(r,n)*cos(n*x))*sin(pow(r,n)*sin(n*x))*cos(x);
    // function for the real part of result
  }
};

struct Func2 {
  template <class T> T operator() (const T& x) {
    return exp(-pow(r,n)*cos(n*x))*cos(pow(r,n)*sin(n*x))*sin(x);
    // function for the real part of result
  }
};

struct Func3 {
	template <class T> T operator() (const T& y) {
	  return exp(-pow(y,n));
	  // function for Gaussian integral
	}
};
struct Func4 {
  template <class T> T operator() (const T& x) {
    return exp(-pow(r,n)*cos(n*x))*sin(pow(r,n)*sin(n*x))*sin(x);
    // function for the imaginary part of result
  }
};

struct Func5 {
  template <class T> T operator() (const T& x) {
    return exp(-pow(r,n)*cos(n*x))*cos(pow(r,n)*sin(n*x))*cos(x);
    // function for the imaginary part of result
  }
};

int main(){
  cout.precision(17);
  itv imGauss1,imGauss2,re,im,reGauss1,reGauss2,ReErf,ImErf,theta,Gauss;
  cp z;
  z=cp(a,b);
  theta=arg(z); // argument of z
  // calculating Gaussian integral
  reGauss1=kv::defint(Func1(), (itv)0., (itv)theta, 10, 10);
  reGauss2=kv::defint(Func2(), (itv)0., (itv)theta, 10, 10); // OK
  Gauss=kv::defint(Func3(), (itv)0., (itv)r, 10, 10); // OK
  imGauss1=kv::defint(Func4(), (itv)0., (itv)theta, 10, 10);
  imGauss2=kv::defint(Func5(), (itv)0., (itv)theta, 10, 10); 
  im=r*imGauss1+r*imGauss2;
  re=r*reGauss1-r*reGauss2+Gauss;
  // calculating factorial
  int fact=1;
  for(int i=1;i<=n;i++){
    fact=fact*i;
  }
  // factorial OK
  // calculating the error function
  ReErf=fact*re/sqrt(kv::constants<itv>::pi());
  ImErf=fact*im/sqrt(kv::constants<itv>::pi());
  cp res;
  res=cp(ReErf, ImErf)/kv::gamma(itv(1+1/n)); 
  cout<<res<<"\n";
}
