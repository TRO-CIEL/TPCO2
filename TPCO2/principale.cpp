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
        
        cout << "\n";
        cout << "========================================================================\n";
        cout << "         CONTROLEUR DE QUALITE DE L'AIR INTERIEUR - CO2               \n";
        cout << "========================================================================\n\n";
        
        cout << "Nombre de registres lus : " << erreurModbus << "\n\n";
        
        cout << "--- DONNEES BRUTES ---\n";
        cout << "+--------+----------+--------------+\n";
        cout << "| Indice | Adresse  | Valeur brute |\n";
        cout << "+--------+----------+--------------+\n";
        for (int i = 0; i < 4; i++) {
            cout << "|   " << i << "    |  0x" << hex << (0x0B + i) << dec << "   |     " << tab_reg[i];
            if (tab_reg[i] < 1000) cout << " ";
            if (tab_reg[i] < 100) cout << " ";
            if (tab_reg[i] < 10) cout << " ";
            cout << "     |\n";
        }
        cout << "+--------+----------+--------------+\n\n";
        
        cout << "--- INTERPRETATION DES DONNEES ---\n\n";
        
        cout << "Registre 0x0B (tab_reg[0]) = " << tab_reg[0] << "\n";
        cout << "  -> Description : Donnee du registre 11\n\n";
        
        cout << "Registre 0x0C (tab_reg[1]) = " << tab_reg[1] << "\n";
        cout << "  -> Description : Donnee du registre 12\n\n";
        
        cout << "Registre 0x0D (tab_reg[2]) = " << tab_reg[2] << "\n";
        cout << "  -> Description : Donnee du registre 13\n\n";
        
        cout << "Registre 0x0E (tab_reg[3]) = " << tab_reg[3] << "\n";
        cout << "  -> Description : Donnee du registre 14\n\n";
        
        cout << "========================================================================\n";
        cout << "Note : Consultez la documentation CO2Meter.pdf pour la signification\n";
        cout << "       exacte des registres 0x0B a 0x0E\n";
        cout << "========================================================================\n";
        
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