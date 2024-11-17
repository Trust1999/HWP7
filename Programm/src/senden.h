#include <iostream>
#include <fstream>
#include <thread>
//#include <b15f/b15f.h>
#include <vector>

/*  Datenstrom
    A - Esc Zeichen
    B - Doppelt

    F - Start

*/
void beginn_senden(std::string);
std::vector<char> sendenVorbereiten(char*, size_t);
void senden(std::vector<char>);
bool melden();

void beginn_senden(std::string eingabe){
    //B15F & drv = B15F :: getInstance () ; //drv wird ein Objekt einer Klasse
    //drv.setRegister (& DDRA , 0x0f ) ;

    const size_t datenBreite = 64; // Anzahl der Zeichen, die auf einmal gelesen werden
    char buffer[datenBreite+1];    // Buffer für das Lesen der Zeichen

    /* Öffnen der Datei im Binärmodus
    std::ifstream file(dateiname, std::ios::binary);*/
    std::ifstream file(eingabe);

    // Überprüfen, ob die Datei erfolgreich geöffnet wurde
    if (!file) {
        
        std::cout << "Die Datei konnte nicht geöffnet werden!" << std::endl;
    }
    else{
        
        //Datei schrittweite Auslesen
        while (file.read(buffer, datenBreite) || file.gcount() > 0) {

            // Anzahl der tatsächlich gelesenen Zeichen (nützlich für den letzten Block)
            size_t nibbleGelesen = file.gcount();

            std::vector<char> sendeBlock= sendenVorbereiten(buffer, nibbleGelesen);
            senden(sendeBlock);
        }

        // Datei schließen
        file.close();
    }
}

std::vector<char> sendenVorbereiten(char buffer[], size_t nG){
    std::vector<char> daten; 
   
    //A-Escape code, F-Startcode
    daten.push_back('A');
    daten.push_back('F');  

    char vorherzeichen = 'A';
    for (size_t i = 0; i < nG; ++i) {
        
        if(buffer[i] == vorherzeichen){
            daten.push_back('A');
            daten.push_back('B');
        }
        vorherzeichen = buffer[i];
        daten.push_back(static_cast<unsigned char>(buffer[i]));
    }

    daten.push_back('A');
    /*TODO
        Hier kommt CRC rein (Prüfsumme [ Du Kiara])
    */
    return daten;
}

void senden(std::vector<char> daten){

    do
    {
        for(size_t i = 0; i < daten.size(); i++){

            //B15F & drv = B15F :: getInstance ();
            //drv.setRegister (& PORTA ,0x0 + daten.at(i));
            std::cout<<daten.at(0x0 + i);
            //drv.delay_ms(50);
    }

        std::cout<<"****************************"<<"\n";

    } while (melden());
}

bool melden(){
    
    /*B15F & drv = B15F :: getInstance ();
    if((( char ) drv.getRegister (& PINA )) == 'A'){
        return false;
    }*/
    return false;
}