#pragma once
#include <vector>
#include <string>
#include "port_status.h"

struct PortInfo {
    int nPuerto;
    std::string usage;
};

//Puerto, servicio asociado
const std::vector<PortInfo> commonPorts = {
    {20, "FTP Data"},
    {21, "FTP Control"},
    {22, "SSH"},
    {23, "Telnet"},
    {25, "SMTP"},
    {53, "DNS"},
    {67, "DHCP Server"},
    {68, "DHCP Client"},
    {80, "HTTP"},
    {110, "POP3"},
    {135, "RPC Endpoint Mapper"},
    {137, "NetBIOS Name Service"},
    {138, "NetBIOS Datagram Service"},
    {139, "NetBIOS Session Service"},
    {143, "IMAP"},
    {443, "HTTPS"},
    {445, "SMB / Microsoft-DS"},
    {3389, "RDP"},
    {5357, "WSD"},
    {5985, "WinRM HTTP"},
    {5986, "WinRM HTTPS"}
};
/*
const std::vector<VulnerablePort> vulnerablePorts = {
    {20, "FTP - Data transfer"},
    {21, "FTP - Control"},
    {22, "SSH - Secure Shell"},
    {23, "Telnet (insecure remote login)"},
    {25, "SMTP (email relay)"},
    {53, "DNS"},
    {67, "DHCP - Server"},
    {68, "DHCP - Client"},
    {69, "TFTP (Trivial FTP)"},
    {80, "HTTP (web traffic)"},
    {110, "POP3 (email retrieval)"},
    {111, "RPCbind / SunRPC"},
    {123, "NTP (Network Time Protocol)"},
    {135, "Microsoft RPC / DCOM"},
    {137, "NetBIOS Name Service"},
    {138, "NetBIOS Datagram Service"},
    {139, "NetBIOS Session Service"},
    {143, "IMAP (email retrieval)"},
    {161, "SNMP (monitoring)"},
    {162, "SNMP Trap"},
    {389, "LDAP (directory services)"},
    {443, "HTTPS (secure web traffic)"},
    {445, "Microsoft SMB/CIFS"},
    {465, "SMTPS (secure mail transfer)"},
    {500, "ISAKMP / IKE (IPSec VPN)"},
    {514, "Syslog (logging)"},
    {515, "LPD (printer service)"},
    {520, "RIP (Routing Information Protocol)"},
    {554, "RTSP (streaming)"},
    {587, "SMTP (submission)"},
    {631, "IPP (printing)"},
    {993, "IMAPS (secure IMAP)"},
    {995, "POP3S (secure POP3)"},
    {1080, "SOCKS Proxy"},
    {1433, "Microsoft SQL Server"},
    {1434, "Microsoft SQL Monitor"},
    {1521, "Oracle Database"},
    {1723, "PPTP VPN"},
    {1883, "MQTT (IoT protocol)"},
    {1900, "SSDP (UPnP discovery)"},
    {2049, "NFS (Network File System)"},
    {3306, "MySQL Database"},
    {3389, "RDP (Remote Desktop)"},
    {3690, "Subversion (SVN)"},
    {4444, "Metasploit / Backdoor port"},
    {5060, "SIP (VoIP)"},
    {5432, "PostgreSQL"},
    {5900, "VNC Remote Desktop"},
    {6379, "Redis Database"},
    {8080, "HTTP Alternate / Proxy"},
    {9200, "Elasticsearch"},
    {11211, "Memcached"}
*/

//Si pertenece al vector de arriba es puerto conocido o que se usa en algun protocolo con posible explotacion
inline bool esPuertoConocido(int port, std::string &usage) {
    for (const auto &p : commonPorts) {
        if (p.nPuerto == port) {
            usage = p.usage;
            return true;
        }
    }
    return false;
}

inline std::string clasifRiesgo(int port, PortStatus status) {
    std::string usage;
    if (status == PortStatus::OPEN) {
        if (esPuertoConocido(port, usage)) return "HIGH";
        else return "MEDIUM";
    } else {
        return "LOW";
    }
}
