#include "JeuSDL.h"
#include <assert.h>
#include <sstream>

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


void Image::dessineTexture(SDL_Renderer * renderer,int x, int y, int w, int h)const{
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
    GrosTitre.loadFichier("data/images/OctetPoly.png",renderer);
    plateau.loadFichier("data/images/octopoly.png",renderer);
    ange.loadFichier("data/images/ange.png",renderer);
    demon.loadFichier("data/images/demon.png",renderer);
    DE.loadFichier("data/images/DE.png",renderer);
    Carte.loadFichier("data/images/CarteChance.png",renderer);
    Drapeau.loadFichier("data/images/DrapeauRouge.png",renderer);

    //Pions :
    pions[0].loadFichier("data/images/Alex.png",renderer);
    pions[1].loadFichier("data/images/Citronnelle.png",renderer);
    pions[2].loadFichier("data/images/Carrouf.png",renderer);
    pions[3].loadFichier("data/images/Demonetisation.png",renderer);
    pions[4].loadFichier("data/images/Elon.png",renderer);
    pions[5].loadFichier("data/images/Finn.png",renderer);
    pions[6].loadFichier("data/images/Fox.png",renderer);
    pions[7].loadFichier("data/images/Guitare.png",renderer);
    pions[8].loadFichier("data/images/Guy.png",renderer);
    pions[9].loadFichier("data/images/Hamid.png",renderer);
    pions[10].loadFichier("data/images/Jo.png",renderer);
    pions[11].loadFichier("data/images/Laetitia.png",renderer);
    pions[12].loadFichier("data/images/Naintendo_Swift.png",renderer);
    pions[13].loadFichier("data/images/Pouce.png",renderer);
    pions[14].loadFichier("data/images/Seb.png",renderer);
    pions[15].loadFichier("data/images/Taupiqueur.png",renderer);

    button.loadFichier("data/images/button.png",renderer);
    buttonClicked.loadFichier("data/images/buttonClicked.png",renderer);
    red_button.loadFichier("data/images/red_button.png",renderer);
    red_buttonClicked.loadFichier("data/images/red_buttonClicked.png",renderer);
    green_button.loadFichier("data/images/green_button.png",renderer);
    green_buttonClicked.loadFichier("data/images/green_buttonClicked.png",renderer);
    blue_button.loadFichier("data/images/blue_button.png",renderer);
    blue_buttonClicked.loadFichier("data/images/blue_buttonClicked.png",renderer);

    poubelle.loadFichier("data/images/Poubelle.png",renderer);


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
    pub11.loadFichier("data/images/pub11.png",renderer);
    pub12.loadFichier("data/images/pub12.png",renderer);

    Police = TTF_OpenFont("data/DejaVuSansCondensed.ttf",50);
    if (Police == NULL) {
            cout << "Failed to load DejaVuSansCondensed.ttf! SDL_TTF Error: " << TTF_GetError() << endl; SDL_Quit(); exit(1);
    }

    font_color.r = 0;font_color.g = 0;font_color.b = 0;
    m.x=-1;m.y=-1;
    act = false;
    a=3;
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
        im_contenue.setSurface(TTF_RenderUTF8_Solid(Police,c1.c_str(),couleur));
        im_contenue.loadSurface(renderer);
        im_contenue.dessineTexture(renderer,x+margin,y+margin,w-margin*2,h-margin*2);
    }
    else if(c2!=NULL){
        if(clicked){
            c2->dessineTexture(renderer,x+margin+(w*0.05),y+margin+(h*0.05),w-margin*2-(w*0.05),h-margin*2-(h*0.05));
        }
        else{
            c2->dessineTexture(renderer,x+margin,y+margin,w-margin*2,h-margin*2);
        }
    }
}


