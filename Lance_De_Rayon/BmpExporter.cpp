#include "stdafx.h"
#include "BmpExporter.h"
#include "bmpfile.h"


BmpExporter::BmpExporter(void)
{
	
}

BmpExporter::BmpExporter(std::string path)
{
	fopen_s (&outfile, path.c_str() , "w");
}


BmpExporter::~BmpExporter(void)
{
	fclose(outfile);
}

size_t BmpExporter::export(ppm_image *img)
{	
    size_t n = 0;
    //n += fprintf(outfile, "P6\n# THIS IS A COMMENT\n%d %d\n%d\n", 
    //            img->width, img->height, 0xFF);
	//n += fwrite(img->data, sizeof(int8_t), img->width * img->height * 3, outfile);
    return n;
}

void BmpExporter::export2(ppm_image *image)
{
	FILE *f;
	unsigned char *img = NULL;
	int filesize = 54 + 3*image->width*image->height;  //w is your image width, h is image height, both int
	if( img )
		free( img );
	img = (unsigned char *)malloc(3*image->width*image->height);
	memset(img,0,sizeof(img));

	for(int i=0; i<image->width*image->height; i++)
	{
		img[i*3+2] = image->data[i].r;
		img[i*3+1] = image->data[i].g;
		img[i*3+0] = image->data[i].b;
	}

	unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0};
	unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0};
	unsigned char bmppad[3] = {0,0,0};

	bmpfileheader[ 2] = (unsigned char)(filesize    );
	bmpfileheader[ 3] = (unsigned char)(filesize>> 8);
	bmpfileheader[ 4] = (unsigned char)(filesize>>16);
	bmpfileheader[ 5] = (unsigned char)(filesize>>24);

	bmpinfoheader[ 4] = (unsigned char)(       image->width    );
	bmpinfoheader[ 5] = (unsigned char)(       image->width>> 8);
	bmpinfoheader[ 6] = (unsigned char)(       image->width>>16);
	bmpinfoheader[ 7] = (unsigned char)(       image->width>>24);
	bmpinfoheader[ 8] = (unsigned char)(       image->height    );
	bmpinfoheader[ 9] = (unsigned char)(       image->height>> 8);
	bmpinfoheader[10] = (unsigned char)(       image->height>>16);
	bmpinfoheader[11] = (unsigned char)(       image->height>>24);

	//fopen_s(&f, "test.bmp","wb");
	fwrite(bmpfileheader,1,14,outfile);
	fwrite(bmpinfoheader,1,40,outfile);
	for(int i=0; i<image->height; i++)
	{
		fwrite(img+(image->width*(image->height-i-1)*3),3,image->height,outfile);
		fwrite(bmppad,1,(4-(image->width*3)%4)%4,outfile);
	}
	fclose(outfile);
}
