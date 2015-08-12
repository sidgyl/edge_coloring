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


// This function returns true if graph G[V][V] is Bipartite, else false
//bool isBipartite(int G[][V], int src)
//bool isBipartite(int **G, int src, int nl, int nr){
//    // Create a color array to store colors assigned to all veritces. Vertex
//    // number is used as index in this array. The value '-1' of colorArr[i]
//    // is used to indicate that no color is assigned to vertex 'i'. The value
//    // 1 is used to indicate first color is assigned and value 0 indicates
//    // second color is assigned.
//    int colorArr[V];
//    for (int i = 0; i < V; ++i)
//        colorArr[i] = -1;
//    
//    // Assign first color to source
//    colorArr[src] = 1;
//    
//    // Create a queue (FIFO) of vertex numbers and enqueue source vertex
//    // for BFS traversal
//    queue <int> q;
//    q.push(src);
//    
//    // Run while there are vertices in queue (Similar to BFS)
//    while (!q.empty())
//    {
//        // Dequeue a vertex from queue ( Refer http://goo.gl/35oz8 )
//        int u = q.front();
//        q.pop();
//        
//        // Find all non-colored adjacent vertices
//        for (int v = 0; v < V; ++v)
//        {
//            // An edge from u to v exists and destination v is not colored
//            if (G[u][v] && colorArr[v] == -1)
//            {
//                // Assign alternate color to this adjacent v of u
//                colorArr[v] = 1 - colorArr[u];
//                q.push(v);
//            }
//            
//            // An edge from u to v exists and destination v is colored with
//            // same color as u
//            else if (G[u][v] && colorArr[v] == colorArr[u])
//                return false;
//        }
//    }
//    
//    // If we reach here, then all adjacent vertices can be colored with
//    // alternate color
//    return true;
//}
//
void assignColor(int **G, int l, int r, int maxClrs, int **colors){
    
}

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
        cout<<colors[l][i];
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
 This method checks to see what colos is not used for both the nodes in the esge
 in case of a conflict. Returns the color that can be used
 */
int findCommon(int **G, int **colors, int l, int r, int currColor){

    int posibleColors[maxClrs];
    int posibleColors1[maxClrs];
    for (int i =0; i<nl; i++) {
        posibleColors[i] = -1;
    }
    for (int i=0; i<nr; i++) {
        posibleColors1[i] = -1;
    }
    
    
    for (int i=0; i<nl; i++) {
        if (-1 == colors[l][i] && colors[l][i] != currColor) {
            posibleColors[i] = i;
        }else{
            posibleColors[i] = -1;
        }
    }
    
    for (int j=0; j<nr; j++) {
        if (colors[j][r] == -1 && colors[j][r] != currColor) {
            posibleColors1[j] = j;
        }else{
            posibleColors1[j] = -1;
        }
    }
    
    for (int i=0; i<nl && i<nr; i++) {
        if (posibleColors[i] == posibleColors1[i] && posibleColors[i] != -1) {
            return posibleColors[i];
        }
    }
    
    return -1;
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
                    colors[i][j] = currColor;
                    currColor = updateCurrColor(currColor);
                }
            }
        }
    }

    return 0;
}
