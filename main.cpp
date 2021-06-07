#include <iostream>
#include <fstream>

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


                        Computation example:

                    Triplet:           Rule vector: 

                      000                   1  
                      001                   1          
                      010                   0
                      011      --->         0
                      100                   1        
                      101                   1            
                      110                   1  
                      111                   1  
       
    */
 
    //arma::arma_rng::set_seed(2); 
    arma::arma_rng::set_seed_random(); 

    // 1-dimensional cellular automata thing
    int const N_x = 41;                         // number of units in the grid
    int const T = 700;   // Number of timesteps/generations after the 0th.
                        // We end up with T+1 in total. 
    int const KERNEL_SIZE = 3;                  // the triplet 

    int const N_RULES = pow(2, KERNEL_SIZE);    // pow gets included by armadillo 
    int RULES[ N_RULES ];



    //----------------------------------------------------------
    // Generate the population, or whatever we want to call it:
    //----------------------------------------------------------
    // Random initial pop:
    //arma::rowvec pop = arma::randi<arma::rowvec>( N_x , arma::distr_param(0, 1) );  
    //pop(0) = 0;             // forcing the initial edges to a set value
    //pop(N_x-1) = 0;         
    
    arma::rowvec pop = arma::ones<arma::rowvec>( N_x );  
    pop(N_x/2) = 0;         // set middle to 0
    
    





    //----------------------------------------------------------
    // Generate rule vector:
    //----------------------------------------------------------
    //random rules:
    //arma::vec rulevec = arma::randi<arma::vec>( N_RULES , arma::distr_param(0, 1) );  
    
    // Generate specific rules:
    arma::vec rulevec = {0,0,0,1,1,1,1,0};    // rule 30
    //arma::vec rulevec = {0,0,1,1,0,1,1,0};      // rule 54


    //----------------------------------------------------------
    // Create a cube that maps the triplet to a binary value,
    // that being the value of node i in the next generation,
    // given the specific triplet.
    //----------------------------------------------------------
    arma::cube rulemat(2,2,2);
    fill_rulemat(rulemat, rulevec);
    

    //----------------------------------------------------------
    // Create a file that stores the rulevector:
    //----------------------------------------------------------
    std::ofstream rulevecfile;
    rulevecfile.open("rulevec.txt");
    rulevecfile << rulevec;
    rulevecfile.close();



    //----------------------------------------------------------
    // Create file for writing the population each generation:
    //----------------------------------------------------------

    std::ofstream popfile;
    popfile.open("pop.txt");

    popfile << pop << std::endl;

    // Iterating over generations:
    for (int t=0; t<T; t++) {

        // Iterating over the units in the population:
        for (int unsigned i=1; i<N_x-1; i++) {
            // getting warning if I don't use unsigned

            int new_val;

            // If not on an edge:
            if (i != 0 && i != N_x-1 ) {
                new_val = rulemat(pop(i-1), pop(i), pop(i+1));
            }

            // Periodic boundary conditions:
            else {
                if (i == 0){
                    new_val = rulemat(pop(N_x-1), pop(i), pop(i+1));
                }
                else if (i == N_x-1) {
                    new_val = rulemat(pop(i-1), pop(i), pop(0));
                }
            }




            // updating to next generation:
            pop(i) = new_val;
        }

        // write current pop to file:
        popfile << pop << std::endl;
    }
    popfile.close();
    

    //cout << pop << endl;


    std::cout << "C++ done" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    return 0;
}



void fill_rulemat(arma::cube& rulemat, arma::vec rulevec) {

    /*
    Fills up a matrix with the elements of the vector rulevec.
    This is used to get the new state for cell_i given the 
    triplet consisting of cell_i and its neighbours.
    */

    int n_rows = rulemat.n_rows;
    int n_cols = rulemat.n_cols;
    int n_slices = rulemat.n_slices;
    
    int ind=0;
    for (int i=0; i<n_rows; i++) {
        for (int j=0; j<n_cols; j++) {
            for (int k=0; k<n_slices; k++) {

                rulemat(i, j, k) = rulevec(ind);
                ind += 1;

                //std::cout << i << j << k << std::endl;
            }
        }
    }
}










