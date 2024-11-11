#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>  // Für std::bitset

int main() {
    
    // Pfad zur Datei im 'data'-Ordner
    std::string dateiname = "data/test.txt";

    // Öffnen der Datei im Binärmodus
    std::ifstream file(dateiname, std::ios::binary);

    // Überprüfen, ob die Datei erfolgreich geöffnet wurde
    if (!file) {
        std::cerr << "Die Datei konnte nicht geöffnet werden!" << std::endl;
        return 1;
    }

    const size_t blockBreite = 64; // Anzahl der Zeichen, die auf einmal gelesen werden
    char buffer[blockBreite  + 1];      // Buffer für das Lesen der Zeichen

    while (file.read(buffer, blockBreite) || file.gcount() > 0) {
        // Anzahl der tatsächlich gelesenen Zeichen (nützlich für den letzten Block)
        std::streamsize byteGelesen = file.gcount();

        // Ausgabe der gelesenen Zeichen in Binärform
        for (std::streamsize i = 0; i < byteGelesen; ++i) {
            // Ausgabe jedes Bytes als binären Wert (8 Bit pro Zeichen)
            std::cout << std::bitset<4>(static_cast<unsigned char>(buffer[i])) << ' ';
        }
        std::cout << "**************************************************************" << std::endl; // Zeilenumbruch nach jedem 64-Zeichen-Block
    }

    // Datei schließen
    file.close();

    return 0;
}