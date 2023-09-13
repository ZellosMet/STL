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

public:
	int get_id()const
	{
		return id;
	}
	const std::string& get_place()const
	{
		return place;
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
	}
	~Crime() {}
};

std::ostream& operator<<(std::ostream& os, const Crime& obj)
{
	return os << obj.get_id() << tab << obj.get_place();
}

void main()
{
	setlocale(LC_ALL, "");

	std::map<std::string, std::list<Crime>> base =
	{
		{"m777ab", {Crime(1, "��. ������"), Crime(2, "��. ������"), Crime(4, "��. ��������� �������")}},
		{"k231cc", {Crime(5, "��. ����� ������"), Crime(6, "��. ����� ������") }},
		{"p441oc", {Crime(3, "��. ������������"), Crime(7, "��. ������������") }}
	};

	for (std::map<std::string, std::list<Crime>>::iterator it = base.begin(); it != base.end(); ++it)
	{
		std::cout << it->first << ":\n";
		for(std::list<Crime>::iterator l_it = it->second.begin(); l_it != it->second.end(); ++l_it)
			std::cout << tab << *l_it << std::endl;
	}
	std::cout << std::endl;
}