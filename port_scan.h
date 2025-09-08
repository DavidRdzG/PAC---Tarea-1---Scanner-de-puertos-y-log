// Realizado por Jair Eliud Flores Puente

#include "port_status.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>
#include <chrono>

#pragma comment(lib, "ws2_32.lib")

PortStatus scanPort(const std::string& ip, int port, int timeout_ms = 3000) {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
        std::cerr << "Error en WSAStartup.\n";
        return PortStatus::FILTERED;
    }

    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        WSACleanup();
        return PortStatus::FILTERED;
    }

    u_long mode = 1;
    ioctlsocket(sock, FIONBIO, &mode);

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(ip.c_str());

    auto start = std::chrono::high_resolution_clock::now();
    int result = connect(sock, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> elapsed = end - start;

    if (result == 0) {
        closesocket(sock);
        WSACleanup();
        return PortStatus::OPEN;
    }

    fd_set writeSet;
    FD_ZERO(&writeSet);
    FD_SET(sock, &writeSet);

    timeval tv;
    tv.tv_sec = timeout_ms / 1000;
    tv.tv_usec = (timeout_ms % 1000) * 1000;

    int sel = select(0, NULL, &writeSet, NULL, &tv);

    closesocket(sock);
    WSACleanup();

    if (sel > 0) return PortStatus::CLOSED;
    else return PortStatus::FILTERED;
}

