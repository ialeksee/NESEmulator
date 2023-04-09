//
//  Mapper.cpp
//  NESEmulator
//
//  Created by Ivaylo Alekseev on 8.04.23.
//

#include "Mapper.h"

Mapper::Mapper(uint8_t prgBanks, uint8_t chrBanks)
{
    nPRGBanks = prgBanks;
    nCHRBanks = chrBanks;
}
Mapper::~Mapper()
{
    
}
