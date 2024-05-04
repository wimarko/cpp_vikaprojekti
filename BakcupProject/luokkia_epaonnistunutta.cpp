//#include <box2d.h>
//#include <SDL.h>
//
//#include <SDL_image.h>
//#include <SDL_timer.h>
//
//#include<stdio.h>
//
//class Game {
//public:
//    Game();
//    ~Game();
//
//    void Run();
//
//
//#define WWIDTH  (860)
//#define WHEIGHT  (640)
//    float pixelsPerMeter = 20.f;
//
//private:
//    void InitializeSDL();
//    void InitializePhysWorld();
//    void Cleanup();
//
//
//
//    SDL_Window* window;
//    SDL_Renderer* renderer;
//
//    b2World* physWorld;
//};
//
//Game::Game() {
//    InitializeSDL();
//    InitializePhysWorld();
//}
//
//Game::~Game()
//{
//    Cleanup();
//}
//
//void InitializeSDL()
//{
//    //sdl
//    // returns zero on success else non-zero
//    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
//        printf("error initializing SDL: %s\n", SDL_GetError());
//    }
//    SDL_Window* window = SDL_CreateWindow("Wiindow", // creates a window
//        SDL_WINDOWPOS_CENTERED,
//        SDL_WINDOWPOS_CENTERED,
//        WWIDTH, WHEIGHT, SDL_WINDOW_SHOWN);
//    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
//
//    SDL_Surface* surface;
//    surface = IMG_Load("boxi.jpg");
//
//    IMG_Load("player.jpg");
//    SDL_Surface* playerSurface = IMG_Load("player.jpg");
//    SDL_Texture* playerTexture =
//        SDL_CreateTextureFromSurface(renderer, playerSurface);
//
//    // loads image to our graphics hardware memory.
//    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surface);
//    SDL_Texture* gtex = SDL_CreateTextureFromSurface(renderer, surface);
//    // clears main-memory
//    SDL_FreeSurface(surface);
//
//    SDL_Rect the_box;
//
//    // connects our texture with dest to control position
//    SDL_QueryTexture(tex, NULL, NULL, &the_box.w, &the_box.h);
//
//
//    SDL_Rect ground;
//    SDL_QueryTexture(gtex, NULL, NULL, &ground.w, &ground.h);
//    // adjust height and width of our image box.
//    ground.w = WWIDTH;
//    ground.h = 20;
//}
//
//void Game::InitializePhysWorld()
//{
//    b2Vec2 gravity(0.0f, 9.81f); // Adjust the gravity as needed
//    b2World world(gravity);
//
//    b2BodyDef groundBodyDef;
//
//    groundBodyDef.position.Set(WWIDTH / (2 * pixelsPerMeter), (WHEIGHT - 20) / pixelsPerMeter);
//
//    //create a body (static, doesn't collide with other static bodies)
//    b2Body* groundBody = world.CreateBody(&groundBodyDef);
//
//    b2PolygonShape groundBox; //half-width, half-height params
//    groundBox.SetAsBox(WWIDTH / (2 * pixelsPerMeter), 10.f / pixelsPerMeter);
//
//    groundBody->CreateFixture(&groundBox, 0.f);
//
//}
//
//void Game::Cleanup()
//{
//
//}
//
//
//int main(int argc, char* argv[])
//{
//    Game game;
//    game.Run();
//
//    return 0;
//}