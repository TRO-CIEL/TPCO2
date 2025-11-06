#include <iostream>
#include <cstdlib>
#include "modbus.h"

using namespace std;

int main()
{
    cout << "Programme de lecture du capteur CO2 via Modbus TCP\n\n";
    
    int exitError = EXIT_SUCCESS;
    modbus_t* modbusPasserelle = nullptr;
    int erreurModbus;
    
    const char* adressSlave = "192.168.1.100";
    int portModbus = 502;
    int DEVICE_ID = 1;
    
    try {
        modbusPasserelle = modbus_new_tcp(adressSlave, portModbus);
        
        if (modbusPasserelle == nullptr) {
            throw string("Erreur creation contexte Modbus");
        }
        
        erreurModbus = modbus_set_slave(modbusPasserelle, DEVICE_ID);
        if (erreurModbus == -1) {
            throw string("Erreur modbus_set_slave : ") + modbus_strerror(errno);
        }
        
        erreurModbus = modbus_connect(modbusPasserelle);
        if (erreurModbus == -1) {
            throw string("Erreur modbus_connect : ") + modbus_strerror(errno);
        }
        
        cout << "Connexion etablie avec succes\n";
        
        uint16_t tab_reg[4];
        
        erreurModbus = modbus_read_registers(modbusPasserelle, 0x0B, 4, tab_reg);
        if (erreurModbus == -1) {
            throw string("Erreur modbus_read_registers : ") + modbus_strerror(errno);
        }
        
        cout << "\n=== DONNEES LUES ===\n";
        cout << "Nombre de registres lus : " << erreurModbus << "\n\n";
        
        cout << "Indice | Adresse | Valeur lue\n";
        cout << "-------|---------|------------\n";
        for (int i = 0; i < 4; i++) {
            cout << "   " << i << "   |  0x" << hex << (0x0B + i) << dec << "  |   " << tab_reg[i] << "\n";
        }
        
        modbus_close(modbusPasserelle);
        modbus_free(modbusPasserelle);
        
        cout << "\nConnexion fermee avec succes\n";
    }
    catch (string const& e) {
        cerr << "\nEXCEPTION ATTRAPEE : " << e << "\n";
        exitError = EXIT_FAILURE;
        
        if (modbusPasserelle != nullptr) {
            modbus_close(modbusPasserelle);
            modbus_free(modbusPasserelle);
        }
    }
    
    return exitError;
}