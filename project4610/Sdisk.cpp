#include "Sdisk.h"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

Sdisk::Sdisk(string diskname, int numberofblocks, int blocksize)
{
	this->diskname = diskname;
	this->numberofblocks = numberofblocks;
	this->blocksize = blocksize;

	ifstream infile;
	infile.open(diskname.c_str());

	if(infile.good())
	{
		cout << "checking disk" << endl;
		int count = 0;
		char c;
		infile.get(c);
		
		while(infile.good())
		{
			count++;
			infile.get(c);
		}

		if(count == numberofblocks * blocksize)
		{
			cout << "disk size is correct" << endl;
		}

		infile.close();
	}

	else
	{
		infile.close();
		ofstream ofile;
		ofile.open(diskname.c_str());
		cout << "creating Sdisk" << endl;
		for(int i=0; i<numberofblocks * blocksize; i++)
		{
			ofile.put('#');
		}
		cout << "Sdisk created" << endl;
	}

	return;
}

int Sdisk::getblock(int blocknumber, string& buffer)
{
	//error checks
	//eg 	0 <= blocknumber < numberofblocks	return 0
	fstream iodisk;
	iodisk.open(diskname.c_str(), ios::in | ios::out);
	char c;
	buffer.clear();
	iodisk.seekg(blocknumber * blocksize);
	for(int i=0; i<blocksize; i++)
	{
		iodisk.get(c);
		buffer += c;
	}
	return 1;
}

int Sdisk::putblock(int blocknumber, string buffer)
{
	/*check
	*1. blocknumber > 0
	*2. blocknumber < numberofblocks
	*3. buffer.length() == blocksize
	*/
	
	fstream iofile;
	iofile.open(diskname.c_str(), ios::in | ios::out);
	
	for(int i=0; i<blocksize; i++)
	{
		iofile.put(buffer[i]);
	}
	
	return 1;
}

int Sdisk::getnumberofblocks() // accessor function
{
	return this->numberofblocks;
}

int Sdisk::getblocksize() // accessor function
{
	return this->blocksize;
}
