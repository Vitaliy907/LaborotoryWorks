МИНИСТЕРСТВО НАУКИ  И ВЫСШЕГО ОБРАЗОВАНИЯ РОССИЙСКОЙ ФЕДЕРАЦИИ  
Федеральное государственное автономное образовательное учреждение высшего образования  
"КРЫМСКИЙ ФЕДЕРАЛЬНЫЙ УНИВЕРСИТЕТ им. В. И. ВЕРНАДСКОГО"  
ФИЗИКО-ТЕХНИЧЕСКИЙ ИНСТИТУТ  
Кафедра компьютерной инженерии и моделирования
<br/><br/>
​
### Отчёт по лабораторной работе № 3<br/> по дисциплине "Программирование"
<br/>
​
студента 1 курса группы ИВТ-б-о-192(2)<br/>
Бородаев Виталий Олегович<br/><br/>
направления подготовки 09.03.01 "Информатика и Вычислительная Техника"
<br/>
​
<table>
<tr><td>Научный руководитель<br/> старший преподаватель кафедры<br/> компьютерной инженерии и моделирования</td>
<td>(оценка)<br/></td>
<td>Чабанов В.В.</td>
</tr>
</table>
<br/><br/>

Симферополь, 2020
<br/><br/>

-------

# Дешифровка текста из изображения

## Цель:
- Закрепить навыки разработки программ использующих операторы цикла;
- Закрепить навыки разработки программ использующих массивы;
- Освоить методы подключения сторонних библиотек.
## Постановка задачи
- Напишите на языке С++ программу, которая по заданному изображению и ключу восстанавливает исходное текстовое сообщение (Си-строка)зашифрованное в изображении.
## Ход работы

### Исходное изображение

<img src="resources/pic4.bmp">


### Ключ для дешифровки

При помощи данного ключа была получена последовательность символов исходного текста: <br>
`11r 11g 11b 10r 10g 10b 01r 01g`

### Зашифрованный текст

```
James Madison Jr. (March 16, 1751[b] Ц June 28, 1836) was an American statesman, lawyer, diplomat, philosopher and Founding Father who served as the fourth president of the United States from 1809 to 1817. He is hailed as the "Father of the Constitution" for his pivotal role in drafting and promoting the Constitution of the United States and the United States Bill of Rights. He co-wrote The Federalist Papers, co-founded the Democratic-Republican Party, and served as the fifth United States secretary of State from 1801 to 1809.
Born into a prominent Virginia planter family, Madison served as a member of the Virginia House of Delegates and the Continental Congress during and after the American Revolutionary War. He became dissatisfied with the weak national government established by the Articles of Confederation and helped organize the Constitutional Convention, which produced a new constitution to supplant the Articles of Confederation. Madison's Virginia Plan served as the basis for the Constitutional Convention's deliberations, and he was one of the most influential individuals at the convention. Madison became one of the leaders in the movement to ratify the Constitution, and he joined with Alexander Hamilton and John Jay in writing The Federalist Papers, a series of pro-ratification essays that is widely considered to be one of the most influential works of political science in American history.
After the ratification of the Constitution, Madison emerged as an important leader in the United States House of Representatives and served as a close adviser to President George Washington. He was the main force behind the ratification of the United States Bill of Rights, which enshrines guarantees of personal freedoms and rights within the Constitution. During the early 1790s, Madison came to oppose the economic program and accompanying centralization of power favored by Secretary of the Treasury Alexander Hamilton. Along with Thomas Jefferson, Madison organized the Democratic-Republican Party, which was, alongside Hamilton's Federalist Party, one of the nation's first major political parties. After Jefferson won the 1800 presidential election, Madison served as secretary of State from 1801 to 1809. In that position, he supervised the Louisiana Purchase, which doubled the size of the United States.
Madison succeeded Jefferson with a victory in the 1808 presidential election. After diplomatic protests and a trade embargo failed to end British attacks against American shipping, he led the United States into the War of 1812. The war was an administrative morass and ended inconclusively, but many Americans saw it as a successful "second war of independence" against Britain. The war convinced Madison of the necessity of a stronger federal government, and he presided over the creation of the Second Bank of the United States and the enactment of the protective Tariff of 1816. He retired from public office in 1817 and died in 1836. Madison is considered to be one of the most important Founding Fathers of the United States, and historians have generally ranked him as an above-average president.
```

### Исходный код программы

Исходный код также доступен по [этой ссылке](code/main.cpp)

```cpp
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
```

