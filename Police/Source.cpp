#include<iostream>
#include<fstream>
#include<Windows.h>
#include<string>
#include<map>
#include<list>

#define delim "\n----------------------------------------------------\n" 
#define tab "\t" 

class Crime;
void Print(std::map<std::string, std::list<Crime>> base);
void Add_crime(std::map<std::string, std::list<Crime>>& base, std::string num_auto, char* place, int id);
void save(std::map<std::string, std::list<Crime>> base, const char filename[]);

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
	return os << "(" << obj.get_id() << ") " << obj.get_crime() << " " << tab << tab << obj.get_place();
}

void main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::string num_auto; //номер автомабиля
	char place[256]; //место
	int id; //ID правонарушения
	char filename[80] = "Crime.txt";

	std::map<std::string, std::list<Crime>> base =
	{
		{"m777ab", {Crime(1, "ул. Ленина"), Crime(2, "ул. Ленина"), Crime(4, "ул. Парижской коммуны")}},
		{"k231cc", {Crime(5, "ул. Карла Маркса"), Crime(6, "ул. Карла Маркса") }},
		{"p441oc", {Crime(3, "ул. Пролетарская"), Crime(7, "ул. Пролетарская") }}
	};

	Print(base);

	//Запрос данных
	std::cout << "Введите номер машины: "; std::cin >> num_auto;
	std::cout << "Введите место правонарушения: "; 
	std::cin.ignore();
	std::cin.getline(place, 256);	
	std::cout << "Введите номер правонарушения согласно списку: " << std::endl << std::endl;
	//Вывод списка правонарушения для ввода
	for (std::pair<int, std::string> cr : CRIMES)
		std::cout << cr.first << ". " << cr.second << std::endl;
	//Ввод правонарушения согласно индексу
	std::cout << "\n-> "; std::cin >> id;

	Add_crime(base, num_auto, place, id);
	Print(base);
	save(base, filename);
}

void Add_crime(std::map<std::string, std::list<Crime>>& base, std::string num_auto, char *place, int id)
{
	std::map<std::string, std::list<Crime>>::iterator it; //Создание итератора для прохождения по дереву
	it = base.find(num_auto); //Поиск элемента дерева через "key"

	if (it != base.end())
	{
		std::list<Crime> temp;	//
		temp = (it->second);	// Создаём временные список для храннеия значений дерева по найденному ключу 
		temp.push_back(Crime(id, place)); //Добавляем в список новый элемент
		base.insert_or_assign(it->first, temp); //Перезаписываем значения в дереве по найденному ключу
	}
	else
	{
		base.insert({ num_auto, {Crime(id, place)} }); //Добавляем новый элемент в дерево
	}
}

void Print(std::map<std::string, std::list<Crime>> base)
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

void save(std::map<std::string, std::list<Crime>> base, const char *filename)
{
	std::ofstream fout(filename); //Открываем поток для записи в файл
	for (std::pair<std::string, std::list<Crime>> it : base) //По циклу записываем ключи
	{
		fout << it.first << ":\n";
		for (Crime l_it : it.second) //По циклу записываем значения
		{
			fout << tab << l_it;
			fout << tab << std::endl;
		}
	}
	fout.close(); //Закрываем поток
	std::string command = "start notepad ";
	command += filename;
	system(command.c_str()); //Открываем созданный файл
}