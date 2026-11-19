#include <iostream>
#include <thread>
#include <chrono>
#include "symbols.h"
#include "utils.h"
#include "rulebook.h"
#include "notepad.h"

using namespace std;

// Variables
bool halt = false;
uint8_t notePadPointer = 0;
uint8_t lastNotePadPointer;
uint8_t rSymbol;
uint8_t wSymbol;
uint8_t nextNotepad;
uint16_t rule = 0;
uint16_t nextRule;
uint16_t lastRule;
long cykles = 0;
long cyklesBefore = 0;

int main() {

    BuildNotepad();
    GenerateRuleBook();

    while(!halt){

        cykles++;
        lastRule = rule;
        lastNotePadPointer = notePadPointer;

        rSymbol = notePad[notePadPointer]; // & 0x01;
        nextRule = ruleBook[rule][rSymbol].nextRule;
        wSymbol = ruleBook[rule][rSymbol].writeSymbol;
        notePad[notePadPointer] = wSymbol;
        notePadPointer = ruleBook[rule][rSymbol].nextNotepad;
        rule = nextRule;

        cykles++;

        if(nextRule == RULE_END | nextRule == RULE_HLT) {

            std::cout << std::endl;
            std::cout << "END State   Cykle: " << static_cast<int>(cykles) << std::endl;
            std::cout << "NPP: " << static_cast<int>(notePadPointer) << 
                "  RSymbol: " << cSymbols[notePad[notePadPointer]] << 
                "  Rule: " << lastRule << ::endl;

            for(uint8_t i = 0; i < 113; i++){
                std::cout << cSymbols[notePad[i]] ;
            }
            std::cout << std::endl;

            if(notePadPointer <= 113) {
                for(uint8_t i = 0; i < notePadPointer; i++){
                    std::cout << "." ;
                }
                std::cout << "|" << std::endl;
                std::cout << std::endl;
            } else {
                for(uint8_t i = 0; i < 113; i++){
                    std::cout << "." ;
                }
                std::cout << std::endl;
            }
            for(uint8_t i = 113; i < 185; i++){
                std::cout << cSymbols[notePad[i]] ;
            }
            std::cout << std::endl;
            if(notePadPointer < 113) {

                std::cout << std::endl;
            } else {

                for(uint8_t i = 113; i < notePadPointer; i++){
                    std::cout << "." ;
                }
                std::cout << "|" << std::endl;
                std::cout << std::endl;
            }
            

            halt = true;

        }

        if(nextRule == RULE_ERROR) {

            std::cout << std::endl;
            std::cout << "ERROR State in Cykle: " << static_cast<int>(cykles) << std::endl;
            std::cout << "NPP: " << static_cast<int>(lastNotePadPointer) << 
                "  RSymbol: " << cSymbols[notePad[lastNotePadPointer]] << 
                "  Rule: " << lastRule << ::endl;

            for(uint8_t i = 0; i < 113; i++){
                std::cout << cSymbols[notePad[i]] ;
            }
            std::cout << std::endl;

            if(lastNotePadPointer <= 113) {
                for(uint8_t i = 0; i < lastNotePadPointer; i++){
                    std::cout << "." ;
                }
                std::cout << "|" << std::endl;
                std::cout << std::endl;
            } else {
                for(uint8_t i = 0; i < 113; i++){
                    std::cout << "." ;
                }
                std::cout << std::endl;
            }
            for(uint8_t i = 113; i < 185; i++){
                std::cout << cSymbols[notePad[i]] ;
            }
            std::cout << std::endl;
            if(lastNotePadPointer < 113) {

                std::cout << std::endl;
            } else {

                for(uint8_t i = 113; i < lastNotePadPointer; i++){
                    std::cout << "." ;
                }
                std::cout << "|" << std::endl;
                std::cout << std::endl;
            }
            
            halt = true;

        }

        if(rule == RULE_OUT) {

            uint8_t outVal = 0;
            if(notePad[19] == 1) outVal |= 0x01;
            if(notePad[17] == 1) outVal |= 0x02;
            if(notePad[15] == 1) outVal |= 0x04;
            if(notePad[13] == 1) outVal |= 0x08;
            if(notePad[11] == 1) outVal |= 0x10;
            if(notePad[9] == 1) outVal |= 0x20;
            if(notePad[7] == 1) outVal |= 0x40;
            if(notePad[5] == 1) outVal |= 0x80;

            std::cout << "Cykles: " << static_cast<int>(cykles - cyklesBefore) << 
                "  Out: " << static_cast<int>(outVal) << ::endl;
            cyklesBefore = cykles;

            // Delay
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }

        // Delay
        //std::this_thread::sleep_for(std::chrono::microseconds(1));     // 1MHz system takt
    }

    return 0;
}