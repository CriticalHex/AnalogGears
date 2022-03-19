#include<iostream>
#include<SFML\Graphics.hpp>
#include<math.h>
#include<vector>

using namespace std;

float PI = 3.14159265358979323;

std::vector<sf::CircleShape> create_gear();
float teeth(float radius);

int main() {
    //RENDER window setup----------------------------------------------------------------------------------------------------------------------------------
    sf::RenderWindow window(sf::VideoMode(1900, 1000), "SFML window");
    window.setFramerateLimit(144);
    //OFFSCREEN windows setup------------------------------------------------------------------------------------------------------------------------------
    sf::RenderTexture offscreen;
    offscreen.create(800, 800);
    sf::RenderTexture renderDots;
    renderDots.create(1900, 1000);
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
    sf::Texture dots(renderDots.getTexture());
    sf::Sprite drawing(dots);
    //GEAR VARIABLES---------------------------------------------------------------------------------------------------------------------------------------
    float gearX = 950;
    float gearY = 500;
    float scale = .5;
    float radius = 375 * scale;
    float g1radius = 375 * .5;
    float g2Teeth = teeth(radius);
    float rotationSpeedDegrees = (PI / 18);
    float rotationSpeedRadians = 0.00304617419787;
    //MOVE GEARS to starting postitions--------------------------------------------------------------------------------------------------------------------
    gear1.setScale(scale, scale);
    gear1.setOrigin(400, 400);
    gear2.setOrigin(400, 400);
    gear1.setPosition(gearX - g1radius, gearY);
    gear2.rotate(-28 * (PI / 18));
    //create LINES-----------------------------------------------------------------------------------------------------------------------------------------
    sf::Vertex gear2gear[] =
    {
        sf::Vertex(sf::Vector2f(750, 500), sf::Color::Blue),
        sf::Vertex(sf::Vector2f(1150, 500), sf::Color::Blue)
    };
    //create DOTS------------------------------------------------------------------------------------------------------------------------------------------
    sf::CircleShape dot(5);
    //DOTS variables---------------------------------------------------------------------------------------------------------------------------------------
    float dotX;
    float dotY;
    float k;
    float t = 3625 * -rotationSpeedRadians;
    float n = 1;
    float d;
    //DOTS setup-------------------------------------------------------------------------------------------------------------------------------------------
    drawing.setOrigin(gearX - radius, gearY);
    drawing.setPosition(gearX - radius, gearY);
    //LINE VARIABLES---------------------------------------------------------------------------------------------------------------------------------------
    float lineX = 0;
    float lineY = 0;
    float lineAngle = -rotationSpeedDegrees;
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
        scale = .5  / 3;
        radius = 375 * scale;
        g2Teeth = teeth(radius);
        gear1.rotate(rotationSpeedDegrees/(36/g2Teeth));
        gear2.rotate(-rotationSpeedDegrees);
        gear2.setPosition(gearX + radius + ((radius * 2) / 40), gearY);
        gear2.setScale(scale, scale);
        //LINE UPDATE--------------------------------------------------------------------------------------------------------------------------------------
        //add point rotation for gear 2, use its Y value to draw dots on gear 1.
        lineX = (150) * cos(lineAngle);
        lineY = (150) * sin(lineAngle);
        gear2gear[0].position = sf::Vector2f(gearX - g1radius, lineY + 500);
        gear2gear[1].position = sf::Vector2f(lineX + (gearX + radius + ((radius * 2) / 40)), lineY + 500);
        //DOT UPDATE---------------------------------------------------------------------------------------------------------------------------------------
        //TODO: Start drawing dots in the center, make line and dots draw at the same speed.
        d = scale * 2;
        k = n / d;
        dotX = (150) * cos(k * t) * cos(t);
        dotY = (150) * cos(k * t) * sin(t);
        dot.setPosition(dotX + (gearX - g1radius), dotY + 500);
        renderDots.draw(dot);
        renderDots.display();
        dots.update(renderDots.getTexture());
        //RENDER section-----------------------------------------------------------------------------------------------------------------------------------
        window.clear();
        window.draw(gear2);
        window.draw(gear1);
        window.draw(gear2gear, 2, sf::LinesStrip);
        window.draw(drawing);
        // Update the window-------------------------------------------------------------------------------------------------------------------------------
        window.display();
        lineAngle += -rotationSpeedRadians;
        t += -(rotationSpeedRadians / 2.99);
        drawing.rotate(rotationSpeedDegrees / (36 / g2Teeth));
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

float teeth(float radius) {
    return ((2 * radius * PI) / 32.7249234749);
}