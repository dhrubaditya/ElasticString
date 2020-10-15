#ifndef FILE_NEWTONKRYLOV_SEEN
#define FILE_NEWTONKRYLOV_SEEN
/*****************************************************************/
// template<int Maxtry=128>
void newton_krylov(void func(double*), double yini[], int ndim,
                  int Maxtry=128,double tol=1.e-3, double eps_temp=1.e-4/2);

// template<int Maxtry=128>
void newton_krylov(void func(double*), double yini[], double fy[], int ndim,
                   int Maxtry=128,double tol=1.e-3, double eps_temp=1.e-4/2);
/*****************************************************************/
#endif