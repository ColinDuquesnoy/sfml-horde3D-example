// *************************************************************************************************
//
// Horde3D
//   Next-Generation Graphics Engine
//
// Sample Application
// --------------------------------------
// Copyright (C) 2006-2011 Nicolas Schulz
//
//
// This sample source file is not covered by the EPL as the rest of the SDK
// and may be used without any restrictions. However, the EPL's disclaimer of
// warranty and liability shall be in effect for this file.
//
// *************************************************************************************************
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "app.h"

// Configuration
const int appWidth = 1024;
const int appHeight = 576;
static bool fullScreen = false;
static int benchmarkLength = 600;
bool setupWindow( int&, int&, bool, const char* title );
static bool running;
static int mx0, my0;
static Application *app;
sf::RenderWindow* pSfmlWindow;
sf::Clock renderClock;
double timeAtLastFrame;
sf::Time timeSinceLastFrame;
sf::Time timeAtCurrentFrame;


int windowCloseListener()
{
    running = false;
    return 0;
}


void keyPressListener( int key )
{
    if( !running ) return;
    int width = appWidth, height = appHeight;
    switch (key)
    {
    case sf::Keyboard::Escape:
        running = false;
        break;

    case sf::Keyboard::F1:
        app->release();
        // Toggle fullscreen mode
        fullScreen = !fullScreen;
        setupWindow(width, height, fullScreen, app->getTitle());
        app->init();
        app->resize( width, height );
        break;

    //KLUDGE ALERT:
    //The samples in trunk use GLFW keycodes to set keystates
    //within Application. In order not to modify the sample code
    //we play nice and set the GLFW keycoded array it is interested in
    case sf::Keyboard::Space:
        app->setKeyState(32,true);
        break;

    case sf::Keyboard::F3:
        app->setKeyState(260,true);
        break;
    case sf::Keyboard::F6:
        app->setKeyState(263,true);
        break;

    case sf::Keyboard::F7:
        app->setKeyState(264,true);
        break;

    case sf::Keyboard::F8:
        app->setKeyState(265,true);
        break;

    case sf::Keyboard::LShift:
        app->setKeyState(287,true);
        break;

    case sf::Keyboard::W:
        app->setKeyState(int('W'),true);
        break;

    case sf::Keyboard::A:
        app->setKeyState(int('A'),true);
        break;

    case sf::Keyboard::S:
        app->setKeyState(int('S'),true);
        break;

    case sf::Keyboard::D:
        app->setKeyState(int('D'),true);
        break;
    }
}

void mouseMoveListener( int x, int y )
{

    if( !running )
    {
        mx0 = x; my0 = y;
        return;
    }

    app->mouseMoveEvent( (float)(x - mx0), (float)(my0 - y) );
    mx0 = x; my0 = y;
}

bool setupWindow( int& width, int& height, bool fullscreen, const char* windowTitle = NULL)
{
    //Initialise OpenGL context using SFML
    sf::ContextSettings settings;    // Create a settings object to initialise OpenGL context with
    settings.depthBits = 24;         // Request a 24 bits depth buffer
    settings.stencilBits = 8;        // Request a 8 bits stencil buffer
    settings.antialiasingLevel = 2;  // Request 2 levels of antialiasing
    if(!windowTitle)
        windowTitle = "SFML Chicago sample";
    if (pSfmlWindow==NULL)  //First time creation
    {
        pSfmlWindow = new sf::RenderWindow(sf::VideoMode(width, height, 32),  //Create a width * height framebuffer with 32 bits per pixel
                                     windowTitle,                                           //Title for the window to be created
                                     sf::Style::Close,                                      //Create a window with a titlebar and close button
                                     settings);                                                     //Settings object to initialise the OpenGL context with
    }
    else
    //Reinitialisation of window
    {
        //Initialise a new window
        if(fullscreen)
        {
            // Creating a fullscreen window with the best video mode supported
            pSfmlWindow->create(sf::VideoMode::getDesktopMode(),
                                windowTitle,
                                sf::Style::Fullscreen,
                                settings);
            width = pSfmlWindow->getSize().x;
            height = pSfmlWindow->getSize().y;
        }
        else
        {
            pSfmlWindow->create(sf::VideoMode(width, height, 32),
                                windowTitle,
                                sf::Style::Close,
                                settings);
        }
    }
    return true;
}


