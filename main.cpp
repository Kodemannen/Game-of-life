#include <iostream>
#include <fstream>
#include <armadillo>

//#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <SFML/OpenGL.hpp>


// random numbers:
#include <cstdlib>      // srand() from here?
#include <ctime>        // and rand() from here?


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
    
    const unsigned int W = 100;
    const unsigned int H = 100;

    // Make a matrix:
    sf::Uint8* pixels = new sf::Uint8[W*H*4];

    // Texture class is needed.
    sf::Texture texture;
    texture.create(W,H);

    sf::Sprite sprite(texture);

    for (register int i=0; i < W*H*4; i += 4) {
        pixels[i]   = rand() % 100;   // r
        pixels[i+1] = rand() % 100;   // g
        pixels[i+2] = rand() % 100;   // b
        pixels[i+3] = rand() % 100;   // a
    }











    window.setTitle("Testing");
    
    // get the size of the window
    //sf::Vector2u size = window.getSize();
    //unsigned int width = size.x;
    //unsigned int height = size.y;


    window.setActive(true);
    window.display();











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

        texture.update(pixels);


        window.draw(sprite);

        window.display();

    }

    
    return 0;
}


void rulefunc(){ 

}











