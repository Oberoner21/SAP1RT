/*
    SAP1RT - SAP1 Turing Random Access
    Modul: rulebook.h

    Rule book for the project

*/

#pragma once
#include "symbols.h"

#define     HIGH            1
#define     LOW             0
#define     RULES           0x4000
#define     SYMBOLS         2

#define     RULE_RESET      0
#define     RULE_FETCH      20
#define     RULE_DECODE     150
#define     RULE_NOP        200
#define     RULE_LDA        250
#define     RULE_ALU        350
#define     RULE_ADD        400
#define     RULE_SUB        500
#define     RULE_STA        600
#define     RULE_LDI        1000
#define     RULE_JMP        750
#define     RULE_JC         800
#define     RULE_JZ         850
#define     RULE_OUT        900
#define     RULE_HLT        950
#define     RULE_END        4094
#define     RULE_ERROR      4095

// Register positions
#define     FZ              2
#define     FC              3
#define     AB              20
#define     PC              29
#define     IR              34
#define     MAR             39


uint8_t controlLines = 0;

struct rule_t {
    uint16_t nextRule;
    uint8_t nextNotepad;
    uint8_t writeSymbol;
    uint8_t outCLK;
} ruleBook[RULES][SYMBOLS];


void ResetControlLines(){
     
    controlLines = 0;
}

void SetSerOUTCLK(uint8_t value){

    if(value == HIGH) controlLines = controlLines | 0x01;
    else controlLines = controlLines & 0xFE;
}


void SetRule(uint16_t rule, uint8_t readSymbol, uint8_t writeSymbol, uint8_t nextNotepad, uint16_t nextRule)
{
    uint8_t numReadSymbol = symbol2num(readSymbol);

    ruleBook[rule][numReadSymbol].writeSymbol = symbol2num(writeSymbol);
    ruleBook[rule][numReadSymbol].nextNotepad = nextNotepad;
    ruleBook[rule][numReadSymbol].nextRule = nextRule;
    // Set the control lines
    ruleBook[rule][numReadSymbol].outCLK = controlLines & 0x01 ? 1 : 0;
}

#include "rule_reset.h"
#include "rule_fetch.h"
#include "rule_decode.h"
#include "rule_ldi.h"
#include "rule_sta.h"

void GenerateRuleBook()
{
    //AllocateRuleBook();     // Allocates the rulebook in PSRAM

    uint16_t rule = 0;

    // Initialize all rules as Error State
    while(rule < RULES){

        SetRule(rule, '0', '0', MAR, RULE_ERROR);  
        SetRule(rule, '1', '1', MAR, RULE_ERROR);
        rule++;
    }

    GenerateRuleRESET(RULE_RESET);
    GenerateRuleFETCH(RULE_FETCH);
    GenerateRuleDECODE(RULE_DECODE);
    GenerateRuleLDI(RULE_LDI);
    GenerateRuleSTA(RULE_STA);
}

