#pragma once
#include "stdafx.h"
#include <string>
#include <fstream>
#include <vector>

namespace std
{
	struct  Bitmap  { 
	//data members : coordinates, dimension, file name, and data stream
	  short   x, y;
	  short   h, w;
	  string filename;
	  fstream pic;
  
	  struct Header {}header; //left out data members to save space
	  struct Info  {}info;  //same here
	  struct Color  { //the color
		unsigned char b;
		unsigned char g;
		unsigned char r;
		unsigned char a;
	  }color;

	 void Create(string name, int h2, int w2)  {
				 h = h2; 
				 w = w2;
		  filename = name;
  
		  Header header = {19778, sizeof(Color)*w*h , 0, 0, 54};
		  Info   info   = {sizeof(Info), w, h, 1, sizeof(Color)*8, 0, ( sizeof(Color) *(w*h) ), 1, 1, 0, 0};
		  Color  color  = {0,255,90,0};

		  vector<Color>data;
		  data.assign(w*h, color);
		  fstream pic;
		  pic.open(filename.c_str(), ios::out|ios::binary);

		  pic.write(reinterpret_cast<char*>(&header), sizeof(header));
		  pic.write(reinterpret_cast<char*>(&info), sizeof(info));
  
		  for (unsigned int f = 0; f < data.size(); ++f)  {
			Color pixel = data.at(f);
			pic.write((char*)&pixel,sizeof(Color));
		   }
  
		}
	};
}