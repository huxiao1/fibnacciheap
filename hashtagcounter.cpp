/*
  Xiao Hu 69363179
 */
#include <bits/stdc++.h>
#include <string>
#include <iostream>
#include "FibonacciHeap.h"
using namespace std;
//split the string
vector<string> split(const string& s,vector<std::string>& v, const string& c)
{
	std::string::size_type pos1, pos2;
        pos2 = s.find(c);
  	pos1 = 0;
  	while(std::string::npos != pos2)
  	{
    		v.push_back(s.substr(pos1, pos2-pos1));
 		pos1 = pos2 + c.size();
    		pos2 = s.find(c, pos1);
  	}
  	if(pos1 != s.length())
    		v.push_back(s.substr(pos1));
	return v;
}

//store the hashtag and the keynumber to the fibheap
void StoreInfib(string buffer, map<string, FibNode*> &table, FibHeap &fibHeap) {
	string hashtag = "";
	int frequency = 0;

	vector<string> v;
	split(buffer,v," ");
	
	//get the hashtag and frequency
	hashtag = v[0].substr(1);
	sscanf(v[1].c_str(),"%d",&frequency);

	if (table[hashtag] == nullptr)
		table[hashtag] = fibHeap.insert(hashtag, frequency);
	else
		fibHeap.update(table, hashtag, frequency);
}


//not in the case of the specified output file
string onlyinput(string input_file) 
{
	string finaldata="";
	string data = "";
	string buffer;
	int i;
	int query;
	//hashtable
	map<string, FibNode*> table;
	FibHeap fibHeap;
	
	ifstream fd(input_file.c_str(), ios::in);	
	if (!fd.is_open()) 
	{
		cout << "Open error!" << endl;
		exit(1);
	}
	
	while(getline(fd, buffer)) 
	{
		//end program
		if (buffer[0] == 's' || buffer[0] == 'S') 
		{
			cout << "Program end!" << endl;
			return finaldata;
		}
		//query
		else if (buffer[0] >= '0' && buffer[0] <= '9')
		{
			query = stoi(buffer);
			if (query > table.size()) {
				cout << "Query should be no more than keywords number!" << endl;
				exit(-1);
			}
			vector<pair<string, int>> temp;
			FibNode* ptr = nullptr;
	
			for (i = 0; i < query; ++i) 
			{
				ptr = fibHeap.removeMax();
				cout << ptr->key << "  " << ptr->freq << endl;
				temp.push_back(make_pair(ptr->key, ptr->freq));
			}
			for (i = 0; i < query; ++i) 
			{
				string key = temp[i].first;
				int freq = temp[i].second;
				table[key] = fibHeap.insert(key, freq);
			}
			
			//return the data to the console
			string data="";
			for (i = 0; i < temp.size(); ++i) 
			{
				if(i==temp.size()-1)
				{
					data = data + temp[i].first;
				}
				else
					data = data + temp[i].first + ",";
			}
			finaldata = finaldata + data + "\n\n";
			data="";
		}
		//store the normal hashtag to the heap
		else 
		{
			StoreInfib(buffer, table, fibHeap);
		}
	}
	fd.close();
	return finaldata;
}


//In the case of the specified output file
void withoutput(string input_file,string output_file) {
	ifstream is(input_file.c_str(), ios::in);	
	string buffer;
	string datafile = "";
	int i;
	int freq;
	int query;
	map<string, FibNode*> table;
	FibHeap fibHeap;
	fstream fd;	

	if (!is.is_open()) 
	{
		cout << "Open error!" << endl;
		exit(1);
	}
     	fd.open(output_file, ios::in);

	//determine whether already have the output file
     	if(!fd)
     	{
          	cout<<output_file<<"do not have,but I can help to create one@_@!"<<endl;
     	}
     	else
     	{
		const char* temprem = output_file.c_str();
          	cout<<output_file<<"already have,we have to del formal one-.-!"<<endl;
		remove(temprem);
     	}

	while(getline(is, buffer)) 
	{
		//end the program
		if (buffer[0] == 's' || buffer[0] == 'S') 
		{ 	
			cout << "the end ^.^!" << endl;
			return;
		}
		//query,use removemax to get the first query number largest hashtags and write into outputfile 
		else if ((buffer[0] >= '0' && buffer[0] <= '2') || (!buffer[1] && buffer[0]>='0')){
			sscanf(buffer.c_str(),"%d",&query);
			if (query > table.size()) 
			{
				cout << "incorrect query number!" << endl;
				exit(-1);
			}
			vector<pair<string, int>> temp;
			FibNode* ptr = nullptr;
	
			for (i = 0; i < query; ++i) 
			{
				ptr = fibHeap.removeMax();
				cout << ptr->key << "  " << ptr->freq << endl;
				temp.push_back(make_pair(ptr->key, ptr->freq));
			}
			for (i = 0; i < query; ++i) 
			{
				string key = temp[i].first;
				freq = temp[i].second;
				table[key] = fibHeap.insert(key, freq);
			}
			
			ofstream fd2(output_file.c_str(), ios::app | ios::out);
			for (i = 0; i < temp.size(); ++i) 
			{
				datafile = datafile + temp[i].first + ",";
			}
			datafile.pop_back();
			fd2 << datafile << endl;
			datafile = "";
			cout << "Data has been successfully written into output_file.txt!" << endl;
			fd2.close();
		}
		else if(buffer[0]!='#' && buffer[1] && buffer[0] > '2')
		{
			cout<<"incorrect query number!"<<endl;
			exit(-1);
		}
		//store the normal hashtag to the heap
		else 
		{
			StoreInfib(buffer, table, fibHeap);
		}
	}
	is.close();
}


//main function
int main(int argc, char** argv) 
{
	string data;
	if (argc == 2)
	{
		data = onlyinput(argv[1]);
		cout<<"due to do not have output file, so write output data to console!"<<endl;
		cout<<data<<endl;
	}	
	else if(argc == 3)
		withoutput(argv[1],argv[2]);	
	else
	{
		cout << "Wrong number of parameters!" << endl;
		cout<<"./hashtagcounter inputfile (outputfile)"<<endl;
	}
	return 0;
}
