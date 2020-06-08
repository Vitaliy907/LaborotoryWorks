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