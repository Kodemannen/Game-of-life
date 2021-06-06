#include <iostream>
//#include <cmath>
#include <armadillo>

using namespace std;
using namespace arma;

//#include <iomanip>


// Declaring functions:
void fill_rulemat(cube& rulemat, vec rulevec); 



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
    int const N_x = 10;                     // number of units in the grid
    int const KERNEL_SIZE = 3;              // the triplet 

    int const N_RULES = pow(2, KERNEL_SIZE);      // pow exists in armadillo 
    int RULES[ N_RULES ];

    int const T = 1;                   // number of timesteps/generations


    // We can use uvec to slice!
    rowvec pop = randi<rowvec>( N_x , distr_param(0, 9) );  

    uvec indices = {1,2,7};
    rowvec slice = pop.cols(indices);
    
    cout << pop << endl;
    cout << slice << endl;
    //cout << pop.submat(indices) << endl;
    //cout << indices << endl;
    //cout << pop << endl;

    
    vec rulevec = linspace(0, N_RULES, N_RULES+1);
    //mat rulemat = rules.reshape(2,2, 2)//
    // not sure how to do this
    
    cube rulemat(2,2,2);


    fill_rulemat(rulemat, rulevec);
    
    //cout << rules << endl;
    cout << rulemat << endl;

    cout << "NASDAW" << endl;
    exit(3);


    
    // Iterating over generations:
    for (int t=0; t<T; t++) {

        // Iterating over the units in the population:
        for (int unsigned i=1; i<N_x-1; i++) {
            // getting warning if I don't use unsigned

            // extract current triplet:
            uvec indices = {i-1, i, i+1};
            rowvec triplet = pop.cols(indices);  

            cout << triplet << endl;


        }

    }
    

    //cout << pop << endl;


    cout << "Funker" << endl;
    return 0;
}




void fill_rulemat(cube& rulemat, vec rulevec) {
    /*
    Fills up a matrix with elements in rulevec 
    */

    //rulemat.zeros();

    int n_elem = rulemat.n_elem;

    int n_rows = rulemat.n_rows;
    int n_cols = rulemat.n_cols;
    int n_slices = rulemat.n_slices;
    
    int ind=0;
    for (double i=0; i<n_rows; i++) {
        for (double j=0; j<n_cols; j++) {
            for (double k=0; k<n_slices; k++) {

                rulemat(k, j, i) = rulevec(ind);
                ind += 1;
            }
        }
    }
}
