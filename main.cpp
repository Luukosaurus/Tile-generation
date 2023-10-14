#include <iostream>
#include <time.h>
using namespace std;

enum Tile {Empty=0, Filled};
const char EMPTY            = '.' ;
const char FILLED           = '*' ; 
const int NO_OF_ROWS        = 40 ;               
const int NO_OF_COLUMNS     = 60 ;    

Tile tile_at (Tile grid [NO_OF_ROWS][NO_OF_COLUMNS], int row, int column){
    if (row > NO_OF_ROWS-1 || column > NO_OF_COLUMNS-1 || row < 0 || column < 0){
        return Empty;
    }
    return grid[row][column];
}

void show_grid (Tile grid [NO_OF_ROWS][NO_OF_COLUMNS]){
    Tile next_cell;
    string map;
    for (int i = 0; i < NO_OF_ROWS; i++){
        for (int j = 0; j < NO_OF_COLUMNS; j++){
            next_cell = grid[i][j];
            if (next_cell == Empty)
                map += EMPTY;
            else if (next_cell == Filled)
                map += FILLED;
        }
        map += '\n';;
    }
    cout << map;
}

void count_neighbors(Tile grid[NO_OF_ROWS][NO_OF_COLUMNS],Tile neighbors[8],int row_nr, int col_nr,int counts[2]){
    int neighbors_cord_trans[8][2]= {{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};
    for (int i = 0; i < 8; i++){
        if(tile_at(grid,row_nr+neighbors_cord_trans[i][0],col_nr+neighbors_cord_trans[i][1]) == Filled){
            if(i == 0 || i == 2 || i == 5 || i == 7){
                counts[0]++;
            } else {
                counts[1]++;
            }
        }
    }
}

void create_random_grid(Tile grid[NO_OF_ROWS][NO_OF_COLUMNS]){
    int total_chance = 100;
    int chance_of_dot;
    cout << "What percent of the grid needs to be filled (0-100): ";
    cin >> chance_of_dot;
    srand(time(0));
    for (int i = 0; i < NO_OF_ROWS; i++){
        for (int j = 0; j < NO_OF_COLUMNS; j++){
            if(rand()%total_chance < chance_of_dot){
                grid[i][j] = Filled;
            } else {
                grid[i][j] = Empty;
            }
        }
    }
}

void next_generation (Tile now [NO_OF_ROWS][NO_OF_COLUMNS], Tile next [NO_OF_ROWS][NO_OF_COLUMNS]){
    Tile current_Tile;
    Tile neighbors[8];
    int Alive_neighbors;
    for (int i = 0; i < NO_OF_ROWS; i++){
        for (int j = 0; j < NO_OF_COLUMNS; j++){
            current_Tile = now[i][j];
            int counts[2] = {0,0};
            count_neighbors(now,neighbors,i,j,counts);    
            if (counts[0] == 4 || counts[1] == 4){
                next[i][j] = Filled;
            } else if (counts[0] >= 2 && counts[1] >= 2 && current_Tile == Filled){
                next[i][j] = Filled;
            } else if ((counts[0] >= 2 && counts[1] == 3)||(counts[0] == 3 && counts[1] >=2)){
                next[i][j] = Filled;
            } else {
                next[i][j] = Empty;
            }
        }
    } 
}

int main (){
    int steps = 5;
    Tile my_uni[NO_OF_ROWS][NO_OF_COLUMNS];
    Tile next_uni[NO_OF_ROWS][NO_OF_COLUMNS];
    create_random_grid(my_uni);
    for (int i = 0; i < steps; i++){
        next_generation(my_uni,next_uni);
        next_generation(next_uni, my_uni);
    }
    show_grid(my_uni);
    return 0;
}
