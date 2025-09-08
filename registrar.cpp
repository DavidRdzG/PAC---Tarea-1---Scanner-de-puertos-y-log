#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <iomanip>
#include <ctime>

inline void logScanResult(const std::string& ip, const std::string& outputLine) {

    std::ofstream file("registro.txt", std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Error al usar registro.txt para escritura.\n";
        return;
    }

    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm* localTimePtr = std::localtime(&t);
    std::tm localTime = *localTimePtr;

    //formato y-m-d h-m-s
    char buffer[20];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &localTime);

    file << buffer << " - " << ip << " - " << outputLine << "\n";

    file.close();
}
