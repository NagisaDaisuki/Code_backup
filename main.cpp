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
//	suoper_sort(str); //�޷���������char����ת��Ϊstd::string<char,std::char_traits<char>,std::allocator<char
//}

namespace Lambda_expression
{
	std::vector<std::string> strVec{"hello", "name", "beautify", "aesthetic", "sentiment"};
	//lambda���ʽ
	bool isShorter(const std::string& s1, const std::string& s2)
	{
		return s1.size() < s2.size();
	}

	void elimDups(std::vector<std::string> words)
	{
		std::stable_sort(words.begin(), words.end(), [](const std::string& s1, const std::string& s2)
			{
				return s1.size() < s2.size();
			}); //����(���ֵ���)

		std::vector<std::string>::iterator it = std::unique(words.begin(), words.end()); //ȥ��
		words.erase(it, words.end()); //ɾȥ�ظ���Ԫ��
	}

	std::string make_plural(size_t ctr, const std::string& words, const std::string& ending)
	{
		return (ctr > 1) ? words + ending : words;
	}

	void biggies(std::vector<std::string>& words, std::vector<std::string>::size_type sz)
	{
		elimDups(strVec); //��words���ֵ�������ɾ���ظ�����
		auto wc = std::find_if(words.begin(), words.end(), [sz](const std::string& a) {
			return a.size() >= sz;

			}); //��find_if�ĵ��÷���һ����������ָ���һ���������Ȳ�С�ڸ�������sz��Ԫ��
		//��������Ĳ��������ڣ��򷵻�words.end()��һ������

	//��������size >= sz ��Ԫ�ص�����
		auto count = words.end() - wc;
		std::cout << count << " " << make_plural(count, "word", "s") << " of length " << sz << " or longer" << std::endl;

		//��ӡ���ȴ��ڵ��ڸ���ֵ�ĵ��ʣ�ÿ�����ʺ����һ���ո�
		std::for_each(wc, words.end(), [](const std::string& s) {std::cout << s << " "; });
		std::cout << std::endl;
	}



	//before episode01
	void test_find_if()
	{
		//std::find_if��C++��<algorithm>ͷ�ļ��е�һ�������������������в��������ض�������Ԫ��
		//����������������һ��ν�ʺ�����Ϊ����
		//Ȼ�󷵻ص�һ������ν��������Ԫ�صĵ�����������Ҳ���ƥ���Ԫ��
		//�򷵻�β��������

		std::vector<int> numbers = { 1,2,3,4,5,6,7,8,9,10 };
		int target = 5;

		//ʹ��find_if���ҵ�һ������Ŀ��ֵ��Ԫ��
		auto it = std::find_if(numbers.begin(), numbers.end(), [target](int value)
			{
				return value > target;
			}
		);

		//����Ƿ��ҵ�������������Ԫ��
		if (it != numbers.end())   
		{
			std::cout << "�ҵ���һ������" << target << "��Ԫ�أ�" << *it << std::endl;
		}
		else
		{
			std::cout << "δ�ҵ�����������Ԫ��." << std::endl;
		}
	}
	void episode01()
	{
		//�Ѿ�ʹ�ù��Ŀɵ��ö��󣺺����ͺ���ָ��
		//���������ɵ��ö��������˺�����������������lambda���ʽ
		//lambda���ʽ��ʾһ���ɵ��õĴ��뵥Ԫ�����Խ������Ϊһ��δ��������������
		// һ��lambda����һ���������͡�һ�������б��һ��������
		// ���뺯����ͬ��lambda���ܶ����ٺ����ڲ�
		// lambda���ʽ���Ժ��Բ����б�ͷ������ͣ���������Զ���������б�ͺ�����
		// 
		//��һ�����ڵ���һ���������ȵĵ����ж��ٲ�ʹ����ֻ��ӡ���ڵ��ڸ������ȵĵ���

		//lambda���ʽ�ͺ���ͨ����������������
		//lambda������Ĭ�ϲ�����Ҳ����lambda���ʽ���õ�ʵ��������Զ���β����

		std::vector<std::string> v = { "hello","nihao","xilanai","amidnight","cumming" };
		std::size_t siz = 6;
		//biggies(v, siz);

		auto sum = [](int a, int b) { std::cout << a << " + " << b << " = " << a + b << "."; return a + b; };
		int res = sum(1, 2);

		std::function<int(int)> test = [res](int t) {return res + t; };
		//std::function��һ��ͨ�õĺ�����װ���������ڴ洢����ɵ��ö��󣬰�������ָ�롢�������󡢳�Ա����ָ��
		//lambda���ʽ




	}

