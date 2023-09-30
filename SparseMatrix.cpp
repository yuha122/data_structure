#include <iostream>
#include <string>
#include <cstdio>
#include "SparseMatrix.h"
using namespace std;

SparseMatrix::SparseMatrix(int r, int c, int t)
{
    rows = r;
    cols = c;
    capacity = t;
    terms = 0;
    smArray = new MatrixTerm[t];
    for (int i = 0; i<t; i++) {
        smArray[i].row = r+c;
        smArray[i].col = r+c;
        smArray[i].value = 0;
    }
}

int SparseMatrix::getvalue(int r, int c) {
    // linear search version
    for (int i = 0; i < terms; i++)
        if (smArray[i].row == r)
            if (smArray[i].col == c)
                return smArray[i].value;
    return 0;
}

void SparseMatrix::setvalue(int r, int c, int v) {
    if ((r < 0) || (r >= rows) || (c < 0) || (c >= cols))
        throw "SparseMatrix index is out of bounds";
    int found = 0;
    MatrixTerm move;
    // linear search version
    for (int i = 0; i < terms; i++) {
        if ((smArray[i].row == r) && (smArray[i].col == c)) {
            smArray[i].value == v;
            found = 1;
            break;
        }
        if ((smArray[i].row > r) || ((smArray[i].row == r) && (smArray[i].col > c))) {
            if (found == 0) {
                move = smArray[i];
                smArray[i].row = r;
                smArray[i].col = c;
                smArray[i].value = v;
                found = 2;
            } else {
                MatrixTerm temp = smArray[i];
                smArray[i] = move;
                move = temp;
            }
        }
    }
    if (found == 1)
        return;
    if (terms == capacity)
        throw "SparseMatrix set exceeds capacity";
    if (found == 0) {
        terms += 1;
        smArray[terms-1].row = r;
        smArray[terms-1].col = c;
        smArray[terms-1].value = v;
    } else if (found == 2) {
        terms += 1;
        smArray[terms-1] = move;
    }
    return;
}


SparseMatrix SparseMatrix::Transpose()
{// Return the transpose of this.
    SparseMatrix b(cols, rows, terms); // capacity of b.smArray is terms
    if (terms > 0) {// nonzero matrix
        int currentB = 0;
        for (int c = 0; c < cols ; c++) // transpose by columns
            for (int i = 0; i < terms; i++)
            // find and move terms in column c
                if (smArray[i].col == c) {
                    b.smArray[currentB].row = c;
                    b.smArray[currentB].col = smArray[i].row;
                    b.smArray[currentB++].value = smArray[i].value;
                    b.terms += 1;
                }
    } // end of if (terms > 0)
    return b;
}

SparseMatrix SparseMatrix::FastTranspose()
{// Return the tanspose of *this in O(terms + cols) time.
    SparseMatrix b(cols, rows, terms);
    if (terms > 0) {// nonzero matrix
        int i;
        int *rowSize = new int[cols];
        int *rowStart = new int[cols];
        // compute rowSize[i] = number of terms in row i of b
        fill(rowSize, rowSize + cols, 0);       // initialize
        for (i=0; i < terms; i++)
            rowSize[smArray[i].col]++;

        // rowStart[i] = starting position of row i in b
        rowStart[0] = 0;
        for (i = 1; i < cols; i++)
            rowStart[i] = rowStart[i-1] + rowSize[i-1];

        for (i = 0; i < terms; i++) {// copy from *this to b
            int j = rowStart[smArray[i].col];
            b.smArray[j].row = smArray[i].col;
            b.smArray[j].col = smArray[i].row;
            b.smArray[j].value = smArray[i].value;
            rowStart[smArray[i].col]++;
            b.terms += 1;
        } // end of for
        delete [] rowSize;
        delete [] rowStart;
    } // end of if
    return b;
}

void SparseMatrix::ChangeSize1D(const int newSize)
{// Change the size of smArray to newSize
    if (newSize < terms)
        throw "New size must be >= number of terms";
    MatrixTerm *temp = new MatrixTerm[newSize]; // new array
    copy(smArray, smArray+terms, temp);
    delete [] smArray;  // deallocate old memeory
    smArray = temp;
    capacity = newSize;
}

void SparseMatrix::StoreSum(const int sum, const int r, const int c) 
{// If sum != 0, then it along with it row and column position are
 // stored as the last term in *this.
    if (sum != 0) {
        if (terms == capacity)
            ChangeSize1D(2*capacity); // double size
        smArray[terms].row = r;
        smArray[terms].col = c;
        smArray[terms++].value = sum;
    }
}

