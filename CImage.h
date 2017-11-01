#pragma once
//an image in the BMP format
#define BMPHEADER 54
#define NO_OF_BYTES 3
#define LOW_SIGNATURE 0x42
#define HIGH_SIGNATURE	0x4D
#define SIGNATURE 0x4D42
#define OFFSET 54
#define BITMAPINFOHEADER 40;
#define	BYTESELECT 0x000000FF

typedef unsigned char Byte;

struct RGBColor
{
	Byte red, green, blue;
};

class CImage
{
	Byte *mImage0;
	Byte *mImage;
	long mLength, mLength0;
	long width, height;
public:
	CImage(unsigned int width, unsigned int height);
	CImage(char* fileName);

	void putPixel(RGBColor color, unsigned int height_way, unsigned int width_way);

	void setWidth(long width);
	void setHeight(long height);

	long getWidth();
	long getHeight();

	long length();

	~CImage();

	void writeImage(const char * fileName);
};