void JeuSDL::affichageLucky(){
    string texte;
    if(!j.getlu().getCartePiocher()){
        dessineRectangle(renderer,110,112,495,130,COL_WINDOW);
        texte = "Quelle chance vous venez d'apercevoir";
        dessineTexte(texte,125,120,12);
        texte =" deux cartes chances sur le sol";
        dessineTexte(texte,125,145,12);
        newButton("\n",300,500,120,30,BLUE,"Ramasser");
    }
    else{
        dessineRectangle(renderer,110,112,495,495,COL_WINDOW);

        affichageCarteChance(115,j.getlu().getCarteUn()->getTitre(),j.getlu().getCarteUn()->getTexte());
        affichageCarteChance(365,j.getlu().getCarteDeux()->getTitre(),j.getlu().getCarteDeux()->getTexte());

        newButton("1",290,300,120,30,BLUE,"Utiliser la 1");
        newButton("2",290,548,120,30,BLUE,"Utiliser la 2");
        newButton("3",560,565,30,30,RED,"",&poubelle);

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
                newButton(" ",190,220,310,310,INVISIBLE,"",&pub1);
                break;

                case 2:
                newButton(" ",190,220,310,310,INVISIBLE,"",&pub2);
                break;

                case 3:
                newButton(" ",190,220,310,310,INVISIBLE,"",&pub3);
                break;

                case 4:
                newButton(" ",190,220,310,310,INVISIBLE,"",&pub4);
                break;

                case 5:
                newButton(" ",190,220,310,310,INVISIBLE,"",&pub5);
                break;

                case 6:
                newButton(" ",190,220,310,310,INVISIBLE,"",&pub6);
                break;

                case 7:
                newButton(" ",190,220,310,310,INVISIBLE,"",&pub7);
                break;

                case 8:
                newButton(" ",190,220,310,310,INVISIBLE,"",&pub8);
                break;

                case 9:
                newButton(" ",190,220,310,310,INVISIBLE,"",&pub9);
                break;

                case 10:
                newButton(" ",190,220,310,310,INVISIBLE,"",&pub10);
                break;

                case 11:
                newButton(" ",190,220,310,310,INVISIBLE,"",&pub11);
                break;

                case 12:
                newButton(" ",190,220,310,310,INVISIBLE,"",&pub12);
                break;
            }

        if( action ==" "&& clique){
            
            clique = false;
        }
        else if (action ==""&& !clique){
            int temp = a;
            srand (time(NULL));
            while(a == temp){
                a = (rand()%12)+1;
            }
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
    GrosTitre.dessineTexture(renderer,(DIMX/2)-350,-30,700,250);
    if(j.getBool("nouvellePartie")){
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
            act[1]=i;
            newButton(act,110+(i-1)*250,460,40,40,RED,"",&poubelle);
            for(int k = 0;k<16;k++){
                string car = "car  ";
                car[3]=i;
                car[4]=k;
                if(j.getPion(i)->getCar()==k){
                    newButton(car,(35+(i-1)*250)+k%4*50,250+int(k/4)*50,45,45,GREEN,"",&pions[k],5);
                }
                else{
                    newButton(car,(35+(i-1)*250)+k%4*50,250+int(k/4)*50,40,40,BLUE,"",&pions[k],5);
                }
            }

        }
        if(j.getBool("attendreNom")){

            dessineTexte("nom :",35+(j.getNbJoueur()-1)*250,200,14);
    
            string nom = j.getPion(j.getNbJoueur())->getNom();

            if(nom.length()>0){
                dessineTexte(nom.c_str(),40+(j.getNbJoueur()-1)*250,230,14);
            }
            afficheCursor(renderer,40+(j.getNbJoueur()-1)*250+nom.length()*14,230,2,20);
            newButton("\n",120+(j.getNbJoueur()-1)*250+150,230,70,70,GREEN,"V",NULL,10);
        }
        else if(j.getBool("confirmation")){
            dessineTexte("Commencer avec ces Joueurs ? ",80,DIMY-70,22);
            newButton("\n",DIMX-300,DIMY-100,90,80,GREEN,"oui",NULL,10);
            newButton("n",DIMX-150,DIMY-100,90,80,RED,"non",NULL,10);
        }
        else{
            newButton("+",40+(j.getNbJoueur())*250+30,230,150,150,BLUE," + ",NULL,25);
            newButton("\n",DIMX-300,DIMY-100,240,80,BLUE,"Commencer !",NULL,10);
        }
    }
    else if(j.getBool("attendreNom")){
        for(unsigned int i = 1;i<=3;i++){
            string nom;
            string act = "";
            act+=char(int('0')+i);
            if(fichierExiste("data/sauvegarde/"+act+".save")){
                nom = " fichier "+act+" ";
            }
            else{
                nom = "<empty file>";
            }
            newButton(act,DIMX/2-100,250+100*(i-1),200,50,DEFAULT,nom,NULL,10);
        }
    }
    else{
        newButton("1",DIMX/2-220,230,440,100,DEFAULT,"  Nouvelle Partie !  ",NULL,10);
        newButton("2",DIMX/2-220,360,440,100,DEFAULT," Charger une Partie !",NULL,10);
        newButton("3",DIMX/2-220,490,440,100,RED    ,"       Quitter       ",NULL,10);
    }
    if(j.getBool("attendreNom")||j.getBool("nouvellePartie")){
        newButton("\e",DIMX-120,50,100,50,RED,"<-retour",NULL,10);
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


void JeuSDL::affichageCampagnePub(Pion *p,Case *c){
    string texte;
    if (p->getNbPropriete() > 0 && p->getCoin() >= (int)j.board.getCase(j.board.getIndice("Campagne de pub"))->getPrix())
    {
        texte = "Vous pouvez organiser une campagne de"; 
        dessineTexte(texte,125,120,12);
        texte = "PUB! Faire de la pub pour ";
        texte+=to_string(c->getPrix());
        texte+="$ ?";
        dessineTexte(texte,125,145,12);
        newButton("o",125,560,120,30,BLUE,"   Oui   ");  
        newButton("\n",300,560,120,30,BLUE,"   Non   ");
    }
    else{
        texte = "Vous êtes sur la campagne de PUB,";
        dessineTexte(texte,125,120,12);
        texte = "Mais vous n'y avez pas accès";
        dessineTexte(texte,125,145,12);
        newButton("\n",300,565,120,30,BLUE,"Continuer");

    }
    if(j.getBool("ad")){
        dessineRectangle(renderer,110,112,495,495,COL_WINDOW);
        texte= "Sur quel propriété faire votre campagne ?";
        dessineTexte(texte,125,120,12);
        int h = 110;
        int l = 165;
        for (unsigned int i = 0; i < p->getNbPropriete() ; ++i){   
            if(i%3==0){
                l = 165;
                h+=40;
            }
            string val ="c"+to_string(i); 
            if (j.getChoix()==to_string(i)){
                newButton(val,l,h,120,30,GREEN,p->getPropriete(i)->getNom());
            }
            else{
                newButton(val,l,h,120,30,BLUE,p->getPropriete(i)->getNom());
            }
            l+=135;
                    
        }
        newButton("o",300,565,120,30,BLUE,"Valider"); 
    }
}

//permet d'afficher la porte ouverte
void JeuSDL::affichagePorteOuverte(Pion *p,Case *c){
    string texte;
    if (j.board.nbCaseFree() > 0 && p->getCoin() > (int)j.board.getCase(j.board.getIndice("Porte Ouverte"))->getPrix())
    {
         texte = "Journée porte ouverte! Vous pouvez";
        dessineTexte(texte,125,120,12);
        texte ="aller où vous voulez.";
        dessineTexte(texte,125,145,12);
        texte =" Acheter un ticket pour ";
        texte+=to_string(c->getPrix());
        texte+="$ ?";
        dessineTexte(texte,125,170,12);
        newButton("o",125,560,120,30,BLUE,"   Oui   ");  
        newButton("\n",300,560,120,30,BLUE,"   Non   ");
        
    }
    else{
        texte = "Journée porte ouverte!";
        dessineTexte(texte,125,120,12);
        texte ="Dommage vous n'y avez pas accès";
        dessineTexte(texte,125,145,12);
        newButton("\n",300,565,120,30,BLUE,"Continuer");
    }

    if(j.getBool("porteO")){
        dessineRectangle(renderer,110,112,495,495,COL_WINDOW);
        texte= "Où-voulez vous vous rendre?";
        dessineTexte(texte,125,120,12);
        int h = 110;
        int l = 165;
        int nb = 0;
        for(unsigned int i = 0 ; i < 32 ; i++){
            if(j.board.getCase(i)->getOccupation() == 0 && (j.board.getCase(i)->getType() == 'B' || j.board.getCase(i)->getType() == 'E')){
                if(nb%3==0){
                    l = 165;
                    h+=40;
                }
                string val ="c"+to_string(i); 
                if (j.getChoix()==to_string(i)){
                    newButton(val,l,h,120,30,GREEN,j.board.getCase(i)->getNom());
                }
                else{
                    newButton(val,l,h,120,30,BLUE,j.board.getCase(i)->getNom());
                }
                l+=135;
                nb++;   
            }
        }
        newButton("o",300,565,120,30,BLUE,"Valider"); 
    }
}


void JeuSDL::affichageVente(){
    Pion * p = j.getPion(j.getJoueurCourant());
    dessineRectangle(renderer,110,112,495,495,COL_WINDOW);
    string texte = "Vous n'avez plus suffisament de sous!";
    dessineTexte(texte,125,120,12);
    texte = "Séléctionner une de vos ville";
    dessineTexte(texte,125,145,12);
    texte = " pour la vendre :";
    dessineTexte(texte,125,170,12);

    int h = 195;
    int l = 165;
    for (unsigned int i = 0; i < p->getNbPropriete() ; ++i)
    {
        if(i%3==0){
            l = 165;
            h+=40;
        }
        texte = p->getPropriete(i)->getNom();
        texte +=" ";
        texte += to_string(p->getPropriete(i)->getPrixDeVente());
        texte+="$";
        string val ="c"+to_string(i); 
        if(!j.dejaEnVente(i))
        {
            if (j.getChoix()==to_string(i)){
                newButton(val,l,h,120,30,GREEN,texte);
            }
            else{
                newButton(val,l,h,120,30,BLUE,texte);
            }
        }
        else
        {
            newButton(" ",l,h,120,30,RED,texte);
        }
        l+=135;
    }
    newButton("+",165,565,120,30,BLUE,"Ajouter");
    newButton("-",305,565,120,30,BLUE,"Retirer");
    if(!j.getBool("confirmation")){
        newButton("o",445,565,120,30,BLUE,"Confirmer");
    }

    texte = "Vous aurez :";
    texte+=to_string((p->getCoin() + j.totalVente()));
    texte +="$";
    dessineTexte(texte,125,540,10);

    if(j.getPrixAPayer() - (p->getCoin() + j.totalVente()) > 0)
    {
        texte = "Il manque ";
        texte += to_string( j.getPrixAPayer() - (p->getCoin() + j.totalVente()));
        texte+="$";
        dessineTexte(texte,420,540,10);
                  
    }
    else
    {
        texte = "Somme suffisante!";
        dessineTexte(texte,420,540,10);
    }
    
}


void JeuSDL::affichagePrison(Pion *p){
    string texte = "Bienvenue en Prison ";
    if(p->getNom()==""){
        texte+= "<anonyme>";
    }
    else{
        texte+=p->getNom();
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

}


void JeuSDL::affichageCarteChance(int H,string Titre, string Texte){
    Carte.dessineTexture(renderer,150,H,400,240);
    dessineTexte(Titre,150+(400-(Titre.length()*10))/2,H+20,10,{255,0,0});
                
    int h =H+120;
    string texte =Texte;
    istringstream iss(texte);
    string mot; 
    string tmp;
    while ( getline( iss, mot, ' ' ) ) 
    { 
        if((tmp.length()*8)+(mot.length()*8)+8<312){
            tmp+=" "+mot;
        }
        else{
            dessineTexte(tmp,150+(400-(tmp.length()*8))/2,h,8,{255,0,0});
            h+=15;
            tmp = mot;
        }                    
    } 
    dessineTexte(tmp,150+(400-(tmp.length()*8))/2,h,8,{255,0,0});
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
            affichagePrison(p);
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
                affichageCarteChance(210,j.getCarte()->getTitre(),j.getCarte()->getTexte());
                newButton("\n",300,565,120,30,BLUE,"Continuer");
            }
            break;
        case 'A':
            
            affichageCampagnePub(p,c);
           
            break;
        case 'O':
            affichagePorteOuverte(p,c);
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
        texte+= "$    Loyer :";
        texte+= to_string(c->getLoyer());
        texte+= "$";
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
                if(c->getType()=='E'){
                    texte = "investissement : niv ";
                    texte+= to_string(c->getInvestissement());
                    dessineTexte(texte,125,450,12);
                }
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
            if(c->getOccupation() == j.getJoueurCourant()&&c->getType()=='E'){
                texte = "coût + :";
                texte +=to_string(c->getPrixB());
                texte+="$         coût - :";
                texte +=to_string(c->getPrixM());
                texte+="$";
                dessineTexte(texte,125,195,12);
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
            else if(c->getType()=='B'&&c->getOccupation()==j.getJoueurCourant()){
                dessineTexte("Bienvenue chez vous !",125,470,12);
                newButton("\n",300,565,120,30,BLUE,"Continuer");

            }
            else if(p->getCoin()>=(int)c->getPrix()){
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
        dessineTexte(texte,750,h,11,{255,0,0});
    }
    else{
         dessineTexte(texte,750,h,11);
    }
    pions[int(p->getCar())].dessineTexture(renderer,725,h-5,20,20);
    for (unsigned int i = 0; i < p->getNbPropriete() ; ++i)
        {   
            texte = p->getPropriete(i)->getNom();
            texte += " : niv ";
            texte+= to_string(p->getPropriete(i)->getInvestissement());
            texte +=" (";
            texte += to_string(p->getPropriete(i)->getLoyer());
            texte +="$ )";
            hp =h+20+20*i;
            if(j.board.getcasePub()!=0){
                if(j.board.getCase(j.board.getcasePub())->getNom() == p->getPropriete(i)->getNom()){
                    Drapeau.dessineTexture(renderer,725,hp,20,20);
                }
            }
            switch(p->getPropriete(i)->getGroup()){
                case 1:
                    dessineTexte(texte,760,hp,10,{148,72,40});
                    break;
                case 2:
                    dessineTexte(texte,760,hp,10,{ 255 , 43 , 149});
                    break;
                case 3:
                    dessineTexte(texte,760,hp,10,{173 , 33 , 106});
                    break;
                case 4:
                    dessineTexte(texte,760,hp,10,{ 245 , 143 , 0});
                    break;
                case 5:
                    dessineTexte(texte,760,hp,10,{ 225, 0 , 15});
                    break;
                case 6:
                    dessineTexte(texte,760,hp,10,{252 , 235 , 1});
                    break;
                case 7:
                    dessineTexte(texte,760,hp,10,{31 , 164 , 74});
                    break;
                case 8:
                    dessineTexte(texte,760,hp,10,{1 , 104 , 179});
                    break;
                case 42:
                    dessineTexte(texte,760,hp,10,{124,122,120});
                    break;
            }
            

        }

}


void JeuSDL::affichageJeu(){
    plateau.dessineTexture(renderer,0,0,DIMY,DIMY);
    GrosTitre.dessineTexture(renderer,DIMX-100,DIMY-50,90,50);
    int h= 30 ;
    for(unsigned int i=1;i<=4;i++){
        unsigned int pos = j.getPion(i)->getPos();
        int x,y;
        
        bool jc;//joueur courant
        jc = j.getPion(i)==j.getPion(j.getJoueurCourant());

        affichageProrpiete(j.getPion(i),h,jc);

        h+=30+20*j.getPion(i)->getNbPropriete();
        
        if(pos>=0&&pos<8){
            x = (DIMY-(108+pos*72))+5;
            y = DIMY-73;
        }
        else if(pos>=8&&pos<16){
            x=5;
            y=(DIMY-(108+(pos-8)*72));
        }
        else if(pos>=16&&pos<24){
            x=(108+(pos-16)*72)-70;
            y=5;
        }
        else if(pos>=24&&pos<32){
            x=DIMY-63;
            y=(108+(pos-24)*72)-70;
        }   
        else{
            //assert(false);//position trop grande
        }
        if(i==2){
            x+=35;
        }
        if(i==3){  
            y+=35;

        }
        if(i==4){
            x+=35;
            y+=35;
        }
        if(j.getPion(i)->getCoin()!=-1){
            pions[int(j.getPion(i)->getCar())].dessineTexture(renderer,x,y,35,35);
        }
        
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
    else if(j.getBool("vend"))
    {
            affichageVente();
    }
    else if(!j.getBool("attendreAmplete")&&!j.getBool("actionObligatoire")&&j.getPion(j.getJoueurCourant())->getCoin()>=0&&j.gete().getn()=="rien"){
        string texte = "Fin du tour. ";
        dessineTexte(texte,125,560,12);
        newButton("\n",130+(texte.length()*12),560,120,30,BLUE,"Continuer");
    }
    else if(j.getPion(j.getJoueurCourant())->getCoin()<0){
        dessineRectangle(renderer,110,112,495,495,COL_WINDOW);
        string texte ="Vous avez fait faillite!";
        dessineTexte(texte,125,520,12);
        newButton("\n",300,565,120,30,BLUE,"Continuer");
    }
    else {
        affichageInteraction();

    }
        
}


void JeuSDL::affichageVictoire(){
    bool v = false;
    string texte = "FIN DE PARTIE !";
    dessineTexte(texte,30,0,70,{255,0,0});
    texte = "Victoire de ";
    if (j.getPion(j.getVainqueur())->getNom()==""){
        texte += "<anonyme>";
    }
    else{
        texte +=j.getPion(j.getVainqueur())->getNom();
    }
    dessineTexte(texte,30,100,20,{255,0,0});
    for(unsigned int i=1;i<=4;i++){
        int sous = j.getPion(i)->getCoin();
        if(sous == -1){
            v = true;
        }
    }
    
        if (j.getPion(j.getVainqueur())->getNom()==""){
            texte = "<anonyme>";
        }
        else{
            texte =j.getPion(j.getVainqueur())->getNom();
        }
    if(v){
        texte += " à gagner en provoquant la faillite des ses advaisaires.";
        dessineTexte(texte,30,200,15);

    }
    else{
        texte += " à gagner en le monopole des propriétés";
        dessineTexte(texte,30,200,15);
    }
    texte = "Valeur du patrimoine actif :";
    texte += to_string(j.getPion(j.getVainqueur())->patrimoineActif());
    texte +="$";
    dessineTexte(texte,30,250,15);
    texte = "Valeur du compte en banque :";
    texte += to_string(j.getPion(j.getVainqueur())->getCoin());
    texte +="$";
    dessineTexte(texte,30,300,15);
    newButton("\n",400,565,200,50,BLUE,"    Retour au menu    ");

}

void JeuSDL::affichagePause(){
    SDL_Color rouge;
    rouge.r = 255;
    rouge.g = 0;
    rouge.b = 0;
    inputTexte.setSurface(TTF_RenderText_Solid(Police,"PAUSE !",rouge));
    inputTexte.loadSurface(renderer);


    dessineRectangle(renderer,112,110,495,495,COL_WINDOW);
    inputTexte.dessineTexture(renderer,(110+(495/2))-150,115,300,80);
    if(!j.getBool("attendreNom")){
        newButton("1",(110+(495/2))-200,220,400,65,DEFAULT,"        Reprendre       ",NULL,10);
        newButton("2",(110+(495/2))-200,300,400,65,DEFAULT,"       Sauvegarder      ",NULL,10);
        newButton("3",(110+(495/2))-200,380,400,65,DEFAULT,"Retour au menu de départ",NULL,10);
        newButton("4",(110+(495/2))-200,460,400,65,RED    ,"         Quitter        ",NULL,10);
    }
    else{
        for(unsigned int i=1;i<=3;i++){
            string nom;
            string act = "";
            act+=char(int('0')+i);
            if(fichierExiste("data/sauvegarde/"+act+".save")){
                nom = " fichier "+act+" ";
            }
            else{
                nom = "<empty file>";
            }
            newButton(act,(110+(495/2))-100,250+80*(i-1),200,65,DEFAULT,nom,NULL,10);
        }
        newButton("\e",545,120,50,50,RED,"X",NULL,10);
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
    else if(j.getVainqueur()!=0){
        affichageVictoire();
    }
    else{

        affichageJeu();

        if(j.getBool("pause")){
            affichagePause();
        }   

        if(j.gete().getn()=="escape"){
           affichageEscape();
        }
        else if(j.gete().getn()=="clicker"){
            affichageClicker();
        }
        else if(j.gete().getn()=="hack"){
            affichageHacking();
        }
        else if(j.gete().getn()=="lucky"){
            affichageLucky();
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
                    if((j.accepteClavier()&&!j.getBool("tourOrdi"))||j.getBool("pause")){//si le jeu accepte les input de type clavier
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
                        if(!j.getBool("tourOrdi")||j.getBool("pause")){
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
    while(!j.getBool("quitte")&&!quit){
        
        affichage();
        quit = update(events);

    }
}


