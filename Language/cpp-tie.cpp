#include <iostream>
#include <string>
#include <tuple>

using namespace std;
using namespace literals;

int main()
{
	int i;
	double d;
	string s;
	tuple<int, double, string> t = {1, 2.0, "s"s};

	std::tie(i, d, s) = t;
}
