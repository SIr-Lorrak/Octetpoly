#include "JeuSDL.h"
#include <assert.h>

using namespace std;

const unsigned int DIMX=1100;
const unsigned int DIMY=720;

const SDL_Color COL_WINDOW = {218, 233, 212};
//different type de bouton l'or de l'appel de affiche bouton


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
    SDL_DestroyTexture(texture);
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

void Image::setSurface(SDL_Surface * surf) {
    SDL_FreeSurface(surface);
    surface = surf;
}



Image::~Image(){
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
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


    window = SDL_CreateWindow("OctetPoly", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DIMX, DIMY, SDL_WINDOW_SHOWN );
    if (window == NULL) {
        cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << endl; SDL_Quit(); exit(1);
    }

    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

    //---> ici rajouter les image a charger.
    plateau.loadFichier("data/images/octopoly.png",renderer);
    ange.loadFichier("data/images/ange.png",renderer);
    demon.loadFichier("data/images/demon.png",renderer);

    button.loadFichier("data/images/button.png",renderer);
    buttonClicked.loadFichier("data/images/buttonClicked.png",renderer);
    red_button.loadFichier("data/images/red_button.png",renderer);
    red_buttonClicked.loadFichier("data/images/red_buttonClicked.png",renderer);
    green_button.loadFichier("data/images/green_button.png",renderer);
    green_buttonClicked.loadFichier("data/images/green_buttonClicked.png",renderer);
    blue_button.loadFichier("data/images/blue_button.png",renderer);
    blue_buttonClicked.loadFichier("data/images/blue_buttonClicked.png",renderer);




    ARRIVEE.loadFichier("data/images/ARRIVEE.png",renderer);
    DEPART.loadFichier("data/images/DEPART.png",renderer);
    H.loadFichier("data/images/H.png",renderer);
    POLICE.loadFichier("data/images/POLICE.png",renderer);
    RH.loadFichier("data/images/RH.png",renderer);
    RV.loadFichier("data/images/RV.png",renderer);
    T1.loadFichier("data/images/T1.png",renderer);
    T2.loadFichier("data/images/T2.png",renderer);
    T3.loadFichier("data/images/T3.png",renderer);
    T4.loadFichier("data/images/T4.png",renderer);
    M.loadFichier("data/images/M.png",renderer);

    Police = TTF_OpenFont("data/DejaVuSansCondensed.ttf",50);
    if (Police == NULL) {
            cout << "Failed to load DejaVuSansCondensed.ttf! SDL_TTF Error: " << TTF_GetError() << endl; SDL_Quit(); exit(1);
    }

    font_color.r = 0;font_color.g = 0;font_color.b = 0;
    m.x=-1;m.y=-1;
}

JeuSDL::~JeuSDL(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit(); 
    TTF_Quit();  
}

void JeuSDL::dessineTexte(const string & texte,int x,int y, unsigned int taille,const SDL_Color couleur){
    texteExemple.setSurface(TTF_RenderText_Solid(Police,texte.c_str(),couleur));
    texteExemple.loadSurface(renderer);
    texteExemple.dessineTexture(renderer,x,y,taille*texte.length(),taille*1.8);
}

void afficheCursor(SDL_Renderer * renderer,const int x,const int y,const int w,const int h,const SDL_Color couleur={0,0,0}){
    //TODO : affiche un rectangle x,y,w,h de couleur couleur par défaut noir
    if(int((float(clock())/float(CLOCKS_PER_SEC))*100)%51<25){
        SDL_SetRenderDrawColor(renderer, couleur.r,couleur.g,couleur.b,255);
        SDL_Rect rectangle = {x,y,w,h};
        SDL_RenderFillRect(renderer,&rectangle);
        SDL_SetRenderDrawColor(renderer, COL_WINDOW.r,COL_WINDOW.g,COL_WINDOW.b,255);
    }
}

