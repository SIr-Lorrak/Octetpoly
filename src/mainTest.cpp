#include <iostream>
#include "core/Jeu.h"

using namespace std;

int main(int argc,char ** argv)
{
	Jeu j;
	unsigned int tab[4];
	j.getOrdre(tab);
	for(int i = 0;i<4;i++){ cout<<tab[i]<<endl;}

	return 0;
}