# PAC---Tarea-1---Scanner-de-puertos-y-log

Descripcion general

Esta herramienta consiste en el desarrollo de un scanner de puertos en C++. Lleva a cabo el scan de puertos de un direccion IP ingresada por el usuario. Los puertos se pueden ingresar en forma de rango de puertos (puertoA - puertoB) o en forma de lista (puertoA, puertoB, puertoC).
Se determina el nivel de riesgo de una posible explotacion del puerto basado en el status del puerto y si es un puerto asociado a un servicio conocido por ser objetivo de ataques. Los resultados del scan y el veredicto de nivel de riesgo son guardados en un archivo de texto llamado "registro.txt". En caso de no haber un registro se creara al momento de presentar los resultados.

Integrantes del equipo

    David Alejandro Rodriguez Garcia - 1814035

    Jair Eliud Flores Puente - 2076332

Instrucciones de compliacion y ejecucion

  Requisitos: Sistema operativo: Windows, Compilador g++
    
  Librerias:
  
      #include <winsock2.h>
      #pragma comment(lib, "ws2_32.lib")
      #include <ws2tcpip.h>
      #include <iostream>
      #include <fstream>
      #include <string>
      #include <vector>
      #include <sstream>
      #include <chrono> 
      #include <ctime> 
      #include <iomanip>

Compilacion:

    g++ main.cpp -o main.exe -lws2_32
  
    .\main.exe

Enfoque:

Este proyecto utiliza Winsock2 para realizar conexiones a puertos sobre la direccion IP ingresada. Para cada puerto dentro del rago o lista de puertos objetivo se intenta establecer una conexion y determina el status del puerto dada su respuesta.

Salida generada:

El archivo de texto en el que se registran los resultados contiene:

    Fecha en formato (yyyy-mm-dd)
    Hora en formato (hh:mm:ss)
    Direccion IPv4 (xxx.xxx.xxx.xxx)
    Puerto (xxxxx)
    Status (OPEN/CLOSED/FILTERED)
    Nivel de riesgo (HIGH/MEDIUM/LOW)

Referencias

    https://learn.microsoft.com/es-es/windows/win32/winsock/creating-a-basic-winsock-application
    https://learn.microsoft.com/es-es/cpp/standard-library/chrono-functions?view=msvc-170