	template<typename Callable>
	void myFunction(Callable func)
	{
		func(3, 4); //ʹ��ģ���������lambda���ʽ(��auto����)
	}

	void test_temp()
	{
		//lambda���ʽ�������ɱ����������������Զ��ƶϣ�ͨ������ʹ��auto�ؼ��ֽ���lambda���ʽ��ʹ��auto��
		//��ʹ���������Ϊ��������������͸��ݳ�ʼ�����ʽ�Զ��ƶ�

		//1.std::function()
		auto lambda = [](int a, int b) {return a + b; };
		std::function<int(int, int)> func = lambda;

		//ʹ��std::function ����lambda���ʽ
		int result = func(3, 4);

		//2.auto
		//3.ģ�����
		//����ʹ��ģ�����������lambda���ʽ����������ģ����Խ��ܲ������͵�lambda
		myFunction(lambda);

		//4.����ָ��

		//���lambda���ʽû�в����κα��������Խ���ת��Ϊ��Ӧ�ĺ���ָ������
		int(*funcPointer)(int, int) = [](int a, int b) {return a + b; };

		//ʹ�ú���ָ�����lambda���ʽ
		int result1 = funcPointer(3, 4);
	}

	void _Test_partition()
	{
		//��C++�У�std::partition��algorithmͷ�ļ��е�һ��������
		//���ڰ���ָ�����������������л���(partition)
		//����˵��std::partition������������Ԫ���ƶ���������ǰ��
		//��������������Ԫ���ƶ��������ĺ󲿣��������ǵ����˳��

		//std::partition ����һ�����������õ�����ָ�������е�һ�������㻮��������Ԫ�ص�λ��
		std::vector<int> numbers = { 1,2,3,4,5,6,7,8,9,10 };

		//ʹ��std::partition�������ƶ���ǰ����ż���ƶ�����
		auto it = std::partition(numbers.begin(), numbers.end(), [](int& num) {
			return num % 2 != 0;
			}); //һԪν��(unary predicate),�����β��б�ֵ�����������в���

		//������ֺ�Ľ��
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
		//���ֺ��Ԫ�����λ�ñ��ֲ���(���ڴ��е�λ��),ֻ�Ǹ��ݻ��������Ĳ�ͬ�ƶ����˲�ͬ��λ��


	}

