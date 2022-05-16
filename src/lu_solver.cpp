/*
 * copied and adapted from wikipedia
 * https://en.wikipedia.org/wiki/LU_decomposition
 * 
 * 
 */
 
#include "lu_solver.hpp"

void LU_solver::solve(std::shared_ptr<BaseMatrix<double> > Ap, const std::vector<double>& b, std::vector<double>& x)
{

	Matrix<double> A = dynamic_cast<Matrix<double>&>(*Ap);
	
	std::vector<int> P(A.nbRows()+1);

	LUPDecompose(A, P);

	LUPSolve(A, P, b, x);

}

/* INPUT: A - array of pointers to rows of a square matrix having dimension N
 *        Tol - small tolerance number to detect failure when the matrix is near degenerate
 * OUTPUT: Matrix A is changed, it contains a copy of both matrices L-E and U as A=(L-E)+U such that P*A=L*U.
 *        The permutation matrix is not stored as a matrix, but in an integer vector P of size N+1 
 *        containing column indexes where the permutation matrix has "1". The last element P[N]=S+N, 
 *        where S is the number of row exchanges needed for determinant computation, det(P)=(-1)^S    
 */
void LU_solver::LUPDecompose(Matrix<double>& A, std::vector<int>& P) {

    UInt imax, j; 
    double maxA, absA;

    for (UInt i = 0; i < P.size(); i++)
        {
			P[i] = i;} //Unit permutation matrix, P[N] initialized with N

    for (UInt i = 0; i < A.nbRows(); i++) {
        maxA = 0.0;
        imax = i;

        for (UInt k = i; k < A.nbRows(); k++)
            if ((absA = fabs(A(k, i))) > maxA) { 
                maxA = absA;
                imax = k;
            }

        //if (maxA < Tol) return 0; //failure, matrix is degenerate
		//assert(maxA > epsilon);

        if (imax != i) {
            //pivoting P
            j = P[i];
            P[i] = P[imax];
            P[imax] = j;

            //pivoting rows of A
            A.permute_rows(i,imax);

            //counting pivots starting from N (for determinant)
            P[A.nbRows()]++;
        }

        for (UInt j = i + 1; j < A.nbRows(); j++) {
            A(j,i) /= A(i,i);

            for (UInt k = i + 1; k < A.nbRows(); k++)
                A(j,k) -= A(j,i) * A(i,k);
        }
    }
  //decomposition done 
}

/* INPUT: A,P filled in LUPDecompose; b - rhs vector; N - dimension
 * OUTPUT: x - solution vector of A*x=b
 */
void LU_solver::LUPSolve(Matrix<double>& A, std::vector<int>& P, const std::vector<double>& b, std::vector<double>& x) {

    for (UInt i = 0; i < A.nbRows(); i++) {
        x[i] = b[P[i]];

        for (UInt k = 0; k < i; k++)
            x[i] -= A(i,k) * x[k];
    }

    for (int i = A.nbRows() - 1; i >= 0; i--) {
        for (UInt k = i + 1; k < A.nbRows(); k++)
            x[i] -= A(i,k) * x[k];

        x[i] /= A(i,i);
    }
}




/* INPUT: A,P filled in LUPDecompose; N - dimension
 * OUTPUT: IA is the inverse of the initial matrix
 
 
void LUPInvert(double **A, int *P, int N, double **IA) {
  
    for (int j = 0; j < N; j++) {
        for (int i = 0; i < N; i++) {
            IA[i][j] = P[i] == j ? 1.0 : 0.0;

            for (int k = 0; k < i; k++)
                IA[i][j] -= A[i][k] * IA[k][j];
        }

        for (int i = N - 1; i >= 0; i--) {
            for (int k = i + 1; k < N; k++)
                IA[i][j] -= A[i][k] * IA[k][j];

            IA[i][j] /= A[i][i];
        }
    }
}
*/
/* INPUT: A,P filled in LUPDecompose; N - dimension. 
 * OUTPUT: Function returns the determinant of the initial matrix

 
double LUPDeterminant(double **A, int *P, int N) {

    double det = A[0][0];

    for (int i = 1; i < N; i++)
        det *= A[i][i];

    return (P[N] - N) % 2 == 0 ? det : -det;
}
 */




