#define _CRT_SECURE_NO_WARNINGS
#include "LZW.h"
#include "Image.h"



Image::Image() {

	pixels = NULL;
	_name = NULL;
	_nameOut = NULL;
}


//Cai dat pixel
int Image::SetPixel(int row, int col, Color color)
{
	if (row < 0 || row >= height
		|| col < 0 || col >= width)
		return 0;

	// color: B, G, R
	int offset = (height - 1 - row) * rowSize + col * 3;
	pixels[offset] = color.B;
	pixels[offset + 1] = color.G;
	pixels[offset + 2] = color.R;
}

//lay pixel
Image::Color Image::GetPixel(int row, int col)
{

	Color color;
	//Trong day se luu nguoc lai RGB -> BGR
	int offset = (height - 1 - row) * rowSize + col * 3;
	color.B = pixels[offset];
	color.G = pixels[offset + 1];
	color.R = pixels[offset + 2];

	return color;
}


// Doc anh
int Image::LoadBitmap()
{

	FILE* f = fopen(_name, "rb");
	if (f == NULL)
		return -1;

	// read BMFHeader
	BMFHeader bmfhd;

	if (fread(&bmfhd, sizeof(BMFHeader), 1, f) == 0)
		return 0;

	if (bmfhd.signature[0] != 'B' || bmfhd.signature[1] != 'M')
		return 0;

	// read DIBHeader
	DIBHeader dibhd;

	if (fread(&dibhd, sizeof(DIBHeader), 1, f) == 0)
		return 0;

	if (dibhd.colorDepth != 24 || dibhd.height < 0)
		return 0;

	// read pixels (24 iblockts = 3 bytes/pixel)
	width = dibhd.width;
	height = dibhd.height;

	rowSize = ((3 * width + 3) / 4) * 4;

	pixels = new unsigned char[height * rowSize]; // luu thanh mang 1 chieu
	if (pixels == NULL)
		return 0;

	fseek(f, bmfhd.pixelAddress, SEEK_SET);
	if (fread(pixels, rowSize, height, f) < height)
		return 0;

	fclose(f);

	return 1;
}

int Image::SaveBitmap()
{

	FILE* f = fopen(_nameOut, "wb");
	if (f == NULL)
		return 0;

	// write BMFHeader	
	BMFHeader bmfhd;
	bmfhd.signature[0] = 'B';
	bmfhd.signature[1] = 'M';
	bmfhd.size = sizeof(BMFHeader) + sizeof(DIBHeader) + rowSize * height;
	bmfhd.reserved = 0;

	bmfhd.pixelAddress = sizeof(BMFHeader) + sizeof(DIBHeader);
	if (fwrite(&bmfhd, sizeof(BMFHeader), 1, f) == 0)
		return 0;

	// write DIBHeader
	DIBHeader dibhd;
	dibhd.size = sizeof(DIBHeader);
	dibhd.width = width;
	dibhd.height = height;
	dibhd.colorPlane = 1;
	dibhd.colorDepth = 24;
	memset(&dibhd.reserved, 0, sizeof(dibhd.reserved));
	if (fwrite(&dibhd, sizeof(DIBHeader), 1, f) == 0)
		return 0;

	// write pixels
	if (fwrite(pixels, height, rowSize, f) < height)
		return 0;

	fclose(f);

	return 1;
}



Image::~Image() {

	if (pixels)
		delete[] pixels;
}


//chuyen tu string sang char*
char* Image::stringtoChar(string in) {

	char* out = new char[in.size() + 1];

	for (int i = 0; i < in.size(); i++)
		out[i] = in[i];
	out[in.size()] = '\0';
	
	return out;
}

//Chuyen tu RGB sang YCrCb 
void Image::RGBtoYCbCr(vector <float>& block, size_t _pos) {

	size_t offset = _pos * 64 * channels;

	vector<float> blockCurr;
	blockCurr.insert(blockCurr.end(), block.begin() + offset, block.begin() + offset + 64 * channels);

	for (size_t i = 0; i < 64 * channels; i += channels){
		//Y
		block[offset + i] = 0.f + 0.299f * blockCurr[i] + 0.587f * blockCurr[i + 1] + 0.114f * blockCurr[i + 2];
		//Cb
		block[offset + i + 1] = 128.f - 0.168736f * blockCurr[i] - 0.331264f * blockCurr[i + 1] + 0.5f * blockCurr[i + 2];
		//Cr
		block[offset + i + 2] = 128.f + 0.5f * blockCurr[i] - 0.418688f * blockCurr[i + 1] - 0.081312f * blockCurr[i + 2];
	}

}

