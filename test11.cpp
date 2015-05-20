#include <iostream>
#include <string>

using namespace std;

int main()
{
	string a = "abc123ABC,";
	for(int i=0;i<a.size();i++)
	{
		cout<<(int)a[i]<<endl;
	}
}