	void _Test_transform()
	{
		/*
			��C++��,"std::transform"��<algorithm>ͷ�ļ��е�һ�����������ڶ������е�Ԫ��ִ��ĳ������
			��������洢����һ��������
			std::transform�������������������������Χ������ѡ���ṩһ��Ŀ����������ʼ������

		*/

		std::vector<int> source = { 1,2,3,4,5 };
		std::vector<int> destination;

		//ʹ��std::transform��ÿ��Ԫ��ִ�г˷���������������洢��destination
		std::transform(source.begin(), source.end(), std::back_inserter(destination), [](int x)
			{
				return x * 2;
			});


		//������
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
	//		��C++�У�"std::count_if"��algorithmͷ�ļ��е�һ������������
	//		��������ָ��������Ԫ�ظ���
	//		std::count_if��������������������һ��ν��(predicate)����
	//		��������������Ԫ�ظ���

	//		template<class InputIt,class UnaryPredicate>
	//		typename iterator_trait<InputIt>::difference_type
	//		count_if(InputIt first,InputIt last,UnaryPredicate p);
	//		//ģ�庯��ԭ��

	//	*/
	//	std::vector<int> numbers = {1,2,3,4,5,6,7,8,9};
	//	
	//	//ʹ��std::count_ifͳ�������ĸ���
	//	int oddCount = std::count_if(numbers.begin(), numbers.end(), [](int num) 
	//		{
	//			return num % 2 != 0; //�ж��Ƿ�Ϊ����
	//		});

	//	//������
	//	std::cout << "�����ĸ���Ϊ: " << oddCount << std::endl;

	//}

	void biggies(std::vector<std::string>& words,
		std::vector<std::string>::size_type sz,
		std::ostream& os = std::cout, char c = ' ')
	{
		elimDups(words);

		//��ȡһ����������ָ���һ������size >= sz ��Ԫ��
		auto wc = std::find_if(words.begin(), words.end(), [sz](const std::string& s) { //s���������в���
			return s.size() >= sz;

			});
		//��������size >= sz��Ԫ�ظ�����
		auto count = words.end() - wc;
		std::cout << count << " " << make_plural(count, "word", "s") << " of length "
			<< sz << " or longer." << std::endl;
		//��ӡ���ȴ��ڵ��ڸ���ֵ�ĵ��ʣ�ÿ�����ʺ����һ���ո�
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

		//��ȡһ����������ָ���һ������size >= sz ��Ԫ��
		auto wc = std::partition(words.begin(), words.end(), std::bind(t, std::placeholders::_1, sz));
		//��������size >= sz��Ԫ�ظ�����
		auto count = words.end() - wc;
		std::cout << count << " " << make_plural(count, "word", "s") << " of length "
			<< sz << " or longer." << std::endl;
		//��ӡ���ȴ��ڵ��ڸ���ֵ�ĵ��ʣ�ÿ�����ʺ����һ���ո�
		std::for_each(wc, words.end(), std::bind(t1, std::placeholders::_1, std::cref(os), c)); //ʹ��bind������������дlambda����

	}

	void episode02()
	{
		//lambda����ͷ���
		//������һ��lambdaʱ������������һ����lambda��Ӧ���µ�(δ������)������
		//��һ����������һ��lambdaʱ��ͬʱ������һ�������ͺ͸����͵�һ������
		//���ݵĲ������Ǵ˱��������ɵ������͵�δ��������

		//lambda���ʽ�����ֲ��񷽷�
		//ֵ��������ò���
		//����ֵ�����ǰ���Ǳ������ÿ���
		//ִ�����ò����ʱ����Ҫȷ��lambda���ʽִ�е�ʱ�����õĶ����Ǵ��ڵ�
		//	����ostream���͵�Ԫ��ֻ��ͨ�����ô���

		//��lambda���ʽ�ڲ���һ��ָ����ߵ�����ʱʹ�����ò��񣬱���ȷ����lambdaִ��ʱ���󶨵�������
		//ָ������õĶ�����Ȼ���ڡ�������Ҫ��֤�������Ԥ�ڵ�ֵ


		//��ʽ����
		//�ڲ����б���дһ��&��=
		//&���߱������������ò���ʽ��=���߱���������ֵ����ʽ
		//��lambda���ʽ�п��Ի��ʹ����ʽ�������ʽ����

		//(�����ǻ��ʹ����ʽ�������ʽ����ʱ�������б��еĵ�һ��Ԫ�ر�����һ��&��=,
		//�˷���ָ����Ĭ�ϲ���ʽΪ���û�ֵ)

		/*
			�����ʹ����ʽ�������ʽ����ʱ����ʽ����ı�������ʹ������ʽ����ͬ�ķ�ʽ����
		*/

		//�ɱ�lambda
		//Ĭ������¶���һ��ֵ�������ı���lambda����ı���ֵ
		//�������ϣ���ܸı�һ��������ı�����ֵ
		//�ͱ����ڲ����б��׼��Ϲؼ���mutable

		size_t v1 = 42;
		//f ���Ըı���������ı�����ֵ
		auto f = [v1]() mutable {return ++v1; };
		v1 = 0;
		auto j = f();
		//j == 43


		//һ�����ò���ı����Ƿ�����޸������ڴ�����ָ�����һ��const���ͻ���һ����const����

		size_t v2 = 42;
		//k �����޸Ĳ���ı������õ�ֵ
		auto k = [&v2]()mutable {return ++v2; };
		v2 = 0;
		auto m = k();
		//m == 0



		/*
			ָ��lambda��������

		*/
		//Ŀ��λ�õ��������ʾ�������п�ʼλ�õĵ�����������ͬ

		//��ĳЩʱ��ʹ��lambdaʱ������ʽָ��lambda�ķ���ֵ
		//��lambda���ʽ�ϱ���ʹ��β�÷�������

		std::vector<int> vi = { 1,2,3,4,5,6,7,8,9 };

		std::transform(vi.begin(), vi.end(), vi.begin(), [](int i)
			{
				return i < 0 ? -i : i;
			}); //����lambda�Զ��ƶϷ�������Ϊint
		std::transform(vi.begin(), vi.end(), vi.begin(), [](int i)
			{
				if (i < 0)
					return -i;
				else
					return i;
			}
		); //��ĳЩ�������ϻ�����������(�����ƶ�lambda�ķ�������)

		std::transform(vi.begin(), vi.end(), vi.begin(), [](int i)->int {
			if (i < 0)
				return -i;
			else
				return i;

			});
		//����ɹ�

	}

	/*void test_(std::string::size_type sz)
	{
		std::vector<std::string> str = {"mobile","consequence","startrail","monster","sailor","anger",};
		std::string::size_type cnt = std::count_if(str.begin(), str.end(), [sz](const std::string& s)
			{
				return s.size() > sz;
			});

		std::cout << "�ַ��������г��ȴ���" << sz << "���ַ�������Ϊ: " << cnt << std::endl;

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
			������
		*/

		//����ֻ��һ�����ط�ʹ�õļ򵥲�����lambda���ʽ�������õġ�
		//�������Ҫ�ںܶ�ط�ʹ����ͬ�Ĳ�����ͨ��Ӧ�ö���һ������
		//�����Ƕ�α�д��ͬ��lambda���ʽ

		//���lambda���ʽ�Ĳ����б�Ϊ�գ�ͨ�������ú��������lambda
		//���Ƕ��ڲ���ֲ�������lambda���ú����Ͳ�̫���滻��
		/*
			bool check_size(const std::string& s,std::string::size_type sz)
			{
				return s.size() >= sz;
			} //�������biggies�����ڵ�find_ifν�ʿ��ú����滻
				//���ǲ��������������Ϊfind_if��һ������
				//find_if����һ��һԪν��
				//��˴��ݸ�find_if�Ŀɵ��ö��������ܵ�һ����

				//lambda���ʽ���ò����б������ھֲ�����
				//��������ֻ���ò����б���һ����һ����

		*/

		/*
			��׼��bind����

		*/

		/*
			bind����������functionalͷ�ļ���,���Խ�bind������һ��ͨ�õĺ���������
			������һ���ɵ��ö�������һ���µĿɵ��ö�����"��Ӧ"ԭ����Ĳ����б�
			auto newCallable = std::bind(callable,arg_list);

		*/


		/*
			��check_size��sz����

		*/
		auto check6 = std::bind(check_size, std::placeholders::_1, 6); //_1 using std::placeholders::_1; using namespace std::placeholders;

		//���bind����ֻ��һ��ռλ������ʾcheck6ֻ���յ�һ������ռλ��������arg_list�ĵ�һ��λ��
		//��ʾcheck6�Ĵ˲�����Ӧcheck_size�ĵ�һ���������˲�����const std::string
		//��˵���check6ֻ��Ҫ����һ����һconst std::string ����
		//check6�Ὣ�˲������ݸ�check_size 
		std::vector<std::string> words = { "" };
		std::string s = "hello";
		bool b1 = check6(s);
		auto wc = std::find_if(words.begin(), words.end(), std::bind(check_size, std::placeholders::_1, sz));


		//bind�Ĳ�����
		/*
		* ����f��һ���ɵ��ö��� ��5������,a,b,cΪ�����ڿɷ��ʵľֲ�����
			auto g = std::bind(f,a,b,std::placeholders::_2,c,std::placeholders::_1);
			����һ���µĿɵ��ö��� g��������������������ֱ���ռλ��_2��_1��ʾ��
			����µĿɵ��ö������Լ��Ĳ�����Ϊ�����������͵�����������ݸ�f


			���ݸ�g�Ĳ�������λ�ð󶨵�ռλ��
			��һ�������󶨵�_1,�ڶ��������󶨵�_2
			��������gʱ���һ�������������ݸ�f��Ϊ���һ���������ڶ��������������ݸ�f��Ϊ����������

			g(_1,_2) == f(a,b,_2,c,_1)


		*/

		//��bind���Ų���˳��

		//����ʹ��bind(ͨ�ú���������)�ߵ�isShorter����˼
		std::sort(words.begin(), words.end(), isShorter); //����ʹ��sort��һԪν��
		//�����ʳ����ɶ���������
		std::sort(words.begin(), words.end(), std::bind(isShorter, std::placeholders::_2, std::placeholders::_1));
		//�����ʳ����ɳ���������



		//bind(ͨ�ú���������)�����ò���
		/*
			Ĭ������£�bind����Щ����ռλ���Ĳ�����*����*��bind���صĿɵ��ö�����
			������lambda���ƣ���ʱ����Щ�󶨵Ĳ�������ϣ�������÷�ʽ���ݣ�����Ҫ�󶨲����������޷�����std::ostream


			std::for_each(words.begin(),words.end(),[&os,c](const string &s){os << s << c;}); //�滻һ�����÷�ʽ����ostream��lambda

			std::ostream &print(std::ostream &os,const std::string &s,char c)
			{
				return os << s << c;
			}

			std::for_each(words.begin(),words.end(),std::bind(print,os,std::placeholders:_1,' '));//���󣺲���ֱ����bind�������os�Ĳ���
			ԭ������bind�������������������ǲ��ܿ���һ��ostream���͵Ĳ���
			������Ҫʹ�ñ�׼��ref����
			std::for_each(words.begin(),words.end(),std::bind(print,std::ref(os),std::placeholders::_1,' '));
			����ref����һ�����󣬰������������ã��˶����ǿ��Կ�����
			��׼���л���һ��cref��������һ������const���õ���
			ref��cref��������fuctionalͷ�ļ���

		*/
		std::ostream& os = std::cout;
		std::for_each(words.begin(), words.end(), std::bind(print, os, std::placeholders::_1, ' '));//���󣺲���ֱ����bind�������os�Ĳ���

		std::for_each(words.begin(), words.end(), std::bind(print, std::ref(os), std::placeholders::_1, ' ')); //std::cref(os)
	}


