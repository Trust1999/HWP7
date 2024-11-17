#include <iostream>
#include <fstream>
#include <thread>
//#include <b15f/b15f.h>
#include <vector>

#include "senden.h"
#include "empfangen.h"

extern void beginn_senden(std::string);
extern void beginn_empfang();

int main() {

    //Pfad data/test.txt
    std::string eingabe;
    std::cout<<"Eingabe: ";
    std::cin>>eingabe;

    std::thread senden_thread(beginn_senden, eingabe);
    std::thread epmfangen_thread(beginn_empfang);
    
    epmfangen_thread.join();
    senden_thread.join();
    
    return 0;
}

