#include <iostream>
#include <fstream>
#include "MapDyn.h"
#include "math.h"
#include <memory.h>
#include <cstdlib>
#include "misc.h"
#include "IO.h"
#include "JacobEigs.h"
#include <Spectra/GenEigsSolver.h>
/*----------------------------------------------*/
typedef Eigen::VectorXcd Vecc;
typedef Eigen::MatrixXd Mat;
typedef Spectra::DenseGenMatProd<double> MatProd;
typedef Eigen::Map<MatrixXd> MapMat;
int const selectionRule = Spectra::LARGEST_REAL;
/*-----------------------------------------------*/
void calc_stab(double *y, int const neigs = 3);
/*-----------------------------------------------*/
int main(){
  // Here I will define whether I am calling the code for fixed point or periodic orbits.
  // Idea is to use the same code for periodic orbit and fixed point both.
  // Fixed point is a periodic orbit with time-period 1 for a map.
  int mapsize = MM.mapsize;
  double y[ndim],y_trans[mapsize],fy_trans[mapsize];
  assign_map_param();
  // First define all the parameters.
  // Now get the initial configuration (t=0) of the system.
  iniconf(y);   // Implement a program for variable number of arguments.
  coordinate_transform(y_trans,y);
  //
  write_param("wparam.txt");
  if(MM.iorbit){
    if (IsPathExist("PSI")){
      cout << "There is already some data in the folder. I can not replace that.\n"
           << "Please run make clean or remove the PSI and then run the exec again. ";
      exit(1);
    }else{
      periodic_orbit(y_trans,fy_trans);
      // Now save the data;
      ofstream outfile("PSI",ofstream::out);
      wData(&outfile,y_trans,Np,1);
      wData(&outfile,fy_trans,MM.time,Np,1);
    }
    // The function use Newton-Raphson and calculate the nearest periodic orbit.
  }
  if(MM.istab){
    if (MM.iorbit){calc_stab(y_trans,3);}
    else {
     // First check whether you actually have the periodic orbit?
      cout << "Is it a periodic orbit?"
             " (if you don't want this, please comment it out in MapSolve.cpp) " << endl;
      if(IsOrbit(y_trans)){calc_stab(y_trans,3);}
      else{
        cout << "The guess is not periodic orbit." << endl << 
        " Did you cross-check the data or time-period? " << endl <<
        "If yes, use our periodic orbit solver to get nearest orbit to the guess." 
        "Set istab=0, iorbit=1" << endl;
      }
    }
  }
}
/*-----------------------------------------------*/
void calc_stab(double *y, int const neigs){
  Vecc eigval(neigs);

  if(IsPathExist("eig") || IsPathExist("Eig")){
    cout << "I have already calculated the stability of this orbit."
            "There are already some eigenvalues in the folder. I can not replace that.\n"
            "Please remove the eig file and run the exec again. ";
    exit(1);
  }
 bool success = jacob_eigval<selectionRule>(&eigval,neigs,ndim,map_multiple_iter,y);
 if(!success){
    cout << "Sorry, there is something wrong." 
            "I can not converge to make stability analysis in a matrix free way."
            "I will calculate the complete Jacobian using finite-difference method with the error o(eps^2)" 
         << endl;
    // double DerM[ndim][ndim];
    // Jacobian(DerM,y);
    // MapMat Mat_Jacob(DerM,ndim,ndim);
    // MatProd op(Mat_Jacob);
    // GenEigsSolver< double, selectionRule, MatProd > eigs(&op, neigs, 2*neigs+1);
    // eigval = eigs.eigenvalues();
  }else{
    ofstream eigenfile;
    eigenfile.open( "eig" );
    eigenfile << "\n#------------- The eigenvalues are: -------------#\n" << eigval << endl;
    eigenfile.close();
  }
}
/*-----------------------------------------------*/