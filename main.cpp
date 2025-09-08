#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "port_scan.h"
#include "analisis.h"
#include "registrar.h"

int main() {
    std::string ip;
    std::cout << "Ingersar direccion IP: ";
    std::cin >> ip;

    std::string choice;
    std::cout << "Seleccionar (rango/lista)";
    std::cin >> choice;

    std::vector<int> ports;

    if (choice == "rango") {
        int start, end;
        std::cout << "Puerto inicial: ";
        std::cin >> start;
        std::cout << "Puerto final: ";
        std::cin >> end;

        for (int p = start; p <= end; ++p)
            ports.push_back(p);
    } else if (choice == "lista") {
        std::cin.ignore(); // clear newline
        std::string portLine;
        std::cout << "Ingresar puertos. MULTIPLES PUERTOS DEBEN SEPARARSE CON UNA COMA (,): ";
        std::getline(std::cin, portLine);

        std::stringstream ss(portLine);
        std::string token;
        while (std::getline(ss, token, ','))
            ports.push_back(std::stoi(token));
    } else {
        std::cerr << "Error en los datos\n";
        return 1;
    }

    std::cout << "\nScan en curso:  " << ip << "...\n\n";

    for (int port : ports) {
        PortStatus status = scanPort(ip, port, 3000);

        std::string statusStr;
        switch (status) {
            case PortStatus::OPEN: statusStr = "OPEN"; break;
            case PortStatus::CLOSED: statusStr = "CLOSED"; break;
            case PortStatus::FILTERED: statusStr = "FILTERED"; break;
        }

        std::string risk = clasifRiesgo(port, status);

        std::string line = "Puerto " + std::to_string(port) +
                           " - Status: " + statusStr +
                           " - Riesgo: " + risk;

        //En terminal
        std::cout << ip << " - " << line << std::endl;

        // En log
        logScanResult(ip, line);
    }

    return 0;
}
