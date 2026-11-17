/*
    SAP1PT - SAP1 Pure Turing
    Modul:  notepad.h

    Copyright(C) 2026 by Oberoner
*/
#pragma once
#include "symbols.h"

#define     NOTEPADSIZE     0x100       // SAP1PT Notepad size 
#define     REG_A_START     5           // Notepad start position of register A/B
#define     REGSIZE         41
#define     MEMSTART        40          // Notepad start position of 16 byte SAP1 Memory

// Fibonacci 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233
//           0x01, 0x02, 0x03, 0x05, 0x08, 0x0D, 0x15, 0x22, 0x37, 0x59, 0x90, 0xE9
uint8_t Program[16] = {
                    // Fibonacci
	0x51,			//	LDI 0x1
	0x4E,			//	STA [0xE]
	0x50,			//	LDI 0x0
	0x2E,			//	ADD [0xE]
	0x70,			//	JC 0x0
	0xE0,			//	OUT
	0x4F,			//	STA [0xF]
	0x1E,			//	LDA [0xE]
	0x4D,			//	STA [0xD]
	0x1F,			//	LDA [0xF]
	0x4E,			//	STA [0xE]
	0x1D,			//	LDA [0xD]
	0x63,			//	JMP 0x3
	0x00,
	0x00,
	0x00
};


const char SAP1_REGISTERS[] = (

    // ZC A/B              PC       IR   MAR
    "$$10$0000000000000000$00000001$0000$0000"
);

uint16_t notePad[NOTEPADSIZE];


void CopyProgram(){

    uint8_t npPointer = MEMSTART;

    for(uint8_t i=0; i<16; i++) {

        notePad[npPointer] = symbol2num('$');     // Start with $
        notePad[npPointer+1] = Program[i] & 0x80 ? symbol2num('1') : symbol2num('0');
        notePad[npPointer+2] = Program[i] & 0x40 ? symbol2num('1') : symbol2num('0');
        notePad[npPointer+3] = Program[i] & 0x20 ? symbol2num('1') : symbol2num('0');
        notePad[npPointer+4] = Program[i] & 0x10 ? symbol2num('1') : symbol2num('0');
        notePad[npPointer+5] = Program[i] & 0x08 ? symbol2num('1') : symbol2num('0');
        notePad[npPointer+6] = Program[i] & 0x04 ? symbol2num('1') : symbol2num('0');
        notePad[npPointer+7] = Program[i] & 0x02 ? symbol2num('1') : symbol2num('0');
        notePad[npPointer+8] = Program[i] & 0x01 ? symbol2num('1') : symbol2num('0');

        npPointer = npPointer + 9;
    }
    // Mark the end of the last memory byte
    notePad[npPointer] = symbol2num('$');

    // Mark the end of Notepad
    notePad[NOTEPADSIZE-1] = symbol2num('$');
    notePad[NOTEPADSIZE-2] = symbol2num('$');
    notePad[NOTEPADSIZE-3] = symbol2num('$');
}


void BuildNotepad()
{
    uint16_t i;

    // Clear the Notepad
    for(i=0; i<NOTEPADSIZE; i++)
    {
        notePad[i] = 0;
    }

    for(i=0; i<MEMSTART+1; i++)
    {
        notePad[i] = symbol2num(SAP1_REGISTERS[i]);
    }

    CopyProgram();
}