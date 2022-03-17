#include<iostream>
#include<SFML\Graphics.hpp>
#include<math.h>
#include<vector>

std::vector<sf::CircleShape> create_gear(float radius, float x, float y);

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML window");
    
    sf::RenderTexture offscreen;
    offscreen.create(800, 800);
    std::vector<sf::CircleShape> Gears = create_gear(375, 400, 400);
    std::vector<sf::CircleShape>::iterator gIter;
    for (gIter = Gears.begin(); gIter != Gears.end(); ++gIter) { //for loop to draw each platform object
        offscreen.draw(*gIter);
    }
    sf::Texture TEMP;
    TEMP.update(offscreen);
    std::cout << "Test";
    sf::Sprite Gear(TEMP);
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // Clear screen
        window.clear(sf::Color::Black);
        window.draw(Gear);
        offscreen.display();
        // Update the window
        window.display();
    }

}

std::vector<sf::CircleShape> create_gear(float radius, float x, float y) {
    std::vector<sf::CircleShape> gears;
    sf::CircleShape mainGear(radius);
    mainGear.setPosition(x - radius, y - radius);
    mainGear.setFillColor(sf::Color(100,100,100));
    gears.push_back(mainGear);
    for (float i = 0; i < (36 * (3.14159265358979323 / 18)); i += (3.14159265358979323 / 18)) {
        sf::CircleShape subGear(radius / 20);
        float xpos = radius * cos(i) + (x - (radius * .05));
        float ypos = radius * sin(i) + (y - (radius * .05));
        subGear.setPosition(xpos, ypos);
        subGear.setFillColor(sf::Color(200, 200, 200));
        gears.push_back(subGear);
    }
    return gears;
}