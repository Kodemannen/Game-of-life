#include <iostream>
#include <fstream>

#include <stdio.h> // for printf


#include <armadillo>

//#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <SFML/OpenGL.hpp>

// random numbers:
#include <cstdlib>      // srand() from here?
#include <ctime>        // and rand() from here?

// for delay:
#include <unistd.h>



// size of state/environment:
const int enlargementFactor = 1;
const unsigned int H = 1080 / enlargementFactor;
const unsigned int W = 1920 / enlargementFactor;

sf::Uint8 * pixels = new sf::Uint8[W*H*4];

sf::Uint8* armaMatrixToPixels(arma::mat state);
arma::mat getNextGen(arma::mat state, arma::mat newState); 
arma::mat enlargeMatrix(arma::mat matr, int k); 

arma::mat createGlider();
arma::mat createRPentominus();
arma::mat createExploder();


int main () {

    /*
               ____                               __   _ _  __      
              / ___| __ _ _ __ ___   ___    ___  / _| | (_)/ _| ___ 
             | |  _ / _` | '_ ` _ \ / _ \  / _ \| |_  | | | |_ / _ \
             | |_| | (_| | | | | | |  __/ | (_) |  _| | | |  _|  __/
              \____|\__,_|_| |_| |_|\___|  \___/|_|   |_|_|_|  \___|
                                                                

            1. Any live cell with to or three live neighbours survives. 
            2. Any dead cell with three live neighbours becomes alive
            3. All other live cells die the next generation, and all
               other dead ones stay dead. 
    */

    // rng seed:
    //srand( (unsigned)time(NULL)); 
    //srand(2);   
    // Rng seed:
    //arma::arma_rng::set_seed(2); 
    arma::arma_rng::set_seed_random(); 

    srand( (unsigned)time(NULL)); 

    // zooming factor:0
    
    int const WINDOW_HEIGHT = H*enlargementFactor;
    int const WINDOW_WIDTH = W*enlargementFactor; 
 
    //----------------------------------------
    // Create window instance:
    //----------------------------------------
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "My window");

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
    //window.setPosition(sf::Vector2i(0,20)); 
    //window.setSize(sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT));



    //----------------------------------------
    // initialize state matrix:
    //----------------------------------------

    // make matrix for the current state:
    // 0s represent dead cells, 1s represent alive ones.
    
    // We let it be +2 larger in each dimension to add padding for periodic boundary 
    arma::mat state = arma::randi<arma::mat>( H, W , arma::distr_param(0, 1) );  
    //state = state*0;
    //arma::mat state = arma::zeros<arma::mat>( H, W );  


    //----------------------------------------
    // Zooming:
    //----------------------------------------
    // Set the view to a rectangle located at (100,100) with size 400x200
    /* sf::View view; */
    /* view.reset(sf::FloatRect(10, 10, 40, 40)); // (locV, locH, height width */
    /* // Set its target viewport to be half of the window */
    /* //view.setViewport(sf::FloatRect(0.f, 0.f, 0.5f, 1.f)); */
    /* // Apply it */
    /* window.setView(view); */


    //----------------------------------------
    // Add a glider or some other object:
    //----------------------------------------
    arma::mat glider = createGlider();
    arma::mat rPentominus = createRPentominus();
    arma::mat exploder = createExploder(); 
    int loc[2];




    for (int i=0; i<10; i++)
    { 
        loc[0] = rand() % 50;
        loc[1] = rand() % 50;
        state(arma::span(loc[0],loc[0]+2), arma::span(loc[1],loc[1]+2)) = rPentominus;
    }




    //----------------------------------------
    // Add line:
    //----------------------------------------
    /* arma::mat c2 = arma::ones<arma::mat>(1,W); */
    /* state(H/2, arma::span(0,W-1)) = c2; */


    //// zero out some part:
    //int d = H/3; 
    //int locV=0; 
    //int locH=0;
    ////state(arma::span(locV,locV+d-1), 
    ////      arma::span(locH,locH+d-1)) = arma::randi<arma::mat>(d,d, arma::distr_param(0, 1));
    //state(arma::span(locV,locV+d-1), 
    //      arma::span(locH,locH+d-1)) = arma::ones(d,d);


    // Apply periodic boundary conditions:
    arma::mat boundaryLeft = state.col(1);
    arma::mat boundaryRight = state.col(W-2);
    arma::mat boundaryTop = state.row(1);
    arma::mat boundaryBottom = state.row(H-2);

    state.col(0) = boundaryRight;
    state.col(W-1) = boundaryLeft;
    state.row(0) = boundaryBottom;
    state.row(H-1) = boundaryTop;


    // make placeholder for the next generation:
    //arma::mat newState = arma::randi<arma::mat>( W+2, H+2 , arma::distr_param(0, 1) );  
    arma::mat newState = state;



    // initialize pixels matrix:
    //sf::Uint8* pixels = new sf::Uint8[W*H*4];

    arma::mat enlarged = enlargeMatrix(state, enlargementFactor);
    sf::Uint8* pixels; 
    pixels = armaMatrixToPixels(enlarged);  
    

    //fillWithRandomBinary(pixels, W, H);


    sf::Texture texture;
    texture.create(W*enlargementFactor,H*enlargementFactor);

    sf::Sprite sprite(texture);
    texture.update(pixels);


    window.setTitle("Testing");
    
    // get the size of the window
    //sf::Vector2u size = window.getSize();
    //unsigned int width = size.x;
    //unsigned int height = size.y;


    // for delay:
    unsigned int delay = 0.04*1e6; // ms


    window.setActive(true);
    texture.update(pixels);
    window.draw(sprite);
    window.display();



    // add some delay after each display:
    usleep(delay);

    int count = 0;
    //----------------------------------------
    // Save initial to image:
    //----------------------------------------
    bool save_img_files = false;
    
    if (save_img_files) 
    {
        auto filename = "images/test" + std::to_string(count) + ".jpg";
        texture.copyToImage().saveToFile(filename); 
    }


    // initialize the event thing:
    sf::Event event;    

    bool running = true;
    while (running) {


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
        newState = getNextGen(state, newState);

        if (enlargementFactor > 1)
        {
            enlarged = enlargeMatrix(newState, enlargementFactor);
            pixels = armaMatrixToPixels(enlarged);
        }
        else
        {
            pixels = armaMatrixToPixels(newState);
        }

       
        
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


        count += 1;
        //std::cout << count << std::endl;

        //----------------------------------------
        // Save render to image:
        //----------------------------------------
        if (save_img_files)
        {
            auto filename = "images/test" + std::to_string(count) + ".jpg";
            texture.copyToImage().saveToFile(filename); 
        }

        // add some delay:
        usleep(delay);


        //if (count >= 2000) { 
        //    return 0;
        //}

    }


    return 0;
}


