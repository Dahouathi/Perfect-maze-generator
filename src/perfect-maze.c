#include "G.h"

/*************************stuff to define*****************/


/*-------------------------------------------------------------------*/
//gcc src/perfect-maze.c -o bin/prog -I include -L lib -lmingw32 -lSDL2main -lSDL2
/*-------------------------------------------------------------------*/

void PrintEror(char* eror);
SDL_bool ProcessEvents(SDL_Event *event);
void Draw(SDL_Renderer *renderer, int colones, int rows, Cell *Grid, int  currentposition );
void Update(Cell **Grid, int rows, int colones,
 int **stack, int *top);

int main(int argc , char**argv)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) !=0){
        PrintEror("Can't initiante");
    }


    /** variables of the window**/

    int width =800;
    int hight =600;
    SDL_Window   *screen  = NULL;
    SDL_Renderer *renderer= NULL;
    screen=SDL_CreateWindow("Perfect Maze Generator",
    SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
    width,hight,SDL_WINDOW_RESIZABLE);
    if(screen==NULL){
        PrintEror("Can't create window");
    }
    renderer=SDL_CreateRenderer(screen,-1,
    SDL_RENDERER_ACCELERATED || SDL_RENDERER_PRESENTVSYNC);
    if(renderer==NULL){
        PrintEror("Can't make the Renderer");
    }
    if(SDL_SetRenderDrawColor(renderer,0,0,0,SDL_ALPHA_OPAQUE)!=0){
        PrintEror("Cant set Renderer color");
    }
    /***************************************************************/

    /**********************maze variables************************/

    int colones =(int)width/W;
    int rows    =(int)hight/W;
    int countcells=0;
    Cell *Grid=malloc(sizeof(Cell)*(rows+1)*colones);
    for(int i=0; i<rows;i++)
        for(int j=0;j<colones;j++)
            {
                countcells=j+i*colones;
                add_cell(&Grid,create_cell(i,j),countcells);
            }
    int currentpostion=0; //change current to position int
    /*********stack variables***********/
    int *stack=malloc(sizeof(int)*(rows+1)*colones);
    int top =-1;

    /**********************Loop**************************/

    SDL_bool Lunch=SDL_TRUE;
    pushstack(&stack,currentpostion,&top);
    while (Lunch)
    {
        /* code */
        if(!is_stack_empty(top)){
            currentpostion=peek(stack,top);
        }
        
        SDL_Event event;
        Lunch=ProcessEvents(&event);
        Draw(renderer,colones, rows,Grid,currentpostion);
        Update(&Grid,rows,colones,&stack,&top);
        //printstack(stack,top);
        SDL_Delay(1000/60);
    
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(screen);
    SDL_Quit();

    return 0;
}

/*--------------------------------------------------------*/
                      // Functions dev :
/*--------------------------------------------------------*/


void PrintEror(char* eror)
{
    SDL_Log("ERREUR :%s >%s\n", eror, SDL_GetError());
    exit(EXIT_FAILURE);
}

SDL_bool ProcessEvents(SDL_Event *event)
{
    SDL_bool Lunch=SDL_TRUE;
    while(SDL_PollEvent(event)){
        switch (event->type)
        {
        case SDL_QUIT:
            printf("it's over");
            Lunch=SDL_FALSE;
            break;
        
        default:
            break;
        }
    }
    return Lunch;
}

void Draw(SDL_Renderer *renderer, int colones, 
int rows, Cell *Grid, int currentposition)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    
    int position;
    for(int i=0;i<rows;i++)
        for(int j=0;j<colones;j++){
            position=j+i*colones;
            Draw_Cell(renderer,Grid[position],255,0,26);
        }
    DrawcurentCell(Grid[currentposition],renderer);
    





    SDL_RenderPresent(renderer);
}

void Update(Cell **Grid, int rows, int colones, 
 int **stack, int *top)
{
    
    if(!is_stack_empty(*top)){
        int currentpostion=peek(*stack,*top);
        (*Grid)[(currentpostion)].visited=SDL_TRUE;
    
        int nextpostion=findNextCell((*Grid)[currentpostion],*Grid,rows,colones);
        if(nextpostion!=-1){
        
            
            pushstack(stack,nextpostion,top);
            destroy_wall(Grid,currentpostion,nextpostion);
        
        }
        else{
            popstack(*stack,top);
        }
    }
    else{
        (*top)++;
    }

    
    

}

