#include <iostream>

using namespace std;

int main(int argc,char ** argv)
{
	int a = 3;
	int & b = a;
	cout<<a<<endl<<b<<endl;
	b+=4;
	cout<<a<<endl;
	return 0;
}