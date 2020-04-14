#include <iostream>
//#include "core/Jeu.h"

#include "../src/core/Evenement.h"


using namespace std;

int main(int argc,char ** argv)

{	Escape e;
	string caractere;
	for(int i=0;i<11;i++){
		for(int j=0;j<11;j++){
			caractere = tab_escape[i][j];
			



			if((e.getJoueur().y == i)&&(e.getJoueur().x == j)){
				cout<<" J ";
			}
			else if((e.getPolice().y == i)&&(e.getPolice().x == j)){
				cout<<" P ";
			}
			else if(tab_escape[i][j]=="M"){
				cout<<" M ";
			}
			else if(tab_escape[i][j]=="H"){
				cout<<" # ";
			}
			else if(tab_escape[i][j]=="RV"){
				cout<<" | ";
			}
			else if(tab_escape[i][j]=="RH"){
				cout<<" _ ";
			}
			else if(tab_escape[i][j]=="DEPART"){
				cout<<" D ";
			}
			else if(tab_escape[i][j]=="ARRIVE"){
				cout<<" A ";
			}
			else if(tab_escape[i][j]=="T1"){
				cout<<" / ";
			}
			else if(tab_escape[i][j]=="T2"){
				cout<<" / ";
			}
			else if(tab_escape[i][j]=="T3"){
				cout<<" / ";
			}
			else if(tab_escape[i][j]=="T4"){
				cout<<" / ";
			}

			if(j==10){
				cout<<endl<<endl;
			}
			
		}
	}	

	return 0;
}