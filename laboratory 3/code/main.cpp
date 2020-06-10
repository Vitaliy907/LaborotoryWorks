#include <iostream>
#include <bitset>
#include <vector>
#include "libs/libbmp.h"

using namespace std;

int color_counter = 0;

enum COLORSID{
	RED,
	GREEN,
	BLUE
};

struct Pixel{
	int x = 0;
	int y = 0;
};

unsigned char get_pixel(BmpImg image, Pixel fetch_pixel, COLORSID col_id){
	switch (col_id)
	{
	case COLORSID::RED:
		return image.red_at(fetch_pixel.x, fetch_pixel.y);
	case COLORSID::GREEN:
		return image.green_at(fetch_pixel.x, fetch_pixel.y);
	case COLORSID::BLUE:
		return image.blue_at(fetch_pixel.x, fetch_pixel.y);
	}
}

std::vector<unsigned char> raw_bits_array;

int main()
{
	BmpImg Image;
	if (Image.read(R"(../resources/pic4.bmp)") != BmpError::BMP_OK) return EXIT_FAILURE;

	int null_term_counter = 0;
	
	for (int i = Image.get_width() - 1; i >= 0; i--)
	{
		for (int j = Image.get_height() - 1; j >= 0; j--)
		{
			Pixel pixel_to_get{ i, j };
			for (int k = 0; k < 3; k++) {
				bitset<8> color_pixel = get_pixel(Image, pixel_to_get, (COLORSID)k);
				raw_bits_array.push_back(color_pixel[0]);
				if (!color_pixel[0])
					null_term_counter++;
				else
					null_term_counter = 0;
				if (null_term_counter == 8)
					goto exitmark;	
			}
		}
	}
	exitmark:

	std::string decrypted_text;

	for (int i = 0; i < raw_bits_array.size() - 8; i += 8){
		bitset<8> new_char;
		for (int j = 0; j < 8; j++) {
			new_char.set(8 - j - 1, raw_bits_array[i + j]);
		}
		decrypted_text += (char)new_char.to_ulong();
	}

	cout << decrypted_text;

}