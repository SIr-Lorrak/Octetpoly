#include <iostream>
#include <assert.h>
#include <fstream>
#include <string>
#include "core/Jeu.h"


using namespace std;

void ecrire(const string & file){
	ofstream fichier (file.c_str());
	assert(fichier.is_open());

	fichier<<0<<" salut"<<" "<<endl<<"zizitos"<<" "<<endl<<" \"test espace\" "<<5<<4<<endl<<0;
	fichier.close();
}

void lire(const string & file){
	ifstream fichier (file.c_str());
	if(!fichier.is_open()){
		cout<<"ce fichier n'existe pas voyons"<<endl;
	}
	else{
		string a;
		for(int i = 0;i<=4;i++){
			fichier>>a;
			cout<<a<<endl;
		}
	}
	fichier.close();
}

int main(int argc,char ** argv)
{
	Jeu j;
	j.testRegression();

	return 0;
}