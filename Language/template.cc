#include <iostream>
template <class T>
std::ostream& printPointee(std::ostream& out, const T* p) {
	return out << *p << "\n";
}

template<>
std::ostream& printPointee<void>(std::ostream& out, const void* p) {
	return out << *static_cast<const char*> (p) << "\n";
}

int main() {
	int i = 42;
	char c = 'a';
	
	printPointee(std::cout, (void*)&i);
	printPointee(std::cout, (void*)&c);

	return 0;
}
