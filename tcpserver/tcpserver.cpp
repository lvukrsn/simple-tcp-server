#include <iostream>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsaData;
    SOCKET serverSocket;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cout << "err create socket" <<WSAGetLastError()<<std::endl;
        return 1;
    }
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {std::cout<< "socket create fail" << std::endl; WSACleanup();return 1;}
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(8080);
    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR){
        std::cout<<"err bind socket"<<WSAGetLastError()<<std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cout << "err listen socket"<<WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }
    std::cout << "waiting for client...\n" << std::endl;




   
    while (true) {
        char buffer[1024];
        SOCKET clientSocket;
        clientSocket = accept(serverSocket, nullptr, nullptr);
        if (clientSocket == INVALID_SOCKET) {
            std::cout << "err accept socket" << WSAGetLastError() << std::endl; break;
        }
        while (true) {
            int byteReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
            if (byteReceived == SOCKET_ERROR) {
                std::cout << "err recv" << WSAGetLastError() << std::endl;
                break;
            }
            if (byteReceived == 0) {
                std::cout << "client disconnected" << std::endl;
                break;
            }
            buffer[byteReceived] = '\0';
            int sendResult = send(clientSocket, buffer, byteReceived, 0);
            if (sendResult == SOCKET_ERROR) {
                std::cout << "err send" << WSAGetLastError() << std::endl;
                break;
            }
            std::cout << "received: " << buffer << std::endl;
        }
        closesocket(clientSocket);
    }
    std::cout << "\n\n\n socket works good, grats!\n" << std::endl;
	closesocket(serverSocket);WSACleanup();
    return 0;
}