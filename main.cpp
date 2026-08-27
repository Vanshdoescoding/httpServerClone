#include <iostream>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

struct Sockaddr_in
{
    short sin_family 
    u_short sin_port 
    struct sin_addr 
}

int main () {
    std::string server = "port 8080";
    std::cout << "Connecting to the server: " << server << '\n';
    int socket_id = socket(PF_INET, SOCK_STREAM, 0);
    std::cout << socket_id << '\n';
    
   // int check_close = close(3);
   // std::cout << check_close << '\n';

   bind(socket_id, sockaddr_in,  )

return 0;
}