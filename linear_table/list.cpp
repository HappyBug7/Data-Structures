#include"list.h"

int main() {
	LinearList<Array, std::string> my_list1 = LinearList<Array, std::string>(10);
	LinearList<Array, std::string> my_list2 = LinearList<Array, std::string>(10);
	LinearList<Array, std::string> receiver1 = LinearList<Array, std::string>(10);
	LinearList<Array, std::string> receiver2 = LinearList<Array, std::string>(10);

	my_list1.push_back("hello");
	my_list1.push_back("happybug");
	my_list2.push_back("cool");
	my_list2.push_back("really?");
	LinearList<Array, std::string>* my_list_new = LinearList<Array, std::string>::merge(my_list1, my_list2); 
	my_list_new->sort("quick");
	"is ok?" >> *my_list_new;
	std::cout << *my_list_new << std::endl;
//	my_list_new->print_list();
}