	//bool yuuka(std::string& s,std::string::size_type sz)
	//{
	//	return s.size() > sz;
	//}

	//void test_(std::string::size_type sz)
	//{
	//	std::vector<std::string> str = { "mobile","consequence","startrail","monster","sailor","anger", };
	//	std::string::size_type cnt = std::count_if(str.begin(), str.end(),std::bind(yuuka,std::placeholders::_1,sz)); //�ɵ��ö���ֻ���ܵ�һ����

	//	std::cout << "�ַ��������г��ȴ���" << sz << "���ַ�������Ϊ: " << cnt << std::endl;

	//}

	bool check_size_test(const std::string& s, std::string::size_type sz)
	{
		return s.size() > sz;
	}

	void _test_challenging(std::string& s, std::vector<int> vec)
	{
		//�ҵ���һ������string���ȵ�ֵ
		auto it = std::find_if(vec.begin(), vec.end(), std::bind(check_size_test, std::placeholders::_1, s.size())); //ռλ�������������в���ֵ
		std::cout << "��һ������string���ȵ�ֵΪ:" << *it << std::endl;
	}









	/*
		��̽������
		��׼����ͷ�ļ�iterator�л������˶��⼸�ֵ�����

		���������(insert iterator): ��Щ������������һ�������ϣ�����������������Ԫ��

		��������(stream iterator): ��Щ���������󶨵������������ϣ����������������й�����IO��

		���������(reverse iterator): ��Щ����������������ǰ�ƶ�������forward_list֮��ı�׼���������з��������

		�ƶ�������(move iterator): ��Щר�õĵ��������ǿ������е�Ԫ�أ������ƶ�����
	*/

