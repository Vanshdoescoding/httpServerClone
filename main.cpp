#include <iostream>
#include <arpa/inet.h>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main () {
    sockaddr_in server_address{};
    server_address.sin_family = AF_INET; // how the adress is formated 
    server_address.sin_port = htons(8080); // which program within in the computer 
// finding the server_adresss.sin_addr since it alreadt exists and just writing in it directly. 
    int conversion_result = inet_pton(
        AF_INET, // // use the IPv4 donversion rules to convert the ip below 
        "127.0.0.1", // tells u which computer 
        &server_address.sin_addr // which computer (binary form of 127.0.0.1)
    );

    if (conversion_result != 1)
    {
        std::cerr << "Failed to convert IP address\n";
        return 1;
    }

    std::string server = "port 8080";
    std::cout << "Connecting to the server: " << server << '\n';
    int socket_id = socket(PF_INET,  // PF is protocol family and PF_Inet means it belongs to IPv4 family. 
         SOCK_STREAM // How the communciation will work SOCKET STREAM -> TCP is what we decided on for reliable communication
         , 0); // just look at the Sock stream and PF_Inet and choose the default protocol that combine sthe 2, 
       if (socket_id == -1)
    {
        std::perror("socket");
        return 1;
    }
    std::cout << socket_id << '\n';

    int successful_bind = bind(socket_id, reinterpret_cast<const sockaddr *>(&server_address), sizeof(server_address));
    //std::cout << successful_bind << '\n';

 if (successful_bind == -1)
    {
        std::perror("bind");
        close(socket_id);
        return 1;
    }
    std::cout << "Socket bound to 127.0.0.1:8080\n";

    listen(socket_id, 5) // make the backlog 5
    accept(socket_id,
         reinterpret_cast<const sockaddr *>(&server_address), // the reason why we have ot change pointer of server adress (sockaddr_in) to sockaddr is bevcause bind expects it for some reason
          &sizeof(server_address))

    close(socket_id);
    return 0;
}