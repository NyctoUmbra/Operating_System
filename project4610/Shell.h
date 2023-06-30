#ifndef SHELL_H
#define SHELL_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

// dir lists files in the class Shell
// Prototype: int Shell::dir() 
int Shell::dir()
{ vector<string> flist=ls();
  for (i=0; i<flist.size(); i++)
      {
        cout << flist[i] << endl;
      }
}
