/*
	Generic Alogrithm
*/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <sstream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <functional>

#include <algorithm>
#include <numeric>
#include <iterator>
//#include <>

#ifndef _START
#define _START




//void suoper_sort(const std::string& str)
//{
//	std::stable_sort(str.begin(), str.end(), [](const std::string &a,const std::string &b){
//		return a.size() < b.size();
//	});
//
//	auto it = std::partition(str.begin(),str.end(),[](const std::string& std){
//		return std.size() >= 5;
//	});
//
//	for (auto i = str.begin(); i != it; i++)
//	{
//		std::cout << *i << " ";
//	}
//	std::cout << std::endl;
//
//	
//
//}
//void test()
//{
//	std::string str = "hello C++ and your best fellow python!";
//	suoper_sort(str); //无法将参数从char类型转换为std::string<char,std::char_traits<char>,std::allocator<char
//}

namespace Lambda_expression
{
	std::vector<std::string> strVec{"hello", "name", "beautify", "aesthetic", "sentiment"};
	//lambda表达式
	bool isShorter(const std::string& s1, const std::string& s2)
	{
		return s1.size() < s2.size();
	}

	void elimDups(std::vector<std::string> words)
	{
		std::stable_sort(words.begin(), words.end(), [](const std::string& s1, const std::string& s2)
			{
				return s1.size() < s2.size();
			}); //稳排(按字典序)

		std::vector<std::string>::iterator it = std::unique(words.begin(), words.end()); //去重
		words.erase(it, words.end()); //删去重复的元素
	}

	std::string make_plural(size_t ctr, const std::string& words, const std::string& ending)
	{
		return (ctr > 1) ? words + ending : words;
	}

	void biggies(std::vector<std::string>& words, std::vector<std::string>::size_type sz)
	{
		elimDups(strVec); //将words按字典序排序，删除重复单词
		auto wc = std::find_if(words.begin(), words.end(), [sz](const std::string& a) {
			return a.size() >= sz;

			}); //对find_if的调用返回一个迭代器，指向第一个参数长度不小于给定参数sz的元素
		//如果这样的参数不存在，则返回words.end()的一个拷贝

	//计算满足size >= sz 的元素的数量
		auto count = words.end() - wc;
		std::cout << count << " " << make_plural(count, "word", "s") << " of length " << sz << " or longer" << std::endl;

		//打印长度大于等于给定值的单词，每个单词后面接一个空格
		std::for_each(wc, words.end(), [](const std::string& s) {std::cout << s << " "; });
		std::cout << std::endl;
	}



	//before episode01
	void test_find_if()
	{
		//std::find_if是C++中<algorithm>头文件中的一个函数，用于再容器中查找满足特定条件的元素
		//接受两个迭代器和一个谓词函数作为参数
		//然后返回第一个满足谓词条件的元素的迭代器。如果找不到匹配的元素
		//则返回尾部迭代器

		std::vector<int> numbers = { 1,2,3,4,5,6,7,8,9,10 };
		int target = 5;

		//使用find_if查找第一个大于目标值的元素
		auto it = std::find_if(numbers.begin(), numbers.end(), [target](int value)
			{
				return value > target;
			}
		);

		//检查是否找到了满足条件的元素
		if (it != numbers.end())   
		{
			std::cout << "找到第一个大于" << target << "的元素：" << *it << std::endl;
		}
		else
		{
			std::cout << "未找到满足条件的元素." << std::endl;
		}
	}
	void episode01()
	{
		//已经使用过的可调用对象：函数和函数指针
		//还有两个可调用对象：重载了函数调用运算符的类和lambda表达式
		//lambda表达式表示一个可调用的代码单元，可以将其理解为一个未命名的内联函数
		// 一个lambda具有一个返回类型、一个参数列表和一个函数体
		// 但与函数不同，lambda可能定义再函数内部
		// lambda表达式可以忽略参数列表和返回类型，但必须永远包含捕获列表和函数体
		// 
		//求一个大于等于一个给定长度的单词有多少并使程序只打印大于等于给定长度的单词

		//lambda表达式和和普通函数调用区别在于
		//lambda不能有默认参数，也就是lambda表达式调用的实参数量永远和形参相等

		std::vector<std::string> v = { "hello","nihao","xilanai","amidnight","cumming" };
		std::size_t siz = 6;
		//biggies(v, siz);

		auto sum = [](int a, int b) { std::cout << a << " + " << b << " = " << a + b << "."; return a + b; };
		int res = sum(1, 2);

		std::function<int(int)> test = [res](int t) {return res + t; };
		//std::function是一个通用的函数封装器，可用于存储任意可调用对象，包含函数指针、函数对象、成员函数指针
		//lambda表达式




	}

