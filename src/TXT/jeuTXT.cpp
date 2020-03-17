#include "jeuTXT.h"


#if not defined _WIN32
int kbhit() {
    struct timeval tv;
    fd_set fds;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds); //STDIN_FILENO is 0
    select(STDIN_FILENO+1, &fds, NULL, NULL, &tv);
    return FD_ISSET(STDIN_FILENO, &fds);
}
#endif




void jeuTXT::affichageHacking(hacking hack){
	system("clear");
	if(hack.getValidation() == 2){
	cout<<"Vous devez tapez la commande suivante pour : "<<hack.getmot()<<endl;
	cout<<hack.getMotSaisie();
	}
	if(hack.getValidation() == 0){
		cout<<"commande validé!"<<endl<<"commande suivante : "<<hack.getmot()<<endl;
		cout<<hack.getMotSaisie();
	}
	if(hack.getValidation() == 1){
		cout<<"commande non validé!"<<endl<<"re-tapez la commande : "<<hack.getmot()<<endl;
		cout<<hack.getMotSaisie();
	}

}


void jeuTXT::update(){
	char touche;
	if(kbhit()){
		touche = fgetc(stdin);
		action_clavier(touche);
	}
}
	
