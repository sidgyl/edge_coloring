//
//  main.cpp
//  edge_coloring
//
//  Created by Sidharth Goyal on 8/7/15.
//  Copyright (c) 2015 Sidharth Goyal. All rights reserved.
//

// C++ program to find out whether a given graph is Bipartite or not
#include <iostream>
#include <queue>
#include <fstream>
#define V 4
using namespace std;

/*
 Global variables used in Program
 nl: number of vertices in the left set
 nr: number of vertices in the right set
 maxClrs: the maximum number of different colors that can be used to color the edges
 */
int  nl=0, nr=0, maxClrs=0;
int * colorMatrix = NULL;
/*
 Updates the color being used to color the edge.
 updates by 1 till it reaches maximum and then 
 starts from 0 again
*/
int updateCurrColor(int currColor){
    colorMatrix[currColor] = -1;
    int count = 0;
    for (int i=0; i<maxClrs; i++) {
        if (colorMatrix[i] != -1) {
            return colorMatrix[i];
        }else{
            count ++;
        }
    }
    
    if (count == maxClrs) {
        for (int i=0; i<maxClrs; i++) {
            colorMatrix[i] = i;
        }
    }
    
    return colorMatrix[0];
}

/*
 Checks neighbors to see if the current color is free on edges connectd to 
 both the nodes
*/
bool checkNeighbors(int **colors, int l, int r, int currClr){
    for (int i=0; i<nr; i++) {
//        cout<<colors[l][i];
        if (colors[l][i] == currClr) {
            return false;
        }
    }
    
    for (int i=0; i<nl; i++) {
        if (colors[i][r] == currClr) {
            return false;
        }
    }
    
    return true;
}

/*
This function counts the maximum degree for each node to get 
the maxumum number of colors that can be used.
*/
int maxColors(int **G){
    int max = 0;
    for (int i; i<nl; i++) {
        int count = 0;
        for (int j=0; j<nr; j++) {
            if (G[i][j] == 1) {
                count++;
                if (count > max) {
                    max = count;
                }
            }
        }
    }
    
    for (int i=0; i<nr; i++) {
        int count = 0;
        for (int j=0; j<nl; j++) {
            if (G[i][j] == 1) {
                count++;
                if (count > max) {
                    max = count;
                }
            }
        }
    }
    
    return max;
}

/*
 This function prints a 2D matrix with given number of rows and columns
 */
void printMatrix(int ** matrix, int rows, int col){
    cout<<endl;
    for (int i=0; i<rows; i++) {
        for (int j = 0; j<col; j++) {
            cout<<matrix[i][j]<<" ";
        }
        cout << endl;
    }
}

/*
 This function checks a speific row and column for a given color. 
 it will check the entire row 'l' and entire column 'r' to make sure 
 that the current color is not used by any neighbors
 */
bool checkColorMatrix(int ** color, int num, int l, int r){
    for (int i=0; i<nr; i++) {
        if (color[l][i] == num) {
            return false;
        }
    }
    
    for (int i=0; i<nl; i++) {
        if (color[i][r] == num) {
            return false;
        }
    }
    
    return true;
}

int findConflictLocation(int **colors, int currClr, int r){
    int conflictLocation = 0;
    for (int i=0; i<nl; i++) {
        if (colors[i][r] == currClr) {
            conflictLocation = i;
            return conflictLocation;
        }
    }
    
    return -1;
}

void swap(int r, int l, int currClr, int **colors){
    int conflict =0;
    int col = 0, i;
    for ( i=0; i<nl; i++) {
        if (colors[i][r] == currClr && i != l) {
            conflict = i;
            break;
        }
    }
    
    if (r == 0) {
        col = 1;
    }else
        col = 0;
    
    if (i != nl) {
        int temp = colors[conflict][col];
        colors[conflict][col] = colors[conflict][r];
        colors[conflict][r] = temp;
        swap(col, conflict, colors[conflict][col], colors);
    }
}

/*
 This method checks to see what colos is not used for both the nodes in the esge
 in case of a conflict. Returns the color that can be used
 */
int findCommon(int **G, int **colors,int l, int r, int currColor){
    for (int i=0; i<maxClrs; i++) {
        //The if checks if the colormatrix has any usable colors. and then checks to
        //see of the color can be used i.e., if the color is not used by any of the
        //neghbors of both the nodes
        if (colorMatrix[i] != -1 && checkColorMatrix(colors, colorMatrix[i], l, r)) {
            currColor = i;
            colors[l][r] = currColor;
            currColor = updateCurrColor(currColor);
            return currColor;
        }
    }
    
    swap(r,l, currColor, colors);
    colors[l][r] = currColor;
    currColor = updateCurrColor(currColor);
//    printMatrix(colors, nl, nr);
    
    return currColor;
}

// Driver program to test above function
int main()
{
    int **G = NULL;     //2D adgecency matrix to hold all the edges
    int **colors = NULL;    //2D matrix to hold the colors assigned to each edge
    int m, vl, vr;
    
    //Takes input from the input file
    ifstream myfile("/Volumes/Macintosh HD/College/semeseters/Spring15/edge_coloring/edge_coloring/k5.dat");
    if (myfile.is_open()) {
        myfile>>nl>>nr>>m;
        G = new int *[nl];
        colors = new  int *[nl];
        for (int i=0; i<nl; i++) {
            G[i] = new int[nr];
            colors[i] = new int[nr];
        }
        
        for (int i =0; i<nl; i++) {
            for (int j=0; j<nr; j++) {
                G[i][j]=0;
                colors[i][j] = -1;
            }
        }
        while (myfile>>vl>>vr) {
            G[vl][vr] = 1;
        }
        
    }
    
    maxClrs = maxColors(G);
    colorMatrix = new int[maxClrs];
    for (int i=0; i<maxClrs; i++) {
        colorMatrix[i] = i;
    }
    int currColor = colorMatrix[0];
    //Nested for loop to traverse each elemnt in the adgecency matrix G.
    for (int i=0; i<nl; i++) {
        for (int j=0; j<nr; j++) {
            if (G[i][j] == 1) {
                if (checkNeighbors(colors, i, j, currColor)) {   //check the nighbors to see if the current color can be used
                    colors[i][j] = currColor; //if the current color is acceptable, update the color matrix
                    currColor = updateCurrColor(currColor);  //update the current color now that it has been used.
                }else{
                    //get possible colors for position i,j
                    currColor = findCommon(G, colors, i, j, currColor);
                }
            }
//            printMatrix(colors, nl, nr);
        }
    }
    
    for (int i=0; i<nl; i++) {
        for (int j=0; j<nr; j++) {
            cout<<i<<" "<<j<<" "<<colors[i][j]<<endl;
        }
    }

    return 0;
}

