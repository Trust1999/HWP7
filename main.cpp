#include <iostream>
#include <fstream>
#include <b15f/b15f.h>
#include <vector>
std::vector<char> daten; 
size_t prüfsumme = 101101 + 'n' + 6;

std::vector<char> sendenVorbereiten(char buffer[], size_t nG){
   
    //A-Escape code, F-Startcode
    daten.push_back('A');
    daten.push_back('F');  

    char vorherzeichen = 'A';
    //size_t z = 0; //Summe Werte
    //size_t d = 0; //Anzahl Werte
    for (size_t i = 0; i < nG; ++i) {
        
        if(buffer[i] == vorherzeichen){
            daten.push_back('B');
        }
        vorherzeichen = buffer[i];
        //z += vorherzeichen;
        //d += 1;
        daten.push_back(static_cast<unsigned char>(buffer[i]));
    }

    daten.push_back('A');
    
    //Prüfsumme
    //size_t prüfsumme = 0;
    //size_t y = std::strlen(buffer); für größe des buffers
    //prüfsumme = z / d;
    //daten.push_back(prüfsumme);
    daten.push_back(77); //-> in 1 Byte = 01110111
    
    return daten;
};
bool melden(){
    
    B15F & drv = B15F :: getInstance ();
    if((( char ) drv.getRegister (& PINA )) == 'A'){
        return false;
    }
    return true;
};
void senden(std::vector<char>){

    do
    {
        for(size_t i = 0; i < daten.size(); i++){

            B15F & drv = B15F :: getInstance ();
            drv.setRegister(&DDRA, 0xff);
            drv.setRegister (&PORTA ,0x00 + daten.at(i));
            std::cout<<daten.at(i);
            drv.delay_ms(50);
    }

        std::cout<<"****************************"<<"\n";

    } while (melden());
};

int main() {

    B15F & drv = B15F :: getInstance () ; //drv wird ein Objekt einer Klasse
    drv.setRegister (& DDRA , 0x0f ) ;
    
    // Pfad zur Datei im 'data'-Ordner
    std::string dateiname = "/home/kschunk/linuxhome/HWP_II/HWP7-main/Programm/src/test.txt";

    /* Öffnen der Datei im Binärmodus
    std::ifstream file(dateiname, std::ios::binary);*/
    std::ifstream file(dateiname);

    // Überprüfen, ob die Datei erfolgreich geöffnet wurde
    if (!file) {
        std::cerr << "Die Datei konnte nicht geöffnet werden!" << std::endl;
        return 1;
    }

    const size_t datenBreite = 64; // Anzahl der Zeichen, die auf einmal gelesen werden
    char buffer[datenBreite+1];      // Buffer für das Lesen der Zeichen

    while (file.read(buffer, datenBreite) || file.gcount() > 0) {

        // Anzahl der tatsächlich gelesenen Zeichen (nützlich für den letzten Block)
        size_t nibbleGelesen = file.gcount();

        std::vector<char> sendeBlock= sendenVorbereiten(buffer, nibbleGelesen);
        senden(sendeBlock);
    }

    // Datei schließen
    file.close();
    return 0;
}





//melden();

//Hinweis von Eric: CRC: Or , 1 Byte Daten mit 1 Byte Prüfsumme(z.B. 31) vergleichen, nach links Daten verschieben bei most sicnificant Bit um besonderen Code zu haben
//also 1 links weg und 0 hinten dran

/*
Bitfolge = daten? -> 1 Byte
Prüfsumme = z.B. 01110111 -> n = 8, n-1 = 7 -> u_int8 = 8 Bit
-> entstehender Rahmen mit [Bits]...0000000 

Rahmen / 
Prüfsumme    wobei bei jeweils der ersten 1 gestartet wird

Zwischenergebnis /
Prüfsumme          wieder bei jeweils erster 1 und so lange bis erstes relevantes Bit bei oder unter n-1 (hier 6) ist

Bitfolge und Ergebnis gleich dahinter dran
-> dies zusammen sind die Daten die übertragen werden

Empfänger dividiert Daten / Prüfsumme und rechnet die Zwischensumme / Prüfsumme solange bis das Ergebnis kleiner als die Prüfsumme ist (hier 7)
-> 0 heißt erfolg, Rest heißt es ist ein Fehler entstanden und die Daten müssen erneut gesendet werden
*/






