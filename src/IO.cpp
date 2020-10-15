#include <iostream>
#include <fstream>
#include "constant.h"
#include <sstream>
#include <string>
#include "misc.h"
using namespace std;
/*-----------------------------------------------*/
void wData(ofstream *fptr, double *y, double time, int Npt, int ppt){
  // If we do not want to write velocity in a file.
  int ndimt = Npt*ppt;
  switch(wDataMeth){
    case 1:
      for(int ip = 0; ip < Npt; ++ip){
        for (int jp = 0; jp < ppt; ++jp){
          *fptr << y[ppt*ip+jp];
          *fptr << '\t';
        }
        *fptr << '\n';
      }
      break;
    case 2:
      (*fptr) << time << "\t";
      for (int idim = 0; idim < ndimt; ++idim){
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
void wData(ofstream *fptr, ofstream *fptr_vel, double *y, double *vel, double time,
          int Npt, int ppt){
  int ndimt = Npt*ppt;
  switch(wDataMeth){
    case 1:
      for(int ip = 0; ip < Npt; ++ip){
        for (int jp = 0; jp < ppt; ++jp){
          *fptr << y[ppt*ip+jp];
          *fptr << '\t';
        }
        // Now next three numbers contain values of velocity.
        for (int jp = 0; jp < ppt; ++jp){
          *fptr << vel[ppt*ip+jp];
          *fptr << '\t';
        }
        *fptr << '\n';
      }
      break;

    case 2:
      (*fptr) << time << "\t";
      (*fptr_vel) << time << "\t";
      for (int idim = 0; idim < ndimt; ++idim){
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
void rData(double *y, string filename, int Npt, int ppt){
  string line,token;
  double num;
  istringstream iss;
  string l;
  ifstream myfile;
  double ndimt = Npt*ppt;
  switch(rDataMeth){
    case 1:
      if(IsPathExist("output")){
        l = "output/";
        l.append(filename);
      }else{
        l=filename;
      }
      myfile.open(l,ifstream::in);
      num=0.0;
      for(int ip = 0; ip < Npt; ++ip){
        for (int jp = 0; jp < ppt; ++jp){
          myfile >> y[2*ip+jp];
        }
        // Now just throw away next two numbers as they contain values of velocity.
        for (int jp = 0; jp < ppt; ++jp){
          myfile >> num;
        }
      }
      myfile.close();
      break;
    case 2:
      if(IsPathExist("data")){
        l = "data/";
        l.append(filename);
      }else{
        l=filename;
      }
      while( getline(myfile,token) ){
        line=token;
        getline(myfile,token);          // Dumping this: #---------
      }
      // Now convert all the tab separated entries to array.
      iss.str(line);
      // getline(iss, token, '\t');        // First entry is time, delete that.
      for (int idim = 0; idim < ndimt; ++idim){
        getline(iss, token, '\t');       // Get next token.
        y[idim]=stod(token);            // Convert to double and store it in y.
      }
      myfile.close();
      break;
    default:
      cout << "Hey, your choice of writing data does not exist. "
              "If you want a new way, Code function: wData( double y[], string filename) "
              "in model.cpp file." << endl;
      exit(1);
  }
}