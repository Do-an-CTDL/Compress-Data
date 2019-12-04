#pragma once

#include <iomanip>

#pragma pack(1)

#define pi 3.14159265358979324
#define channels 3

//Do choi
const uint8_t ChrominanceComponent[64] =
{17, 18, 24, 47, 99, 99, 99, 99 ,
 18, 21, 26, 66, 99, 99, 99, 99,
 24, 26, 56, 99, 99, 99, 99, 99,
 47, 66, 99, 99, 99, 99, 99, 99,
 99, 99, 99, 99, 99, 99, 99, 99,
 99, 99, 99, 99, 99, 99, 99, 99,
99, 99, 99, 99, 99, 99, 99, 99,
 99, 99, 99, 99, 99, 99, 99, 99 };

//Luong tu khoa sac do
const uint8_t LuminanceComponent[64]{
	 16,  11,  10,  16,  24,  40,  51,  61,
	 12,  12,  14,  19,  26,  58,  60,  55,
	 14,  13,  16,  24,  40,  57,  69,  56,
	 14,  17,  22,  29,  51,  87,  80,  62,
	 18,  22,  37,  56,  68, 109, 103,  77,
	 24,  35,  55,  64,  81, 104, 113,  92,
	 49,  64,  78,  87, 103, 121, 120,  101,
	 72,  92,  95,  98, 112, 100, 103,  99,
};

const int zigzacMatrix[64]{
	0,1,8,16,9,2,3,10,
	17,24,32,25,18,11,4,5,
	12,19,26,33,40,48,41,34,
	27,20,13,6,7,14,21,28,
	35,42,49,56,57,50,43,36,
	29,22,15,23,30,37,44,51,
	58,59,52,45,38,31,39,46,
	53,60,61,54,47,55,62,63,
};





class Image{
private:
	//3 thang mau chinh
	struct Color
	{
		unsigned char R, G, B;
	};

	//Data Information bitmap header
	struct DIBHeader
	{
		unsigned int size;
		unsigned int width;
		unsigned int height;
		unsigned short colorPlane;
		unsigned short colorDepth;
		unsigned char reserved[24];
	};

	struct BMFHeader
	{
		char signature[2]; //2 bit dau là BM
		unsigned int size; // kích thước
		unsigned int reserved; // không sử dụng
		unsigned int pixelAddress; // Địa chỉ của pixel
	};

	char* stringtoChar(string);
private:

	char* _name;
	char* _nameOut;
	size_t width;//chieu rong
	size_t height;// chieu cao
	size_t rowSize;
	unsigned char* pixels;
private:

	//Nen 
	void RGBtoYCbCr(vector <float>&, size_t);
	void UnionChannels(vector<float>& , size_t );
	void DCT(vector<float>& , size_t , size_t );
	void Zigzag(vector<float>& , size_t , size_t );
private:

	//Giai nen
	void Unzigzag(vector<float>& , size_t , size_t );
	void Dequantize(vector<float>& , size_t , size_t , float );
	void IDCT(vector<float>& , size_t , size_t );
	void ScatterChannels(vector<float>& , size_t );
	void YCCtoRGB(vector<float>& , size_t );
public:

	~Image();
	Image();
public:

	int SetPixel(int , int , Color );
	Color GetPixel(int , int );
public:

	int Compress(float );
	int Decoding();
public:

	int LoadBitmap();
	int SaveBitmap();
public:

	bool InputImageEncoding();
	bool InputImageDecoding();
};