//Chuyen ket tuong ung
void Image::UnionChannels(vector<float>& block, size_t block_id)
{
	size_t offset = block_id * 64 * channels;
	
	vector<float> blockCurr;
	blockCurr.insert(blockCurr.end(), block.begin() + offset, block.begin() + offset + 64 * channels);

	//Co 3 kenh mau RGB
	for (size_t c = 0; c < 3; ++c)
		for (size_t i = 0; i < 64; i++)
			block[offset + c * 64 + i] = blockCurr[i * 3 + c];
}


void Image::DCT(vector<float>& block, size_t block_id, size_t channel)
{
	//Bang he so cos
	size_t len = 64;
	size_t w = 8, h = 8;
	vector<float> radius(len);
	for (size_t x = 0; x < h; ++x)
		for (size_t u = 0; u < w; ++u)
			radius[u * w + x] = .5f * cos((2 * x + 1) * u * pi / 16.f) * (u == 0 ? 1.0 / sqrt(2) : 1);

	size_t offset = block_id * 64 * channels + channel * 64;
	vector<float> blockCurr;
	blockCurr.insert(blockCurr.end(), block.begin() + offset, block.begin() + offset + 64);
	vector <float> temp(64, 0.f);

	for (size_t e = 0; e < 64; ++e)
		blockCurr[e] -= 128.f;

	for (size_t i = 0; i < 8; i++)
		for (size_t j = 0; j < 8; j++)
			for (size_t k = 0; k < 8; ++k)
				temp[i * 8 + j] += radius[i * 8 + k] * blockCurr[k * 8 + j];

	
	for (size_t e = 0; e < 64; ++e)
		blockCurr[e] = 0.f;

	for (size_t i = 0; i < 8; i++)
		for (size_t j = 0; j < 8; j++)
			for (size_t k = 0; k < 8; ++k)
				blockCurr[i * 8 + j] += temp[i * 8 + k] * radius[j * 8 + k];

	for (size_t e = 0; e < 64; ++e)
		block[offset + e] = blockCurr[e];
}

//Luong tu hoa
void Quantize(vector<float>& block, size_t block_id, size_t channel, float quality)
{
	size_t offset = block_id * 64 * channels + channel * 64;

	for (size_t i = 0; i < 64; ++i) {

		//Thang y
		if (channel == 1)
			block[offset + i] = round(block[offset + i] / LuminanceComponent[i] * quality);
		else {
			block[offset + i] = round(block[offset + i] / ChrominanceComponent[i] * quality);
		}

	}
}

//in theo hinh zigzac
void Image::Zigzag(vector<float>& block, size_t block_id, size_t channel)
{
	size_t offset = block_id * 64 * channels + channel * 64;
	vector<float> blockCurr;
	blockCurr.insert(blockCurr.end(), block.begin() + offset, block.begin() + offset + 64);

	for (size_t e = 0; e < 64; ++e)
		block[offset + e] = blockCurr[zigzacMatrix[e]];
}