	template<typename Callable>
	void myFunction(Callable func)
	{
		func(3, 4); //使用模板参数接收lambda表达式(和auto类似)
	}

	void test_temp()
	{
		//lambda表达式的类型由编译器根据其内容自动推断，通常可以使用auto关键字接受lambda表达式。使用auto可
		//以使代码更灵活，因为它允许变量的类型根据初始化表达式自动推断

		//1.std::function()
		auto lambda = [](int a, int b) {return a + b; };
		std::function<int(int, int)> func = lambda;

		//使用std::function 调用lambda表达式
		int result = func(3, 4);

		//2.auto
		//3.模板参数
		//可以使用模板参数来接收lambda表达式，这样函数模板可以接受不用类型的lambda
		myFunction(lambda);

		//4.函数指针

		//如果lambda表达式没有捕获任何变量，可以将其转换为对应的函数指针类型
		int(*funcPointer)(int, int) = [](int a, int b) {return a + b; };

		//使用函数指针调用lambda表达式
		int result1 = funcPointer(3, 4);
	}

	void _Test_partition()
	{
		//在C++中，std::partition是algorithm头文件中的一个函数，
		//用于按照指定的条件对容器进行划分(partition)
		//具体说，std::partition将满足条件的元素移动到容器的前部
		//而不满足条件的元素移动到容器的后部，保持它们的相对顺序

		//std::partition 返回一个迭代器，该迭代器指向容器中第一个不满足划分条件的元素的位置
		std::vector<int> numbers = { 1,2,3,4,5,6,7,8,9,10 };

		//使用std::partition将奇数移动到前部，偶数移动到后部
		auto it = std::partition(numbers.begin(), numbers.end(), [](int& num) {
			return num % 2 != 0;
			}); //一元谓词(unary predicate),函数形参列表值从输入序列中捕获

		//输出划分后的结果
		std::cout << "Partitioned vector: ";
		for (auto iter = numbers.begin(); iter != it; ++iter)
		{
			std::cout << *iter << " ";
		}
		std::cout << " | ";
		for (; it != numbers.end(); ++it)
		{
			std::cout << *it << " ";
		}
		//划分后的元素相对位置保持不变(在内存中的位置),只是根据划分条件的不同移动到了不同的位置


	}

	void _Test_transform()
	{
		/*
			在C++中,"std::transform"是<algorithm>头文件中的一个函数，用于对容器中的元素执行某个操作
			并将结果存储到另一个容器中
			std::transform接受两个或三个输入迭代器范围，并可选地提供一个目标容器的起始迭代器

		*/

		std::vector<int> source = { 1,2,3,4,5 };
		std::vector<int> destination;

		//使用std::transform对每个元素执行乘法操作，并将结果存储到destination
		std::transform(source.begin(), source.end(), std::back_inserter(destination), [](int x)
			{
				return x * 2;
			});


		//输出结果
		std::cout << "Source vector: ";
		for (int num : source)
		{
			std::cout << num << " ";
		}
		std::cout << "\nDoubled vector: ";
		for (int num : destination)
		{
			std::cout << num << " ";
		}

	}


	//void _Test_count_if()
	//{
	//	/*
	//		在C++中，"std::count_if"是algorithm头文件中的一个函数，用于
	//		计算满足指定条件的元素个数
	//		std::count_if接受两个迭代器参数和一个谓词(predicate)函数
	//		返回满足条件的元素个数

	//		template<class InputIt,class UnaryPredicate>
	//		typename iterator_trait<InputIt>::difference_type
	//		count_if(InputIt first,InputIt last,UnaryPredicate p);
	//		//模板函数原型

	//	*/
	//	std::vector<int> numbers = {1,2,3,4,5,6,7,8,9};
	//	
	//	//使用std::count_if统计奇数的个数
	//	int oddCount = std::count_if(numbers.begin(), numbers.end(), [](int num) 
	//		{
	//			return num % 2 != 0; //判断是否为奇数
	//		});

	//	//输出结果
	//	std::cout << "奇数的个数为: " << oddCount << std::endl;

