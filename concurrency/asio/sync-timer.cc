#include <iostream>
#include <asio.hpp>

int main()
{
	asio::io_context io_context;

	asio::steady_timer t(io_context, asio::chrono::seconds(5));

	t.wait();
	
	std::cout << "timer expire fter 5 seconds\n";

	return 0;
}