int Image::Compress(float quality) {


	int widthBlock = width % 8 == 0 ? width / 8 : width / 8 + 1;
	int heightblock = height % 8 == 0 ? height / 8 : height / 8 + 1;

	//chia thanh cac khoi 8x8, co 3 kenh mau
	vector<float> blocks(widthBlock * heightblock * 64 * channels, 0.f);

	//Dau tien chia cac khoi co cac thang mau xen ke [R, G, B] x 64 x 64 x 64
	for (size_t i = 0; i < height; i++)
	{
		for (size_t j = 0; j < width; j++)
		{
			size_t iblock = i / 8, bj = j / 8;
			size_t ii = i - 8 * iblock, jj = j - 8 * bj;

			Color color = GetPixel(i, j);
			blocks[((iblock * widthBlock + bj) * 64 + (ii * 8 + jj)) * channels] = color.R;
			blocks[((iblock * widthBlock + bj) * 64 + (ii * 8 + jj)) * channels + 1] = color.G;
			blocks[((iblock * widthBlock + bj) * 64 + (ii * 8 + jj)) * channels + 2] = color.B;
		}
	}

	// bu cac canh thua
	for (size_t i = 0; i < height; i++)
	{
		for (size_t j = width; j < widthBlock * 8; j++)
		{
			size_t iblock = i / 8, bj = j / 8;
			size_t ii = i - 8 * iblock, jj = j - 8 * bj;

			Color color = GetPixel(i, width - 1);
			blocks[((iblock * widthBlock + bj) * 64 + (ii * 8 + jj)) * channels] = color.R;
			blocks[((iblock * widthBlock + bj) * 64 + (ii * 8 + jj)) * channels + 1] = color.G;
			blocks[((iblock * widthBlock + bj) * 64 + (ii * 8 + jj)) * channels + 2] = color.B;
		}
	}

	
	for (size_t i = height; i < heightblock * 8; i++)
	{
		for (size_t j = 0; j < widthBlock * 8; j++)
		{
			size_t iblock = i / 8, bj = j / 8;
			size_t ii = i - 8 * iblock, jj = j - 8 * bj;


			Color color = GetPixel(height - 1, j);
			blocks[((iblock * widthBlock + bj) * 64 + (ii * 8 + jj)) * channels] = color.R;
			blocks[((iblock * widthBlock + bj) * 64 + (ii * 8 + jj)) * channels + 1] = color.G;
			blocks[((iblock * widthBlock + bj) * 64 + (ii * 8 + jj)) * channels + 2] = color.B;
		}
	}
	//--------------------------------------------------------

	

	// RGB to YCrCb
	for (size_t i = 0; i < heightblock; i++)
		for (size_t j = 0; j < widthBlock; j++)
			RGBtoYCbCr(blocks, i * widthBlock + j);

	
	// chuyen ve format
	// [Y x 64] [Cr x64] [Cb x64] 

	for (size_t i = 0; i < heightblock; i++)
		for (size_t j = 0; j < widthBlock; j++)
			UnionChannels(blocks, i * widthBlock + j);

	// bien doi fourier roi rac
	for (size_t i = 0; i < heightblock; i++)
		for (size_t j = 0; j < widthBlock; j++)
			for (size_t k = 0; k < 3; ++k)
				DCT(blocks, i * widthBlock + j, k);



	//Luong tu hoa
	for (size_t i = 0; i < heightblock; i++)
		for (size_t j = 0; j < widthBlock; j++)
			for (size_t k = 0; k < channels; ++k)
				Quantize(blocks, i * widthBlock + j, k, quality);

	

	//In theo hinh zigzac
	for (size_t i = 0; i < heightblock; i++)
		for (size_t j = 0; j < widthBlock; j++)
			for (size_t c = 0; c < channels; ++c)
				Zigzag(blocks, i * widthBlock + j, c);

	//Nen theo LZW
	int check = LZW::encoding(blocks, width, height, quality, _nameOut);
	if (check == 1) {

		cout << space << "Ten file nen la: " << _nameOut << "\n";
		return 1;
	}

	if (!check)
		return 0;
}

//giai zigzac
void Image::Unzigzag(vector<float>& block, size_t block_id, size_t channel)
{
	size_t offset = block_id * 64 * channels + channel * 64;
	vector<float> blockCurr;
	blockCurr.insert(blockCurr.end(), block.begin() + offset, block.begin() + offset + 64);

	for (size_t e = 0; e < 64; ++e)
		block[offset + zigzacMatrix[e]] = blockCurr[e];
}

//Giai luong tu hoa
void Image::Dequantize(vector<float>& block, size_t block_id, size_t channel, float quality)
{
	size_t offset = block_id * 64 * channels + channel * 64;

	for (size_t e = 0; e < 64; ++e) {
		if (channel == 1)
			block[offset + e] *= LuminanceComponent[e] / quality;
		else {

			block[offset + e] *= ChrominanceComponent[e] / quality;
		}
	}
}