	//}

	void biggies(std::vector<std::string>& words,
		std::vector<std::string>::size_type sz,
		std::ostream& os = std::cout, char c = ' ')
	{
		elimDups(words);

		//获取一个迭代器，指向第一个满足size >= sz 的元素
		auto wc = std::find_if(words.begin(), words.end(), [sz](const std::string& s) { //s从输入序列捕获
			return s.size() >= sz;

			});
		//计算满足size >= sz的元素个数；
		auto count = words.end() - wc;
		std::cout << count << " " << make_plural(count, "word", "s") << " of length "
			<< sz << " or longer." << std::endl;
		//打印长度大于等于给定值的单词，每个单词后面接一个空格
		std::for_each(wc, words.end(), [&os, c](const std::string& s) {os << s << c; });

	}

	bool t(const std::string& s, std::string::size_type sz)
	{
		return s.size() >= sz;
	}

	std::ostream& t1(const std::string& s, std::ostream& os, char c)
	{
		return os << s << c;
	}

	void biggies1(std::vector<std::string>& words,
		std::vector<std::string>::size_type sz,
		std::ostream& os = std::cout, char c = ' ')
	{
		elimDups(words);

		//获取一个迭代器，指向第一个满足size >= sz 的元素
		auto wc = std::partition(words.begin(), words.end(), std::bind(t, std::placeholders::_1, sz));
		//计算满足size >= sz的元素个数；
		auto count = words.end() - wc;
		std::cout << count << " " << make_plural(count, "word", "s") << " of length "
			<< sz << " or longer." << std::endl;
		//打印长度大于等于给定值的单词，每个单词后面接一个空格
		std::for_each(wc, words.end(), std::bind(t1, std::placeholders::_1, std::cref(os), c)); //使用bind函数适配器重写lambda方法

	}

	void episode02()
	{
		//lambda捕获和返回
		//当定义一个lambda时，编译器生成一个与lambda对应的新的(未命名的)类类型
		//当一个函数传递一个lambda时，同时定义了一个新类型和该类型的一个对象
		//传递的参数就是此编译器生成的类类型的未命名对象

		//lambda表达式有两种捕获方法
		//值捕获和引用捕获
		//采用值捕获的前提是变量可用拷贝
		//执行引用捕获的时候需要确保lambda表达式执行的时候被引用的对象是存在的
		//	类似ostream类型的元素只能通过引用传递

		//当lambda表达式在捕获一个指针或者迭代器时使用引用捕获，必须确保在lambda执行时，绑定到迭代器
		//指针或引用的对象仍然存在。而且需要保证对象具有预期的值


		//隐式捕获
		//在捕获列表内写一个&或=
		//&告诉编译器采用引用捕获方式，=告诉编译器采用值捕获方式
		//在lambda表达式中可以混合使用隐式捕获和显式捕获

		//(当我们混合使用隐式捕获和显式捕获时，捕获列表中的第一个元素必须是一个&或=,
		//此符号指定了默认捕获方式为引用或值)

		/*
			当混合使用隐式捕获和显式捕获时，显式捕获的变量必须使用与隐式捕获不同的方式捕获
		*/

		//可变lambda
		//默认情况下对于一个值被拷贝的变量lambda不会改变其值
		//如果我们希望能改变一个被捕获的变量的值
		//就必须在参数列表首加上关键字mutable

		size_t v1 = 42;
		//f 可以改变它所捕获的变量的值
		auto f = [v1]() mutable {return ++v1; };
		v1 = 0;
		auto j = f();
		//j == 43


		//一个引用捕获的变量是否可以修改依赖于此引用指向的是一个const类型还是一个非const类型

		size_t v2 = 42;
		//k 可以修改捕获的变量引用的值
		auto k = [&v2]()mutable {return ++v2; };
		v2 = 0;
		auto m = k();
		//m == 0



		/*
			指定lambda返回类型

		*/
		//目的位置迭代器与表示输入序列开始位置的迭代器可以相同

		//在某些时候使用lambda时必须显式指出lambda的返回值
		//在lambda表达式上必须使用尾置返回类型

		std::vector<int> vi = { 1,2,3,4,5,6,7,8,9 };

		std::transform(vi.begin(), vi.end(), vi.begin(), [](int i)
			{
				return i < 0 ? -i : i;
			}); //这里lambda自动推断返回类型为int
		std::transform(vi.begin(), vi.end(), vi.begin(), [](int i)
			{
				if (i < 0)
					return -i;
				else
					return i;
			}
		); //在某些编译器上会产生编译错误(不能推断lambda的返回类型)

		std::transform(vi.begin(), vi.end(), vi.begin(), [](int i)->int {
			if (i < 0)
				return -i;
			else
				return i;

			});
		//编译成功

	}

