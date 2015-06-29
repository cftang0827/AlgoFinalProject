//以下部分為湯智帆所做
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main(int argc, char* argv[])
{

	fstream in(argv[1], ios::in);
	fstream out(argv[2], ios::out);
	while(!in.eof())
	{
		string a;
		string b;
		getline(in,a);
		for(int i = 0 ; i<a.size(); i++)
		{
			if(a[i] == 40)
			{
			    for(int j = i+1; j < a.size()-1; j++)
				{
					out<<a[j];
				}
				out<<endl;
				break;
			}
			
		}
		
		
	}
	
	
}
	