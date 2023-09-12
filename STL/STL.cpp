//STL
#include<iostream>
#include<array>
#include<vector>
#include<list>
#include<forward_list>

template<typename T> void vector_properties(const std::vector<T>& vec);
template<typename T> std::forward_list<int>::iterator Iterator_FL(std::forward_list<T>& fl, int index);
template<typename T> std::list<int>::iterator Iterator_List_Begin(std::list<T>& fl, int index);
template<typename T> std::list<int>::iterator Iterator_List_End(std::list<T>& list, int index);

#define delim "\n----------------------------------------------------\n" 
#define tab "\t" 

//#define STL_ARRAY
//#define STL_VECTOR
//#define STL_FORWARD_LIST
//#define STL_LIST

void main()
{
	setlocale(LC_ALL, "");
	int index;
	int value;

#ifdef  STL_ARRAY

	// array - это контейнер, который хранит данные в виде статического массива

	const int N = 5;
	std::array<int, N> arr = { 3,5,8,13,21 };
	
	for (int i = 0; i < arr.size(); i++) std::cout << arr[i] << "\t";
	std::cout << std::endl;

#endif 
#ifdef STL_VECTOR

	//vector - это контейнер, который хранит данные в виде динамического массива

	std::vector<int> vec = { 0,1,1,2,3,5,8,13,21,34, };

	for (int i = 0; i < vec.size(); i++) std::cout << vec[i] << tab;
	std::cout << delim << std::endl;	

	vector_properties(vec);
	std::cout << delim << std::endl;
	vec.push_back(55);
	vector_properties(vec);	
	std::cout << delim << std::endl;

	vec.resize(8); //переопределение размера
	for (int i = 0; i < vec.size(); i++) std::cout << vec.at(i) /*проверяет выход за пределы вектора*/ << tab;
	vector_properties(vec);	
	std::cout << delim << std::endl;
	vec.reserve(120); // резервирует необходимый объём памяти
	vector_properties(vec);	
	std::cout << delim << std::endl;
	vec.shrink_to_fit(); // уменьшает объём зарезервированной памяти до фактической
	vector_properties(vec);	
	std::cout << delim << std::endl;

	//обработка исключений
	try
	{
		for (int i = 0; i < vec.size() * 2; i++)
		{
			std::cout << vec.at(i) << tab;
			//std::cout << vec[i] << tab;
		}
		std::cout << delim << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	//std::vector<int> vec2(100);
	//vector_properties(vec2);	
	//std::cout << delim << std::endl;	
	//vec2.push_back(1024);
	//vector_properties(vec2);
	//std::cout << delim << std::endl;

	std::vector<double> d_vec;
	vector_properties(d_vec);

	int index;
	int value;
	std::cout << "Введите индекс добавляемого элемента: "; std::cin >> index;
	std::cout << "Введите значение добавляемого элемента: "; std::cin >> value;
	vec.insert(vec.begin() + index, value);
	for (int i = 0; i < vec.size(); i++) std::cout << vec[i] << tab;
	std::cout << delim << std::endl;
	vec.erase(vec.begin()+index);
	for (int i = 0; i < vec.size(); i++) std::cout << vec[i] << tab;

#endif
#ifdef STL_FORWARD_LIST

	std::forward_list<int> fl = { 3,5,8,13,21,34,55 };
	std::forward_list<int> fl1(10, 5);
	std::forward_list<int> fl2(fl1);
	std::cout << "Список fl" << std::endl;
	for (int i : fl) std::cout << i << tab;
	std::cout << delim;
	fl.push_front(2);
	for (int i : fl) std::cout << i << tab;
	std::cout << delim;
	std::cout << "Список fl1" << std::endl;
	for (int i : fl1) std::cout << i << tab;
	std::cout << delim;
	std::cout << "Список fl2" << std::endl;
	for (int i : fl2) std::cout << i << tab;

	std::cout << "\nВведите индекс добавляемого элемента: "; std::cin >> index;
	std::cout << "\nВведите значение добавляемого элемента: "; std::cin >> value;
	
	fl.insert_after(Iterator_FL(fl, index), value);
	for (int i : fl) std::cout << i << tab;

	std::cout << "\nВведите индекс удаляемого элемента: "; std::cin >> index;

	fl.erase_after(Iterator_FL(fl, index));
	for (int i : fl) std::cout << i << tab;	
#endif
#ifdef STL_LIST
	std::list<int> list = { 3,5,8,13,21,34,55,89,144,233 };
	for (int i : list) std::cout << i << tab;

	std::cout << "\nВведите индекс добавляемого элемента: "; std::cin >> index;
	std::cout << "\nВведите значение добавляемого элемента: "; std::cin >> value;

	list.insert(Iterator_List_Begin(list, index), value);
	for (int i : list) std::cout << i << tab;
	
	std::cout << "\nВведите индекс удаляемого элемента: "; std::cin >> index;
	list.erase(Iterator_List_End(list, index));
	for (int i : list) std::cout << i << tab;
#endif
}

template<typename T> std::forward_list<int>::iterator Iterator_FL(std::forward_list<T>& fl, int index)
{
	typename std::forward_list<T>::iterator it = fl.begin();
	for (int i = 0; i < index - 2; i++) ++it;
	return it;
}
template<typename T> std::list<int>::iterator Iterator_List_Begin(std::list<T>& list, int index)
{
	typename std::list<T>::iterator it = list.begin();
	for (int i = 0; i < index; i++) ++it;
	return it;
}
template<typename T> std::list<int>::iterator Iterator_List_End(std::list<T>& list, int index)
{
	typename std::list<T>::iterator it = list.end();
	for (int i = 0; i < list.size() - index; i++) --it;
	return it;
}
template<typename T>void vector_properties(const std::vector<T>& vec)
{
	std::cout << "Size:    \t" << vec.size() << std::endl; //текущий размер 
	std::cout << "MaxSize: \t" << vec.max_size() << std::endl; // Максимальный размер
	std::cout << "Capacity:\t" << vec.capacity() << std::endl; //Общая ёмкость(резервирование памяти)
}