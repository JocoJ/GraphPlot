#include <stdio.h>
#include <exception>

#include "CImage.h"

static const Byte BasicHeader[] = {66, 77, 118, 21, 14, 0, 0, 0, 0, 0, 54, 0, 0, 0, 40,
									0, 0, 0, 68, 3, 0, 0, 112, 1, 0, 0, 1, 0, 24, 0, 0, 
									0, 0, 0, 64, 21, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
									0, 0, 0, 0, 0, 0};

union TakeBytes
{
	unsigned int value;
	Byte vector[4];
};

Byte *DataRead(char *fileName, long &fileSize)
{
	fileSize = 0;
	if(!fileName) return 0;
	FILE *fp = fopen(fileName, "rb");
	if(!fp)
	{
		printf("Error opening file");
		return 0;
	}
	fseek(fp, 0, SEEK_END);
	long nrBytes = ftell(fp);
	if(nrBytes <= 0)
	{
		printf("File empty");
		return 0;
	}
	rewind(fp);
	Byte *data;
	data = new Byte[nrBytes];
	long readResult = fread(data, sizeof(Byte), nrBytes, fp);
	if(readResult != nrBytes)
	{
		printf("Incorrect read");
		delete[] data;
		fclose(fp);
		return 0;
	}
	fileSize = readResult;
	fclose(fp);
	return data;
}

CImage::CImage(unsigned int width, unsigned int height) 
{
	mImage0 = new Byte[BMPHEADER + width*height*NO_OF_BYTES];
	mImage = mImage0+BMPHEADER;
	mLength = (width*height) * 3;
	mLength0 = mLength + BMPHEADER;
	
	for (int i = 0; i<BMPHEADER; ++i)
	{
		mImage0[i] = BasicHeader[i];
	}

	this->width = width;
	this->height = height;

	TakeBytes w,h;
	w.value = width;
	h.value = height;

	mImage0[18] = w.vector[0];
	mImage0[19] = w.vector[1];
	mImage0[20] = w.vector[2];
	mImage0[21] = w.vector[3];

	mImage0[22] = h.vector[0];
	mImage0[23] = h.vector[1];
	mImage0[24] = h.vector[2];
	mImage0[25] = h.vector[3];

	for (int i = 0; i< mLength; ++i)
	{
		mImage[i] = 255;
	}

	FILE *f = fopen("txt.out", "w");

	for (int i = 0; i< BMPHEADER; ++i)
	{
		fprintf(f, "%d\n", mImage0[i]);
	}

}

CImage::CImage(char* fileName)
{
	mImage0 = DataRead(fileName, mLength0);
	mImage = mImage0 + BMPHEADER;
	mLength = mLength0-BMPHEADER;

	TakeBytes wide, high;
	for (int i = 0;i<4; ++i)
	{
		wide.vector[i] = mImage0[i+18];
		high.vector[i] = mImage0[i+22];
	}

	width = wide.value;
	height = high.value;

	/*FILE *f = fopen("temp.out", "w");
	for (int i = 0; i<54; ++i)
	{
		fprintf(f, "%d\n", mImage0[i]);
	}*/
}

CImage::~CImage()
{
	delete[] mImage0;
	mImage = nullptr;
	mImage0 = nullptr;
}

long CImage::length()
{
	return mLength0;
}

void CImage::writeImage(const char* fileName)
{
	FILE *out = fopen(fileName, "wb");

	if (!out)
	{
		return;
	}
	fwrite(mImage0, sizeof(Byte), mLength0, out);
}

void CImage::putPixel(RGBColor color, unsigned int x, unsigned int y)
{
	if ((x*width + y)*3 < mLength)
	{
		mImage[3 * (x*width+y) + 0] = color.blue;
		mImage[3 * (x*width+y) + 1] = color.green;
		mImage[3 * (x*width+y) + 2] = color.red;
	}
}

long CImage::getHeight()
{
	return height;
}

long CImage::getWidth()
{
	return width;
}

void CImage::setHeight(long x)
{
	height = x;
}

void CImage::setWidth(long z)
{
	width = z;
}