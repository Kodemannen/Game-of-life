#include <iostream>
//#include <cmath>
#include <armadillo>

//using namespace std;
//using namespace arma;

//#include <iomanip>


// Declaring functions:
void fill_rulemat(arma::cube& rulemat, arma::vec rulevec); 



int main () {

    /*
    We have a one dimensional grid. Each unit in the grid is 0 or 1,
    visualized as black or white.

    We iterate over the whole grid, and for each unit i we examine the triplet
    that consists of unit_i and its nearest neighbours.

    The number of possible microstates for this triplet is 2^N_x

    The value of unit_i in the next generation is a function of this triplet.


                           Ruleset example:

                    Triplet:       Value next generation:

                        000       ->         1         
                        100       ->         0      
                        010       ->         1      
                        110       ->         1       ->   This column is rulevec  
                        001       ->         0             
                        101       ->         0      
                        011       ->         0      
                        111       ->         1      

    */
 
    arma::arma_rng::set_seed(0); 

    // 1-dimensional cellular automata thing
    int const N_x = 10;                         // number of units in the grid
    int const KERNEL_SIZE = 3;                  // the triplet 

    int const N_RULES = pow(2, KERNEL_SIZE);    // pow gets included by armadillo 
    int RULES[ N_RULES ];

    int const T = 100;                   // number of timesteps/generations


    arma::rowvec pop = arma::randi<arma::rowvec>( N_x , arma::distr_param(0, 1) );  

    //arma::vec rulevec = {1, 0, 1, 1, 0, 0, 0, 1};
    arma::vec rulevec = {0, 0, 0, 1, 1, 0, 0, 1};

    arma::cube rulemat(2,2,2);
    fill_rulemat(rulemat, rulevec);
    

    // Iterating over generations:
    for (int t=0; t<T; t++) {

        // Iterating over the units in the population:
        for (int unsigned i=1; i<N_x-1; i++) {
            // getting warning if I don't use unsigned

            // extract current triplet:
            arma::uvec indices = {i-1, i, i+1};
            arma::rowvec triplet = pop.cols(indices);  

            int new_val = rulemat(triplet(0), triplet(1), triplet(2));

            // updating to next generation:
            pop(i) = new_val;

        }

        std::cout << pop << std::endl;

    }
    

    //cout << pop << endl;


    std::cout << "Funker" << std::endl;
    return 0;
}




void fill_rulemat(arma::cube& rulemat, arma::vec rulevec) {

    /*
    Fills up a matrix with elements in rulevec 
    */

    int n_elem = rulemat.n_elem;

    int n_rows = rulemat.n_rows;
    int n_cols = rulemat.n_cols;
    int n_slices = rulemat.n_slices;
    
    int ind=0;
    for (int i=0; i<n_rows; i++) {
        for (int j=0; j<n_cols; j++) {
            for (int k=0; k<n_slices; k++) {

                rulemat(k, j, i) = rulevec(ind);
                ind += 1;

                //std::cout << k << j << i << std::endl;
            }
        }
    }
}
