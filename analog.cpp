//Left and Right arrows controls Right Gear, Up and Down arrows control the Left Gear, Space toggles Framerate.
#include<iostream>
#include<SFML\Graphics.hpp>
#include<math.h>
#include<vector>

using namespace std;

enum DIRECTIONS { ONEUP, ONEDOWN, TWOUP, TWODOWN };

float PI = 3.14159265358979323;

std::vector<sf::CircleShape> create_gear();
float teeth(float radius);

int main() {
    //INPUT setup------------------------------------------------------------------------------------------------------------------------------------------
    bool keys[] = { false, false, false, false };
    int keyDelay = 0;
    //RENDER window setup----------------------------------------------------------------------------------------------------------------------------------
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Rhodonea Gears", sf::Style::Fullscreen);                                                                                //
    int framerate = 144;                                                                                                                                 //
    int frameTick = 0;                                                                                                                                   //
    bool pause = false;                                                                                                                                      //
    window.setFramerateLimit(framerate);                                                                                                                 //
    //OFFSCREEN windows setup------------------------------------------------------------------------------------------------------------------------------
    sf::RenderTexture gearTexture;                                                                                                                       //
    gearTexture.create(800, 800);                                                                                                                        //
    sf::RenderTexture renderDots;                                                                                                                        //
    renderDots.create(1920, 1080);                                                                                                                       //
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
    float centerY = window.getSize().y / 2;                                                                                                              //
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
        sf::Vertex(sf::Vector2f(0, window.getSize().y / 2), sf::Color::Red),                                                                                                //
        sf::Vertex(sf::Vector2f(window.getSize().x, window.getSize().y / 2), sf::Color::Red)                                                                                              //
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
    string ratio;
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
        }
        while (pause == true) {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                pause = false;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
                window.close();
                return 0;
            }
        }
        //KEYBOARD INPUT 
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && keyDelay % 10 == 0) {
            if (g2Multiplier <= 1) {
                g2Multiplier *= 2;
                renderDots.clear(sf::Color(255, 255, 255, 0));
            }
            else {
                g2Multiplier += 1;
                renderDots.clear(sf::Color(255, 255, 255, 0));
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && keyDelay % 10 == 0) {
            if (g2Multiplier <= 1) {
                g2Multiplier /= 2;
                renderDots.clear(sf::Color(255, 255, 255, 0));
            }
            else {
                g2Multiplier -= 1;
                renderDots.clear(sf::Color(255, 255, 255, 0));
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && keyDelay % 10 == 0) {
            if (g1Multiplier <= 1) {
                g1Multiplier *= 2;
                renderDots.clear(sf::Color(255, 255, 255, 0));
            }
            else {
                g1Multiplier += 1;
                renderDots.clear(sf::Color(255, 255, 255, 0));
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && keyDelay % 10 == 0) {
            if (g1Multiplier <= 1) {
                g1Multiplier /= 2;
                renderDots.clear(sf::Color(255, 255, 255, 0));
            }
            else {
                g1Multiplier -= 1;
                renderDots.clear(sf::Color(255, 255, 255, 0));
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && keyDelay % 10 == 0) {
            switch (frameTick % 2) {
            case 0:
                framerate = 144;
                break;
            case 1:
                framerate = 0;
                break;
            }
            frameTick++;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
            pause = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
            window.close();
            return 0;
        }

        //UPDATE section-----------------------------------------------------------------------------------------------------------------------------------
        //SCALE update-------------------------------------------------------------------------------------------------------------------------------------
        g1scale = .125 * g1Multiplier;
        g2scale = .125 * g2Multiplier;
        //GEAR UPDATE--------------------------------------------------------------------------------------------------------------------------------------
        g1radius = 375 * g1scale;
        g2radius = 375 * g2scale;
        centerX = (window.getSize().x / 2) + g1radius;
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
        yAxis[1].position = sf::Vector2f(centerX - g1radius, window.getSize().y);
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
        dot.setPosition(point.x + (555.8), point.y + (137.75));
        renderDots.draw(dot);
        /*renderDots.draw(xAxis, 2, sf::LineStrip);
        renderDots.draw(yAxis, 2, sf::LineStrip);*/
        renderDots.display();
        dots.update(renderDots.getTexture());
        //TEXT UPDATE--------------------------------------------------------------------------------------------------------------------------------------
        ratio = to_string(g1Multiplier) + " : " + to_string(g2Multiplier) + "  --  " + to_string(framerate) + "FPS (Paused: " + to_string(pause) +")";
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
        window.setFramerateLimit(framerate);
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
        subGear.setFillColor(sf::Color(50 + (i * 5.5555555555), 50 + (i * 5.5555555555), 50 + (i * 5.5555555555)));
        gears.push_back(subGear);
    }
    return gears;
}

float teeth(float radius) {
    return ((2 * radius * PI) / 32.7249234749);
}