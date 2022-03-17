#include<iostream>
#include<SFML\Graphics.hpp>
#include<math.h>
#include<vector>

std::vector<sf::CircleShape> create_gear(float radius, float x, float y);

int main() {
    sf::RenderWindow window(sf::VideoMode(1900, 1000), "SFML window");
    window.setFramerateLimit(60);
    sf::RenderTexture offscreen;
    offscreen.create(800, 800);
    std::vector<sf::CircleShape> Gears = create_gear(375, 400, 400);
    std::vector<sf::CircleShape>::iterator gIter;
    for (gIter = Gears.begin(); gIter != Gears.end(); ++gIter) { //for loop to draw each platform object
        offscreen.draw(*gIter);
    }
    offscreen.display();
    sf::Sprite gear1(offscreen.getTexture());
    sf::Sprite gear2(offscreen.getTexture());
    gear1.scale(.5, .5);
    gear1.setOrigin(400, 400);
    gear1.move(500, 500);
    gear2.scale(.5, .5);
    gear2.setOrigin(400, 400);
    gear2.move(880, 500);
    gear2.rotate(-30 * (3.14159265358979323 / 18));
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
        window.clear();
        gear1.rotate((3.14159265358979323 / 18));
        gear2.rotate(-(3.14159265358979323 / 18));
        window.draw(gear2);
        window.draw(gear1);
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