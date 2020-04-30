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
    DE.loadFichier("data/images/DE.png",renderer);
    Carte.loadFichier("data/images/CarteChance.png",renderer);

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

    hack.loadFichier("data/images/hack.png",renderer);

    clicker.loadFichier("data/images/clicker.png",renderer);
    pub1.loadFichier("data/images/pub1.png",renderer);
    pub2.loadFichier("data/images/pub2.png",renderer);
    pub3.loadFichier("data/images/pub3.png",renderer);
    pub4.loadFichier("data/images/pub4.png",renderer);
    pub5.loadFichier("data/images/pub5.jpg",renderer);
    pub6.loadFichier("data/images/pub6.png",renderer);
    pub7.loadFichier("data/images/pub7.png",renderer);
    pub8.loadFichier("data/images/pub8.png",renderer);
    pub9.loadFichier("data/images/pub9.png",renderer);
    pub10.loadFichier("data/images/pub10.png",renderer);


    Police = TTF_OpenFont("data/DejaVuSansCondensed.ttf",50);
    if (Police == NULL) {
            cout << "Failed to load DejaVuSansCondensed.ttf! SDL_TTF Error: " << TTF_GetError() << endl; SDL_Quit(); exit(1);
    }

    font_color.r = 0;font_color.g = 0;font_color.b = 0;
    m.x=-1;m.y=-1;
    act = false;

    a = 3;
    clique = true;
}


JeuSDL::~JeuSDL(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit(); 
    TTF_Quit();  
}


void JeuSDL::dessineTexte(const string & texte,int x,int y, unsigned int taille,const SDL_Color couleur){
    inputTexte.setSurface(TTF_RenderUTF8_Solid(Police,texte.c_str(),couleur));
    inputTexte.loadSurface(renderer);
    inputTexte.dessineTexture(renderer,x,y,taille*texte.length(),taille*1.8);
}


void afficheCursor(SDL_Renderer * renderer,const int x,const int y,const int w,const int h,const SDL_Color couleur={0,0,0}){
    //affiche un rectangle clignotant x,y,w,h de couleur couleur par défaut noir
    if(int((float(clock())/float(CLOCKS_PER_SEC))*100)%51<25){
        SDL_SetRenderDrawColor(renderer, couleur.r,couleur.g,couleur.b,255);
        SDL_Rect rectangle = {x,y,w,h};
        SDL_RenderFillRect(renderer,&rectangle);
        SDL_SetRenderDrawColor(renderer, COL_WINDOW.r,COL_WINDOW.g,COL_WINDOW.b,255);
    }
}


void dessineRectangle(SDL_Renderer * renderer,const int x,const int y,const int w,const int h,const SDL_Color couleur={0,0,0}){
    //affiche un rectangle clignotant x,y,w,h de couleur couleur par défaut noir
    SDL_SetRenderDrawColor(renderer, couleur.r,couleur.g,couleur.b,255);
    SDL_Rect rectangle = {x,y,w,h};
    SDL_RenderFillRect(renderer,&rectangle);
    SDL_SetRenderDrawColor(renderer, COL_WINDOW.r,COL_WINDOW.g,COL_WINDOW.b,255);
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
        cout<<SDL_GetError()<<endl;

    }
}


