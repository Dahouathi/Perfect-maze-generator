#include<stdio.h>
#include<stdlib.h>
#include<SDL.h>
#include<time.h>
#define W 40
#define rc 255
#define gc 255
#define bc 255
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
   SDL_Rect rect ;
   rect.x=x;
   rect.y=y;
   rect.h=W;
   rect.w=W;
   SDL_SetRenderDrawColor(renderer,0,0,0,SDL_ALPHA_OPAQUE);
   SDL_RenderFillRect(renderer,&rect);
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

void DrawcurentCell(Cell current, SDL_Renderer *renderer){
    //Draw current cell 
    SDL_Rect rect ;
    int i=current.i;
    int j=current.j;
    rect.x=j*W;
    rect.y=i*W;
    rect.h=W;
    rect.w=W;
    SDL_SetRenderDrawColor(renderer,rc,gc,bc,SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer,&rect);
}
int findNextCell(Cell current, Cell *Grid, int rows, int colones){
    int i=current.i;
    int j=current.j;
    
    int tab[4];
    int nb=0;
    if(i>0 && i<rows-1 && j>0 && j<colones-1)
    {
        //printf("i am here in the\n ");
        if(!Grid[j+1+i*colones].visited)
        {
            tab[nb]=j+1+i*colones;
            nb++;
        
        }
        if(!Grid[j+(i+1)*colones].visited)
        {
            tab[nb]=j+(i+1)*colones;
            nb++;
        
        }
        if(!Grid[j-1+(i)*colones].visited)
        {
            tab[nb]=j-1+(i)*colones;
            nb++;
        
        }
        if(!Grid[j+(i-1)*colones].visited)
        {
            tab[nb]=j+(i-1)*colones;
            nb++;
        
        }
    }
    else if (i==0 && j==0)
    {
        /* code */
        //printf("i am here both 0\n");
        if(!Grid[j+1+i*colones].visited)
        {
            tab[nb]=j+1+i*colones;
            nb++;
        
        }
        if(!Grid[j+(i+1)*colones].visited)
        {
            tab[nb]=j+(i+1)*colones;
            nb++;
        
        }
        
    }
    else if (i==0 && j==colones-1)
    {
        /* code */
        //printf("i am here both i0 j n\n");
        
        if(!Grid[j+(i+1)*colones].visited)
        {
            tab[nb]=j+(i+1)*colones;
            nb++;
        
        }
        if(!Grid[j-1+(i)*colones].visited)
        {
            tab[nb]=j-1+(i)*colones;
            nb++;
        
        }
        
    }
    else if (i==rows-1 && j==0)
    {
        /* code */
        //printf("i am here both in j0\n");
        if(!Grid[j+1+i*colones].visited)
        {
            tab[nb]=j+1+i*colones;
            nb++;
        
        }
        if(!Grid[j+(i-1)*colones].visited)
        {
            tab[nb]=j+(i-1)*colones;
            nb++;
        
        }
        
    }
    else if (i==0)
    {
        if(!Grid[j+1+i*colones].visited)
        {
            tab[nb]=j+1+i*colones;
            nb++;
        
        }
        if(!Grid[j+(i+1)*colones].visited)
        {
            tab[nb]=j+(i+1)*colones;
            nb++;
        
        }
        if(!Grid[j-1+(i)*colones].visited)
        {
            tab[nb]=j-1+(i)*colones;
            nb++;
        
        }
        
    }
    else if (j==0)
    {
        //printf("i am here j 0\n");
        if(!Grid[j+1+i*colones].visited)
        {
            tab[nb]=j+1+i*colones;
            nb++;
        
        }
        if(!Grid[j+(i+1)*colones].visited)
        {
            tab[nb]=j+(i+1)*colones;
            nb++;
        
        }
        if(!Grid[j+(i-1)*colones].visited)
        {
            tab[nb]=j+(i-1)*colones;
            nb++;
        
        }
    }
    else if (j==colones-1 && i==rows-1)
    {
        //printf("i am here both n\n");
        if(!Grid[j-1+(i)*colones].visited)
        {
            tab[nb]=j-1+(i)*colones;
            nb++;
        
        }
        if(!Grid[j+(i-1)*colones].visited)
        {
            tab[nb]=j+(i-1)*colones;
            nb++;
        
        }
    }
    else if (i==rows-1)
    {
        //printf("i am here i n\n");
        if(!Grid[j+1+i*colones].visited)
        {
            tab[nb]=j+1+i*colones;
            nb++;
        
        }
        if(!Grid[j-1+(i)*colones].visited)
        {
            tab[nb]=j-1+(i)*colones;
            nb++;
        
        }
        if(!Grid[j+(i-1)*colones].visited)
        {
            tab[nb]=j+(i-1)*colones;
            nb++;
        
        }
    }
    else if (j==colones-1)
    {
       //printf("i am here j n\n");
        if(!Grid[j+(i+1)*colones].visited)
        {
            tab[nb]=j+(i+1)*colones;
            nb++;
        
        }
        if(!Grid[j-1+(i)*colones].visited)
        {
            tab[nb]=j-1+(i)*colones;
            nb++;
        
        }
        if(!Grid[j+(i-1)*colones].visited)
        {
            tab[nb]=j+(i-1)*colones;
            nb++;
        
        }
    }
    
    //printf("current postiont%d,%d\n",i,j); 
    //printf("nb%d\n",nb);
    if(nb>1){
        srand(time(NULL));   // Initialization, should only be called once.
        int r = rand() %nb;
        //printf("next postiont%d,%d\n",Grid[tab[r]].i,Grid[tab[r]].j);      // Returns a pseudo-random integer between 0 and RAND_MAX.
        return tab[r];
    }
    else if (nb==1)
    {
        //printf("next postiont%d,%d\n",Grid[tab[0]].i,Grid[tab[0]].j);      // Returns a pseudo-random integer between 0 and RAND_MAX.
        return tab[0];
    }
    else {
        //printf("nonextposition\n");
        return -1;   
    }
}

void destroy_wall(Cell *current, Cell *next){

    if(current->j-next->j==-1){
        next->state[3]=SDL_FALSE;
        current->state[1]=SDL_FALSE;
    }
    if(current->j-next->j==1){
        next->state[1]=SDL_FALSE;
        current->state[3]=SDL_FALSE;
    }
    if(current->i-next->i==-1){
        next->state[0]=SDL_FALSE;
        current->state[2]=SDL_FALSE;
    }
    if(current->i-next->i==-1){
        next->state[2]=SDL_FALSE;
        current->state[0]=SDL_FALSE;
    }

}








