#include<iostream>
#include<fstream>
#include<windows.h>
#include<DirectXTex.h>
using namespace std;
using namespace DirectX;
void save_file()
{
	//~~~~读取TGA纹理
	TexMetadata new_data;
	ScratchImage new_image;
	HRESULT hr = DirectX::LoadFromTGAFile(L"test.tga", &new_data, new_image);
	int pixel_size = new_image.GetPixelsSize();
	uint8_t* pixel_data = new_image.GetPixels();
	for (int i = 0; i < pixel_size / 4; ++i)
	{
		pixel_data[i * 4 + 3] = rand() % 255;
	}
	//~~~~读取二进制数据
	ifstream inF;
	int size;
	// C++获取文件大小方法四  
	HANDLE handle = CreateFile(L"111.zip", FILE_READ_EA, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
	if (handle != INVALID_HANDLE_VALUE)
	{
		size = GetFileSize(handle, NULL);
		CloseHandle(handle);
	}
	char* data = new char[size];
	inF.open("111.zip", std::ifstream::binary);
	inF.read(data, sizeof(char) * size);
	inF.close();
	cout << size << endl;
	int magic_start = size / 3.1415926;
	if (size < pixel_size / 4)
	{
		for (int i = 0; i < magic_start; ++i)
		{
			int magic_save = static_cast<int>(data[i]) + 128;
			int pixel_count = ((pixel_size / 4) - i - 1) * 4 + 3;
			pixel_data[pixel_count] = magic_save;
		}

		for (int i = magic_start; i < size; ++i)
		{
			int usigned_save = static_cast<int>(data[i]) + 128;
			int new_count = i - magic_start;
			pixel_data[new_count * 4 + 3] = usigned_save;
		}

	}
	DirectX::SaveToTGAFile(new_image.GetImages()[0], L"test2.tga");

}
int main()
{
	save_file();
	read_file();

	return 0;
}