void JeuSDL::affichageClicker(){
    clicker.dessineTexture(renderer,112,110,495,495);
    string texte;
    if (j.getc().getFin()==false){
        texte = "Timer : ";
        texte+=to_string(10-((clock()/CLOCKS_PER_SEC)-(j.gete().gettempsD()/CLOCKS_PER_SEC)));
        texte+=" seconde";
        dessineTexte(texte,122,110,12);
        texte ="Appuyez à répétion sur la pub ";
        dessineTexte(texte,135,135,12);
        texte ="pour faire de la pub!";
        dessineTexte(texte,135,155,12);
        texte ="nombre de pub réalisé : ";
        texte+=to_string(j.getc().getnbclique());
        dessineTexte(texte,135,180,12);

        switch(a){
                case 1:
                pub1.dessineTexture(renderer,200,230,300,300);
                break;

                case 2:
                pub2.dessineTexture(renderer,200,230,300,300);
                break;

                case 3:
                pub3.dessineTexture(renderer,200,230,300,300);
                break;

                case 4:
                pub4.dessineTexture(renderer,200,230,300,300);
                break;

                case 5:
                pub5.dessineTexture(renderer,200,230,300,300);
                break;

                case 6:
                pub6.dessineTexture(renderer,200,230,300,300);
                break;

                case 7:
                pub7.dessineTexture(renderer,200,230,300,300);
                break;

                case 8:
                pub8.dessineTexture(renderer,200,230,300,300);
                break;

                case 9:
                pub9.dessineTexture(renderer,200,230,300,300);
                break;

                case 10:
                pub10.dessineTexture(renderer,200,230,300,300);
                break;
            }

        newButton(" ",400,550,120,30,BLUE,"pubber");
        if( action ==" "&& clique){
            int temp = a;
            srand (time(NULL));
            while(a == temp){
                a = (rand()%10)+1;
            }
            clique = false;
        }
        else if (action ==""&& !clique){
            clique = true;
        }

        
    }   
    else{
        texte = "TERMINER! Vous avez réalisé ";
        texte+=to_string(j.getc().getnbclique());
        dessineTexte(texte,135,135,12);
        texte ="Vous gagner ";
        texte+=to_string(j.gete().getgain());
        texte+="$";
        dessineTexte(texte,135,155,12);
        newButton("\n",300,500,120,30,BLUE,"Continuer");
    }
}


void JeuSDL::affichageHacking(){
    hack.dessineTexture(renderer,35,44,612,660);
    string texte;
    texte ="progression : [";

    unsigned int cas = j.geth().getIntAff();//affichage de la fin
    for(unsigned int i=0;i<j.geth().getnbMot();i++){
        if(i<j.geth().getnbSaisie()){
            texte+="#";
        }
        else{
            texte+=" ";
        }
    }
    texte+="]";
    dessineTexte(texte,110,150,10,{48,253,0});
    if(j.geth().getFin())
    {
        if(j.gete().getT() == true){
            texte="Vous avez GAGNE en ";
            texte+=to_string(j.gete().gettps());
            texte+=" seconde";
            dessineTexte(texte,110,190,10,{48,253,0});
            dessineTexte("les hackers n'ont pas eu le temps de vous voler",110,210,10,{48,253,0});
            dessineTexte("[press enter]",110,290,10,{48,253,0});

        }

        else{
            texte ="Vous avez PERDU en ";
            texte+=to_string(j.gete().gettps());
            texte+=" seconde";
            dessineTexte(texte,110,190,10,{48,253,0});
            texte ="On vous a volé ";
            texte+=to_string(j.gete().getgain()*-1);
            texte+="$ !";
            dessineTexte(texte,110,210,10,{48,253,0});
            dessineTexte("[press enter]",110,290,10,{48,253,0});
            
        }

    }
    else{
        texte = "timer : ";
        texte+=to_string(((clock()/CLOCKS_PER_SEC)-(j.gete().gettempsD())/CLOCKS_PER_SEC));
            dessineTexte(texte,110,170,10,{48,253,0});
        switch(cas){
            case 2 : // premier affiche, quand le hack commence
                dessineTexte("Vous devez tapez la commande suivante pour gagne : ",110,210,10,{48,253,0});
                break;

            case 0: // affiche quand le mot tapé précédement est correcte
                dessineTexte("commande valide!",110,210,10,{48,253,0});
                dessineTexte("Commande suivante : ",110,230,10,{48,253,0});
                break;

            case 1: // affichage quand le mot tapé précédement est incorrecte
                dessineTexte("commande non valide!",110,210,10,{48,253,0});
                dessineTexte("re-tapez la commande : ",110,230,10,{48,253,0});
                break;

            case 3: // enleve l'affichage précédent avant l'affichage suivant
                j.seth(1);
                break;

            case 4: // enleve l'affichage précédent avant l'affichage de la fin
                j.seth(2);
                break;
        }
        texte = ">>";
        texte+=j.geth().getMot();
        texte+= "<<";
        dessineTexte(texte,110,260,10,{48,253,0});
        texte =">";
        texte+=j.geth().getMotSaisie();
        dessineTexte(texte,110,290,10,{48,253,0});
        afficheCursor(renderer,110+(texte.length()*10),290,2,20,{48,253,0});
    }
}