int main( int argc, char** argv )
{
    printf("Starting SFML Chicago!\n");

    // Initialize application and engine
    app = new Application( std::string(argv[0]));

    // Fonts must be loaded before creating the sf::RenderWindow and
    // initializing Horde3D to avoid crashes with old nvidia gpu
    // on windows xp (GeForce 9400 GT) .
    sf::Font font;
    font.loadFromFile("Content/fonts/arial.ttf");

    // Initialize a SFML window
    pSfmlWindow = NULL;
    int width = appWidth, height = appHeight;
    if( !setupWindow( width, height, fullScreen, app->getTitle() ) ) return -1;

    // SFML text used to draw benchmark informations
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(30);
    text.setColor(sf::Color::Magenta);
    text.setString("FPS: ");
    text.setPosition(10, 10);

    // SFML logo
    sf::Texture tex;
    tex.loadFromFile("Content/textures/logo.png");
    sf::Sprite sfmlLogo;
    sfmlLogo.setTexture(tex);
    sfmlLogo.setPosition(100, 100);

    // Check if benchmark mode is requested
    bool benchmark = false;
    if( argc > 1 && strcmp( argv[1], "-bm" ) == 0 )
    {
        benchmark = true;
    }

    if ( !app->init() )
    {
        std::cout << "Unable to initalize engine" << std::endl;
        std::cout << "Make sure you have an OpenGL 2.0 compatible graphics card";
        return -1;
    }
    app->resize( appWidth, appHeight );
    pSfmlWindow->setMouseCursorVisible(false);

    int frames = 0;
    float fps = 30.0f;
    timeSinceLastFrame = renderClock.restart();
    timeAtCurrentFrame += timeSinceLastFrame;
    running = true;
    // Game loop
    while( running )
    {
        timeSinceLastFrame = renderClock.restart();
        timeAtCurrentFrame += timeSinceLastFrame;

        // Calc FPS
        ++frames;
        if( !benchmark && frames >= 3 )
        {
            fps = frames / timeSinceLastFrame.asSeconds();
            if( fps < 5 ) fps = 30;  // Handle breakpoints
            frames = 0;
            char str[256];
            sprintf( str, "FPS: %.2f", fps );
            text.setString(str);
        }

        //Initialise all app keys' states to false
        for( int i = 0; i < 320; ++i )
            app->setKeyState(i,false);

        // Inject inputs from SFML
        sf::Event evt;
        while (pSfmlWindow->pollEvent(evt))
        {
            // Window closed
            if (evt.type == sf::Event::Closed)
                running = false;
            // Key Press Event
            else if (evt.type == sf::Event::KeyPressed)
            {
                keyPressListener(evt.key.code);
            }
            else if(evt.type == sf::Event::MouseMoved)
            {
                mouseMoveListener(evt.mouseMove.x,evt.mouseMove.y);
            }
        }
        app->keyStateHandler();

        // Render 3D scene + Horde3D overlay
        app->mainLoop( benchmark ? 60 : fps );

        // Prepare for SFML rendering
        pSfmlWindow->resetGLStates();

        pSfmlWindow->draw(text);
        pSfmlWindow->draw(sfmlLogo);

        pSfmlWindow->display();

        if( benchmark && frames == benchmarkLength ) break;
    }

    pSfmlWindow->setMouseCursorVisible(true);

    // Quit
    app->release();
    delete app;

    if(pSfmlWindow->isOpen())
        pSfmlWindow->close();

    delete pSfmlWindow;

    return 0;

}

