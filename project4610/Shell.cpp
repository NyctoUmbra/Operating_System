#include <string>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

class Shell: public Filesys
{
	Public:
		Shell(string filename, int blocksize, int numberofblocks);
		int dir();// lists all files
		int add(string file);// add a new file using input from the keyboard
		int del(string file);// deletes the file
		int type(string file);//lists the contents of file
		int copy(string file1, string file2);//copies file1 to file2
};

Shell::Shell(string filename, int blocksize, int number of blocks):Filesys(filename, blocksize, numberofblocks)
{
}

int Shell::add(string file, string buffer)
{
	int errorcode = newfile(file);
	if (errorcode == 0)
	{
		//file can not be created
		return 0;
	}
	vector <string> blocks = block (buffer, getblocksize());
	for (int i = 0; i < block.size(); i++)
	{
		errorcode = addblock(file, blocks[i]);
	}
	return 1;
}

//remove blocks
int Shell::del(string file)
{
	int b = getfirstblock(file);
	if(b == -1)
	{
		return 0;
	}
	if(b == 0)
	{
		return 1;
	}
	while(b != 0)
	{
		delblock(file b);
		b = getfirstblock(file);
	}
	rmfile(file);
	return 1;
}

//type
{
	string buffer1, buffer2;
	int b = getfirstblock(file);
	if(b == -1)
	{
		//no file
	}
	if(b == 0)
	{
		return buffer2;
	}
	while(b != 0)
	{
		readblock(file, b, buffer1);
		buffer2 += buffer1;
		b = nextblock(file, b)
	}
	cout << buffer2;
}

//copy file 1 to file 2
{
	int b1 = getfirstblock(file1);
	//error check here
	/*
	*/
	int b2 = getfirstblock(file2);
	//if file 2 exists -> exit	//error check
	/*
	*/
	string buffer;
	while(b1 != 0)
	{
		readblock(file1, b1, buffer);
		b1 = nextblock(file1, b1);
		addblock(file2, buffer);
	}
	return 1;
}
