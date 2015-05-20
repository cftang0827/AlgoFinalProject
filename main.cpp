#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

//function declaration
void getData();

using namespace std;
typedef vector<string> Data;
typedef vector<Data> DataList;

DataList list;
string alpha, beta, omega;

int main()
{
	getData();
	for(int i = 0;i<list.size();i++)
	{
		for(int j=0;j<list[i].size();j++)
		{
			cout<<list[i][j]<<" ";
		}
		cout<<endl;
	}

	cout<<"alpha: "<<alpha<<endl;
	cout<<"beta: "<<beta<<endl;
	cout<<"omega: "<<omega<<endl; 
	

}




void getData()
{
	fstream fs ("test.txt" ,fstream::in);
	//cout<<"asdf"<<endl;
	string line;
	stringstream al;
	stringstream be;
	stringstream om;

	
	while(getline(fs,line))
	{	
		//cout<<"1234"<<endl;
		int a = line[0];
		string num;
		Data d;
		if(a>=48 && a<=57)
		{
			num.push_back(line[0]);
			for(int i=1; i< line.size(); i++)
			{
			//	cout<<"i: "<<i<<endl;
			//	cout<<"line.size() "<<line.size()<<endl;
				if((int)line[i]>=48 && (int)line[i]<=57 && i != line.size()-1)
				{
			//		cout<<"a"<<endl;
					num.push_back(line[i]);
				}else if((int)line[i] == 44 )
				{
			//		cout<<"b"<<endl;
					d.push_back(num);
					num.clear();
				}else if(i == line.size()-1)
				{
					num.push_back(line[i]);
			//		cout<<"dd"<<endl;
					d.push_back(num);
					num.clear();
					list.push_back(d);
					d.clear();
				}
			}
		}
		else if(a==65)
		{
			for(int i=1;i<line.size();i++)
			{
				if(line[i]>=48 && line[i]<=57)
				{
					alpha.push_back(line[i]);
				}
			}
		}
		else if(a==66)
		{
			for(int i=1;i<line.size();i++)
			{
				if(line[i]>=48 && line[i]<=57)
				{
					beta.push_back(line[i]);
				}
			}
		}
		else if(a==79)
		{
			for(int i=1;i<line.size();i++)
			{
				if(line[i]>=48 && line[i]<=57)
				{
					omega.push_back(line[i]);
				}
			}
		}
	}
}