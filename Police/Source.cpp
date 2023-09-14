#include<iostream>
#include<map>
#include<list>

#define delim "\n----------------------------------------------------\n" 
#define tab "\t" 

const std::map<int, std::string> CRIMES =
{
	{0, "N/A"},
	{1, "Проезда на красный"},
	{2, "Привышение скорости"},
	{3, "Парковка в неположенномм месте"},
	{4, "Пересечение спложной"},
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

void print(std::map<std::string, std::list<Crime>> base)
{
	for (std::pair<std::string, std::list<Crime>> it : base)
	{
		std::cout <<  it.first << ":\n";
		for (Crime l_it : it.second)
		{
			std::cout << tab << l_it; 
			std::cout << tab << std::endl;
		}
	}
	std::cout << std::endl;
}

void main()
{
	setlocale(LC_ALL, "");
	std::map<std::string, std::list<Crime>>::iterator it;
	std::string num_auto;
	std::string place;
	int id;

	std::map<std::string, std::list<Crime>> base =
	{
		{"m777ab", {Crime(1, "ул. Ленина"), Crime(2, "ул. Ленина"), Crime(4, "ул. Парижской коммуны")}},
		{"k231cc", {Crime(5, "ул. Карла Маркса"), Crime(6, "ул. Карла Маркса") }},
		{"p441oc", {Crime(3, "ул. Пролетарская"), Crime(7, "ул. Пролетарская") }}
	};
	print(base);

	std::cout << "Введите номер машины: "; std::cin >> num_auto;
	std::cout << "Введите место правонарушения: "; std::cin >> place;
	std::cout << "Введите номер правонарушения согласно списку: " << std::endl << std::endl;

	for (std::pair<int, std::string> cr : CRIMES)
		std::cout << cr.first << ". " << cr.second << std::endl;

	std::cout << "-> "; std::cin >> id;

	it = base.find(num_auto);

	if (it!= base.end())
	{
		it->second
	}
	else
	{
		base.insert( { num_auto, { Crime(id, place) } } );
	}
	print(base);
}