	//���������
	/*
		�����������һ�ֵ�����������������һ������������һ��������
		��ʵ��������������Ԫ��

		������(���������)����������: �������Ԫ�ز����λ��

		back_inserter:����һ��ʹ��push_back()�ĵ�����
		front_inserter:����һ��ʹ��push_front()�ĵ�����
		inserter: ��������������ܵڶ����������������������	**һ��ָ����������ĵ�����**


		����������ṩ�˸����Ĳ���ѡ�����������ʱѡ��ͬ�Ĳ������
		ֱ�ӵ���������Ա����������Ҫ�ڱ���ʱȷ������λ�ã�������һЩ�����(��������������)

	*/

	void inserter_list()
	{
		//back_inserter ��Ŀ������ĩβ����Ԫ��
		//ʹ��push_back��Ԫ����ӵ�Ŀ��������ĩβ

		std::vector<int> vec = { 1,2,3 };
		std::back_insert_iterator<std::vector<int>> backInserter(vec);
		//Ҳ����ʹ��back_inserter ����һ��������������� auto it = std::back_inserter(vec)

		*backInserter = 4; //��Ԫ��4���뵽vec��ĩβ
		++backInserter;

		std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));


		//front_inserter ��Ŀ��������ͷ����Ԫ��
		//ʹ��push_front ��Ԫ����ӵ�Ŀ��������ͷ

		std::list<int> lst = { 1,2,3 };
		std::front_insert_iterator<std::list<int>> frontInserter(lst);

		*frontInserter = 4;
		++frontInserter;

		std::copy(lst.begin(), lst.end(), std::ostream_iterator<int>(std::cout, " "));
		//ostream_iterator<> д�����


		//inserter ��Ŀ������ָ��λ�ò���Ԫ��
		//ʹ��ָ���Ĳ���λ�ã�ͨ����Ŀ�������ĵ���������Ԫ�ز��뵽ָ��λ��

		std::set<int> mySet = { 1,2,3 };
		std::inserter(mySet, mySet.begin()) = 4; //��Ԫ��4���뵽ָ��λ��
		/*
			auto it = std::inserter(mySet,mySet.begin());
			auto == std::inserter_iterator
			*it = 4;
		*/

		std::copy(mySet.begin(), mySet.end(), std::ostream_iterator<int>(std::cout, " ")); //��mySet�е�ֵ�Ա�׼������ķ�ʽ�������������

	}

	void episode04()
	{
		std::vector<int> v = { 1,2,3,4,5,6,7,8,9 };
		auto it = v.begin() + 3;
		int val = 0;
		//���������Ĺ��������Ǻ���Ҫ��
		auto it1 = std::inserter(v, it); //�ڶ�������Ϊָ����������ĵ������������������֮ǰ����Ԫ��
		*it1 = val; //��it������ָ������Ԫ��λ��ǰ����Ԫ��

		//��һ�������Ĵ���ͬ��Ч��
		it = v.insert(it, val); //���������ڳ�Ա����ʵ�ֲ���
		++it; //�ƶ���������ԭ��it��λ��

		/*
			front_inserter���ɵĵ�������inserter���ɵĵ�������ȫ��һ��
			front_inserter���ǲ��뵽�����ĵ�һ��Ԫ��֮ǰ
		*/

		std::list<int> lst = { 1,2,3,4 };
		std::list<int> lst2, lst3; //��list
		//�����������listֱ�Ӹ�ֵ�ᱨ��

		//����algorithmͷ�ļ��е�copy����ʵ��Ԫ�ؿ���
		std::copy(lst.begin(), lst.end(), std::front_inserter(lst2)); //����������ΪĿ��λ�õ�������������front_inserterʵ�ַ���
		// 4,3,2,1

		std::copy(lst.begin(), lst.end(), std::back_inserter(lst3)); //back_inserter ʵ������
		//1��2��3��4

		/*
			��Щ����������ṩ��һ�ַ���ķ�ʽ��ͨ��������������ֱ�ӵ��������ĳ�Ա����������Ԫ��
			ѡ��ʹ���ĸ�ȡ����Ҫ�����λ���Լ�ϣ��ʹ�õĲ��뷽��
		*/




	}

	void unique_copy_test()
	{
		//std::unique_copy()��c++��׼���е�һ���㷨�����ڴ�һ����Χ��ֵԪ�ص���һ��Ԫ��
		//�����ڸ��ƹ�����ȥ�����ڵ��ظ�Ԫ�ء���ͨ�����ڴ�һ������Χ�д���һ��������
		//�ظ�Ԫ�ص�������

		//ԭʼ����
		std::vector<int> source = { 1,2,3,4,5,6,2,3,4, };

		//Ŀ�����������ڴ洢ȥ�������ظ�Ԫ�غ�Ľ��
		std::vector<int> destination;

		//Ϊ��������
		std::sort(source.begin(), source.end(), [](int& a, int& b) {
			return a < b;
			});
		//unique_copyҪ��Χ����������ģ���Ϊ��ֻ��ȥ�����ڵ��ظ�Ԫ��

		//ʹ��std::unique_copy ���Ʋ�ȥ�������ظ�Ԫ��
		std::unique_copy(source.begin(), source.end(), std::back_inserter(destination)); //β�������


		//��ӡ���
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
		//�ڶ�������Ϊָ��������ĵ�����

		//ʹ��copy����ʵ�ֶ�������Ԫ�صĿ���
		std::copy(vec.begin(), vec.end(), it1);
		std::copy(vec.begin(), vec.end(), it2);
		std::copy(vec.begin(), vec.end(), it3);
	}


	/*
		iostream������


		��Ȼiostream���Ͳ�������������׼�ⶨ���˿���������ЩIO���Ͷ���ĵ�����

		istream_iterator ��ȡ������
		ostream_iterator ��һ�������д����
		
		��Щ�����������Ƕ�Ӧ��������һ���ض����͵�Ԫ������������
	*/

	void episode05()
	{
		//istream_iterator ����
		//������һ����ʱ������ָ����������Ҫ��д�Ķ�������
			//istream_iterator ʹ�� >> ����ȡ��
			//��ˣ�istream_iterator Ҫ��ȡ�����ͱ��붨�������������
		
		
		//����istream_iterator ����
		std::istream_iterator<int> int_it(std::cin); //ָ������������������
		//��cin��ȡint

		std::istream_iterator<int> int_eof; //Ĭ�ϳ�ʼ������������������β�������

		std::ifstream in("afile"); //�ļ�������
		std::istream_iterator<std::string> str_it(in); //��afile��ȡ�ַ���

		//����һ���󶨵����ĵ�������һ����������������ļ�β��IO���󣬵�������ֵ����β����������

		std::vector<int> vec;
		std::istream_iterator<int> in_iter(std::cin); //�ӱ�׼��������ȡ����
		std::istream_iterator<int> eof; //end of file

		while (in_iter != eof)
		{
			vec.push_back(*in_iter++);
		}

		//����ĳ��������д������Ĵ���
		std::istream_iterator<int> in_iter1(std::cin),eof;

		std::vector<int> vec(in_iter,eof); //ʹ�õ��������г�ʼ��
		//�ӵ�������Χ����vec

		//Ԫ�ط�Χ��ͨ���ӹ��������ж�ȡ���ݻ�õģ������ж�ȡ�����ݱ���������vec



		/*
			ʹ���㷨��������������
			�����㷨ʹ�õ�������������ȡ���ݣ�����������������֧��ĳЩ����������������������ٿ�����ĳЩ�㷨��������������

		*/

		std::istream_iterator<int> in(std::cin), end;
		std::cout << std::accumulate((std::istream_iterator<int>)in,end, 0) << std::endl;
		//�㷨�õ�������������������
		//istream_iterator����������ֵ
		//��׼�Ᵽ֤�����ǵ�һ�ν����õ�����֮ǰ�������ж�ȡ���ݵĲ������Ѿ������
		//��������˵����֧���Ƴٶ��������Ķ�ȡ��







		/*
			ostream_iterator���������

			���ǿ��Զ���������������������Ͷ���ostream_iterator��
			������һ��ostream_iterator����ʱ�����ǿ����ṩ�ڶ�������
			�ڶ�������������һ��C�����ַ���(��һ���ַ������泣������һ��ָ���Կ��ַ���β���ַ������ָ��)
			ostream_iterator����󶨵�һ��ָ��������������յĻ��ʾβ��λ�õ�ostream_iterator

		*/

		//���ǿ�����ostream_iterator�����ֵ������
		std::ostream_iterator<int> out_iter(std::cout," ");
		
		for (auto& e : vec)
		{
			*out_iter++ = e; //�������������(ostream_iterator)��eд�뵽�������
		}

		//��������out_iter��ֵ��ʱ�򣬿��Ժ��Խ����ú͵�������
		//out_iter = e;
		//�����* ��++ʵ���϶�ostream_iterator�������κ�����
		//��˺������Ƕ����ǵĳ���û���κ�Ӱ��

		//����ͨ������copy����ӡvec�е�Ԫ��
		std::copy(vec.begin(),vec.end(),out_iter); //��vec�е�Ԫ�ؿ����������������




	}

	int test02()
	{
		//ʹ������������ȡһ���ı��ļ�������һ��vector�е�string��
		
		//���ı��ļ�
		std::ifstream file("C:\\Users\\wsxl2\\source\\repos\\Generic Algorithm_next\\example.txt");
		
		//����ļ��Ƿ�ɹ���
		if (!file.is_open())
		{
			std::cerr << "Error opening the file." << std::endl;
			return 1; //���ش�����
		}

		//ʹ��std::istream_iterator ���ļ��ж�ȡ�ַ���ֱ���ļ�ĩβ
		std::istream_iterator<std::string> fileIterator(file); //�ı��ļ�������
		std::istream_iterator<std::string> endIterator; //eof
		
		//ʹ�õ��������ļ��е��ַ����洢��vector��
		std::vector<std::string> lines(fileIterator,endIterator); 

		//��ӡvector�е��ַ���
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
		���������

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