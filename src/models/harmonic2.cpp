#include <iostream>
#include<fstream>
#include "ode.h"
#include "model.h"
using namespace std;
/**************************/
void eval_rhs(double time,double y[],double rhs[]){
  //  double y[ndim],rhs[ndim];
	rhs[0] = y[1];	
	rhs[1] = k1*(y[2]-y[0]-l)-k2*(y[0]);
	rhs[2] = y[3];
	rhs[3] = -k1*(y[2]-y[0]-l)-k2*(y[2]);

  // rhs[0]=y[1];
  // rhs[1]=-omega2*y[0] + f0*sin(fom*time);
  //  cout<<f0*sin(fom*time)<<time<<"\n";
}
/**************************/
void iniconf(double y[]){
  y[0]=1.;
  y[1]=0;
  y[2]=2.;
  y[3]=0;
}