	/*void test_(std::string::size_type sz)
	{
		std::vector<std::string> str = {"mobile","consequence","startrail","monster","sailor","anger",};
		std::string::size_type cnt = std::count_if(str.begin(), str.end(), [sz](const std::string& s)
			{
				return s.size() > sz;
			});

		std::cout << "字符串集合中长度大于" << sz << "的字符串个数为: " << cnt << std::endl;

	}

	void test__()
	{
		int te = 5;
		auto f = [&te](int sz)mutable ->bool{
			if (te > 0)
			{
				--te;
				return false;
			}
			else if(te == 0)
			{
				return true;
			}
			else
			{
				return false;
			}
		};
	}*/
	bool check_size(const std::string& s, std::string::size_type sz)
	{
		return s.size() >= sz;
	}

	std::ostream& print(std::ostream& os, const std::string& s, char c)
	{
		return os << s << c;
	}

	void episode03(std::string::size_type sz)
	{
		/*
			参数绑定
		*/

		//对于只在一两个地方使用的简单操作，lambda表达式是最有用的。
		//如果我们要在很多地方使用相同的操作，通常应该定义一个函数
		//而不是多次编写相同的lambda表达式

		//如果lambda表达式的捕获列表为空，通常可以用函数来替代lambda
		//但是对于捕获局部变量的lambda，用函数就不太好替换了
		/*
			bool check_size(const std::string& s,std::string::size_type sz)
			{
				return s.size() >= sz;
			} //在上面的biggies函数内的find_if谓词可用函数替换
				//但是不能用这个函数作为find_if的一个参数
				//find_if接受一个一元谓词
				//因此传递给find_if的可调用对象必须接受单一参数

				//lambda表达式可用捕获列表捕获函数内局部变量
				//但函数就只能用参数列表捕获一个单一参数

		*/

		/*
			标准库bind函数

		*/

		/*
			bind函数定义在functional头文件中,可以将bind看作是一个通用的函数适配器
			它接受一个可调用对象，生成一个新的可调用对象来"适应"原对象的参数列表
			auto newCallable = std::bind(callable,arg_list);

		*/


		/*
			绑定check_size的sz参数

		*/
		auto check6 = std::bind(check_size, std::placeholders::_1, 6); //_1 using std::placeholders::_1; using namespace std::placeholders;

		//这个bind调用只有一个占位符，表示check6只接收单一参数。占位符出现在arg_list的第一个位置
		//表示check6的此参数对应check_size的第一个参数。此参数是const std::string
		//因此调用check6只需要传递一个单一const std::string 参数
		//check6会将此参数传递给check_size 
		std::vector<std::string> words = { "" };
		std::string s = "hello";
		bool b1 = check6(s);
		auto wc = std::find_if(words.begin(), words.end(), std::bind(check_size, std::placeholders::_1, sz));


		//bind的参数绑定
		/*
		* 假设f是一个可调用对象 有5个参数,a,b,c为函数内可访问的局部变量
			auto g = std::bind(f,a,b,std::placeholders::_2,c,std::placeholders::_1);
			生成一个新的可调用对象 g，这个对象有两个参数分别用占位符_2和_1表示。
			这个新的可调用对象将它自己的参数作为第三个参数和第五个参数传递给f


			传递给g的参数按照位置绑定到占位符
			第一个参数绑定到_1,第二个参数绑定到_2
			即当调用g时其第一个参数将被传递给f作为最后一个参数，第二个参数将被传递给f作为第三个参数

			g(_1,_2) == f(a,b,_2,c,_1)


		*/

		//用bind重排参数顺序

		//可以使用bind(通用函数适配器)颠倒isShorter的意思
		std::sort(words.begin(), words.end(), isShorter); //正常使用sort和一元谓词
		//按单词长度由短至长排序
		std::sort(words.begin(), words.end(), std::bind(isShorter, std::placeholders::_2, std::placeholders::_1));
		//按单词长度由长至短排序



		//bind(通用函数适配器)绑定引用参数
		/*
			默认情况下，bind的那些不是占位符的参数被*拷贝*到bind返回的可调用对象中
			但是与lambda类似，有时对有些绑定的参数我们希望以引用方式传递，或是要绑定参数的类型无法拷贝std::ostream


			std::for_each(words.begin(),words.end(),[&os,c](const string &s){os << s << c;}); //替换一个引用方式捕获ostream的lambda

			std::ostream &print(std::ostream &os,const std::string &s,char c)
			{
				return os << s << c;
			}

			std::for_each(words.begin(),words.end(),std::bind(print,os,std::placeholders:_1,' '));//错误：不能直接用bind来代替对os的捕获
			原因在于bind拷贝其他参数，而我们不能拷贝一个ostream类型的参数
			这里需要使用标准库ref函数
			std::for_each(words.begin(),words.end(),std::bind(print,std::ref(os),std::placeholders::_1,' '));
			函数ref返回一个对象，包含给定的引用，此对象是可以拷贝的
			标准库中还有一个cref函数生成一个保存const引用的类
			ref和cref都定义在fuctional头文件中

		*/
		std::ostream& os = std::cout;
		std::for_each(words.begin(), words.end(), std::bind(print, os, std::placeholders::_1, ' '));//错误：不能直接用bind来代替对os的捕获

		std::for_each(words.begin(), words.end(), std::bind(print, std::ref(os), std::placeholders::_1, ' ')); //std::cref(os)
	}


