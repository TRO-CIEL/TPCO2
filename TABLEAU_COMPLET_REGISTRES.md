# Tableau des Registres Modbus - Capteur CO2

## Requête Modbus effectuée
```cpp
modbus_read_registers(modbusPasserelle, 0x0B, 4, tab_reg);
```
Cette requête lit 4 registres consécutifs à partir de l'adresse **0x0B (11 en décimal)**.

---

## Tableau complété (valeurs typiques pour un capteur CO2)

| Indice | Adresse du registre | Signification de la donnée | Plage de valeurs | Valeurs lues |
|--------|--------------------|-----------------------------|------------------|--------------|
| **0**  | 0x0B (11)          | tab_reg[0]                  | 0 - 65535        | À mesurer    |
| **1**  | 0x0C (12)          | tab_reg[1]                  | 0 - 65535        | À mesurer    |
| **2**  | 0x0D (13)          | tab_reg[2]                  | 0 - 65535        | À mesurer    |
| **3**  | 0x0E (14)          | tab_reg[3]                  | 0 - 65535        | À mesurer    |

---

## Informations techniques

### Type de données
- **Type** : `uint16_t` (entier non signé 16 bits)
- **Plage générique** : 0 à 65535 (2^16 - 1)

### Comment compléter "Signification de la donnée"

Vous devez consulter la **documentation du capteur CO2** (fichier `CO2Meter.pdf`) et chercher :

1. **Modbus Memory Map** ou **Carte mémoire Modbus**
2. **Holding Registers** ou **Input Registers**
3. Trouver les adresses **0x000B, 0x000C, 0x000D, 0x000E**

---

## Exemples typiques de registres CO2 (à vérifier dans la doc)

### Exemple 1 : Capteur avec CO2, Température, Humidité

| Indice | Adresse | Signification           | Plage de valeurs      | Unité        |
|--------|---------|-------------------------|----------------------|--------------|
| 0      | 0x0B    | CO2 (partie haute)      | 0 - 65535           | ppm (MSB)    |
| 1      | 0x0C    | CO2 (partie basse)      | 0 - 65535           | ppm (LSB)    |
| 2      | 0x0D    | Température             | -400 à 1250         | °C × 10      |
| 3      | 0x0E    | Humidité relative       | 0 à 1000            | % × 10       |

**Note** : Température × 10 signifie que 235 = 23.5°C

### Exemple 2 : Capteur simple

| Indice | Adresse | Signification           | Plage de valeurs      | Unité        |
|--------|---------|-------------------------|----------------------|--------------|
| 0      | 0x0B    | Concentration CO2       | 0 - 5000            | ppm          |
| 1      | 0x0C    | État du capteur         | 0 - 255             | Code status  |
| 2      | 0x0D    | Température             | -40 à 125           | °C           |
| 3      | 0x0E    | Réservé                 | 0                   | -            |

---

## Comment obtenir les "Valeurs lues"

### Méthode 1 : Connecter le capteur réel

1. Connectez le capteur CO2 au réseau
2. Modifiez l'adresse IP dans `principale.cpp` :
   ```cpp
   const char* adressSlave = "192.168.X.XXX"; // Adresse réelle du capteur
   ```
3. Exécutez le programme
4. Le programme affichera les valeurs lues :
   ```
   === DONNEES LUES ===
   Nombre de registres lus : 4

   Indice | Adresse | Valeur lue
   -------|---------|------------
      0   |  0xb  |   450        ← tab_reg[0]
      1   |  0xc  |   235        ← tab_reg[1]
      2   |  0xd  |   620        ← tab_reg[2]
      3   |  0xe  |   455        ← tab_reg[3]
   ```

### Méthode 2 : Utiliser un simulateur Modbus

Si vous n'avez pas de capteur physique, utilisez un simulateur Modbus TCP pour tester.

---

## Format de présentation pour votre rapport

```
┌────────┬──────────┬─────────────────────┬───────────────┬──────────────┐
│ Indice │ Adresse  │ Signification       │ Plage         │ Valeurs lues │
├────────┼──────────┼─────────────────────┼───────────────┼──────────────┤
│   0    │  0x0B    │ [À compléter]       │ 0 - 65535     │ [mesure]     │
├────────┼──────────┼─────────────────────┼───────────────┼──────────────┤
│   1    │  0x0C    │ [À compléter]       │ 0 - 65535     │ [mesure]     │
├────────┼──────────┼─────────────────────┼───────────────┼──────────────┤
│   2    │  0x0D    │ [À compléter]       │ 0 - 65535     │ [mesure]     │
├────────┼──────────┼─────────────────────┼───────────────┼──────────────┤
│   3    │  0x0E    │ [À compléter]       │ 0 - 65535     │ [mesure]     │
└────────┴──────────┴─────────────────────┴───────────────┴──────────────┘
```

---

## Code pour afficher les valeurs

Le code dans `principale.cpp` affiche déjà les valeurs :

```cpp
cout << "\n=== DONNEES LUES ===\n";
cout << "Nombre de registres lus : " << erreurModbus << "\n\n";

cout << "Indice | Adresse | Valeur lue\n";
cout << "-------|---------|------------\n";
for (int i = 0; i < 4; i++) {
    cout << "   " << i << "   |  0x" << hex << (0x0B + i) 
         << dec << "  |   " << tab_reg[i] << "\n";
}
```

---

## Actions à réaliser

1. ✅ **Consulter** le fichier `CO2Meter.pdf` page "Modbus Register Map"
2. ✅ **Noter** la signification des registres 0x0B à 0x0E
3. ✅ **Noter** les plages de valeurs attendues
4. ✅ **Connecter** le capteur CO2 au réseau
5. ✅ **Modifier** l'adresse IP dans le code si nécessaire
6. ✅ **Exécuter** le programme `TPCO2.exe`
7. ✅ **Noter** les valeurs affichées
8. ✅ **Compléter** le tableau pour votre rapport

---

## Résumé

- **Plage de valeurs générique** : 0 à 65535 pour tous les registres `uint16_t`
- **Plages spécifiques** : Dépendent de la documentation du capteur
- **Valeurs lues** : Obtenues en exécutant le programme avec le capteur connecté
- **Signification** : À trouver dans le manuel `CO2Meter.pdf`
