#include<iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<box2d/box2d.h>

#include "Character.hh"
#include "Background.hh"
#include "Inputs.hh"
#include "Tile.hh"
#include "GameObject.hh"
#include "ContactListener.hh"
#include "Score.hh"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define GAME_NAME "Corona Game"
#define TILES1 "assets/sprites/tiles1.png"
#define TILES2 "assets/sprites/tiles2.png"
#define FONT1 "assets/fonts/8-bit Arcade In.ttf"
#define ICON "assets/GelIcon.png"
#define BG_MUSIC "assets/audio/bgmusic.ogg"
#define SPRITE_SCALE 4.f
#define FPS 120
#define GEL_MOVESPEED 3.0f

int main()
{
    //esto es la ventana de tu grafico
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), GAME_NAME);
    sf::Image* iconTexture{new sf::Image()};
    iconTexture->loadFromFile(ICON);
    window->setIcon(32, 32, iconTexture->getPixelsPtr());
    //aqui vas a guardar los eventos dentro de la ventana, ej: teclado, mouse, etc.
    sf::Event event;

    sf::SoundBuffer* soundBuffer{new sf::SoundBuffer()};
    sf::Sound* sound{new sf::Sound()};
    soundBuffer->loadFromFile(BG_MUSIC);
    sound->setBuffer(*soundBuffer);
    sound->setLoop(true);
    sound->play();

    Score* score{new Score(FONT1, "SCORE ", 24, new sf::Vector2f(25, 5), new sf::Color(255, 255, 255), window)};

    //physics declaration
    b2Vec2* gravity{new b2Vec2(0.f, 0.f)};
    b2World* world{new b2World(*gravity)}; 

    sf::Clock* clock{new sf::Clock()};
    float deltaTime{};

    window->setFramerateLimit(FPS);
    //Game inputs
    Inputs* inputs{new Inputs()};
    //Textures
    sf::Texture* tilesTexture1{new sf::Texture()};
    tilesTexture1->loadFromFile(TILES1);
    sf::Texture* tilesTexture2{new sf::Texture()};
    tilesTexture2->loadFromFile(TILES2);

    const float tileBaseWidth{16 * SPRITE_SCALE};
    const float tileBaseHeight{16 * SPRITE_SCALE};


    //Main player
    Character* character1{new Character(tilesTexture1, 16 * 1, 16 * 5, 16, 16, 
    SPRITE_SCALE, SPRITE_SCALE, new b2Vec2(400, 300), b2BodyType::b2_dynamicBody, world, window)};
    character1->SetAnimations(
        new Animation*[2]
        {
            new Animation(0, 0, 5, character1->GetSprite(), 40.f),
            new Animation(1, 0, 5, character1->GetSprite(), 50.f)
        }
    );
    
    character1->SetTagName("gel");
    //character1->SetDebug(true);

    unsigned int N{10}, M{13};
    Maze* maze1{new Maze(N, M, SPRITE_SCALE, 16, tilesTexture2, "assets/mazes/maze1.txt", world)};
    Maze* maze2{new Maze(N, M, SPRITE_SCALE, 16, tilesTexture2, "assets/mazes/maze2.txt", world)};
    Maze*& currentMaze{*&maze1};

    GameObject* virus{new GameObject(tilesTexture2, 16 * 0, 16 * 0, 16, 16, 
    SPRITE_SCALE, SPRITE_SCALE, new b2Vec2(100, 500), b2BodyType::b2_staticBody, world, window)}; 
    virus->SetTagName("virus");
    GameObject* virus2{new GameObject(tilesTexture2, 16 * 0, 16 * 0, 16, 16, 
    SPRITE_SCALE, SPRITE_SCALE, new b2Vec2(200, 300), b2BodyType::b2_staticBody, world, window)}; 
    virus2->SetTagName("virus");
    GameObject* virus3{new GameObject(tilesTexture2, 16 * 0, 16 * 0, 16, 16,
    SPRITE_SCALE, SPRITE_SCALE, new b2Vec2(500, 500), b2BodyType::b2_staticBody, world, window)}; 
    virus3->SetTagName("virus");
    GameObject* virus4{new GameObject(tilesTexture2, 16 * 0, 16 * 0, 16, 16,
    SPRITE_SCALE, SPRITE_SCALE, new b2Vec2(400, 100), b2BodyType::b2_staticBody, world, window)}; 
    virus4->SetTagName("virus");
    GameObject* virus5{new GameObject(tilesTexture2, 16 * 0, 16 * 0, 16, 16,
    SPRITE_SCALE, SPRITE_SCALE, new b2Vec2(300, 500), b2BodyType::b2_staticBody, world, window)}; 
    virus5->SetTagName("virus");
    GameObject* virus6{new GameObject(tilesTexture2, 16 * 0, 16 * 0, 16, 16,
    SPRITE_SCALE, SPRITE_SCALE, new b2Vec2(200, 100), b2BodyType::b2_staticBody, world, window)}; 
    virus6->SetTagName("virus");
    GameObject* virus7{new GameObject(tilesTexture2, 16 * 0, 16 * 0, 16, 16,
    SPRITE_SCALE, SPRITE_SCALE, new b2Vec2(310, 390), b2BodyType::b2_staticBody, world, window)}; 
    virus7->SetTagName("virus");
    GameObject* virus8{new GameObject(tilesTexture2, 16 * 0, 16 * 0, 16, 16,
    SPRITE_SCALE, SPRITE_SCALE, new b2Vec2(699, 454), b2BodyType::b2_staticBody, world, window)}; 
    virus8->SetTagName("virus");
    GameObject* virus9{new GameObject(tilesTexture2, 16 * 0, 16 * 0, 16, 16,
    SPRITE_SCALE, SPRITE_SCALE, new b2Vec2(668, 123), b2BodyType::b2_staticBody, world, window)}; 
    virus9->SetTagName("virus");
    GameObject* virus10{new GameObject(tilesTexture2, 16 * 0, 16 * 0, 16, 16,
    SPRITE_SCALE, SPRITE_SCALE, new b2Vec2(605, 303), b2BodyType::b2_staticBody, world, window)}; 
    virus10->SetTagName("virus");
    GameObject* virus11{new GameObject(tilesTexture2, 16 * 0, 16 * 0, 16, 16,
    SPRITE_SCALE, SPRITE_SCALE, new b2Vec2(045, 303), b2BodyType::b2_staticBody, world, window)}; 
    virus11->SetTagName("virus");
    GameObject* virus12{new GameObject(tilesTexture2, 16 * 0, 16 * 0, 16, 16,
    SPRITE_SCALE, SPRITE_SCALE, new b2Vec2(065, 103), b2BodyType::b2_staticBody, world, window)}; 
    virus12->SetTagName("virus");

    /*GameObject* stairs{new GameObject(tilesTexture3, 16 * 3, 16 * 6, 16, 16, 
    SPRITE_SCALE, SPRITE_SCALE, new b2Vec2(100, 500), b2BodyType::b2_staticBody, world, window)};
    stairs->SetTagName("stairs");
    //stairs->SetDebug(true);*/

    std::vector<GameObject*>* covid{new std::vector<GameObject*>()};
    covid->push_back(virus);
    covid->push_back(virus2);
    covid->push_back(virus3);
    covid->push_back(virus4);
    covid->push_back(virus5);
    covid->push_back(virus6);
    covid->push_back(virus7);
    covid->push_back(virus8);
    covid->push_back(virus9);
    covid->push_back(virus10);
    covid->push_back(virus11);
    covid->push_back(virus12);
    //items->push_back(stairs);

    ContactListener* conctactListener{new ContactListener(score, covid)};

    world->SetContactListener(conctactListener);

    //esto es el loop principal, mientras la ventana este abierta, esto se va ejecutar.
    while (window->isOpen())
    {
        //mientras se esten ejecutando eventos dentro de la ventana, esto se va repetir eje: teclado, joystick, mouse, etc
        while (window->pollEvent(event))
        {
            //si el evento fue la acción de cerrar la ventana, entonces termina la aplicación.
            if(event.type == sf::Event::Closed)
            {
                window->close();
            }
        }

        /*switch (conctactListener->GetSceneIndex())
        {
            case 0:
                currentMaze = maze1;
                break;
            case 1:
                currentMaze = maze2;
                break;
            default:
                currentMaze = maze1;
                break;
        }*/
        
        Vec2* keyboardAxis{inputs->GetKeyboardAxis()};
        Vec2* joystickAxis{inputs->GetJoystickAxis()};

        if(sf::Joystick::isConnected(0))
        {
            character1->Move(new b2Vec2(joystickAxis->x * deltaTime * GEL_MOVESPEED, joystickAxis->y * deltaTime * GEL_MOVESPEED));
            character1->FlipSpriteX(joystickAxis->x);

            if(std::abs(joystickAxis->x) > 0 || std::abs(joystickAxis->y) > 0)
            {
                //run
                character1->GetAnimation(1)->Play(deltaTime);
            }
            else
            {
                //idle
                character1->GetAnimation(0)->Play(deltaTime);
            }
        }
        else
        {
            character1->Move(new b2Vec2(keyboardAxis->x * deltaTime * GEL_MOVESPEED, keyboardAxis->y * deltaTime * GEL_MOVESPEED));
            character1->FlipSpriteX(keyboardAxis->x);

            if(std::abs(keyboardAxis->x) > 0 || std::abs(keyboardAxis->y) > 0)
            {
                //run
                character1->GetAnimation(1)->Play(deltaTime);
            }
            else
            {
                //idle
                character1->GetAnimation(0)->Play(deltaTime);
            }
        }

        window->clear(*(new sf::Color(0, 0, 0, 0)));//limpiar la pantalla

        for(auto& mazeTile : *currentMaze->GetContainer())
        {
            window->draw(*mazeTile->GetSprite());
        }

        //stairs->Update();
        
        for(auto& covid : *covid)
        {
            covid->Update();
        }

        character1->Update();

        score->Update();

        window->display(); //mostrar en pantalla lo que se va dibujar

        sf::Time timeElapsed = clock->getElapsedTime();
        deltaTime = timeElapsed.asMilliseconds();
        world->ClearForces();
        world->Step(1.f / 100 * deltaTime, 8, 8);
        clock->restart();
        
        //std::cout << "delta time: " << deltaTime << std::endl;

        delete keyboardAxis;
        delete joystickAxis;
    }
    
    return 0;
}