void JeuSDL::newButton(const string & effet,const int x,const int y,const int w,const int h,const unsigned int type,const string & c1,const Image * c2,const int margin,const SDL_Color couleur){
    if(c1!="" && c2!=NULL){//si l'utilisateur a demandé d'afficher un bouton contenant a la fois du texte et a la fois une image
        cout<<"erreur : vous ne pouvez pas vous ne pouvez pas mettre du texte ET une image dans un bouton (c'est peut être dure mais il faut choisir)"<<endl;
        assert(false);
    }
    bool clicked = m.x>x&&m.x<x+w  &&   m.y>y&&m.y<y+h;
    if(clicked){
        action=effet;
    }
    switch(type){
        case DEFAULT:
            if(clicked){
                buttonClicked.dessineTexture(renderer,x,y,w,h);
            }
            else{
                button.dessineTexture(renderer,x,y,w,h);
            }
            break;

        case RED:
            if(clicked){
                red_buttonClicked.dessineTexture(renderer,x,y,w,h);
            }
            else{
                red_button.dessineTexture(renderer,x,y,w,h);
            }
            break;

        case GREEN:
            if(clicked){
                green_buttonClicked.dessineTexture(renderer,x,y,w,h);
            }
            else   {
                green_button.dessineTexture(renderer,x,y,w,h);
            }
            break;

        case BLUE:
            if(clicked){
                blue_buttonClicked.dessineTexture(renderer,x,y,w,h);
            }
            else{
                blue_button.dessineTexture(renderer,x,y,w,h);
            }
            break;

        case INVISIBLE:
            break;//on n'affiche rien puisqu'il est invisible
        default:
            cout<<"erreur : type de bouton invalid"<<endl;
            assert(false);
            break;//je sais que le break sers a rien mais je le met pour la forme
    }

    Image im_contenue;
    if(c1!=""){
        im_contenue.setSurface(TTF_RenderText_Solid(Police,c1.c_str(),couleur));
        im_contenue.loadSurface(renderer);
        im_contenue.dessineTexture(renderer,x+margin,y+margin,w-margin*2,h-margin*2);
    }
    else if(c2!=NULL){
        im_contenue = * c2;
        im_contenue.dessineTexture(renderer,x+margin,y+margin,w-margin*2,h-margin*2);
    }
}

void JeuSDL::affichageClicker(){
    //TODO
}

void JeuSDL::affichageHacking(){
    //TODO
}

void JeuSDL::affichageEscape(){//cette fonction doit être adapté !
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
            
        dessineTexte("Utilsez les touches Z, Q, S et D pour echapez rapidemant a la police",730,50);
    
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

void JeuSDL::affichageMenu(){
    SDL_Color rouge;
    rouge.r = 255;
    rouge.g = 0;
    rouge.b = 0;
    texteExemple.setSurface(TTF_RenderText_Solid(Police,"OctetPoly !",rouge));
    texteExemple.loadSurface(renderer);
    texteExemple.dessineTexture(renderer,(DIMX/2)-250,0,500,100);
    unsigned int n = j.getNbJoueur();
    if(j.getBool("attendreNom")){
        n-=1;
    }
    for(unsigned int i=1;i<=n;i++){
        string nom = "1.";
        nom[0]=int('0')+j.getPion(i)->getRang();
        nom+=j.getPion(i)->getNom();
        if(j.getPion(i)->getNom().length()==0){
            nom+="<anonyme>";
        }
        dessineTexte(nom.c_str(),35+(i-1)*250,200,14);
        string act = "- ";
        act[1]=1;
        newButton(act,35+i*250-30,250,30,30,RED,"X");

    }
    if(j.getBool("attendreNom")){

        dessineTexte("nom :",35+(j.getNbJoueur()-1)*250,200,14);

        string nom = j.getPion(j.getNbJoueur())->getNom();

        if(nom.length()>0){
            dessineTexte(nom.c_str(),40+(j.getNbJoueur()-1)*250,230,14);
        }
        afficheCursor(renderer,50+(j.getNbJoueur()-1)*250+nom.length()*16,230,2,20);
        newButton("\n",120+(j.getNbJoueur()-1)*250+150,230,30,30,GREEN,"V");
    }
    else if(j.getBool("confirmation")){
        dessineTexte("Commencer avec ces Joueurs ? ",80,DIMY-70,22);
        newButton("\n",DIMX-300,DIMY-100,90,80,GREEN,"oui",NULL,10);
        newButton("n",DIMX-150,DIMY-100,90,80,RED,"non",NULL,10);
    }
    else{
        newButton("+",40+(j.getNbJoueur())*250,200,30,30,BLUE,"+");
        newButton("\n",DIMX-300,DIMY-100,240,80,BLUE,"Commencer !",NULL,10);
    }
}

void JeuSDL::affichageJeu(){
    //TODO
    plateau.dessineTexture(renderer,0,0,DIMY,DIMY);
}

void JeuSDL::affichage(){

    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, COL_WINDOW.r,COL_WINDOW.g,COL_WINDOW.b,255);

    //afficheCursor(renderer,50,50,50,50);

    //exemple de bouton
    //newButton("je ne fais rien!",200,200,200,50,DEFAULT,"je suis un bouton",NULL,10);

    if(j.getNbTour()==0){
        affichageMenu();
    }
    else{

        affichageJeu();

    

        if(j.gete().getn()=="escape"){
           affichageEscape();
        }
        else if(j.gete().getn()=="clicker"){
            affichageClicker();
        }
        else if(j.gete().getn()=="hack"){
            affichageHacking();
        }
    }

    SDL_RenderPresent(renderer);
}

