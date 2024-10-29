#include <iostream>
#include <asio.hpp>

//void printer(asio::error& /*e*/)
void printer(const std::error_code& /*e*/)
{
	std::cout << "timer async expired after 5 seconds\n"; 
}

int main()
{
	asio::io_context io_context;

	asio::steady_timer t(io_context, asio::chrono::seconds(5));

	t.async_wait(printer);

	io_context.run();
	
	std::cout << "Main thread exit\n";

	return 0;
	
}
