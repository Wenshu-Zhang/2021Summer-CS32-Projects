//
//  Previous.cpp
//  Project1
//
//  Created by Claire Z on 6/22/21.
//

#include "Previous.h"
#include "Arena.h"
using namespace std;

Previous::Previous(int nRows, int nCols){
    m_rows = nRows;
    m_cols = nCols;
    //set counts at all positions to 0
    for (int i = 0; i < m_rows; i++){
        for (int k = 0; k < m_cols; k++){
            nCrumb[i][k] = 0;
        }
    }
}

bool Previous::dropACrumb(int r, int c){
    if (r > m_rows || c > m_cols || r < 1 || c < 1)
        return false;
    else{
        nCrumb[r-1][c-1]++;
        return true;
    }
}

void Previous::showPreviousMoves() const{
    clearScreen();
    char grid[MAXROWS][MAXCOLS];
    for (int i = 0; i < m_rows; i++){
        for (int k = 0; k < m_cols; k++){
            grid[i][k] = '.';
        }
    }
    for (int i = 0; i < m_rows; i++){
        for (int k = 0; k < m_cols; k++){
            int count = nCrumb[i][k];
            switch(count){
                case 0: grid[i][k] = '.'; break;
                case 1: grid[i][k] = 'A'; break;
                case 2: grid[i][k] = 'B'; break;
                case 3: grid[i][k] = 'C'; break;
                case 4: grid[i][k] = 'D'; break;
                case 5: grid[i][k] = 'E'; break;
                case 6: grid[i][k] = 'F'; break;
                case 7: grid[i][k] = 'G'; break;
                case 8: grid[i][k] = 'H'; break;
                case 9: grid[i][k] = 'I'; break;
                case 10: grid[i][k] = 'J'; break;
                case 11: grid[i][k] = 'K'; break;
                case 12: grid[i][k] = 'L'; break;
                case 13: grid[i][k] = 'M'; break;
                case 14: grid[i][k] = 'N'; break;
                case 15: grid[i][k] = 'O'; break;
                case 16: grid[i][k] = 'P'; break;
                case 17: grid[i][k] = 'Q'; break;
                case 18: grid[i][k] = 'R'; break;
                case 19: grid[i][k] = 'S'; break;
                case 20: grid[i][k] = 'T'; break;
                case 21: grid[i][k] = 'U'; break;
                case 22: grid[i][k] = 'V'; break;
                case 23: grid[i][k] = 'W'; break;
                case 24: grid[i][k] = 'X'; break;
                case 25: grid[i][k] = 'Y'; break;
                case 26: grid[i][k] = 'Z'; break;
                default: grid[i][k] = 'Z'; break;
            }
        }
    }
    for (int r = 0; r < m_rows; r++){
        for (int c = 0; c < m_cols; c++){
            cout << grid[r][c];
        }
        cout << endl;
    }
    cout << endl;
}
