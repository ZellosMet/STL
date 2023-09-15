//STL
#include<iostream>
#include<array>
#include<vector>
#include<forward_list>
#include<list>

template<typename T> void vector_properties(const std::vector<T>& vec);
template<typename T> typename std::list<T>::const_iterator Iterator_List(const std::list<T>& list, const int index);
template<typename T> typename std::forward_list<T>::const_iterator Iterator_FList(const std::forward_list<T>& fl, const int index);

#define delim "\n----------------------------------------------------\n" 
#define tab "\t" 

//#define STL_ARRAY
//#define STL_VECTOR
#define STL_FORWARD_LIST
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

	std::forward_list<int> fl = { 3,5,8,13,21 };
	std::vector<int> vec = { 34,55 };

	for (int i : fl) std::cout << i << tab;

	std::cout << "\nВведите индекс добавляемого элемента: "; std::cin >> index;
	std::cout << "\nВведите значение добавляемого элемента: "; std::cin >> value;
	
	fl.insert_after(Iterator_FList(fl, index), value);
	for (int i : fl) std::cout << i << tab;

	std::cout << "\nВведите индекс удаляемого элемента: "; std::cin >> index;

	fl.erase_after(Iterator_FList(fl, index));
	for (int i : fl) std::cout << i << tab;	

	std::cout << delim;
	fl.insert_after(Iterator_FList(fl, index), vec.begin(), vec.end());
	for (int i : fl) std::cout << i << tab;
	
	std::cout << delim;
	fl.insert_after(Iterator_FList(fl, index), 5 , value);
	for (int i : fl) std::cout << i << tab;
	
	std::cout << delim;
	fl.insert_after(Iterator_FList(fl, index), {100,101,102});
	for (int i : fl) std::cout << i << tab;

#endif
#ifdef STL_LIST
	std::list<int> list = { 3,5,8,13,21,34 };
	std::forward_list<int> f_list = { 55,89,144,233 };
	for (int i : list) std::cout << i << tab;

	std::cout << "\nВведите индекс добавляемого элемента: "; std::cin >> index;
	std::cout << "\nВведите значение добавляемого элемента: "; std::cin >> value;

	list.insert(Iterator_List(list, index), value);
	for (int i : list) std::cout << i << tab;
	
	std::cout << "\nВведите индекс удаляемого элемента: "; std::cin >> index;
	list.erase(Iterator_List(list, index));
	for (int i : list) std::cout << i << tab;

	std::cout << delim;
	list.insert(Iterator_List(list, index), f_list.begin(), f_list.end());
	for (int i : list) std::cout << i << tab;
	
	std::cout << delim;
	list.insert(Iterator_List(list, index), {55,89});
	for (int i : list) std::cout << i << tab;

	std::cout << delim;
	list.insert(Iterator_List(list, index), 5, value);
	for (int i : list) std::cout << i << tab;
#endif
}

template<typename T> typename std::forward_list<T>::const_iterator Iterator_FList(const std::forward_list<T>& fl, const int index)
{
	typename std::forward_list<T>::const_iterator it = fl.cbegin();
	for (int i = 0; i < index - 1; i++) ++it;
	return it;
}

template<typename T> typename std::list<T>::const_iterator Iterator_List( const std::list<T>& list, const int index)
{
	if (index >= list.size() / 2)
	{
		typename std::list<T>::const_iterator it = list.cend();
		for (int i = 0; i < list.size() - index; i++) --it;
		return it;
	}
	else
	{
		typename std::list<T>::const_iterator it = list.cbegin();
		for (int i = 0; i < index; i++) ++it;
		return it;
	}
}

template<typename T>void vector_properties(const std::vector<T>& vec)
{
	std::cout << "Size:    \t" << vec.size() << std::endl; //текущий размер 
	std::cout << "MaxSize: \t" << vec.max_size() << std::endl; // Максимальный размер
	std::cout << "Capacity:\t" << vec.capacity() << std::endl; //Общая ёмкость(резервирование памяти)
}