#pragma once
#include "utils.h"
#include <string>

class BmpExporter
{
public:
	BmpExporter(void);
	BmpExporter(std::string path);
	~BmpExporter(void);
	size_t export(ppm_image *img);
	void export2(ppm_image *img);
private:
	FILE * outfile;
};

