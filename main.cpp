#include <iostream>
#include <fstream>
#include <armadillo>

//#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <SFML/OpenGL.hpp>


// random numbers:
#include <cstdlib>      // srand() from here?
#include <ctime>        // and rand() from here?



sf::Uint8* pixels;
sf::Uint8* armaMatrixToPixels(arma::mat state);

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
    srand( (unsigned)time(NULL)); 
    srand(2);   

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

    sf::Uint8* pixels = new sf::Uint8[W*H*4];
    fillWithRandomBinary(pixels, W, H);

    for (int i=0; i<40; i++) {
        std::cout << pixels[i] << std::endl;
    }


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


    //state = arma::randi<arma::mat>( W, H , arma::distr_param(0, 1) );  










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

        //std::cout << state.n_rows << std::endl;
        
        //state = arma::randi<arma::mat>( W, H , arma::distr_param(0, 1) );  

        //pixels = armaMatrixToPixels(state);
        //pixels = fillWithRandomBinary(pixels, W, H);
        fillWithRandomBinary(pixels, W, H);


        texture.update(pixels);
        window.draw(sprite);

        window.display();

    }

    
    return 0;
}





sf::Uint8* armaMatrixToPixels(arma::mat state){ 

    int const H = state.n_rows;
    int const W = state.n_cols;

    // Make a matrix:
    sf::Uint8* pixels = new sf::Uint8[W*H*4];
    int val;

    int ind=0; 
    for (register int i=0; i<H; i++) {
        for (register int j=0; j<W; j++) {

            val = state(i,j)*255;
            //val = rand() % 255;
            std::cout << val << std::endl;

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


//sf::Uint8* createRandomBinaryMatrix(int const H; int const W){ 
//
//    //int const H = state.n_rows;
//    //int const W = state.n_cols;
//
//    // Make a matrix:
//    sf::Uint8* pixels = new sf::Uint8[W*H*4];
//    int val;
//
//    int ind=0; 
//    for (register int i=0; i<H; i++) {
//        for (register int j=0; j<W; j++) {
//
//            val = state(i,j)*255;
//            //val = rand() % 255;
//
//            // each pixel is represented by a set of four numbers
//            // between 0 and 255
//            pixels[ind]   = val;      // R
//            pixels[ind+1] = val;      // G
//            pixels[ind+2] = val;      // B
//            pixels[ind+3] = val;      // a
//
//            ind += 4;
//        }
//    }
//
//    return pixels;
//}





