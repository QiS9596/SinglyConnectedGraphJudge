//
//  main.c
//  SingleConnectedGraphJudge
//
//  Created by Rolo on 16/5/20.
//  Copyright © 2016年 Rolo. All rights reserved.
//

#include <stdio.h>
const int COLOR_WHITE = 0;
const int COLOR_GRAY = 1;
const int COLOR_BLACK = 2;
int adjacency_matrix[1000][1000];

struct vertex{
    int color;
    int visited_count;
};

void DFS_visit(struct vertex * vertices, int vertices_count, int vertex,int * flag);

int main(int argc, const char * argv[]) {
    //open file
    FILE * file = fopen("test.txt","r");
    //read how many graphs in the current file
    int graph_count;
    fscanf(file,"%d",&graph_count);
    //the following loop handle one graph each loop
    for (int index = 0; index < graph_count; index++) {
        //read how many vertices is in this graph
        int vertices_count;
        fscanf(file, "%d", &vertices_count);

        //build a array to store the vertices in the current graph information
        //including the color and visited_count in a depth first search
        struct vertex vertices[vertices_count];
        //initialization of vertices' color and visited count properties
        //initialization of adjacency list
        for(int indexa = 0; indexa < vertices_count; indexa++){
            vertices[indexa].color = COLOR_WHITE;
            vertices[indexa].visited_count = 0;
            for (int indexb = 0; indexb < vertices_count; indexb++) {
                adjacency_matrix[indexa][indexb] = 0;
            }
        }// end of initialization loop

        //read how many edges are in this graph
        int edge_count;
        fscanf(file,"%d", &edge_count);
        for (int indexa = 0; indexa < edge_count; indexa++) {
            int start_vertex, end_vertex;
            fscanf(file, "%d", &start_vertex);
            fscanf(file, "%d", &end_vertex);
            adjacency_matrix[start_vertex][end_vertex] = 1;
        }

        //build a table stores the value find by depth first search
        //the following loop initialize the table to zeros
        int path_table[vertices_count][vertices_count];
        for (int indexa = 0; indexa < vertices_count; indexa++) {
            for (int indexb = 0; indexb < vertices_count; indexb++) {
                path_table[indexa][indexb] = 0;
            }
        }

        //pay DFS visit for each point in the graph
        //if we discover an edge who leads to a BLACK vertex, we find a forward or cross edge
        //which result int multiple simple path
        //record the visited_count filed and re-initialize the visited_count and color fild of the vertices
        int flag = 1;
        //the following loop use dfs search a vertex onece a time
        for (int indexa = 0; indexa < vertices_count; indexa++) {
            DFS_visit( vertices, vertices_count, indexa,&flag);
            for (int indexb = 0; indexb < vertices_count; indexb++) {
                path_table[indexa][indexb] = vertices[indexb].visited_count;
            }
            for (int indexb = 0; indexb < vertices_count; indexb++) {
                vertices[indexb].visited_count = 0;
                vertices[indexb].color = COLOR_WHITE;
            }
        }
        //print out the result
        printf("%d %s\n", index+1,(flag?"yes":"no"));
    }
    printf("program terminated\n");
    return 0;
}
//DFS visit form a vertex
//if we discover an edge who leads to black vertex, we find a forward edge or cross edge
//then we set flag to 0 to indecate that this graph is not singly connected
void DFS_visit(struct vertex * vertices, int vertices_count, int vertex, int * flag){
    vertices[vertex].visited_count+=1;
    vertices[vertex].color = COLOR_GRAY;
    for (int index = 0; index < vertices_count; index++) {
        if(adjacency_matrix[vertex][index]){
            if(vertices[index].color == COLOR_GRAY)
                vertices[index].visited_count++;
            else if(vertices[index].color == COLOR_BLACK)
            {
                vertices[index].visited_count++;
                (*flag) = 0;
            }
            else DFS_visit(vertices, vertices_count, index, flag);
        }
    }
    vertices[vertex].color = COLOR_BLACK;

}
