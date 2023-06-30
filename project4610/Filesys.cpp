#include "Filesys.h"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

// This function is part of the Filesys class
// Prototype: vector<string> ls();
vector<string> Filesys::ls()
{ vector string flist;
  for (int i=0; i<filename.size(); i++)
      {
        if (filename[i] != "$$$$$")
           {
             flist.push_back(filename[i]);
           }
      }
  return flist;
}

Filesys::Filesys(string diskname, int numberofblocks, int blocksize) : Sdisk (diskname, numberofblocks, blocksize)
{
	int blocksize = getblocksize();
	int numberofblocks = getnumberofblocks();
	this -> rootsize = blocksize / 12);

	this -> fatsize = (6 * numberofblocks) / blocksize + 1;
	
	string buffer;
	int error = getblock(1, buffer);
	if (buffer[0] == "#")
	{
		build fs();
		fssynch();
	}
	else
	{
		read fs();
	}
	return;
}

int Filesys::build fs()
{
	for (int i = 0; i < rootsize; i++)
	{
		filename.push_back("$$$$$");
		firstblock.push_back(0);
	}	//root created
	
	fat.push_back (2 + fatsize);
	fat.push_back (-1);
	
	for (int i = 0; i < fatsize; i++)
	{
		fat.push_back (-1);
	}
	for (int i = 2 + fatsize; i < numberofblocks; i++)
	{
		fat.push_back(i++);
	}
	fat[fat.size() - 1] = 0;
	return 1;
}

int Filesys::fssynch()
{
	//root//
	ostringstream ostream;
	for (int i = 0; i < filename.size; i++)
	{
		ostream << filename[i] << " " << firstblock[i] << " ";
	}
	string buffer1 = ostream.str();
	vector <string> blocks1 = block(buffer1, getblocksize());
	int error = putblock(1, blocks1[0]);
	//error checking
	
	//fat//
	ostringstream ostream2;
	for (int i = 0; i < fat.size(); i++)
	{
		ostream2 << fat[i] << " ";
	}
	string buffer2 = ostream2.str();
	vector <string> blocks2 = block(buffer2, getblocksize());
	for (int i = 0; i < blocks2.size(); i++)
	{
		putblock(2 + i, blocks2[i]);
	}
	return 1;
}

int Filesys::readfs()
{
	//get root
	string buffer;
	getblock(1, buffer);
	istringstream instream1;
	instream1.str(buffer);
	for (int i = 0; i < rootsize; i++)
	{
		string s;
		int b;
		instream1 >> s >> b;
		filename.push_back(s);
		firstblock.push_back(b);
	}
	//get fat
	string buffer2, b;
	for (int i = 0; i < fatsize; i++)
	{
		getblock(2 + i, b);
		buffer2 += b; //buffer2 = buffer2 + b
	}
	istringstream instream2;
	instream2.str(buffer2)
	for (int i = 0; getnumberofblocks(); i++)
	{
		int n;
		instream2 >> n;
		fat.push_back(n);
	}
	return 1;
}	//end readfs()

int Filesys::fclose()
{
	return 1;
}

int Filesys::newfile(string file)
{
	for (int i = 0; i < filename.size(); i++)
	{
		if (filename[i] == file)
		{
			cout << "file exists";
			return 0;
		}
	}
	for (int i = 0; i < filename.size(); i++)
	{
		if (filename[i] == "$$$$$")
		{
			filename[i] = file;
			filename[i] = 0;
			fssynch();			
			return 1;
		}
	}
	return 0;
}

int Filesys::rmfile(string file)
{
	for (int i = 0; i <filename.size(); i++)
	{
		if (filename[i] == file)
		{
			cout << "File not empty";
			return 0;
		}
	}
	
	int b = getfirstblock(file);
	if (getfirstblock != 0)
	{
		filename[i] = "$$$$$";
		fssynch();
		
		return 0;
	}

	return 1;
}

int Filesys::getfirstblock(string file)
// check if file exists
{
	for (int i = 0; i < filename.size(); i++)
	{
		if (filename[i] == file)
		{
			return firstblock[i];
		}
	}
	return -1;
}

int Filesys::addblock(string file, string block)
//string block added to file = last block
{
	int allocate = fat[0];
	if (allocate == 0)
	{
		cout << "No space in root";
		return 0;
	}

	int b = getfirstblock(file);
	if (b == -1)
	{
		cout << "File does not exist";
		return 0;
	}
	else
	{
		cout << "Everything looks good";
	}
	
	fat[0] = fat[allocate];	//allocate = fat[0]
	fat[allocate] = 0;

	if (b == 0)
	{
		//update root
		for (int i = 0; i < filename.size(); i++)
		{
			if (filename[i] == file)
			{
				firstblock[i] = allocate;
			}
		}
	}
	else
	{
		while (fat[b] != 0)
		{
			b = fat[b];
		}
		fat[b] = allocate;
	}
	
	putblock(allocate, block);	//write data back to disk
	fssynch();
	return allocate;
}

bool Filesys::checkfileblock(string file, int block)
//returns true if block belongs to the file
//false otherwise
{
	int blockid = getfirstblock(file);
	if (blockid <= 0)
	{
		//file does not exist or is empty
		return false;
	}
	while (blockid != 0)
	{
		if (blockid == block)
		{
			return true;
		}
		else
		{
			blockid = fat[blockid];
		}
	}
	return false;
}

int Filesys::delblock(string file, int block)
//deletes blocknumber block from file
{
	int deallocate = block;
	if (! checkfileblock (file, block))
	{
		return 0;
	}
	int b = getfirstblock(file);
	if (b == block)
	{
		for (int i = 0; filename.size; i++)
		{
			if (filename[i] == file)
			{
				firstblock[i] = fat[block];
				break;
			}
		}
	}
	else
	{
		while (fat[b] != deallocate)
		{
			b = fat[b];
		}
		//fat[b] = block to be deleted
		fat[b] = fat[block];
	}
	fat[block] = fat[0];
	fat[0] = block;
	
	fssynch();
}

int Filesys::readblock(string file, int blocknumber, string& buffer)
{
	if (checkfileblock(file, blocknumber))
	{
		getblock (blocknumber, buffer);
		return 1;
	}
	else
	{
		return 0;
	}
}

int Filesys::writeblock(string file, int blocknumber, string buffer)
{
	if (checkfileblock(file, blocknumber))
	{
		putblock (blocknumber, buffer);
		return 1;
	}
	else
	{
		return 0;
	}
}

int Filesys::nextblock(string file, int blocknumber)
{
	if (checkblock(file, blocknumber))
	{
		return fat[blocknumber];
	}
	else
	{
		return -1;
	}
}
