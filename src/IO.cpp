#include <iostream>
#include <fstream>
#include "model.h"
#include "constant.h"
#include <sstream>
using namespace std;
/*-----------------------------------------------*/
void wData(ofstream *fptr, double *y, double time){
  // If we do not want to write velocity in a file.
  switch(wDataMeth){
    case 1:
      for(int ip = 0; ip < Np; ++ip){
        for (int jp = 0; jp < pp; ++jp){
          *fptr << y[pp*ip+jp];
          *fptr << '\t';
        }
        *fptr << '\n';
      }
      break;
    case 2:
      (*fptr) << time << "\t";
      for (int idim = 0; idim < ndim; ++idim){
        *fptr << y[idim] << "\t";
      }
      *fptr <<  endl;
      *fptr << "#------------------------------------------------#" << endl;
      break;
    default:
      cout << "Hey, your choice of writing data does not exist. "
              "If you want a new way, Code function: wData(ofstream *fptr, double y[], double vel[]) "
              "in model.cpp file." << endl;
      exit(1);
  }
}
/*-----------------------------------------------*/
void wData(ofstream *fptr, ofstream *fptr_vel, double *y, double *vel, double time){
  switch(wDataMeth){
    case 1:
      for(int ip = 0; ip < Np; ++ip){
        for (int jp = 0; jp < pp; ++jp){
          *fptr << y[pp*ip+jp];
          *fptr << '\t';
        }
        // Now next three numbers contain values of velocity.
        for (int jp = 0; jp < pp; ++jp){
          *fptr << vel[pp*ip+jp];
          *fptr << '\t';
        }
        *fptr << '\n';
      }
      break;

    case 2:
      (*fptr) << time << "\t";
      (*fptr_vel) << time << "\t";
      for (int idim = 0; idim < ndim; ++idim){
        *fptr << y[idim] << "\t";
        *fptr_vel << vel[idim] << "\t";
      }
      *fptr <<  endl;
      *fptr << "#------------------------------------------------#" << endl;

      *fptr_vel <<  endl;
      *fptr_vel << "#------------------------------------------------#" << endl;
      break;
    default:
      cout << "Hey, your choice of writing data does not exist. "
              "If you want a new way, Code function: wData(ofstream *fptr, double y[], double vel[]) "
              "in model.cpp file." << endl;
      exit(1);
  }
}
/*-----------------------------------------------*/
// Wrapper function for wData, in case y and vel contains multiple rows.
// We do not pass the file pointer, but the fname.
// void wData(string fname, double y[][ndim], double time[], int nrow){
//   switch(wDataMeth){
//     case 1:{
//       // for (int irow = 0; irow < nrow; ++irow){
//       //   ofstream outfile("output/var"+to_string()+".txt",fstream::out);
//       //   for(int ip = 0; ip < Np; ++ip){
//       //     for (int jp = 0; jp < pp; ++jp){
//       //       file << y[irow][pp*ip+jp];
//       //       file << '\t';
//       //     }
//       //     // Now just throw away next three numbers as they contain values of velocity.
//       //     for (int jp = 0; jp < pp; ++jp){
//       //       file << vel[irow][pp*ip+jp];
//       //       file << '\t';
//       //     }
//       //     file << '\n';
//       //   }
//       // }
//       cout << "This is not necessary. I am EXITING from function wData." << endl;
//       break;
//     }
//     case 2:{
//       ofstream outfile(fname,ofstream::out);
//       for (int irow = 0; irow < nrow; ++irow){
//         wData(&outfile,y[irow],time[irow]);
//       }
//       outfile.close();
//       break;
//       // for (int idim = 0; idim < ndim; ++idim){
//       //   *fptr << y[idim] << "\t";
//       //   *fptr_vel << vel[idim] << "\t";
//       // }
//       // *fptr <<  "\n";
//       // *fptr << "#------------------------------------------------#\n";

//       // *fptr_vel <<  "\n";
//       // *fptr_vel << "#------------------------------------------------#\n";
//       // break;
//     }
//     default:
//       cout << "Hey, your choice of writing data does not exist. "
//               "If you want a new way, Code function: wData(ofstream *fptr, double y[], double vel[]) "
//               "in model.cpp file." << endl;
//       exit(1);
//   }
// }
// /*-----------------------------------------------*/
// void rData(ifstream *fptr, double *y){
//   double num=0.0;
//   for(int ip = 0; ip < Np; ++ip){
//     *fptr >> y[3*ip];
//     *fptr >> y[3*ip+1];
//     *fptr >> y[3*ip+2];
//     // Now just throw away next three numbers as they contain values of velocity.
//     *fptr >> num;
//     *fptr >> num;
//     *fptr >> num;
//   }
// }
/********************************************/
void rData(ifstream *fptr, double *y){
  string line,token;
  double num;
  istringstream iss;
  switch(rDataMeth){
    case 1:
      num=0.0;
      for(int ip = 0; ip < Np; ++ip){
        *fptr >> y[2*ip];
        *fptr >> y[2*ip+1];
        // Now just throw away next two numbers as they contain values of velocity.
        *fptr >> num;
        *fptr >> num;
      }
      break;
    case 2:
      while( getline(*fptr,token) ){
        line=token;
        getline(*fptr,token);          // Dumping this: #---------
      }
      // Now convert all the tab separated entries to array.
      iss.str(line);
      // getline(iss, token, '\t');        // First entry is time, delete that.
      for (int idim = 0; idim < ndim; ++idim){
        getline(iss, token, '\t');       // Get next token.
        y[idim]=stod(token);            // Convert to double and store it in y.
      }
      break;
    default:
      cout << "Hey, your choice of writing data does not exist. "
              "If you want a new way, Code function: wData(ofstream *fptr, double y[], double vel[]) "
              "in model.cpp file." << endl;
      exit(1);
  }
}