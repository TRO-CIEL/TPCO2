#include <iostream>
#include "modbus.h"

int main()
{
    std::cout << "Programme de lecture du capteur CO2 via Modbus TCP\n";
    
    const char* adressSlave = "192.168.1.100";
    int portModbus = 502;
    int DEVICE_ID = 1;
    modbus_t* modbusPasserelle = modbus_new_tcp(adressSlave, portModbus);
    
    return 0;
}