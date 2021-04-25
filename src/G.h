#include<stdio.h>
#include<stdlib.h>
#include<SDL.h>

#define W 40

typedef struct Cell{
    int i ; // i nd j are position of the cell in the grid 
    int j ;
    SDL_bool visited; // state of a cell if it's visited or not
    SDL_bool state[4]; // state of walls if true then the wall apreas 
}Cell;




/***************functions cell related************/
void Draw_Cell(SDL_Renderer *renderer, Cell cell, int r , int g, int b){
   int x=cell.j*W;
   int y=cell.i*W;
    SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);
    if(cell.state[0]){
        SDL_RenderDrawLine(renderer, x     , y     , x + W , y     ); //top 
    }
    if(cell.state[1]){
    SDL_RenderDrawLine(renderer, x + W , y     , x + W , y + W ); //right
    }
    if(cell.state[2]){
    SDL_RenderDrawLine(renderer, x + W , y + W , x     , y + W ); //down 
    }
    if(cell.state[3]){
    SDL_RenderDrawLine(renderer, x     , y + W , x     ,y      ); //left
    }
}
Cell create_cell(int i, int j){
    Cell cell;
    cell.i=i;
    cell.j=j;
    cell.visited=SDL_FALSE;
    for(int i=0;i<4;i++)
        cell.state[i]=SDL_TRUE;
    return cell;
}
void add_cell(Cell **Grid, Cell cell, int countcells){
    (*Grid)[countcells]=cell;
}