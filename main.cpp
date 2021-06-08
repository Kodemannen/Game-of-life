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
               ____                               __   _ _  __      
              / ___| __ _ _ __ ___   ___    ___  / _| | (_)/ _| ___ 
             | |  _ / _` | '_ ` _ \ / _ \  / _ \| |_  | | | |_ / _ \
             | |_| | (_| | | | | | |  __/ | (_) |  _| | | |  _|  __/
              \____|\__,_|_| |_| |_|\___|  \___/|_|   |_|_|_|  \___|
                                                                
    */
 
    //arma::arma_rng::set_seed(2); 
    arma::arma_rng::set_seed_random(); 

    int const N = 300;    // number of cells per dim
    int const T = 300;    // number of timesteps/generations

    int const KERNEL_SIZE = 3;  // the triplet 

    int const N_RULES = pow(2, KERNEL_SIZE);
    int RULES[ N_RULES ];



    //----------------------------------------------------------
    // Generate the cell population, or whatever we want to call it:
    //----------------------------------------------------------
    // Random initial scene:
    //arma::rowvec scene = arma::randi<arma::rowvec>( N_x , arma::distr_param(0, 1) );  
    
    arma::mat scene = arma::ones<arma::mat>( N, N );  
    scene(N/2, N/2) = 0;         // set middle to 0
    // initial disturbances:
    //scene(3) = 0;         
    //scene(9) = 0;         
    
    
    //----------------------------------------------------------
    // Create placeholder for next generation:
    //----------------------------------------------------------
    arma::mat next_gen = arma::ones<arma::mat>( N, N );  
    next_gen = scene;

    //int n_rows = scene.n_rows;
    //int n_cols = scene.n_cols;




    

    /*
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
    popfile.open("scene.txt");
    popfile << scene << std::endl;

    // Iterating over generations:
    for (int t=0; t<T; t++) {

        // Iterating over the units in the population:
        for (int unsigned i=0; i<N_x; i++) {
            // getting warning if I don't use unsigned


        }

        scene = next_gen;

        // write current scene to file:
        popfile << scene << std::endl;
    }


    popfile.close();
    

    //cout << scene << endl;


    std::cout << "C++ done" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    */
    return 0;
}


void rulefunc(){ 

}











