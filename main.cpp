#include <stdlib.h>
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
	cout<<argc<<endl<<argv[1]<<endl;
	string s = "commit -m \"" << argv[1] << "\"";
	cout<<s<<endl;
	/*if(argc>1){
		system("add -A");
		system("commit -m \"%s\"",argv[1]);
		system("git push");	
	}*/
	return 0;
}