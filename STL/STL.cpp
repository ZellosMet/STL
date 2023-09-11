//STL
#include<iostream>
#include<array>
#include<vector>

template<typename T>void vector_properties(const std::vector<T>& vec);

#define delim "\n----------------------------------------------------\n" 
#define tab "\t" 

//#define STL_ARRAY
#define STL_VECTOR

void main()
{
	setlocale(LC_ALL, "");

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
	std::cout << "Введите индекс добавляемого элемента: "; std::cin >> value;
	vec.insert(vec.begin() + index, value);
	for (int i = 0; i < vec.size(); i++) std::cout << vec[i] << tab;
	std::cout << delim << std::endl;
	vec.erase(vec.begin()+index);
	for (int i = 0; i < vec.size(); i++) std::cout << vec[i] << tab;

#endif 

}

template<typename T>void vector_properties(const std::vector<T>& vec)
{
	std::cout << "Size:    \t" << vec.size() << std::endl; //текущий размер 
	std::cout << "MaxSize: \t" << vec.max_size() << std::endl; // Максимальный размер
	std::cout << "Capacity:\t" << vec.capacity() << std::endl; //Общая ёмкость(резервирование памяти)
}