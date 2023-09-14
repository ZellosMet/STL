#include<iostream>
#include<map>
#include<list>

#define delim "\n----------------------------------------------------\n" 
#define tab "\t" 

const std::map<int, std::string> CRIMES =
{
	{0, "N/A"},
	{1, "������� �� �������"},
	{2, "���������� ��������"},
	{3, "�������� � ������������� �����"},
	{4, "����������� ��������"},
	{5, "���� � ��������� ����"},
	{6, "����������� �������"},
	{7, "������ ������������"}
};

class Crime
{
	int id; //������
	std::string place; //����� ��������������
	std::string crime; //����������� ������

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
		{"m777ab", {Crime(1, "��. ������"), Crime(2, "��. ������"), Crime(4, "��. ��������� �������")}},
		{"k231cc", {Crime(5, "��. ����� ������"), Crime(6, "��. ����� ������") }},
		{"p441oc", {Crime(3, "��. ������������"), Crime(7, "��. ������������") }}
	};
	print(base);

	std::cout << "������� ����� ������: "; std::cin >> num_auto;
	std::cout << "������� ����� ��������������: "; std::cin >> place;
	std::cout << "������� ����� �������������� �������� ������: " << std::endl << std::endl;

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