bool JeuSDL::update(SDL_Event & events){

    bool quit = false;
    string input="";
    while(SDL_PollEvent(&events)) {
            switch (events.type) {
                    
                case SDL_QUIT :
                    quit = true;
                    break;


                case SDL_KEYDOWN://certaine touches ne peuvent pas être détectée sous la forme de texte donc on est obligé de les spécifier
                    switch(events.key.keysym.scancode){
                        case SDL_SCANCODE_BACKSPACE:
                            input = "\b";
                            break;
                        case SDL_SCANCODE_ESCAPE:
                            input = "\e";
                            quit = true;
                            break;
                        case SDL_SCANCODE_RETURN:
                            input = "\n";
                        default:
                            break;
                    }
                    if(j.accepteClavier()){//si le jeu accepte les input de type clavier
                        j.actionClavier(input);
                    }
                    break;

                case SDL_TEXTINPUT: //detecter une touche sous forme de texte (comme ça pas besoin de scancode pour toutes les touches qu'on utilise)
                    
                    input = events.text.text;
                    if(j.accepteClavier()){//si le jeu accepte les input de type clavier
                        j.actionClavier(input);
                    }
                    break;


                case SDL_MOUSEBUTTONDOWN:
                
                    if(events.button.button==SDL_BUTTON_LEFT){
                        //enregistré les coordonnées de la souris au clique
                        m.x=events.button.x;
                        m.y=events.button.y;
                    }
                    
                    break;

                case SDL_MOUSEBUTTONUP:
                    if(events.button.button==SDL_BUTTON_LEFT){
                        //lancer l'action donner par un bouton lors du relachement de la souris
                        cout<<m.x<<"-"<<m.y<<endl;
                        cout<<action<<endl;
                        j.action(action);
                        m.x=-1;
                        m.y=-1;
                        action="";//l'action est effectuée elle est donc vidée
                    }

                default: break;
            }
        }
        
        e.deplacePolice(ev.gettempsD());//normalement fonction dans jeu
        e.victoireDefaite();//normalement fonction dans jeu
    return quit;
}

void JeuSDL::run(){
    bool quit = false;

    SDL_Event events;
    SDL_StartTextInput();

    //cout<<1;
    //ev.Declenchement();//normalement fonction dans jeu
    while(!quit){
        
        affichage();
        quit = update(events);

    }
}