//bien doi fourier nguoc
void Image::IDCT(vector<float>& block, size_t block_id, size_t channel)
{

	size_t n = 64;
	size_t w = 8, h = 8;
	vector<float> radius(n);
	for (size_t x = 0; x < h; ++x)
		for (size_t u = 0; u < w; ++u)
			radius[u * w + x] = .5f * cos((2 * x + 1) * u * pi / 16.f) * (u == 0 ? 1.0 / sqrt(2) : 1);

	size_t offset = block_id * 64 * channels + channel * 64;
	vector<float> blockCurr;
	blockCurr.insert(blockCurr.end(), block.begin() + offset, block.begin() + offset + 64);
	vector <float> temp(64, 0.f);

	for (size_t i = 0; i < 8; i++)
		for (size_t j = 0; j < 8; j++)
			for (size_t k = 0; k < 8; ++k)
				temp[i * 8 + j] += radius[k * 8 + i] * blockCurr[k * 8 + j];

	for (size_t i = 0; i < 64; ++i)
		blockCurr[i] = 0.f;

	for (size_t i = 0; i < 8; i++)
		for (size_t j = 0; j < 8; j++)
			for (size_t k = 0; k < 8; ++k)
				blockCurr[i * 8 + j] += temp[i * 8 + k] * radius[k * 8 + j];


	for (size_t e = 0; e < 64; ++e)
		block[offset + e] = blockCurr[e] + 128.f;
}

// [r]x64, [g]x64, [b]x64 =>  [r, g, b] x 64 x 64 x 64
void Image::ScatterChannels(vector<float>& block, size_t block_id)
{
	size_t offset = block_id * 64 * channels;
	
	vector<float> blockCurr;
	blockCurr.insert(blockCurr.end(), block.begin() + offset, block.begin() + offset + 64 * channels);

	for (size_t c = 0; c < 3; ++c)
		for (size_t i = 0; i < 64; i++)
			block[offset + i * 3 + c] = blockCurr[c * 64 + i];
}

// YCbCr to RGB
void Image::YCCtoRGB(vector<float>& block, size_t block_id)
{
	size_t offset = block_id * 64 * channels;

	vector<float> blockCurr;
	blockCurr.insert(blockCurr.end(), block.begin() + offset, block.begin() + offset + 64 * channels);

	for (size_t e = 0; e < 64 * channels; e += channels)
	{
		block[offset + e + 0] = blockCurr[e] + 1.402f * (blockCurr[e + 2] - 128.f);
		block[offset + e + 1] = blockCurr[e] - 0.344136f * (blockCurr[e + 1] - 128.f) - 0.714136f * (blockCurr[e + 2] - 128.f);
		block[offset + e + 2] = blockCurr[e] + 1.772f * (blockCurr[e + 1] - 128.f);
	}

}