	//bool yuuka(std::string& s,std::string::size_type sz)
	//{
	//	return s.size() > sz;
	//}

	//void test_(std::string::size_type sz)
	//{
	//	std::vector<std::string> str = { "mobile","consequence","startrail","monster","sailor","anger", };
	//	std::string::size_type cnt = std::count_if(str.begin(), str.end(),std::bind(yuuka,std::placeholders::_1,sz)); //可调用对象只接受单一参数

	//	std::cout << "字符串集合中长度大于" << sz << "的字符串个数为: " << cnt << std::endl;

	//}

	bool check_size_test(const std::string& s, std::string::size_type sz)
	{
		return s.size() > sz;
	}

	void _test_challenging(std::string& s, std::vector<int> vec)
	{
		//找到第一个大于string长度的值
		auto it = std::find_if(vec.begin(), vec.end(), std::bind(check_size_test, std::placeholders::_1, s.size())); //占位符从输入序列中捕获值
		std::cout << "第一个大于string长度的值为:" << *it << std::endl;
	}









	/*
		再探迭代器
		标准库在头文件iterator中还定义了额外几种迭代器

		插入迭代器(insert iterator): 这些迭代器被绑定在一个容器上，可以来向容器插入元素

		流迭代器(stream iterator): 这些迭代器被绑定到输入或输出流上，可以用来遍历所有关联的IO流

		反向迭代器(reverse iterator): 这些迭代器向后而不是向前移动，除了forward_list之外的标准库容器都有反向迭代器

		移动迭代器(move iterator): 这些专用的迭代器不是拷贝其中的元素，而是移动它们
	*/

	//插入迭代器
	/*
		插入迭代器是一种迭代器适配器，接受一个容器，生成一个迭代器
		能实现向给定容器添加元素

		插入器(插入迭代器)有三种类型: 差别在于元素插入的位置

		back_inserter:创建一个使用push_back()的迭代器
		front_inserter:创建一个使用push_front()的迭代器
		inserter: 这个插入器件接受第二个参数，这个参数必须是	**一个指向给定容器的迭代器**


		插入迭代器提供了更灵活的插入选项，可以在运行时选择不同的插入策略
		直接调用容器成员函数可能需要在编译时确定插入位置，限制了一些灵活性(操作依赖于容器)

	*/