void JeuSDL::affichageEscape(){//cette fonction doit être adapté !
    int ix = 112;
    int iy = 110;
    if(j.getes().getFin()==false){
            
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
                if((j.getes().getJoueur().y == y)&&(j.getes().getJoueur().x == x)){
                    POLICE.dessineTexture(renderer,ix-45,iy,45,45);
                }
                else if((j.getes().getPolice().y == y)&&(j.getes().getPolice().x == x)){
                        POLICE.dessineTexture(renderer,ix-45,iy,45,45);
                }


                if(x==10){
                    ix=112;
                    iy+=45;
                }

                
            }
        }
            
        dessineTexte("Utilsez les touches Z, Q, S et D ",122,110,12);
        dessineTexte("pour echaper rapidemant a la police",122,130,12);

        dessineTexte("Attention de ne pas quitter la route, ",122,565,12);
        
    }
    if(j.getes().getFin()==true) {
        int ix = 112;
        int iy = 110;
        for(int y=0;y<11;y++){
            for(int x=0;x<11;x++){
                if(tab_escape[y][x]=="M"){
                       M.dessineTexture(renderer,ix,iy,45,45);

                       ix+=45;
                }
                 else {
                    H.dessineTexture(renderer,ix,iy,45,45);
                    ix+=45;
                }
                if(x==10){
                    ix=112;
                    iy+=45;
                }
            }
        }

        if(j.getes().getEchec()==true){

            dessineTexte("Vous n'avez pas reussit ",172,245,11);
            dessineTexte("a vous echaper!",172,265,11);
            dessineTexte("Direction la prison!",172,300,11);
            newButton("\n",300,500,120,30,BLUE,"Continuer");
        }
        else{
            dessineTexte("Vous avez reussit a vous echaper",172,245,11);
            newButton("\n",300,500,120,30,BLUE,"Continuer");

        }
            
    }

}


