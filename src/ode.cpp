#include <iostream>
#include<fstream>
#include "ode.h"
using namespace std;
/*********************************/
void euler(unsigned int ndim, double *y, double time,double dt){
  double  k1[ndim];
  int idim;
  eval_rhs(time,y,k1);
  for(idim=0;idim<ndim;idim++){
    y[idim]=y[idim]+k1[idim]*dt;
  }
}
/*********************************/
void rnkt2(unsigned int ndim, double *y, double time,double dt){
  double  temp[ndim],k1[ndim],k2[ndim];
  int idim;
//
  eval_rhs(time,y,k1);
  for(idim=0;idim<ndim;idim++){
    temp[idim]=y[idim]+k1[idim]*dt/2.;
  }
  eval_rhs(time+(dt/2.),temp,k2);
  for(idim=0;idim<ndim;idim++){
    y[idim]=y[idim]+k2[idim]*dt;
  }
}
/*********************************/
void rnkt4(unsigned int ndim, double *y, double time,double dt){
  double  temp[ndim],k1[ndim],k2[ndim],k3[ndim],k4[ndim];
  int idim;
  eval_rhs(time,y,k1);
  for(idim=0;idim<ndim;idim++){
    temp[idim]=y[idim]+k1[idim]*dt/2.;
  }
  eval_rhs(time+(dt/2.),temp,k2);
  for(idim=0;idim<ndim;idim++){
    temp[idim]=y[idim]+k2[idim]*dt/2.;
  }
  eval_rhs(time+(dt/2.),temp,k3);
  for(idim=0;idim<ndim;idim++){
    temp[idim]=y[idim]+k3[idim]*dt;
  }
  eval_rhs(time+dt,temp,k4);
  for(idim=0;idim<ndim;idim++){
    y[idim]=y[idim]+dt*(  (k1[idim]/6.) + (k2[idim]/3.) + (k3[idim]/3.) + (k4[idim]/6.) );
  }
}
/* call eval_rhs(y,t,k1)
call eval_rhs(y+k1*(dt/2.),t+(dt/2.),k2)
call eval_rhs(y+k2*(dt/2.),t+(dt/2.),k3)
call eval_rhs(y+k3*dt,t+dt,k4)
y=y+dt*((k1/6.)+(k2/3.)+k3/3.+k4/6.) */
/* ----------------- */

