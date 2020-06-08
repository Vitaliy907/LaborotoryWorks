МИНИСТЕРСТВО НАУКИ  И ВЫСШЕГО ОБРАЗОВАНИЯ РОССИЙСКОЙ ФЕДЕРАЦИИ  
Федеральное государственное автономное образовательное учреждение высшего образования  
"КРЫМСКИЙ ФЕДЕРАЛЬНЫЙ УНИВЕРСИТЕТ им. В. И. ВЕРНАДСКОГО"  
ФИЗИКО-ТЕХНИЧЕСКИЙ ИНСТИТУТ  
Кафедра компьютерной инженерии и моделирования
<br/><br/>
​
### Отчёт по лабораторной работе № 5<br/> по дисциплине "Программирование"
<br/>
​
студента 1 курса группы ИВТ-192(2)<br/>
Бородаев Виталий Олегович  
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



**Цель:**
1. Научиться работать с текстовыми файлами;
2. Закрепить навыки работы со структурами.

**Код программы:**

``` c++
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <stdlib.h>
using std::cin;
using std::cout;
using std::string;
#include <iostream>
#include<string>
#include<vector>
#include<fstream>
using namespace std;
struct human_data {
	int PassengerId;
	bool Survived;
	int Pclass;
	string Name;
	string	Sex;
	int Age;
	int	SibSp;
	int	Parch;
	int	Ticket;
	string Fare;
	string Cabin;
	string Embarked;
	void set_data(int i, std::string data) {

		switch (i) {
		case 0:
			PassengerId = atoi(data.c_str());
			break;
		case 1:
			Survived = atoi(data.c_str());
			break;
		case 2:
			Pclass = atoi(data.c_str());
			break;
		case 3:
			Name = data;
			break;
		case 4:
			Name = Name + data;
			break;
		case 5:
			Sex = data;
			break;
		case 6:
			Age = atoi(data.c_str());
			break;
		case 7:
			SibSp = atoi(data.c_str());
			break;
		case 8:
			Parch = atoi(data.c_str());
			break;
		case 9:
			Ticket = atoi(data.c_str());
			break;
		case 10:
			Fare = data;
			break;
		case 11:
			Cabin = data;
			break;
		case 12:
			Embarked = data;
			break;
		}

	}
};
int main()
{
	//human_data data;
	//human_data* ptr=&data;
	//data.PassengerId = 2;
	//data.Survived = true;
	//data.Pclass = 1;
	//cout << *ptr << *ptr + 1 << &ptr + 2;
	////cin >> data.Parch;
//	string to_str(&) {}
	int i = 0, counter_surv_male=0,counter_surv = 0;
	vector<human_data> data_human;
	human_data temp_data;
	string temp = "";
	ifstream trainScv("train.csv");
	char ch;
	string str;
	while (trainScv.get(ch)) {
		if (ch == '"')continue;
		//if ((temp[0] == '"') && (temp[1] == '"')) {
		//	if ((temp[temp.length()-2] == '"') &&(temp.length()!=2)&& (temp[temp.length() - 1] == '"')) {
		//		cout << temp << "\n";
		//		data_human[counter].set_data(i, temp);
		//		i++;
		//		temp = "";
		//		continue;
		//	}
		//}
		else if ((ch == ',')) {
			temp_data.set_data(i, temp);
			temp = "";
			i++;
			continue;
		}
		if (ch == '\n') {
			temp_data.set_data(i, temp);
			data_human.push_back(temp_data);
			temp = "";
			i = 0;
		}
		temp = temp + ch;
	}
	data_human.erase(data_human.begin());
	int number_of_survivors = 0, first_class_survivors = 0, two_class_survivors = 0, three_class_survivors = 0,
		male_survivors = 0, female_survivors = 0, age_male = 0, age_female = 0,
		average_age = 0, state_Cherbourg = 0, state_Queenstown = 0, state_Southampton = 0;
	string identifiers_minors = "", state;

	for (int i = 0; i < data_human.size(); i++) {
		number_of_survivors = number_of_survivors + data_human[i].Survived;
		if (data_human[i].Age > 0) {
			average_age += data_human[i].Age;
			counter_surv++;
		}
		if ((data_human[i].Age < 18)&&(data_human[i].Age>0)) {
			identifiers_minors += ","+std::to_string(data_human[i].PassengerId);
		}
		if (data_human[i].Embarked == "S")state_Southampton++;
		if (data_human[i].Embarked == "Q")state_Queenstown++;
		if (data_human[i].Embarked == "C")state_Cherbourg++;
		if ((data_human[i].Pclass == 1) && (data_human[i].Survived == 1))first_class_survivors++;
		if ((data_human[i].Pclass == 2) && (data_human[i].Survived == 1))two_class_survivors++;
		if ((data_human[i].Pclass == 3) && (data_human[i].Survived == 1))three_class_survivors++;
		if ((data_human[i].Sex == "female") && (data_human[i].Age > 0)) age_female += data_human[i].Age;
		if ((data_human[i].Sex == "male") && (data_human[i].Age > 0)) { 
			age_male += data_human[i].Age; 
			counter_surv_male++;
		}
		if ((data_human[i].Sex == "female") && (data_human[i].Survived == 1))female_survivors++;
		if ((data_human[i].Sex == "male") && (data_human[i].Survived == 1))male_survivors++;

	}
	if ((state_Southampton > state_Queenstown) && (state_Southampton > state_Cherbourg))state = "Southampton";
	else if ((state_Queenstown > state_Southampton) && (state_Queenstown > state_Cherbourg))state = "Queenstown";
	else state = "Cherbourg";
	identifiers_minors = identifiers_minors.substr(1, identifiers_minors.length() -1);
	ofstream out("outfile.txt", ios::out);
	out << "Общее число выживших: "<<number_of_survivors << endl;
	out << "Число выживших из 1 класса: " << first_class_survivors << endl;
	out << "Число выживших из 2 класса: " << two_class_survivors << endl;
	out << "Число выживших из 3 класса: " << three_class_survivors << endl;
	out << "Количество выживших женщин: " << female_survivors << endl;
	out << "Количество выживших мужчин: " << male_survivors << endl;
	out << "Средний возраст пассажира / женский / мужской: " <<average_age/counter_surv << " "
		<< age_female/ (counter_surv- counter_surv_male) << " " <<age_male/ counter_surv_male << endl;
	out << "Штат, в котором село больше всего пассажиров: " << state << endl;
	out << "Список идентификаторов несовершеннолетних: " << identifiers_minors << endl;
	out.close();
	data_human.clear();
	trainScv.close();

	return 0;

}

```