arma::mat getNextGen(arma::mat state, arma::mat newState) {
    
    int const H = state.n_rows;
    int const W = state.n_cols;

    //arma::mat newState = arma::randi<arma::mat>( W, H , arma::distr_param(0, 1) );  
    //arma::mat newState = arma::diagmat(state);
    //arma:: mat neighbourhood(3,3);

    for (int i=1; i<H-1; i++) {
        for (int j=1; j<W-1; j++) {

            auto current = state(i,j);

            // Check neighbourhood:
            auto neighbourhood = state(arma::span(i-1,i+1), arma::span(j-1,j+1));

            // count number of alive neighbours:
            int aliveNeighbours = arma::accu(neighbourhood);


            // This is to not include the current cell 
            // when counting neighbours: 
            if (current==1) {
                aliveNeighbours -= 1;
            }



            // Rule 1.  Any live cell with to or three live neighbours survives. 
            if (current==1 && (aliveNeighbours==2 || aliveNeighbours==3)) {
                newState(i,j) = 1;
            }

            // Rule 2. Any dead cell with three live neighbours becomes alive
            //else if (current==0 && (aliveNeighbours==3 || aliveNeighbours==8)){
            else if (current==0 && (aliveNeighbours==3 )){
                newState(i,j) = 1;
            }

            // Rule 3. All other live cells die the next generation, and all
            // other dead ones stay dead. 
            else {
                newState(i,j) = 0;
            }
        }
    }


    // Apply periodic boundary conditions: 
    arma::mat boundaryLeft = newState.col(1);
    arma::mat boundaryRight = newState.col(W-2);
    arma::mat boundaryTop = newState.row(1);
    arma::mat boundaryBottom = newState.row(H-2);

    newState.col(0) = boundaryRight;
    newState.col(W-1) = boundaryLeft;
    newState.row(0) = boundaryBottom;
    newState.row(H-1) = boundaryTop;


    return newState;
}


int applyRules(arma::mat neighourhood) {

    return 0;
}



sf::Uint8* armaMatrixToPixels(arma::mat state){ 

    int const H = state.n_rows;
    int const W = state.n_cols;

    // Make a matrix:
    // sf::Uint8* pixels = new sf::Uint8[W*H*4];
    int val;

    int ind=0; 
    for (int i=0; i<H; i++) {
        for (int j=0; j<W; j++) {

            val = state(i,j)*200;

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






arma::mat enlargeMatrix(arma::mat matr, int k) {
    /*
    Function that maps each pixel in matr to a k \times k submatrix in a new matrix, 
    i.e. makes every pixel into a larger square.
    */
    
    int const H = matr.n_rows;    // height
    int const W = matr.n_cols;    // width

    // initialize new matrix:
    arma::mat enlarged(H*k, W*k); 

    // markers for where we insert values into the new matrix:
    int rowMarker=0;       //  
    int colMarker=0;

    // base for the submatrix we will insert into the new:
    auto base = arma::ones(k,k);

    for (int i=0; i<H; i++) {
        for (int j=0; j<W; j++) {

            auto val = matr(i,j); 

            // insert values:
            enlarged(arma::span(rowMarker,rowMarker+k-1), 
                     arma::span(colMarker,colMarker+k-1)) = base*val;

            colMarker += k;
            colMarker = colMarker % (k*W);

        }
        rowMarker += k;
        rowMarker = rowMarker % (k*H);
    }

    return enlarged;

}



arma::mat createGlider() {
    arma::mat glider = {{0,0,1}, 
                        {1,0,1},
                        {0,1,1}};
    return glider;
}

arma::mat createRPentominus() {
    arma::mat rPentominus = {{0,1,1}, 
                             {1,1,0},
                             {0,1,0}};
    return rPentominus;
}

arma::mat createExploder() {
    arma::mat exploder = {{1,0,1}, 
                          {1,0,1},
                          {1,1,1}};
    return exploder;
}


