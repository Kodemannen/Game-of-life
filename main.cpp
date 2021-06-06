#include <iostream>
//#include <cmath>
#include <armadillo>

using namespace std;
using namespace arma;


// Create function for extracting a slice

//#include <iomanip>

int main () {

    /*
    We have a one dimensional grid. Each unit in the grid is 0 or 1,
    visualized as black or white.

    We iterate over the whole grid, and for each unit i we examine the triplet
    that consists of unit_i and its nearest neighbours.

    The number of possible microstates for this triplet is 2^N_x

    The value of unit_i in the next generation is a function of this triplet.
    */
 
    arma_rng::set_seed(0); 

    // 1-dimensional cellular automata thing
    int N_x = 10;                   // number of units in the grid

    int N_RULES = pow(2, N_x);      // pow exists in armadillo 
    int RULES[ N_RULES ];

    int T = 1;                   // number of timesteps/generations


    // We can use uvec to slice!
    rowvec pop = randi<rowvec>( N_x , distr_param(0, 9) );  
    uvec indices = {1,2,7};
    rowvec slice = pop.cols(indices);
    
    cout << pop << endl;
    cout << slice << endl;
    //cout << pop.submat(indices) << endl;
    //cout << indices << endl;
    //cout << pop << endl;

    
    

    // Iterating over generations:
    for (int t=0; t<T; t++) {

        // Iterating over the units in the population:
        for (int i=1; i<N_x-1; i++) {
            
            // not sure why, but it gives a warning unless I do this:
            //
            long unsigned a = i-1; long unsigned b = i; long unsigned c = i+1;

            uvec indices = {a, b, c};

            //uvec indices = {0,1,2};
            rowvec triplet = pop.cols(indices);  
            cout << triplet << endl;


        }

    }
    

    //cout << pop << endl;


    cout << "Funker" << endl;
    return 0;
}

