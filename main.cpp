#include <iostream>
#include <fstream>
#include <armadillo>

//#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <SFML/OpenGL.hpp>

// random numbers:
#include <cstdlib>      // srand() from here?
#include <ctime>        // and rand() from here?

sf::Uint8* armaMatrixToPixels(arma::mat state);

arma::mat getNextGen(arma::mat state, arma::mat newState); 
//arma:: mat neighbourhood(3,3);

//sf::Uint8* fillWithRandom(int const N_ROWS, int const N_COLS);

void fillWithRandomBinary(sf::Uint8* pixels, int const N_ROWS, int const N_COLS);


int main () {

    /*
               ____                               __   _ _  __      
              / ___| __ _ _ __ ___   ___    ___  / _| | (_)/ _| ___ 
             | |  _ / _` | '_ ` _ \ / _ \  / _ \| |_  | | | |_ / _ \
             | |_| | (_| | | | | | |  __/ | (_) |  _| | | |  _|  __/
              \____|\__,_|_| |_| |_|\___|  \___/|_|   |_|_|_|  \___|
                                                                
    */
    // rng seed:
    //srand( (unsigned)time(NULL)); 
    //srand(2);   
    // Rng seed:
    //arma::arma_rng::set_seed(2); 
    arma::arma_rng::set_seed_random(); 

    // window size:
    int const WINDOW_WIDTH = 500; 
    int const WINDOW_HEIGHT = 500;
 
    //----------------------------------------
    // Create window instance:
    //----------------------------------------
    sf::RenderWindow window(sf::VideoMode(500, 500), "My window");
    //sf::RenderWindow window;
    // can take a third argument: sf::Style::Fullscreen
    // or sf::Style::Resize, and more.

    glEnable(GL_TEXTURE_2D);
    

    // get the application to run at the same freq as the monitor refresh rate
    //window.setVerticalSyncEnabled(true); 

    // Alternative:
    //window.setFramerateLimit(60);


    //----------------------------------------
    // Set screen position and size:
    //----------------------------------------
    // (x, y), where (0,0) is top right corner
    window.setPosition(sf::Vector2i(0,20)); 
    window.setSize(sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT));



    //----------------------------------------
    // make matrix that we want to visualize:
    //----------------------------------------
    

    // initialize
    //arma::mat state; //= arma::randi<arma::mat>( W, H , arma::distr_param(0, 1) );  
    const unsigned int W = WINDOW_WIDTH;
    const unsigned int H = WINDOW_HEIGHT;
    //const unsigned int W = 30;
    //const unsigned int H = 30;


    //----------------------------------------
    // initialize:
    //----------------------------------------
    // make matrix for the current state:
    // 0s represent dead cells, 1s represent alive ones.
    
    // We let it be +2 larger in each dimension to add padding for periodic boundary 
    //arma::mat state = arma::randi<arma::mat>( W+2, H+2 , arma::distr_param(0, 1) );  
    arma::mat state = arma::zeros<arma::mat>( W+2, H+2 );  
    int d = 100;
    state(arma::span(50,50+d-1), arma::span(50,50+d-1)) = arma::ones<arma::mat>(d,d);


    // Apply periodic boundary conditions:
    arma::mat boundaryLeft = state.col(1);
    arma::mat boundaryRight = state.col(W);
    arma::mat boundaryTop = state.row(1);
    arma::mat boundaryBottom = state.row(H);

    state.col(0) = boundaryRight;
    state.col(W+1) = boundaryLeft;
    state.row(0) = boundaryBottom;
    state.row(H+1) = boundaryTop;


    // make placeholder for the next generation:
    //arma::mat newState = arma::randi<arma::mat>( W+2, H+2 , arma::distr_param(0, 1) );  
    arma::mat newState = state;



    // initialize pixels matrix:
    //sf::Uint8* pixels = new sf::Uint8[W*H*4];
    sf::Uint8* pixels; 
    pixels = armaMatrixToPixels(state);  
    

    //fillWithRandomBinary(pixels, W, H);


    sf::Texture texture;
    texture.create(W,H);

    sf::Sprite sprite(texture);
    texture.update(pixels);


    window.setTitle("Testing");
    
    // get the size of the window
    //sf::Vector2u size = window.getSize();
    //unsigned int width = size.x;
    //unsigned int height = size.y;


    window.setActive(true);
    window.display();





    int count = 0;

    bool running = true;
    while (running) {


        // initialize the event thing:
        sf::Event event;    

        while (window.pollEvent(event)){
            // sf::Event::Closed = 1 when the close button is presset
            
            // Events:
            switch (event.type) {

                case sf::Event::Closed:     // like an if test
                    running = false;
                    window.close();
                    break;

                case sf::Event::KeyPressed:
                    std::cout << "key pressed" << std::endl;

                case sf::Event::TextEntered:
                    std::cout << static_cast<char>(event.text.unicode) << std::endl;

                default:
                    break;
            }

            if (event.type == sf::Event::Closed) // 
                window.close();
        }

        //----------------------------------------
        // Update state matrix here:
        //----------------------------------------
        //state = arma::randi<arma::mat>( W, H , arma::distr_param(0, 1) );  
        newState = getNextGen(state, newState);
        pixels = armaMatrixToPixels(newState);
       
        
        //----------------------------------------
        // update old state
        //----------------------------------------
        state = newState;


        //----------------------------------------
        // Clear and update screen:
        //----------------------------------------
        window.clear(sf::Color::Black);

        texture.update(pixels);
        window.draw(sprite);
        window.display();
    }
    
    return 0;
}


