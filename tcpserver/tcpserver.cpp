#include <iostream>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main()
{
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    SOCKET serverSocket;
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) { cout << "socket create fail" << endl; WSACleanup();return 1;}
    cout << "\n\n\n socket works good, grats!\n" << endl;
    closesocket(serverSocket); WSACleanup();

    return 0;
}