int Image::Decoding()
{
	int checkDecompress = 1;
	vector <float> blocks = LZW::decoding(_name, checkDecompress);

	if (checkDecompress == 0) {
		cout << space << "Khong the tai file\n";
		return 0;
	}
	if (checkDecompress == -1) {

		cout << space << "Day khong phai ma hoa do chuong trinh chung toi lam\n";
		return -1;
	}

	fstream fs(_name, ios::in | ios::binary);


	
	float quality;
	//khong su dung so nay
	int ignore;
	fs >> ignore;

	fs >> width;
	fs >> height;
	fs >> quality;
	fs.close();

	int widthBlock = width % 8 == 0 ? width / 8 : width / 8 + 1;
	int heightblock = height % 8 == 0 ? height / 8 : height / 8 + 1;


	// Unzigzag
	for (size_t i = 0; i < heightblock; i++)
		for (size_t j = 0; j < widthBlock; j++)
			for (size_t c = 0; c < channels; ++c)
				Unzigzag(blocks, i * widthBlock + j, c);


	// Dequantize

	for (size_t i = 0; i < heightblock; i++)
		for (size_t j = 0; j < widthBlock; j++)
			for (size_t c = 0; c < channels; ++c)
				Dequantize(blocks, i * widthBlock + j, c, quality);




	// bien doi fourier nguoc
	for (size_t i = 0; i < heightblock; i++)
		for (size_t j = 0; j < widthBlock; j++)
			for (size_t c = 0; c < channels; ++c)
				IDCT(blocks, i * widthBlock + j, c);


	//  [Y x64] [Cb x64] [Cr x64] 
	for (size_t i = 0; i < heightblock; i++)
		for (size_t j = 0; j < widthBlock; j++)
			ScatterChannels(blocks, i * widthBlock + j);



	// YCrCb to RGB
	for (size_t i = 0; i < heightblock; i++)
		for (size_t j = 0; j < widthBlock; j++)
			YCCtoRGB(blocks, i * widthBlock + j);

	// chuyen sang pixel

	rowSize = ((3 * width + 3) / 4) * 4;

	pixels = new unsigned char[height * rowSize];

	for (size_t i = 0; i < height; i++)
	{
		for (size_t j = 0; j < width; j++)
		{
			size_t iblock = i / 8, bj = j / 8;
			size_t ii = i - 8 * iblock, jj = j - 8 * bj;

			Color color;
			color.R = blocks[((iblock * widthBlock + bj) * 64 + (ii * 8 + jj)) * channels] > 255 ? 255 : blocks[((iblock * widthBlock + bj) * 64 + (ii * 8 + jj)) * channels] < 0 ? 0 : unsigned char(blocks[((iblock * widthBlock + bj) * 64 + (ii * 8 + jj)) * channels]);
			color.G = blocks[((iblock * widthBlock + bj) * 64 + (ii * 8 + jj)) * channels + 1] > 255 ? 255 : blocks[((iblock * widthBlock + bj) * 64 + (ii * 8 + jj)) * channels + 1] < 0 ? 0 : unsigned char(blocks[((iblock * widthBlock + bj) * 64 + (ii * 8 + jj)) * channels + 1]);
			color.B = blocks[((iblock * widthBlock + bj) * 64 + (ii * 8 + jj)) * channels + 2] > 255 ? 255 : blocks[((iblock * widthBlock + bj) * 64 + (ii * 8 + jj)) * channels + 2] < 0 ? 0 : unsigned char(blocks[((iblock * widthBlock + bj) * 64 + (ii * 8 + jj)) * channels + 2]);

			SetPixel(i, j, color);

		}
	}


	
	
}


bool Image::InputImageEncoding() {

	cout << space << "Nhap ten cua anh: ";
	string tmp;
	cin.ignore();
	getline(cin, tmp);


	_name = new char[tmp.size()];

	strcpy(_name, tmp.c_str());

	//cat chuoi thanh file nen
	for (int i = 0; i < tmp.size(); i++)
		if (tmp[i] == '.') {
			tmp[i] = '\0';
			break;
		}
	_nameOut = stringtoChar(tmp);

	int check = LoadBitmap();
	if (check == 0) {
		cout << space << "File nay khong phai bitmap\n";
		return 0 ;
	}
	else
		if (check == -1) {
			cout << space << "Khong ton tai file anh nay\n";
			return 0;
		}
	cout << space << "Xin cho trong giay lat\n";

	int checkCompress = Compress(1);
	if (checkCompress)
		return 1;
	else
		return 0;
}

//Nhap file giai nen
bool Image::InputImageDecoding() {

	cout << space << "Nhap ten file nen: ";
	string tmp;
	cin.ignore();
	getline(cin, tmp);

	_name = stringtoChar(tmp);

	//cat chuoi thanh file nen
	tmp += "Decompress.bmp";
	_nameOut = stringtoChar(tmp);

	cout << space << "Xin cho trong giay lat\n";
	int checkDecode = Decoding();
	

	if (checkDecode == 0 || checkDecode == -1) {

		return 0 ;
	}
	
	
	int check = SaveBitmap();
	
	if (check == 0) {
		cout << space << "Khong the xuat file hinh anh\n";
		return 0;
	}


	cout << space << "Ten hinh anh sau khi giai nen: " << _nameOut << "\n";
	return 1;
}

