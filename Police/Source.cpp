#include<iostream>
#include<fstream>
#include<Windows.h>
#include<string>
#include<map>
#include<list>

#define delim "\n----------------------------------------------------\n" 
#define tab "\t" 
#define mymap std::map<std::string, std::list<Crime>>

class Crime;
void Print(mymap base);
void Add_crime(mymap& base, std::string num_auto, char* place, int id);
void Save(mymap base, const char filename[]);
mymap Load(const char* filename);
void Search(const mymap base, std::string find_num);
void Search_by_range(mymap Base, int Begin, int End);

const std::map<int, std::string> CRIMES =
{
	{0, "N/A"},
	{1, "Проезда на красный"},
	{2, "Привышение скорости"},
	{3, "Парковка в неположенном месте"},
	{4, "Пересечение сплошной"},
	{5, "Езда в нетрезвом виде"},
	{6, "Оскорбление офицера"},
	{7, "Ремень безопасности"}
};

class Crime
{
	int id; //статья
	std::string place; //место правонарушения
	std::string crime; //расшифровка статьи

public:
	int get_id()const
	{
		return id;
	}
	const std::string& get_place()const
	{
		return place;
	}
	const std::string& get_crime()const
	{
		return crime;
	}
	void set_id(int id)
	{
		if (id > CRIMES.size()) id = 0;
		this->id = id;
	}
	void set_place(const std::string& place)
	{
		this->place = place;
	}
	Crime(int id, const std::string& place)
	{
		set_id(id);
		set_place(place);
		crime = CRIMES.find(id)->second;
	}
	~Crime() {}
	void insert(int id, const std::string& place)
	{
		Crime d(id, place);	
	}
};

std::ostream& operator<<(std::ostream& os, const Crime& obj)
{
	std::cout.width(5);
	return os << obj.get_crime() << " " << tab << tab << obj.get_place();
}
std::ofstream& operator<<(std::ofstream& ofs, const Crime& obj)
{
	ofs << obj.get_id() << " " << obj.get_place();
	return ofs;
}

void main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::string num_auto; //номер автомабиля
	std::string searc_num; //искомый номер
	int star_of_range; //начало диапозона
	int end_of_range; //конец диапозона
	char place[256]; //место
	int id; //ID правонарушения
	char filename[80] = "Crime.txt";

	mymap base =
	{
		{"m777ab", {Crime(1, "ул. Ленина"), Crime(2, "ул. Ленина"), Crime(4, "ул. Парижской коммуны")}},
		{"k231cc", {Crime(5, "ул. Карла Маркса"), Crime(6, "ул. Карла Маркса") }},
		{"p441oc", {Crime(3, "ул. Пролетарская"), Crime(7, "ул. Пролетарская") }}
	};

	Print(base);

	//Запрос данных
	//std::cout << "Введите номер машины: "; std::cin >> num_auto;
	//std::cout << "Введите место правонарушения: "; 
	//std::cin.ignore();
	//std::cin.getline(place, 256);	
	//std::cout << "Введите номер правонарушения согласно списку: " << std::endl << std::endl;
	//Вывод списка правонарушения для ввода
	//for (std::pair<int, std::string> cr : CRIMES)
	//	std::cout << cr.first << ". " << cr.second << std::endl;
	//Ввод правонарушения согласно индексу
	//std::cout << "\n-> "; std::cin >> id;

	//Add_crime(base, num_auto, place, id);
	//Print(base);
	//save(base, filename);
	//mymap base_load = load(filename);
	//Print(base_load);

	//std::cout << "Введите номер машины для поиска: "; std::cin >> searc_num;

	//Search(base, searc_num);

	std::cout << "Введите начало диапозона: "; std::cin >> star_of_range;
	std::cout << "Введите конец диапозона: "; std::cin >> end_of_range;

	Search_by_range(base, star_of_range, end_of_range);
}

void Add_crime(mymap& base, std::string num_auto, char *place, int id)
{
	std::map<std::string, std::list<Crime>>::iterator it; //Создание итератора для прохождения по дереву
	it = base.find(num_auto); //Поиск элемента дерева через "key"

	if (it != base.end())
	{
		it->second.push_back(Crime(id, place));
	}
	else
	{
		base.insert({ num_auto, {Crime(id, place)} });
	}
}

void Print(const mymap base)
{
	for (std::pair<std::string, std::list<Crime>> it : base)
	{
		std::cout << it.first << ":\n";
		for (Crime l_it : it.second)
		{
			std::cout << tab << l_it;
			std::cout << tab << std::endl;
		}
	}
	std::cout << std::endl;
}

void Save(mymap base, const char *filename)
{
	std::ofstream fout(filename); //Открываем поток для записи в файл
	for (std::pair<std::string, std::list<Crime>> it : base) //По циклу записываем ключи
	{
		fout << it.first <<":\t";
		for (Crime l_it : it.second) fout << l_it << ",";
		fout.seekp(-1, std::ios::cur); //смещаем курсор на позицию влево
		fout << ";\n";
	}
	fout.close(); //Закрываем поток
	std::string command = "start notepad ";
	command += filename;
	system(command.c_str()); //Открываем созданный файл
}

mymap Load(const char* filename)
{
	std::map<std::string, std::list<Crime>> base;
	std::string licence_plate;
	std::string all_crimes;

	std::ifstream fin(filename);
	if (fin.is_open())
	{
		while (!fin.eof())
		{
			std::getline(fin, licence_plate, ':');
			if (licence_plate.empty()) continue;
			fin.ignore();
			std::getline(fin, all_crimes);
			size_t start = 0;
			size_t end = 0;
			while (end != std::string::npos)
			{
				end = all_crimes.find(',');
				std::string s_crime = all_crimes.substr(0, end);
				if (all_crimes.empty()) break;
				int id = std::stoi(s_crime, nullptr, 10);
				s_crime.erase(0, s_crime.find_first_of(' ') + 1);
				base[licence_plate].push_back(Crime(id, s_crime));
				all_crimes.erase(0, end + 1);
			}
		}
		fin.close();
	}
	return base;
}

void Search(const mymap base, std::string find_num)
{
	mymap::const_iterator it; //Создание итератора для прохождения по дереву
	it = base.find(find_num);
	if (it != base.end())
	{
		std::cout << it->first << ":" << std::endl;
		for (Crime l_it : it->second)
		{
			std::cout << tab << l_it;
			std::cout << tab << std::endl;
		}
	}
	else
	{
		std::cout << "Данного номера в базе нет" << std::endl;
	}
}

void Search_by_range( const mymap Base, int Begin, int End)
{
	mymap::const_iterator begin = Base.cbegin();
	for (int i = 0; i < (Begin >= 0 ? Begin : Begin = 0); i++)//в цикле провека, чтобы не вылететь за пределы дерева
		begin++;
	mymap::const_iterator end = Base.cbegin();
	for (int i = 0; i <= (End<=Base.size()-1 ? End : Base.size()-1); ++i)//в цикле провека, чтобы не вылететь за пределы дерева
		end++;

	for (begin; begin != end; ++begin)
	{
		std::cout << begin->first << ":\n";
		for (Crime l_it : begin->second)
		{
			std::cout << tab << l_it;
			std::cout << tab << std::endl;
		}
	}
}