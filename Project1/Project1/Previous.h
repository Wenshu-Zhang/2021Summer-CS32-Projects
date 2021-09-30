//
//  Previous.h
//  Project1
//
//  Created by Claire Z on 6/22/21.
//
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

#include "globals.h"

class Arena;

#ifndef Previous_h
#define Previous_h

class Previous
{
 public:
    Previous(int nRows, int nCols);
    bool dropACrumb(int r, int c);
    void showPreviousMoves() const;
 private:
    Arena* m_arena;
    int m_rows;
    int m_cols;
    int nCrumb[MAXROWS][MAXCOLS];
};

#endif /* Previous_h */