<a href="code/main/outfile.txt">Файл с результатами расчета</a>

<br/>

| Характеристика | Результат  |
|:-:|:-:|
| Общее число выживших | 342  |
| Число выживших из 1 класса | 136 |
| Число выживших из 2 класса | 87 |
| Число выживших из 3 класса | 119 |
| Количество выживших женщин | 233 |
| Количество выживших мужчин | 109 |
| Средний возраст пассажира | 29 |
| Средний возраст женский | 28 |
| Средний возраст мужчин | 31 |
| Штат, в котором село больше всего пассажиров: | Southampton |
| Список идентификаторов несовершеннолетних | 6,8,10,11,15,17,18,20,23,25,27,29,30,32,33,37,40,43,44,46,47,48,49,51,56,<br/>59,60,64,65,66,69,72,77,78,79,83,85,87,88,96,102,108,110,112,115,120,<br/>122,126,127,129,139,141,148,155,157,159,160,164,165,166,167,169,172,<br/>173,177,181,182,183,184,185,186,187,194,197,199,202,206,209,215,221,<br/>224,230,234,236,238,241,242,251,257,261,262,265,267,271,275,278,279,<br/>283,285,296,298,299,301,302,304,305,306,307,308,325,330,331,334,335,<br/>336,341,348,349,352,353,355,359,360,365,368,369,375,376,382,385,387,<br/>389,390,408,410,411,412,414,416,420,421,426,429,432,434,436,445,446,<br/>447,449,452,455,458,460,465,467,469,470,471,476,480,481,482,486,490,<br/>491,496,498,501,503,505,508,512,518,523,525,528,531,532,533,534,536,<br/>539,542,543,548,550,551,553,558,561,564,565,569,574,575,579,585,590,<br/>594,597,599,602,603,612,613,614,619,630,634,635,640,643,644,645,649,<br/>651,654,657,668,670,675,681,684,687,690,692,693,698,710,712,719,721,<br/>722,728,732,733,739,740,741,747,751,752,756,761,765,767,769,774,777,<br/>778,779,781,782,784,788,789,791,792,793,794,803,804,814,816,820,825,<br/>826,827,828,829,831,832,833,838,840,842,845,847,850,851,853,854,860,<br/>864,869,870,876,879,889 |

# Вывод
В данной работе получены навыки работы с текстовыми файлами, ознакомились с форматом ***CSV***, а также закреплены навыки работы со структурами