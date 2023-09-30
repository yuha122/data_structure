#include <string>
using namespace std;

#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H

class MatrixTerm 
{ // an entry in a sparse matrix
    friend class SparseMatrix;
    private: 
        int row, col, value;
};

class SparseMatrix
{//A set of triples, <row, column, value>, where row and column are non-negative
// integers and form a unique combination; value is also an integer.
public:
    SparseMatrix(int r, int c, int t);
    // The constructor function creates a SparseMatrix with
    // r rows, c columns, and a capacity of t nonzero terms.

    int getvalue(int r, int c);
    // atomic getter, use index operator

    void setvalue(int r, int c, int v);
    // atomic setter, use index operator

    SparseMatrix Transpose();
    SparseMatrix FastTranspose();
    // Returns the SparseMatrix obtained by interchanging the row and column
    // value of every triple in *this.

    SparseMatrix Add(SparseMatrix b);
    // If the dimensions of this and b are the same, then the matrix produced by
    // adding corresponding items, namely those with identical row and column
    // values is returned; otherwise, an exception is thrown.

    SparseMatrix Multiply (SparseMatrix b);
    // If the number of columns in this equals the number of rows in b then the
    // matrix d produced by multiplying this and b according to the formula
    // d[i][j] = Σ(a [i][k ] · b [k ][j]), where d[i][j] is the (i, j)th element, is returned.
    // k ranges from 0 to one less than the number of columns in *this;
    // otherwise, an exception is thrown.

    string toString();
    // render a version of the matrix

private:
    int rows, cols, terms, capacity;
    MatrixTerm *smArray;

    void StoreSum(const int sum, const int r, const int c);
    void ChangeSize1D(const int newSize);
};
#endif