//以下部分為湯智帆所做
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;


double absolute(double a)
{
	if (a < 0)
	{
		return (-1)*a;
	}else{
		return a;
	}
}


int main(int argc, char* argv[])
{
	string name;
	fstream out(argv[2],ios::out);
	fstream in(argv[1],ios::in);
	int numOfColorDensity;
	double colorADensity, colorBDensity;
	double f,g;
	

	cout<<"name of test: ";
	out<<"name of test: ";
	cin>>name;

	out<<name<<endl;
	cout<<"number of color density windows in test: ";
	out<<"number of color density windows in test: ";
	cin>>numOfColorDensity;
	out<<numOfColorDensity<<endl;
	
	

	cout<<"if color build correct fill 20: ";
	out<<"if color build correct fill 20: ";
	cin>>f;
	out<<f<<endl;
	cout<<"if color shown correct fill 10: ";
	out<<"if color shown correct fill 10: ";
	cin>>g;
	out<<g<<endl;
	cout<<"fill in the color A density and color B density: "<<endl;
	out<<"fill in the color A density and color B density: "<<endl;
	
	double* colorAarray = new double [numOfColorDensity];
	double* colorBarray = new double [numOfColorDensity];
	for(int i = 0; i<numOfColorDensity ; i++)
	{
		cout<<"color A density: ";
		out<<"color A density: ";
		string tempA;
		in>>tempA;
		stringstream ss1;
		ss1<<tempA;
		ss1>>colorAarray[i];
		cout<<endl;
		out<<colorAarray[i]<<endl;
		cout<<"color B density: ";
		out<<"color B density: ";
		
		string tempB;
		in>>tempB;
		stringstream ss2;
		ss2<<tempB;
		ss2>>colorBarray[i];
		cout<<endl;
		out<<colorBarray[i]<<endl;
	
	}
	
	double h;
	h = f+g;
	for(int i = 0; i<numOfColorDensity ; i++)
	{
		h = h+(((double)70/(double)numOfColorDensity)-(absolute(colorAarray[i] - colorBarray[i]))/5);
	}
	
	cout<<"the score of test case"<<name<<" is: "<<endl;
	out<<"the score of test case"<<name<<" is: "<<endl;
	cout<<h<<endl;
	out<<h<<endl;
	
	
}


