#include <box2d.h>
#include <SDL.h>

#include <SDL_image.h>
#include <SDL_timer.h>

#include<stdio.h>


#define DEG_TO_RAD(X)	((X) * ((float)M_PI / 180.0f))
#define WWIDTH  (860)
#define WHEIGHT  (640)
#define NUM_BOXES 200

b2Body* boxes[NUM_BOXES];
b2Body* playerBody = nullptr;

float pixelsPerMeter = 20.f;
int pixelY, pixelX;
float moveForce = 20.f;
float jumpForce = 200.f;

SDL_Rect dest = { 0, 0, 20, 20 }; // Initialize dest with default values

int main(int argc, char* argv[])
{
    //create gravity
    b2Vec2 gravity(0.f, 9.2f);

    //greate world, with gravity
    b2World world(gravity);

    //define a body
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(WWIDTH / (2 * pixelsPerMeter), (WHEIGHT - 20) / pixelsPerMeter);

    //create a body (static, doesn't collide with other static bodies)
    b2Body* groundBody = world.CreateBody(&groundBodyDef);

    b2PolygonShape groundBox; //half-width, half-height params
    groundBox.SetAsBox(WWIDTH / (2 * pixelsPerMeter), 10.f / pixelsPerMeter);

    groundBody->CreateFixture(&groundBox, 0.f);

    // Define the player's body
    b2BodyDef playerDef;
    playerDef.type = b2_dynamicBody;
    playerDef.position.Set(400.f / pixelsPerMeter, 200.f / pixelsPerMeter);
    playerBody = world.CreateBody(&playerDef);

    // Create a polygon-shape for the player
    b2PolygonShape playerBox;
    playerBox.SetAsBox(1.f, 1.f);

    // Set characteristics for the player
    b2FixtureDef playerFixtureDef;
    playerFixtureDef.shape = &playerBox;
    playerFixtureDef.density = 1.f;
    playerFixtureDef.friction = 0.2f;
    playerFixtureDef.restitution = 0.1f; 
        

    // Create fixture for the player
    playerBody->CreateFixture(&playerFixtureDef);

    //Dynamic Body
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(400.f, 200.f);
    b2Body* body = world.CreateBody(&bodyDef);

    //boxi : 64x64 pix
    //create polygon-shape for box
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.f, 1.f);

    //set characteristics
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.f;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.7f;



    //create fixture
    body->CreateFixture(&fixtureDef);


    //SIMULATING WORLD
    float timestep = 1.0f / 30.f;

    //iteration times for physics / step
    int32 veloIterations = 7;
    int32 posIterations = 2;


    //sdl
    // returns zero on success else non-zero
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }
    SDL_Window* window = SDL_CreateWindow("Wiindow", // creates a window
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WWIDTH, WHEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_Surface* surface;
    surface = IMG_Load("boxi.jpg");

    IMG_Load("player.jpg");
    SDL_Surface* playerSurface = IMG_Load("player.jpg");
    SDL_Texture* playerTexture =
        SDL_CreateTextureFromSurface(renderer, playerSurface);

    // loads image to our graphics hardware memory.
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Texture* gtex = SDL_CreateTextureFromSurface(renderer, surface);
    // clears main-memory
    SDL_FreeSurface(surface);

    SDL_Rect the_box;

    // connects our texture with dest to control position
    SDL_QueryTexture(tex, NULL, NULL, &the_box.w, &the_box.h);


    SDL_Rect ground;
    SDL_QueryTexture(gtex, NULL, NULL, &ground.w, &ground.h);
    // adjust height and width of our image box.
    ground.w = WWIDTH;
    ground.h = 20;

    // Render each box with the texture
    for (int i = 0; i < NUM_BOXES; ++i) {
        // Set the position of each box
        bodyDef.position.Set(10.0f, 10.0f - i * 7.0f);

        // Create a body for each box
        boxes[i] = world.CreateBody(&bodyDef);

        // Create polygon-shape for each box
        b2PolygonShape dynamicBox;
        dynamicBox.SetAsBox(0.8f, 0.8f); // Adjusted size

        // Set characteristics for each box
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &dynamicBox;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.2f;
        fixtureDef.restitution = 0.2f;

        // Create fixture for each box
        boxes[i]->CreateFixture(&fixtureDef);
    }


    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);

    /*SDL_Delay(3000);*/

    int close = 0;

    while (!close)
    {
        // Handle SDL events
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                close = 1;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                playerFixtureDef.friction = 0.2f;
                // Apply forces or impulses to the player based on key presses
                /*switch (event.key.keysym.sym)
                {*/
                if (event.key.keysym.sym == SDLK_LEFT) 
                {
                    printf("Left arrow key pressed\n");
                    playerBody->ApplyForceToCenter(b2Vec2(-moveForce, 0.0f), true);
                }                    
                if (event.key.keysym.sym == SDLK_RIGHT) {
                    printf("Right arrow key pressed\n");
                    playerBody->ApplyForceToCenter(b2Vec2(moveForce, 0.0f), true);
                }
                if (event.key.keysym.sym == SDLK_UP) {
                    printf("Up arrow key pressed\n");
                    playerBody->ApplyForceToCenter(b2Vec2(0.0f, -jumpForce), true);
                }
                if(event.key.keysym.sym == SDLK_DOWN)
                {
                    printf("Down arrow key pressed\n");
                    playerBody->ApplyForceToCenter(b2Vec2(0.0f, moveForce), true);
                }
                
            }

        }

        // Step the Box2D world forward in time
        world.Step(timestep, veloIterations, posIterations);

        // Clear the renderer
        SDL_RenderClear(renderer);

        // Render each box
        for (int i = 0; i < NUM_BOXES; ++i) {
            // Get the position and angle of the current box
            b2Vec2 position = boxes[i]->GetPosition();
            float angle = boxes[i]->GetAngle();

            // Convert Box2D position to SDL position using the scale factor
            int pixelX = static_cast<int>(position.x * pixelsPerMeter);
            int pixelY = static_cast<int>(position.y * pixelsPerMeter);

            // Set the destination rectangle for rendering the texture
            SDL_Rect box_rect;
            box_rect.x = pixelX - 10; // Adjusting the position based on half the width of the texture
            box_rect.y = pixelY - 10; // Adjusting the position based on half the height of the texture
            box_rect.w = 30; // Set the width of the texture
            box_rect.h = 30; // Set the height of the texture

            // Render the texture at the adjusted position and angle
            SDL_RenderCopyEx(renderer, tex, NULL, &box_rect, angle * (180.f / M_PI),
                NULL, SDL_FLIP_NONE);
        }

        // Render the player
        b2Vec2 playerPosition = playerBody->GetPosition();
        /*printf("Player Position: (%.2f, %.2f)\n", playerPosition.x, playerPosition.y);*/

        float playerAngle = playerBody->GetAngle();
        int playerPixelX = static_cast<int>(playerPosition.x * pixelsPerMeter);
        int playerPixelY = static_cast<int>(playerPosition.y * pixelsPerMeter);
        SDL_Rect playerRect = { 
            playerPixelX - 10, 
            playerPixelY - 10,
            30, 30 
        }; // Adjusting the position based on half the size of the player
        SDL_RenderCopyEx(renderer, playerTexture, NULL, &playerRect, playerAngle * (180.f / M_PI), NULL, SDL_FLIP_NONE);


        // Present the renderer
        SDL_RenderPresent(renderer);

        // Calculate to maintain 60 fps
        SDL_Delay(1000 / 60);
    }

    return 0;
}