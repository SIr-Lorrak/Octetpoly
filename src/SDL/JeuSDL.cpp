#include "JeuSDL.h"

using namespace std;


//----------------------Image-----------
Image::Image(){

    surface = NULL;
    texture = NULL;

}


void Image::loadFichier(const char* nom_fichier, SDL_Renderer * renderer){
    surface = IMG_Load(nom_fichier);
    if(surface == NULL){
        cout<<"probleme chargement image :"<<nom_fichier<<endl;
        exit(1);
    }

    SDL_Surface * surfaceCorrectPixelFormat = SDL_ConvertSurfaceFormat(surface,SDL_PIXELFORMAT_ARGB8888,0);
    SDL_FreeSurface(surface);
    surface = surfaceCorrectPixelFormat;


     texture = SDL_CreateTextureFromSurface(renderer,surface);
     cout<<SDL_GetError()<<endl;
    
     if(texture == NULL){
        cout<<"probleme creation texture :"<<nom_fichier<<endl;
        exit(1);
     }
}


void Image::dessineTexture(SDL_Renderer * renderer,int x, int y, int w, int h){
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = w;
    r.h = h;
    SDL_RenderCopy(renderer,texture,NULL,&r);
}

SDL_Texture * Image::getTexture(){
    return texture;
}


//--------------------------JeuSDL--------------------------


JeuSDL::JeuSDL(){
     if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << endl;SDL_Quit();exit(1);
    }

    if (TTF_Init() != 0) {
        cout << "Erreur lors de l'initialisation de la SDL_ttf : " << TTF_GetError() << endl;SDL_Quit();exit(1);
    }

    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if( !(IMG_Init(imgFlags) & imgFlags)) {
        cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;SDL_Quit();exit(1);
    }


    window = SDL_CreateWindow("OctetPoly", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 900, 720, SDL_WINDOW_SHOWN );
    if (window == NULL) {
        cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << endl; SDL_Quit(); exit(1);
    }

    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);


    plateau.loadFichier("data/octopoly.png",renderer);
    test.loadFichier("data/screen.png",renderer);

    a = false;


}

JeuSDL::~JeuSDL(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();   
}


void JeuSDL::affichageJeu(){
    SDL_SetRenderDrawColor(renderer, 120, 120, 120, 255);
    SDL_RenderClear(renderer);

    //afficher plateau
    plateau.dessineTexture(renderer,0,0,720,720);

    if(a == true){
       test.dessineTexture(renderer,20,20,200,200);
    }
    else{
        //printf("bonjour\n");
        a = false;
    }

}


void JeuSDL::boucleJeu(){
    SDL_Event events;
    bool quit = false;
    //cout<<1;
    while(!quit){
        while(SDL_PollEvent(&events)) {
            if(events.type == SDL_QUIT){
                quit = true;
            }
            switch (events.key.keysym.scancode) {
                case SDLK_a:
                    a = true;
                    break;
                case SDLK_z:
                    a = false;
                    break;
                case SDL_SCANCODE_ESCAPE:
                    quit = true;
                    break;
                default: break;
            }
        }
        affichageJeu();

        SDL_RenderPresent(renderer);
    }
}