arma::mat getNextGen(arma::mat state, arma::mat newState) {
    
    int const H = state.n_rows-2;
    int const W = state.n_cols-2;

    //arma::mat newState = arma::randi<arma::mat>( W, H , arma::distr_param(0, 1) );  
    //arma::mat newState = arma::diagmat(state);
    //arma:: mat neighbourhood(3,3);

    for (int i=1; i<W+1; i++) {
        for (int j=1; j<H+1; j++) {

            auto current = state(i,j);

            // Check neighbourhood:
            auto neighbourhood = state(arma::span(i-1,i+1), arma::span(j-1,j+1));
            //std::cout << neighbourhood << std::endl;


            // count number of alive neighbours:
            int aliveNeighbours = arma::accu(neighbourhood);


            /* Rules:
            1. Any live cell with to or three live neighbours survives. 
            2. Any dead cell with three live neighbours becomes alive
            3. All other live cells die the next generation, and all
               other dead ones stay dead. 
            */
            


            // Rule 1.  Any live cell with to or three live neighbours survives. 
            if (current==1 && (aliveNeighbours==2 || aliveNeighbours==3)) {
                newState(i,j) = 1;
            }
            // Rule 2. Any dead cell with three live neighbours becomes alive
            else if (current==0 && aliveNeighbours==3){
                newState(i,j) = 1;
            }
            else {
                newState(i,j) = 0;
            }
            

        }

    }

    // Apply periodic boundary conditions: 
    arma::mat boundaryLeft = newState.col(1);
    arma::mat boundaryRight = newState.col(W);
    arma::mat boundaryTop = newState.row(1);
    arma::mat boundaryBottom = newState.row(H);

    newState.col(0) = boundaryRight;
    newState.col(W+1) = boundaryLeft;
    newState.row(0) = boundaryBottom;
    newState.row(H+1) = boundaryTop;


    return newState;
}


int applyRules(arma::mat neighourhood) {

    return 0;
}



sf::Uint8* armaMatrixToPixels(arma::mat state){ 

    int const H = state.n_rows-2;
    int const W = state.n_cols-2;

    // Make a matrix:
    sf::Uint8* pixels = new sf::Uint8[W*H*4];
    int val;

    int ind=0; 
    for (register int i=1; i<H+1; i++) {
        for (register int j=1; j<W+1; j++) {

            val = state(i,j)*255;
            //val = rand() % 255;
            //std::cout << val << std::endl;

            // each pixel is represented by a set of four numbers
            // between 0 and 255
            pixels[ind]   = val;      // R
            pixels[ind+1] = val;      // G
            pixels[ind+2] = val;      // B
            pixels[ind+3] = val;      // a

            ind += 4;
        }
    }

    return pixels;
}


void fillWithRandomBinary(sf::Uint8* pixels, int const N_ROWS, int const N_COLS){ 

    // fills an sf::Uint8* pointer with random binary numbers

    // Make a matrix:
    //sf::Uint8* pixels = new sf::Uint8[W*H*4];
    int val;

    int ind=0; 
    for (register int i=0; i<N_ROWS; i++) {
        for (register int j=0; j<N_COLS; j++) {

            //val = state(i,j)*255;
            val = rand() % 255;

            // each pixel is represented by a set of four numbers
            // between 0 and 255
            pixels[ind]   = val;      // R
            pixels[ind+1] = val;      // G
            pixels[ind+2] = val;      // B
            pixels[ind+3] = val;      // a

            ind += 4;
        }
    }
}


