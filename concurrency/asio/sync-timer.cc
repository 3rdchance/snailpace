#include <iostream>
#include <asio.hpp>

int main()
{
	asio::io_context io_context;

	asio::steady_timer t(io_context, asio::chrono::seconds(5));

	t.wait();
	
	std::cout << "\033[31mtimer expire fter 5 seconds\033[0m\n";

	return 0;
}
