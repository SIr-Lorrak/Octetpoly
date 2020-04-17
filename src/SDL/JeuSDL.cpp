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
     //cout<<SDL_GetError()<<endl;
    
     if(texture == NULL){
        cout<<"probleme creation texture :"<<nom_fichier<<endl;
        exit(1);
     }
}

void Image::loadSurface (SDL_Renderer * renderer) {
    texture = SDL_CreateTextureFromSurface(renderer,surface);
    if (texture == NULL) {
        cout << "Error: problem to create the texture from surface " << endl;
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

void Image::setSurface(SDL_Surface * surf) {surface = surf;}


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


    window = SDL_CreateWindow("OctetPoly", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1100, 720, SDL_WINDOW_SHOWN );
    if (window == NULL) {
        cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << endl; SDL_Quit(); exit(1);
    }

    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);


    plateau.loadFichier("data/octopoly.png",renderer);

    ARRIVEE.loadFichier("data/ARRIVEE.png",renderer);
    DEPART.loadFichier("data/DEPART.png",renderer);
    H.loadFichier("data/H.png",renderer);
    POLICE.loadFichier("data/POLICE.png",renderer);
    RH.loadFichier("data/RH.png",renderer);
    RV.loadFichier("data/RV.png",renderer);
    T1.loadFichier("data/T1.png",renderer);
    T2.loadFichier("data/T2.png",renderer);
    T3.loadFichier("data/T3.png",renderer);
    T4.loadFichier("data/T4.png",renderer);
    M.loadFichier("data/M.png",renderer);

    Police = TTF_OpenFont("data/DejaVuSansCondensed.ttf",50);
    if (Police == NULL) {
            cout << "Failed to load DejaVuSansCondensed.ttf! SDL_TTF Error: " << TTF_GetError() << endl; SDL_Quit(); exit(1);
    }

    font_color.r = 0;font_color.g = 0;font_color.b = 0;


}

JeuSDL::~JeuSDL(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit(); 
    TTF_Quit();  
}


void JeuSDL::affichageJeu(){

    SDL_SetRenderDrawColor(renderer, 218, 233, 212, 255);
    SDL_RenderClear(renderer);

    //afficher plateau
    plateau.dessineTexture(renderer,0,0,720,720);

    

    

   if(ev.getn()=="escape"){
       affichageEscape();
    }
}


void JeuSDL::affichageEscape(){
    int ix = 112;
    int iy = 110;
    if(e.getFin()==false){
            
        for(int y=0;y<11;y++){
            for(int x=0;x<11;x++){
            
                
                    
                if(tab_escape[y][x]=="M"){
                       M.dessineTexture(renderer,ix,iy,45,45);

                       ix+=45;
                }
                else if(tab_escape[y][x]=="H"){
                    H.dessineTexture(renderer,ix,iy,45,45);
                    ix+=45;
                }
                else if(tab_escape[y][x]=="RV"){
                    RV.dessineTexture(renderer,ix,iy,45,45);
                    ix+=45;
                }
                else if(tab_escape[y][x]=="RH"){
                    RH.dessineTexture(renderer,ix,iy,45,45);
                    ix+=45;
                }
                else if(tab_escape[y][x]=="DEPART"){
                    DEPART.dessineTexture(renderer,ix,iy,45,45);
                    ix+=45;
                }
                else if(tab_escape[y][x]=="ARRIVE"){
                    ARRIVEE.dessineTexture(renderer,ix,iy,45,45);
                    ix+=45;
                }
                else if(tab_escape[y][x]=="T1"){
                    T1.dessineTexture(renderer,ix,iy,45,45);
                    ix+=45;
                }
                else if(tab_escape[y][x]=="T2"){
                    T2.dessineTexture(renderer,ix,iy,45,45);
                    ix+=45;
                }
                else if(tab_escape[y][x]=="T3"){
                    T3.dessineTexture(renderer,ix,iy,45,45);
                    ix+=45;
                }
                else if(tab_escape[y][x]=="T4"){
                    T4.dessineTexture(renderer,ix,iy,45,45);
                    ix+=45;
                }
                if((e.getJoueur().y == y)&&(e.getJoueur().x == x)){
                    POLICE.dessineTexture(renderer,ix-45,iy,45,45);
                }
                else if((e.getPolice().y == y)&&(e.getPolice().x == x)){
                        POLICE.dessineTexture(renderer,ix-45,iy,45,45);
                }


                if(x==10){
                    ix=112;
                    iy+=45;
                }

                
            }
        }
            
        texteExemple.setSurface(TTF_RenderText_Solid(Police,"Utilsez les touches Z, Q, S et D pour echapez rapidemant a la police",font_color));
        texteExemple.loadSurface(renderer);
        texteExemple.dessineTexture(renderer,730,50,370,30);
    
        texteExemple.setSurface(TTF_RenderText_Solid(Police,"Attention de ne pas quitter la route, sinon vous reculez!",font_color));
        texteExemple.loadSurface(renderer);
        texteExemple.dessineTexture(renderer,730,90,370,30);
    }
    if(e.getFin()==true) {
        if(e.getEchec()==true){
            texteExemple.setSurface(TTF_RenderText_Solid(Police,"Vous n'avez pas reussit a vous echaper!",font_color));
            texteExemple.loadSurface(renderer);
            texteExemple.dessineTexture(renderer,730,50,370,30);

            texteExemple.setSurface(TTF_RenderText_Solid(Police,"direction la prison!",font_color));
            texteExemple.loadSurface(renderer);
            texteExemple.dessineTexture(renderer,730,90,370,30);
        }
        else{
            texteExemple.setSurface(TTF_RenderText_Solid(Police,"Vous avez reussit a vous echaper",font_color));
            texteExemple.loadSurface(renderer);
            texteExemple.dessineTexture(renderer,730,50,370,30);
        }
            
    }

}


void JeuSDL::boucleJeu(){
    SDL_Event events;
    bool quit = false;
    //cout<<1;
    ev.Declenchement();//normalement fonction dans jeu
    while(!quit){
        while(SDL_PollEvent(&events)) {
            if(events.type == SDL_QUIT){
                quit = true;
            }
            switch (events.type) {
                
                case SDL_SCANCODE_ESCAPE:
                    quit = true;
                    break;

                case SDL_KEYDOWN: //detecter une touche: par exemple pour les mini jeu passer events.key.keysym.sym dans l'appel de la fonction
                    
                    if(ev.getn()=="escape"){//normalement appel action clavier ou un truc du genre avec la touche
                        if(events.key.keysym.sym==122){
                            e.avancerJoueur("z");
                        }
                        if(events.key.keysym.sym==113){
                            e.avancerJoueur("q");
                        }
                        if(events.key.keysym.sym==115){
                            e.avancerJoueur("s");
                        }
                        if(events.key.keysym.sym==100){
                            e.avancerJoueur("d");
                        }
                    }
                    break;
                    
                case SDL_MOUSEBUTTONDOWN:
                
                    if(events.button.button==SDL_BUTTON_LEFT){
                        //ici pour la souris, il suffit delettre des if avec les coordonéé
                        if((events.button.y>0) && (events.button.x>0) && (events.button.y<200) && (events.button.y<200) ){
                            
                        }
                    }
                    
                    break;
                default: break;
            }
            
        }
        
        e.deplacePolice(ev.gettempsD());//normalement fonction dans jeu
        e.victoireDefaite();//normalement fonction dans jeu
        affichageJeu();

        SDL_RenderPresent(renderer);
    }
}

