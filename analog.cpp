#include<iostream>
#include<SFML\Graphics.hpp>
#include<math.h>
#include<vector>

using namespace std;
float PI = 3.14159265358979323;

std::vector<sf::CircleShape> create_gear();
float rpm(float rpm);
float teeth(float radius);
int main() {
    //RENDER window setup----------------------------------------------------------------------------------------------------------------------------------
    sf::RenderWindow window(sf::VideoMode(1900, 1000), "SFML window");
    window.setFramerateLimit(144);
    //OFFSCREEN windows setup------------------------------------------------------------------------------------------------------------------------------
    sf::RenderTexture offscreen;
    offscreen.create(800, 800);
    //GEAR VECTOR setup------------------------------------------------------------------------------------------------------------------------------------
    std::vector<sf::CircleShape> Gears = create_gear();
    std::vector<sf::CircleShape>::iterator gIter;
    //draw GEARS TO OFFSCREEN window-----------------------------------------------------------------------------------------------------------------------
    for (gIter = Gears.begin(); gIter != Gears.end(); ++gIter) {
        offscreen.draw(*gIter);
    }
    offscreen.display();
    //create GEAR TEXTURES---------------------------------------------------------------------------------------------------------------------------------
    sf::Sprite gear1(offscreen.getTexture());
    sf::Sprite gear2(offscreen.getTexture());
    //create LINES-----------------------------------------------------------------------------------------------------------------------------------------
    sf::Vertex gear2gear[] =
    {
        sf::Vertex(sf::Vector2f(0, 0), sf::Color::Blue),
        sf::Vertex(sf::Vector2f(0, 0), sf::Color::Blue)
    };
    //LINE VARIABLES---------------------------------------------------------------------------------------------------------------------------------------
    float lineX = 0;
    float lineY = 0;
    float lineAngle0 = 0;
    float lineAngle1 = 0;
    //GEAR VARIABLES---------------------------------------------------------------------------------------------------------------------------------------
    float gearX = 950;
    float gearY = 500;
    float scale = .5;
    float radius = 375 * scale;
    float g2Teeth = teeth(radius);
    float rotationSpeed = (PI / 18);
    //MOVE GEARS to starting postitions--------------------------------------------------------------------------------------------------------------------
    gear1.setScale(scale, scale);
    gear1.setOrigin(400, 400);
    gear2.setOrigin(400, 400);
    gear1.move(gearX - radius, gearY);
    gear2.rotate(-28 * (PI / 18));
    while (window.isOpen())
    {
        // Process events----------------------------------------------------------------------------------------------------------------------------------
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit--------------------------------------------------------------------------------------------------------------------------
            if (event.type == sf::Event::Closed)
                window.close();
        }
        //UPDATE section-----------------------------------------------------------------------------------------------------------------------------------
        //GEAR UPDATE--------------------------------------------------------------------------------------------------------------------------------------
        scale += .001;
        radius = 375 * scale;
        g2Teeth = teeth(radius);
        gear1.rotate(rotationSpeed/(36/g2Teeth));
        gear2.rotate(-rotationSpeed);
        gear2.setPosition(gearX + radius + ((radius * 2) / 40), gearY);
        gear2.setScale(scale, scale);
        //LINE UPDATE--------------------------------------------------------------------------------------------------------------------------------------

        gear2gear[0].position = sf::Vector2f(10, 0);
        gear2gear[1].position = sf::Vector2f(10, 0);
        //DOT UPDATE---------------------------------------------------------------------------------------------------------------------------------------
        //RENDER section-----------------------------------------------------------------------------------------------------------------------------------
        window.clear();
        window.draw(gear2);
        window.draw(gear1);
        window.draw(gear2gear, 2, sf::LinesStrip);
        // Update the window-------------------------------------------------------------------------------------------------------------------------------
        window.display();
    }

}

std::vector<sf::CircleShape> create_gear() {
    std::vector<sf::CircleShape> gears;
    sf::CircleShape mainGear(375);
    mainGear.setPosition(25, 25);
    mainGear.setFillColor(sf::Color(100,100,100));
    gears.push_back(mainGear);
    for (float i = 0; i < (36 * (PI / 18)); i += (PI / 18)) {
        sf::CircleShape subGear(375 / 20);
        float xpos = 375 * cos(i) + (400 - (375 * .05));
        float ypos = 375 * sin(i) + (400 - (375 * .05));
        subGear.setPosition(xpos, ypos);
        subGear.setFillColor(sf::Color(200, 200, 200));
        gears.push_back(subGear);
    }
    return gears;
}

float rpm(float rpm) {
    return 1;
}

float teeth(float radius) {
    return ((2 * radius * PI) / 32.7249234749);
}