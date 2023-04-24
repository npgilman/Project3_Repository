#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>

#include "windowUtils.cpp"

using namespace std;

/// @brief Driving function for program
/// @param  None
/// @return Code representing finishing status of program
int main(void)
{   
    int height = 1080, width = 1920;
    string title = "Food Finder";

    sf::RenderWindow window(sf::VideoMode(width, height), title, sf::Style::Close);
    WindowUtils wutils = WindowUtils(window);

    // Window main loop
    while (window.isOpen())
    {
        // Render graphics
        wutils.drawBackground(window);

        sf::Event event;
        while (window.pollEvent(event))
        {
            // Expand on this to accept user clicks
            if (event.type == sf::Event::MouseButtonPressed)
            {
                wutils.handleClick(window, event);
            }
            // Expand on this to take user input
            if (event.type == sf::Event::TextEntered)
            {
                wutils.handleText(window, event);          
            }
            // Close program
            if (event.type == sf::Event::Closed) {window.close();}
        }
        window.display();
    }
    return 0;
}
