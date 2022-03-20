//Left and Right arrows controls Right Gear, Up and Down arrows control the Left Gear.
#include<iostream>
#include<SFML\Graphics.hpp>
#include<math.h>
#include<vector>

using namespace std;

enum DIRECTIONS { SUP, SDOWN, KUP, KDOWN };

float PI = 3.14159265358979323;

std::vector<sf::CircleShape> create_gear();
float teeth(float radius);

int main() {
    //INPUT setup------------------------------------------------------------------------------------------------------------------------------------------
    bool keys[] = { false, false, false, false };
    int keyDelay = 0;
    //RENDER window setup----------------------------------------------------------------------------------------------------------------------------------
    sf::RenderWindow window(sf::VideoMode(1900, 1000), "Rhodonea Gears");                                                                                //
    window.setFramerateLimit(144);                                                                                                                       //
    //OFFSCREEN windows setup------------------------------------------------------------------------------------------------------------------------------
    sf::RenderTexture gearTexture;                                                                                                                       //
    gearTexture.create(800, 800);                                                                                                                        //
    sf::RenderTexture renderDots;                                                                                                                        //
    renderDots.create(1900, 1000);                                                                                                                       //
    //GEAR VECTOR setup------------------------------------------------------------------------------------------------------------------------------------
    std::vector<sf::CircleShape> Gears = create_gear();                                                                                                  //
    std::vector<sf::CircleShape>::iterator gIter;                                                                                                        //
    //draw GEARS TO OFFSCREEN window-----------------------------------------------------------------------------------------------------------------------
    for (gIter = Gears.begin(); gIter != Gears.end(); ++gIter) {                                                                                         //
        gearTexture.draw(*gIter);                                                                                                                        //
    }                                                                                                                                                    //
    gearTexture.display();                                                                                                                               //
    //create GEAR TEXTURES---------------------------------------------------------------------------------------------------------------------------------
    sf::Sprite gear1(gearTexture.getTexture());                                                                                                          //
    sf::Sprite gear2(gearTexture.getTexture());                                                                                                          //
    sf::Texture dots(renderDots.getTexture());                                                                                                           //
    sf::Sprite drawing(dots);                                                                                                                            //
    drawing.setScale(.125, .125);                                                                                                                        //
    //GEAR VARIABLES---------------------------------------------------------------------------------------------------------------------------------------
    float multiplyOffset = 0;                                                                                                                            //
    float g1Multiplier = 1;                                                                                                                              //
    float g2Multiplier = 1;                                                                                                                              //
    float g1scale = .125;                                                                                                                                //
    float g2scale = .125;                                                                                                                                //
    float centerX;                                                                                                                                       //
    float centerY = 500;                                                                                                                                 //
    float g2radius;                                                                                                                                      //
    float g1radius;                                                                                                                                      //
    float g1Teeth;                                                                                                                                       //
    float g2Teeth;                                                                                                                                       //
    float rotationSpeedDegrees = (PI / 18);                                                                                                              //
    float rotationSpeedRadians = 0.00304617419787;                                                                                                       //
    //MOVE GEARS to starting postitions--------------------------------------------------------------------------------------------------------------------
    gear1.setOrigin(400, 400);                                                                                                                           //
    gear2.setOrigin(400, 400);                                                                                                                           //
    gear2.rotate(-28 * (PI / 18));                                                                                                                       //
    //create LINES-----------------------------------------------------------------------------------------------------------------------------------------
    sf::Vertex GearToGear[] =                                                                                                                            //
    {                                                                                                                                                    //
        sf::Vertex(sf::Vector2f(0, 0), sf::Color::Blue),                                                                                                 //
        sf::Vertex(sf::Vector2f(0, 0), sf::Color::Blue)                                                                                                  //
    };                                                                                                                                                   //
    sf::Vertex GearToLine[] =                                                                                                                            //
    {                                                                                                                                                    //
        sf::Vertex(sf::Vector2f(0, 0), sf::Color::Blue),                                                                                                 //
        sf::Vertex(sf::Vector2f(0, 0), sf::Color::Blue)                                                                                                  //
    };                                                                                                                                                   //
    sf::Vertex Gear1YAxis[] =                                                                                                                            //
    {                                                                                                                                                    //
        sf::Vertex(sf::Vector2f(0, 0), sf::Color::Blue),                                                                                                 //
        sf::Vertex(sf::Vector2f(0, 0), sf::Color::Blue)                                                                                                  //
    };                                                                                                                                                   //
    sf::Vertex xAxis[] =                                                                                                                                 //
    {                                                                                                                                                    //
        sf::Vertex(sf::Vector2f(0, 500), sf::Color::Red),                                                                                                //
        sf::Vertex(sf::Vector2f(1900, 500), sf::Color::Red)                                                                                              //
                                                                                                                                                         //
    };                                                                                                                                                   //
    sf::Vertex yAxis[] =                                                                                                                                 //
    {                                                                                                                                                    //
        sf::Vertex(sf::Vector2f(0, 0), sf::Color::Green),                                                                                                //
        sf::Vertex(sf::Vector2f(0, 0), sf::Color::Green)                                                                                                 //
    };                                                                                                                                                   //
    //create DOTS------------------------------------------------------------------------------------------------------------------------------------------
    sf::CircleShape dot(5);                                                                                                                              //
    dot.setFillColor(sf::Color::Red);                                                                                                                    //
    //LINE VARIABLES---------------------------------------------------------------------------------------------------------------------------------------
    float lineX = 0;                                                                                                                                     //
    float lineY = 0;                                                                                                                                     //
    float lineAngle = 0;                                                                                                                                 //
    //create TRANSFORMATION--------------------------------------------------------------------------------------------------------------------------------
    sf::Transform transform;                                                                                                                             //
    //create POINT-----------------------------------------------------------------------------------------------------------------------------------------
    sf::Vector2f point;                                                                                                                                  //
    //TEXT setup-------------------------------------------------------------------------------------------------------------------------------------------
    string ratio = to_string(g1Multiplier) + " / " + to_string(g2Multiplier);
    sf::Font font;
    font.loadFromFile("arial.ttf");
    sf::Text text(ratio, font);
    text.setCharacterSize(30);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(sf::Color::Blue);
    //GAME LOOP--------------------------------------------------------------------------------------------------------------------------------------------
    while (window.isOpen())
    {
        // Process events----------------------------------------------------------------------------------------------------------------------------------
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit--------------------------------------------------------------------------------------------------------------------------
            if (event.type == sf::Event::Closed)
                window.close();
            //KEYBOARD INPUT 
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                keys[SUP] = true;
            }
            else keys[SUP] = false;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                keys[SDOWN] = true;
            }
            else keys[SDOWN] = false;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                keys[KUP] = true;
            }
            else keys[KUP] = false;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                keys[KDOWN] = true;
            }
            else keys[KDOWN] = false;
        }

        if (keys[SUP] == true && keyDelay % 10 == 0) {
            if (g2Multiplier <= 1) {
                g2Multiplier *= 2;
                renderDots.clear(sf::Color(255,255,255,0));
            }
            else {
                g2Multiplier += 1;
                renderDots.clear(sf::Color(255,255,255,0));
                }
        }
        else if (keys[SDOWN] == true && keyDelay % 10 == 0) {
            if (g2Multiplier <= 1) {
                g2Multiplier /= 2;
                renderDots.clear(sf::Color(255,255,255,0));
            }
            else {
                g2Multiplier -= 1;
                renderDots.clear(sf::Color(255,255,255,0));
            }
        }
        if (keys[KUP] == true && keyDelay % 10 == 0) {
            if (g1Multiplier <= 1) {
                g1Multiplier *= 2;
                renderDots.clear(sf::Color(255,255,255,0));
            }
            else {
                g1Multiplier += 1;
                renderDots.clear(sf::Color(255,255,255,0));
            }
        }
        else if (keys[KDOWN] == true && keyDelay % 10 == 0) {
            if (g1Multiplier <= 1) {
                g1Multiplier /= 2;
                renderDots.clear(sf::Color(255,255,255,0));
            }
            else {
                g1Multiplier -= 1;
                renderDots.clear(sf::Color(255,255,255,0));
                }
        }

        //UPDATE section-----------------------------------------------------------------------------------------------------------------------------------
        //SCALE update-------------------------------------------------------------------------------------------------------------------------------------
        g1scale = .125 * g1Multiplier;
        g2scale = .125 * g2Multiplier;
        //GEAR UPDATE--------------------------------------------------------------------------------------------------------------------------------------
        g1radius = 375 * g1scale;
        g2radius = 375 * g2scale;
        centerX = 950 + g1radius;
        g1Teeth = teeth(g1radius);
        g2Teeth = teeth(g2radius);
        gear1.rotate(rotationSpeedDegrees/(g1Teeth/g2Teeth));
        gear2.rotate(-rotationSpeedDegrees);
        gear1.setPosition(centerX - g1radius, centerY);
        gear2.setPosition(centerX + g2radius + ((g2radius * 2) / 40), centerY);
        gear1.setScale(g1scale, g1scale);
        gear2.setScale(g2scale, g2scale);
        //LINE UPDATE--------------------------------------------------------------------------------------------------------------------------------------
        lineX = (g1radius - (g1radius * .10)) * cos(lineAngle);
        lineY = (g1radius - (g1radius * .10)) * sin(lineAngle);
        GearToGear[0].position = sf::Vector2f(centerX - g1radius, lineY + centerY);
        GearToGear[1].position = sf::Vector2f(lineX + (centerX + g2radius + ((g2radius * 2) / 40)), lineY + centerY);
        yAxis[0].position = sf::Vector2f(centerX - g1radius, 0);
        yAxis[1].position = sf::Vector2f(centerX - g1radius, 1000);
        GearToLine[0].position = gear2.getPosition();
        GearToLine[1].position = GearToGear[1].position;
        Gear1YAxis[0].position = sf::Vector2f(gear1.getPosition().x, gear1.getPosition().y - g1radius);
        Gear1YAxis[1].position = sf::Vector2f(gear1.getPosition().x, gear1.getPosition().y + g1radius);
        //DOT UPDATE---------------------------------------------------------------------------------------------------------------------------------------
        drawing.setScale(g1scale, g1scale);
        drawing.setOrigin(centerX - g1radius, centerY);
        drawing.setPosition(centerX - g1radius, centerY);
        transform = gear1.getInverseTransform();
        point = transform.transformPoint(GearToGear[0].position);
        dot.setPosition(point.x + (544.5), point.y + (95));
        renderDots.draw(dot);
        /*renderDots.draw(xAxis, 2, sf::LineStrip);
        renderDots.draw(yAxis, 2, sf::LineStrip);*/
        renderDots.display();
        dots.update(renderDots.getTexture());
        //TEXT UPDATE--------------------------------------------------------------------------------------------------------------------------------------
        ratio = to_string(g1Multiplier) + " : " + to_string(g2Multiplier);
        text.setString(ratio);
        //RENDER section-----------------------------------------------------------------------------------------------------------------------------------
        window.clear();
        window.draw(gear2);
        window.draw(gear1);
        window.draw(Gear1YAxis, 2, sf::LineStrip);
        window.draw(GearToLine, 2, sf::LineStrip);
        window.draw(GearToGear, 2, sf::LineStrip);
        window.draw(drawing);
        window.draw(text);
        // Update the window-------------------------------------------------------------------------------------------------------------------------------
        window.display();
        lineAngle += -rotationSpeedRadians;
        drawing.rotate(rotationSpeedDegrees / (g1Teeth / g2Teeth));
        keyDelay++;
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