	void inserter_list()
	{
		//back_inserter 在目标容器末尾插入元素
		//使用push_back将元素添加到目标容器的末尾

		std::vector<int> vec = { 1,2,3 };
		std::back_insert_iterator<std::vector<int>> backInserter(vec);
		//也可以使用back_inserter 创建一个插入迭代器对象 auto it = std::back_inserter(vec)

		*backInserter = 4; //将元素4插入到vec的末尾
		++backInserter;

		std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));


		//front_inserter 在目标容器开头插入元素
		//使用push_front 将元素添加到目标容器开头

		std::list<int> lst = { 1,2,3 };
		std::front_insert_iterator<std::list<int>> frontInserter(lst);

		*frontInserter = 4;
		++frontInserter;

		std::copy(lst.begin(), lst.end(), std::ostream_iterator<int>(std::cout, " "));
		//ostream_iterator<> 写输出流


		//inserter 在目标容器指定位置插入元素
		//使用指定的插入位置，通常是目标容器的迭代器，将元素插入到指定位置

		std::set<int> mySet = { 1,2,3 };
		std::inserter(mySet, mySet.begin()) = 4; //将元素4插入到指定位置
		/*
			auto it = std::inserter(mySet,mySet.begin());
			auto == std::inserter_iterator
			*it = 4;
		*/

		std::copy(mySet.begin(), mySet.end(), std::ostream_iterator<int>(std::cout, " ")); //将mySet中的值以标准输出流的方式拷贝到输出流上

	}

	void episode04()
	{
		std::vector<int> v = { 1,2,3,4,5,6,7,8,9 };
		auto it = v.begin() + 3;
		int val = 0;
		//理解插入器的工作过程是很重要的
		auto it1 = std::inserter(v, it); //第二个参数为指向给定容器的迭代器，在这个迭代器之前插入元素
		*it1 = val; //在it迭代器指向容器元素位置前插入元素

		//上一句和下面的代码同等效力
		it = v.insert(it, val); //调用容器内成员函数实现插入
		++it; //移动迭代器到原来it的位置

		/*
			front_inserter生成的迭代器和inserter生成的迭代器完全不一样
			front_inserter总是插入到容器的第一个元素之前
		*/

		std::list<int> lst = { 1,2,3,4 };
		std::list<int> lst2, lst3; //空list
		//这里如果给空list直接赋值会报错

		//调用algorithm头文件中的copy函数实现元素拷贝
		std::copy(lst.begin(), lst.end(), std::front_inserter(lst2)); //第三个参数为目的位置迭代器，这里用front_inserter实现反插
		// 4,3,2,1

		std::copy(lst.begin(), lst.end(), std::back_inserter(lst3)); //back_inserter 实现正插
		//1，2，3，4

		/*
			这些插入迭代器提供了一种方便的方式，通过迭代器而不是直接调用容器的成员函数来插入元素
			选择使用哪个取决于要插入的位置以及希望使用的插入方法
		*/




	}

	void unique_copy_test()
	{
		//std::unique_copy()是c++标准库中的一个算法，用于从一个范围赋值元素到另一个元素
		//并且在复制过程中去除相邻的重复元素。它通常用于从一个有序范围中创建一个不包含
		//重复元素的新容器

		//原始容器
		std::vector<int> source = { 1,2,3,4,5,6,2,3,4, };

		//目标容器，用于存储去除相邻重复元素后的结果
		std::vector<int> destination;

		//为容器排序
		std::sort(source.begin(), source.end(), [](int& a, int& b) {
			return a < b;
			});
		//unique_copy要求范围必须是有序的，因为它只能去除相邻的重复元素

		//使用std::unique_copy 复制并去除相邻重复元素
		std::unique_copy(source.begin(), source.end(), std::back_inserter(destination)); //尾插迭代器


		//打印结果
		for (const auto& element : destination)
		{
			std::cout << element << " ";
		}
	}

	void test01()
	{
		std::vector<int> vec = { 1,2,3,4,5,6,7,8,9 };

		std::vector<int> vec2, vec3, vec4;

		std::front_insert_iterator<std::vector<int>> it1 = std::front_inserter(vec2);

		std::back_insert_iterator<std::vector<int>> it2 = std::back_inserter(vec3);

		std::insert_iterator<std::vector<int>> it3 = std::inserter(vec4, vec4.begin());
		//第二个参数为指向绑定容器的迭代器

		//使用copy函数实现对容器内元素的拷贝
		std::copy(vec.begin(), vec.end(), it1);
		std::copy(vec.begin(), vec.end(), it2);
		std::copy(vec.begin(), vec.end(), it3);
	}


	/*
		iostream迭代器


		虽然iostream类型不是容器，但标准库定义了可以用于这些IO类型对象的迭代器

		istream_iterator 读取输入流
		ostream_iterator 向一个输出流写数据
		
		这些迭代器将它们对应的流当作一个特定类型的元素序列来处理
	*/

	void episode05()
	{
		//istream_iterator 操作
		//当创建一个流时，必须指定迭代器将要读写的对象类型
			//istream_iterator 使用 >> 来读取流
			//因此，istream_iterator 要读取的类型必须定义了输入运算符
		
		
		//创建istream_iterator 对象
		std::istream_iterator<int> int_it(std::cin); //指定迭代器读对象类型
		//从cin读取int

		std::istream_iterator<int> int_eof; //默认初始化流迭代器可以用作尾后迭代器

		std::ifstream in("afile"); //文件输入流
		std::istream_iterator<std::string> str_it(in); //从afile读取字符串

		//对于一个绑定到流的迭代器，一旦其关联的流遇到文件尾或IO错误，迭代器的值就与尾后迭代器相等

		std::vector<int> vec;
		std::istream_iterator<int> in_iter(std::cin); //从标准输入流读取数据
		std::istream_iterator<int> eof; //end of file

		while (in_iter != eof)
		{
			vec.push_back(*in_iter++);
		}

		//上面的程序可以重写成下面的代码
		std::istream_iterator<int> in_iter1(std::cin),eof;

		std::vector<int> vec(in_iter,eof); //使用迭代器进行初始化
		//从迭代器范围构造vec

		//元素范围是通过从关联的流中读取数据获得的，从流中读取的数据被用来构造vec



		/*
			使用算法来操作流迭代器
			由于算法使用迭代器操作来读取数据，而流迭代器又至少支持某些迭代器操作，因此我们至少可以用某些算法来操作流迭代器

		*/

		std::istream_iterator<int> in(std::cin), end;
		std::cout << std::accumulate((std::istream_iterator<int>)in,end, 0) << std::endl;
		//算法用迭代器来操作流中数据
		//istream_iterator允许懒惰求值
		//标准库保证在我们第一次解引用迭代器之前，从流中读取数据的操作就已经完成了
		//（具体来说就是支持推迟对输入流的读取）







		/*
			ostream_iterator输出迭代器

			我们可以对任意具有输出运算符的类型定义ostream_iterator。
			当创建一个ostream_iterator对象时，我们可以提供第二个参数
			第二个参数必须是一个C风格的字符串(即一个字符串字面常量或者一个指向以空字符结尾的字符数组的指针)
			ostream_iterator必须绑定到一个指定的流，不允许空的或表示尾后位置的ostream_iterator

		*/

		//我们可以用ostream_iterator来输出值的序列
		std::ostream_iterator<int> out_iter(std::cout," ");
		
		for (auto& e : vec)
		{
			*out_iter++ = e; //利用输出迭代器(ostream_iterator)将e写入到输出流中
		}

		//当我们向out_iter赋值的时候，可以忽略解引用和递增运算
		//out_iter = e;
		//运算符* 和++实际上对ostream_iterator对象不做任何事情
		//因此忽略它们对我们的程序没有任何影响

		//可以通过调用copy来打印vec中的元素
		std::copy(vec.begin(),vec.end(),out_iter); //将vec中的元素拷贝到输出流迭代器




	}

	int test02()
	{
		//使用流迭代器读取一个文本文件，存入一个vector中的string里
		
		//打开文本文件
		std::ifstream file("C:\\Users\\wsxl2\\source\\repos\\Generic Algorithm_next\\example.txt");
		
		//检查文件是否成功打开
		if (!file.is_open())
		{
			std::cerr << "Error opening the file." << std::endl;
			return 1; //返回错误码
		}

		//使用std::istream_iterator 从文件中读取字符串直到文件末尾
		std::istream_iterator<std::string> fileIterator(file); //文本文件输入流
		std::istream_iterator<std::string> endIterator; //eof
		
		//使用迭代器将文件中的字符串存储到vector中
		std::vector<std::string> lines(fileIterator,endIterator); 

		//打印vector中的字符串
		std::cout << "Contents of vector: " << std::endl;
		
		for (const auto& line : lines)
		{
			std::cout << line << std::endl;
		}

		file.close();
		return 0;

	}

	void test03()
	{
		
	}







	/*
		反向迭代器

	*/



}

#endif

int main()
{

	//Lambda_expression::episode01();


	//test();
	std::string s = "hello,world!";
	std::vector<int> vec = { 1,3,5,7,9,11,13,15 };
	Lambda_expression::inserter_list();

	return EXIT_SUCCESS;
}
