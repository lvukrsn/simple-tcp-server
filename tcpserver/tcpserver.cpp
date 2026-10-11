#include <iostream>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(    2, 2), &wsaData);
    SOCKET serverSocket;
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (WSAStartup(MAKEWORD(2, 2), &wsaData ) != 0){cout<< "err create socket" << endl;
    }
    if (serverSocket == INVALID_SOCKET) { cout << "socket create fail" << endl; WSACleanup();return 1;}
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(8080);
    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR){
        cout << "err bind socket" <<WSAGetLastError()<<endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        cout << "err listen socket"<<WSAGetLastError() << endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }
    cout << "bind success!" << endl;
    cout << "\n\n\n socket works good, grats!\n" << endl;
    cout << "press any key to exit";cin.get();
    closesocket(serverSocket); WSACleanup();
    return 0;
}