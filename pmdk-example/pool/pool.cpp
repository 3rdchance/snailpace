/* example of pool management
 * create a pool, reopen it, increase the count
 */
#include <iostream>
#include "libpmemobj++/persistent_ptr.hpp"
#include "libpmemobj++/pool.hpp"
#include "libpmemobj.h"

#define LAYOUT "TEST-OBJCPP"

struct root {
	int cnt;
};


int main(int argc, char **argv)
{
	bool create = false;

	if (argc < 2) {
		std::cout << "Usage: " << argv[0] << " pool-file\n";
		return -1;
	}

	pmem::obj::pool<root> pop;
	try {
            pop = pmem::obj::pool<root>::open(argv[1], LAYOUT);
        } catch(const std::exception &e) {
		std::cerr << "Open failed: " << e.what() << std::endl;
		create = true;
	}

	if (create) {
		try {
		pop = pmem::obj::pool<root>::create(argv[1], LAYOUT, PMEMOBJ_MIN_POOL, 0666);
		} catch (const std::exception &e) {
			std::cout << "\033[1;31m Create Pool Failed " << e.what() << 
				"\n\033[0m";
			return -1;
		}
	}

	std::cout << "\033[1;32m Pool " << argv[1] << "Create Success\n \033[0m";
	auto root = pop.root();
	if (create) {
		root->cnt = 0;
	} else  {
		root->cnt++;
	}

	std::cout << "\033[1;32mOpen Pool " << argv[1] <<" " << root->cnt << "times \n \033[0m";
	pop.close();
	return 0;

}
