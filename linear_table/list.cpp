#include"list.h"

int main() {
	LinearList<DLList, std::string> my_list1 = LinearList<DLList, std::string>(10);
	LinearList<DLList, std::string> my_list2 = LinearList<DLList, std::string>(10);
	LinearList<DLList, std::string> receiver1 = LinearList<DLList, std::string>(10);
	LinearList<DLList, std::string> receiver2 = LinearList<DLList, std::string>(10);
	my_list1.push_back("hello");
	my_list1.push_back("happybug");
	my_list2.push_back("cool");
	my_list2.push_back("really?");
	LinearList<DLList, std::string> my_list_new(10); 
	LinearList<DLList, std::string> temp = my_list1 + my_list2; 
	my_list_new = temp;
	std::cout << temp << std::endl;
	std::cout << my_list_new << std::endl;
	std::cout << my_list1 << std::endl;
	std::cout << my_list2[1] << std::endl;
}
