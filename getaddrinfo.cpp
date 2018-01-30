#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <cstring>
#include <iostream>

int main(int argc, char *argv[]) {
	struct addrinfo hints;
	struct addrinfo *result, *rp;
	struct sockaddr_in *addr;
	int s;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_flags = 0;
	hints.ai_protocol = 0;

	s = getaddrinfo(argv[1], argv[2], &hints, &result);

	if (s != 0) {
		std::cerr << "getaddrinfo: " << gai_strerror(s) << std::endl;
		return -1;
	}

	for (rp = result; rp != NULL; rp = rp->ai_next) {
		addr = (sockaddr_in*) rp->ai_addr;
		std::cout << inet_ntoa(addr->sin_addr) << std::endl;
	}

	freeaddrinfo(result);

	return 0;
}
