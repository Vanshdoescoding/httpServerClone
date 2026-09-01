#include <iostream>
#include <arpa/inet.h>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>

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

    int what_the_helly = listen(socket_id, 5); // make the backlog 5
    
    if (what_the_helly == -1){
        std::perror("Listen");
        close(socket_id);
        return 1;
    } 

    sockaddr_in client_address{};
    socklen_t client_address_length = sizeof(client_address);

    int client_socket = accept(socket_id,
         reinterpret_cast< sockaddr *>(&client_address), // the reason why we have ot change pointer of server adress (sockaddr_in) to sockaddr is bevcause bind expects it for some
          &client_address_length);

    if (client_socket == -1)
    {
        std::perror("accept");
        close(socket_id);
        return 1;
    }

    char buffer_1[4096]{};

    ssize_t bytes_received = recv(client_socket, buffer_1, sizeof(buffer_1), 0);

    if (bytes_received == -1){

        std::perror("recv");
        close(client_socket);
        close(socket_id);
        return 1;
    } 
    if (bytes_received == 0){ // the client side of things are already close 
        close(client_socket);
        close(socket_id); 
        return 0;
    } 

    std::cout.write(buffer_1, bytes_received);


   close(client_socket);
  close(socket_id);
    
    return 0;
}