void JeuSDL::affichageMenu(){
    SDL_Color rouge;
    rouge.r = 255;
    rouge.g = 0;
    rouge.b = 0;
    inputTexte.setSurface(TTF_RenderText_Solid(Police,"OctetPoly !",rouge));
    inputTexte.loadSurface(renderer);
    inputTexte.dessineTexture(renderer,(DIMX/2)-250,0,500,100);
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


void JeuSDL::affichageDees(){
        DE.dessineTexture(renderer,130,160,60,60);
        DE.dessineTexture(renderer,220,160,60,60);
        int x =130;
        int y = 160;
        int val = j.getPion(j.getJoueurCourant())->getDes().D1;

        for(int i =0;i<2;i++){
            switch(val){
                case 1:
                    dessineTexte("o",x+23,y+19,12);
                    break;
                case 2:
                    dessineTexte("o",x+10,y+5,12);
                    dessineTexte("o",x+39,y+34,12);
                    break;
                case 3:
                    dessineTexte("o",x+10,y+5,12);
                    dessineTexte("o",x+23,y+19,12);
                    dessineTexte("o",x+39,y+34,12);
                    break;
                case 4:
                    dessineTexte("o",x+10,y+5,12);
                    dessineTexte("o",x+10,y+34,12);
                    dessineTexte("o",x+39,y+34,12);
                    dessineTexte("o",x+39,y+5,12);
                    break;
                case 5:
                    dessineTexte("o",x+10,y+5,12);
                    dessineTexte("o",x+23,y+19,12);
                    dessineTexte("o",x+39,y+34,12);
                    dessineTexte("o",x+39,y+5,12);
                    dessineTexte("o",x+10,y+34,12);
                    break;
                case 6:
                    dessineTexte("o",x+10,y+5,12);
                    dessineTexte("o",x+10,y+19,12);
                    dessineTexte("o",x+39,y+19,12);
                    dessineTexte("o",x+39,y+34,12);
                    dessineTexte("o",x+39,y+5,12);
                    dessineTexte("o",x+10,y+34,12);
                    break;
            }
            val = j.getPion(j.getJoueurCourant())->getDes().D2;
            x = 220;

        }
     
}


void JeuSDL::affichageInteraction(){
    Pion * p = j.getPion(j.getJoueurCourant());
    Case * c = j.board.getCase(p->getPos());
    string texte;
    switch(c->getType()){
        case 'E':
            texte = "Vous etes sur l'entrprise ";
            texte +=c->getNom();
            dessineTexte(texte,125,120,12);
            break;

        case 'B':
            texte = "Vous etes sur la banque ";
            texte +=c->getNom();
            dessineTexte(texte,125,120,12);
            break;

        case 'D':
            texte = "Vous etes sur la case Depart ";
            dessineTexte(texte,125,120,12);
            break;

        case 'P':
            texte = "Bienvenue en Prison ";
            if(p->getNom()==""){
                texte+= "<anonyme>";
            }
            else{
                if(p->getNom()==""){
                    texte+="<anonyme>";
                }
                else{
                    texte+=p->getNom();
                }
            }
            texte+=" !";
            dessineTexte(texte,125,120,12);
            if(j.getBool("avance")){
                newButton("\n",300,560,120,30,BLUE,"Continuer");
            }
            
            if(!j.getBool("desLance")){
                texte = "Faire un double";
                newButton("1",125,565,120,30,BLUE,texte);
                texte = "Payer ";
                texte+= to_string(j.getPrixAPayer());
                texte+="$";
                newButton("2",300,565,120,30,BLUE,texte);
            }
            if(j.getBool("desLance")){
                affichageDees();
                newButton("\n",300,560,120,30,BLUE,"Continuer");
            }
            break;
        case 'I':
            texte = "Il faut payer ses impots monsieur !"; 
            dessineTexte(texte,125,120,12);
            texte = "Payer ";
            texte+=to_string(j.getPrixAPayer());
            texte+="$";
            newButton("\n",300,565,120,30,BLUE,texte);
            break;
        case 'C':
            if(j.getCarte()==NULL){
                string texte = "Piochez une carte chance !";
                dessineTexte(texte,125,520,12);
                newButton("\n",300,560,120,30,BLUE,"Piocher");
            }
            else{
                Carte.dessineTexture(renderer,150,210,400,240);
                dessineTexte(j.getCarte()->getTitre(),150+(400-(j.getCarte()->getTitre().length()*10))/2,230,10,{255,0,0});
                dessineTexte(j.getCarte()->getTexte(),150+(400-(j.getCarte()->getTexte().length()*8))/2,330,8,{255,0,0});
                newButton("\n",300,565,120,30,BLUE,"Continuer");
            }
            break;
        case 'A':
            texte = "vous pouvez organiser une campagne de PUB! Faire de la pub ?";
            dessineTexte(texte,125,560,12);

            if (p->getNbPropriete() > 0 && p->getCoin() > j.board.getCase(j.board.getIndice("Campagne de pub"))->getPrix())
            {
                //cout<<"Souhaitez-vous faire de la pub ? (o/n)"<<endl;
            }
            break;
        case 'O':
            texte = "Journée porte ouverte! Vous pouvez aller où vous voulez. Acheter un ticket?";
            dessineTexte(texte,125,560,12);
            if (j.board.nbCaseFree() > 0 && p->getCoin() > j.board.getCase(j.board.getIndice("Porte Ouverte"))->getPrix())
            {
                //cout<<"Souhaitez-vous acheter un ticket ? (o/n)"<<endl;
            }
            break;
        default:
            cout<<c->getType()<<endl;
            cout<<"1"<<c->getNom()<<"1"<<endl;
            assert(false);

            //dessineTexte("fin du tour",125,560,12);
            break;
    }
    if(c->getType()=='E'||c->getType()=='B'){
        texte = "Prix :";
        texte += to_string(c->getPrix());
        texte+= "   Loyer :";
        texte+= to_string(c->getLoyer());
        dessineTexte(texte,125,170,12);
        texte = "   Propriétaire : ";
        
        if(c->getOccupation()==0){
            texte+= "personne";
            dessineTexte(texte,125,145,12);
            
        }
        else{
            if(j.getPion(c->getOccupation())->getNom()==""){
                texte += "<anonyme>";
            }
            else{
                texte+= j.getPion(c->getOccupation())->getNom();
            } 
            dessineTexte(texte,125,145,12);

            if(c->getType()=='E'){
                texte = "investissement : niv ";
                texte+= to_string(c->getInvestissement());
                dessineTexte(texte,125,450,12);
            }
        }
        if(j.getBool("actionObligatoire")&&j.getBool("avance")&&c->getOccupation() != 0 && c->getOccupation()!=p->getRang()){//si il viens d'avancer et que la case est a quelqu'un d'autre
            texte ="vous devez payer le loyer au joueur ";
            texte += j.getPion(c->getOccupation())->getNom();
            texte += " !";
            dessineTexte(texte,125,475,12);
            newButton("\n",125,560,120,30,BLUE,"   Payer   ");
        }
        if(j.getBool("attendreAmplete")&&j.getBool("avance")){//si le pion a avance et qu'il na plus d'action obligatoire, il doit faire ces amplète
            if(c->getOccupation() == j.getJoueurCourant()){
                dessineTexte("+ pour investir dans le légal,",125,470,12);
                dessineTexte("- pour investir dans l'illégal.",125,490,12);
               texte ="/!\\ si vous avez déjà investit dans le légal,";
               dessineTexte(texte,125,515,10);
               texte = "investir dans l'illégal enlèvera vos ";
               dessineTexte(texte,125,530,10);
               texte ="investissement précédent et inverssement !";
               dessineTexte(texte,125,545,10);
               newButton("+",125,565,30,30,BLUE,"+");
               newButton("-",175,565,30,30,BLUE,"-");
               newButton("\n",300,565,120,30,BLUE,"Continuer");
                
            }

            else if(p->getCoin()>=c->getPrix()){
                if(c->getOccupation()==0){
                    newButton("o",125,560,120,30,BLUE,"Acheter");  
                    newButton("\n",300,560,120,30,BLUE,"Ne pas acheter"); 
                }
                else if (!j.getBool("actionObligatoire") && j.board.getCase(p->getPos())->getType() == 'E'){
                    texte = "voulez vous exproprier cette case ? ";
                    dessineTexte(texte,125,540,12);
                    texte = "Payez "; 
                    texte+= to_string(j.board.getCase(p->getPos())->getPrix());
                    texte += "$";
                    newButton("o",125,565,120,30,BLUE,texte);
                    newButton("\n",300,565,120,30,BLUE,"Ne rien faire");
                    

                }
            }
        }
    }

}


void JeuSDL::affichageProrpiete(Pion * p,int h,bool jc){
    int hp = h;
    string texte;
    if(p->getNom()==""){
        texte = "<anonyme>";
    }
    else{
        texte = p->getNom();
    }
    texte+= " : ";
    texte+=to_string(p->getCoin());
    texte+="$";
    if(jc == 1){
        dessineTexte(texte,740,h,11,{255,0,0});
    }
    else{
         dessineTexte(texte,740,h,11);
    }
    for (unsigned int i = 0; i < p->getNbPropriete() ; ++i)
        {   
            texte = p->getPropriete(i)->getNom();
            texte += " : niv ";
            texte+= to_string(p->getPropriete(i)->getInvestissement());
            texte +=" (";
            texte += to_string(p->getPropriete(i)->getLoyer());
            texte +="$ )";
            hp =h+20+20*i;
            dessineTexte(texte,730,hp,10,{124,122,120});

        }

}


void JeuSDL::affichageJeu(){
    //TODO
    plateau.dessineTexture(renderer,0,0,DIMY,DIMY);
    int h= 30 ;
    for(unsigned int i=1;i<=4;i++){
        unsigned int pos = j.getPion(i)->getPos();
        int x,y;
        unsigned char r,g,b;
        r=g=b=0;
        bool jc;
        if(j.getPion(i)==j.getPion(j.getJoueurCourant())){
            jc = 1;
        }
        else{
            jc = 0;
        }
        affichageProrpiete(j.getPion(i),h,jc);
        h+=30+20*j.getPion(i)->getNbPropriete();
        
        if(pos>=0&&pos<8){
            x = (DIMY-(108+pos*72))+5;
            y = DIMY-63;
        }
        else if(pos>=8&&pos<16){
            x=0;
            y=(DIMY-(108+(pos-8)*72))+5;
        }
        else if(pos>=16&&pos<24){
            x=(108+(pos-16)*72)-5;
            y=0;
        }
        else if(pos>=24&&pos<32){
            x=DIMY-63;
            y=(108+(pos-24)*72)-5;
        }   
        else{
            //assert(false);//position trop grande
        }
        if(i==1){
            r=g=255;
        }
        if(i==2){
            x+=33;
            r=255;
        }
        if(i==3){  
            y+=33;
            g=255;

        }
        if(i==4){
            x+=33;
            y+=33;
            b=255;
        }
        dessineRectangle(renderer,x,y,30,30,{r,g,b});
        //if(j.getBool(''))
    }
   
    if (!j.getBool("avance")&&!j.getPion(j.getJoueurCourant())->getPrisonnier()){
        string texte = j.getPion(j.getJoueurCourant())->getNom();
        if (texte ==""){
            texte = "anonyme joue.";
        }
        else{
            texte += " joue.";
        }
        
        dessineTexte(texte,125,560,12);

        if(j.getBool("desLance")){
            affichageDees();
            newButton("\n",130+(texte.length()*12),560,120,30,BLUE,"Avancer");
        }
        else{
        
            newButton("\n",130+(texte.length()*12),560,120,30,BLUE,"Lancer les des");
        }     
        
        
    }
    else if(!j.getBool("attendreAmplete")&&!j.getBool("actionObligatoire")&&j.gete().getn()=="rien"){
        string texte = "Fin du tour. ";
        dessineTexte(texte,125,560,12);
        newButton("\n",130+(texte.length()*12),560,120,30,BLUE,"Continuer");
    }
    else {
        affichageInteraction();
    }
        
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
    j.updateMiniJeu();
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
                    if((j.accepteClavier()&&!j.getBool("tourOrdi"))||input=="\e"){//si le jeu accepte les input de type clavier
                        j.actionClavier(input);
                    }
                    break;

                case SDL_TEXTINPUT: //detecter une touche sous forme de texte (comme ça pas besoin de scancode pour toutes les touches qu'on utilise)
                    
                    input = events.text.text;
                    if(j.accepteClavier()&&!j.getBool("tourOrdi")){//si le jeu accepte les input de type clavier
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
                        if(!j.getBool("tourOrdi")||action=="\e"){
                            j.action(action);
                        }
                        m.x=-1;
                        m.y=-1;
                        action="";//l'action est effectuée elle est donc vidée
                    }

                default: break;
            }
    }
    if(j.getBool("tourOrdi")&&!j.getBool("pause")){
        if(int((float(clock())/float(CLOCKS_PER_SEC))*100)%201<100){
            if(act){
                act = false;
                j.actionOrdi();// a intervalle régulier genre toutes les 5 secondes
            }
        }

        else{
            act = true;
        }
    }    
        
    return quit;
}


void JeuSDL::run(){
    bool quit = false;

    SDL_Event events;
    SDL_StartTextInput();

    //cout<<1;
    while(!quit){
        
        affichage();
        quit = update(events);

    }
}


