#include <iostream>
#include "core/Jeu.h"


using namespace std;

int main(int argc,char ** argv)
{
	Jeu j,g,h;
	unsigned int tab[4];
	j.getOrdre(tab);
	for(int i = 0;i<4;i++){ 
		cout<<tab[i]<<" ";
	}
	cout<<endl;

	cout<<"test\ntest"<<endl;

	Plateau board;
	board.testRegressionPlateau();

	return 0;
}