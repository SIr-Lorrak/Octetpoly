#ifndef OCTET_CASE_H
#define OCTET_CASE_H

class Case{
private:

	int occupation;
	char type;
	int investissement;

public:
	Case();

	~Case();


	//Getters 
	int getoccupation();
	char gettype();
	int getinvestissement();

	//Setters
	void setoccupation(int occupation);
	void settype(char categorie);
	void setinvestissement(int i);

};

#endif