SparseMatrix SparseMatrix::Multiply(SparseMatrix b)
{// Return the producr of the sparce matrices *this and b.
    if (cols != b.rows)
        throw "Incompatible matrices for Multiply";
    SparseMatrix bXpose = b.FastTranspose();
    SparseMatrix d(rows, b.cols, 0);
    int currRowIndex = 0,
        currRowBegin = 0,
        currRowA = smArray[0].row;
    // set boundary conditions
    if (terms == capacity) ChangeSize1D(terms+1);
    bXpose.ChangeSize1D(bXpose.terms+1);
    smArray[terms].row = rows;
    bXpose.smArray[b.terms].row = b.cols;
    bXpose.smArray[b.terms].col = -1;
    int sum = 0;
    while (currRowIndex < terms)
    {// generate row currentRowA of d
        int currColB = bXpose.smArray[0].row;
        int currColIndex = 0;
        while (currColIndex <= b.terms)
        {// multiply row currRowA of *this by column currColB of b
            if (smArray[currRowIndex].row != currRowA)
            {// end of row currRowA
                d.StoreSum(sum, currRowA, currColB);
                sum = 0;    // reset sum
                currRowIndex = currRowBegin;
                // advance to next column
                while (bXpose.smArray[currColIndex].row == currColB)
                    currColIndex++;
                currColB = bXpose.smArray[currColIndex].row;
            } else 
            if (bXpose.smArray[currColIndex].row != currColB)
            {// end of column currColB of b
                d.StoreSum(sum, currRowA, currColB);
                sum = 0;    // reset sum
                // set to multiply row currRowA with next column
                currRowIndex = currRowBegin;
                currColB = bXpose.smArray[currColIndex].row;
            } else 
            if (smArray[currRowIndex].col < bXpose.smArray[currColIndex].col)
                currRowIndex++;     // advance to the next term in row
            else 
            if (smArray[currRowIndex].col == bXpose.smArray[currColIndex].col)
            {// add to sum
                sum += smArray[currRowIndex].value * bXpose.smArray[currColIndex].value;
                currRowIndex++; currColIndex++;
            }
            else
                currColIndex++;     // next term in currColB
        } // end of while (currColIndex <= b.terms)
        while (smArray[currRowIndex].row == currRowA) // advance to next row
            currRowIndex++;
        currRowBegin = currRowIndex;
        currRowA = smArray[currRowIndex].row;
    } // end of while (currRowIndex < terms)
    return d;
}

SparseMatrix SparseMatrix::Add(SparseMatrix b)
{
    if ((cols != b.cols) || (rows != b.rows)){
        throw "Incompatible matrices for Add";
    }
    SparseMatrix sum(rows, cols, terms + b.terms);
    int thisIndex = 0, bIndex = 0;
    

    while ((thisIndex < terms) || (bIndex < b.terms)){
        int trow, tcol, brow, bcol;
        if (thisIndex < terms){
            trow = smArray[thisIndex].row;
            tcol = smArray[thisIndex].col;
        } else{
            trow = rows;
            tcol = cols;
        }
        if (bIndex < b.terms){
            brow = b.smArray[bIndex].row;
            bcol = b.smArray[bIndex].col;
        }else{
            brow = rows;
            bcol = cols;
        }
        if ((trow == brow) && (tcol == bcol)){
            sum.setvalue(trow, bcol, smArray[thisIndex].value + b.smArray[bIndex].value);
            thisIndex++;
            bIndex++;
        } else{
            if (((trow == brow) && (tcol < bcol)) || (trow < brow)){
                sum.setvalue(trow, tcol, smArray[thisIndex].value);
                thisIndex++;
            }
            else {
                sum.setvalue(brow, bcol, b.smArray[bIndex].value);
                bIndex++;
            }
        }
    }
    return sum;    
}

string SparseMatrix::toString()
{
    string output = "";
    MatrixTerm term;
    for (int i = 0; i < terms; i++) {
        MatrixTerm term = smArray[i];
        output += "smArray[" + to_string(term.row) + "][" + to_string(term.col) + "] = ";
        output += to_string(term.value) + "\n";
    }
    return output;
}



/*********************************************
void classic(SparseMatrix a, SparseMartix b) {
    SparseMatrix c;
    SparseMatrix bxpose = b.FastTranspose();
    for (int i = 0; i < a.rows; i++)
        for (int j = 0; j < bxpose.rows; j++) {
            sum = 0;
            for (int k = 0; k < a.cols; k++)
                if ((a[i] has index k) && (b[j] has index k))
                    sum += a[i][k] * b[j][k];
            c[i][j] = sum;
        }
}
*********************************************/