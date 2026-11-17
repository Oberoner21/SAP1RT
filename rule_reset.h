/*
    SAP1PT - SAP1 Pure Turing
    Modul:  rule_reset.h

    Copyright(C) 2026 by Oberoner
*/

/*
    Reset procedure to start the machine
    Entry conditions: Nothing is marked
    Entry point     : NP pointer position 0
    Exit point      : NP pointer position 0 
    Rules           : 87 
*/

void GenerateRuleRESET(uint16_t rule) {

    // ------------ Skip to position MAR0 -------------

    // Skip the MAR and go to rule FETCH
    SetRule(rule, '0', '0', MAR, RULE_FETCH);
    SetRule(rule, '1', '1', MAR, RULE_FETCH);
    SetRule(rule, '$', '$', MAR, RULE_FETCH);
    rule++;
}