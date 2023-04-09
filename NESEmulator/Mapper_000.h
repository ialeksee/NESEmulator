//
//  Mapper_000.h
//  NESEmulator
//
//  Created by Ivaylo Alekseev on 8.04.23.
//

#ifndef Mapper_000_h
#define Mapper_000_h
#include "Mapper.h"

class Mapper_000 : public Mapper
{
public:
    Mapper_000(uint8_t prgBanks, uint8_t chrBanks);
    ~Mapper_000();

public:
    bool cpuMapRead(uint16_t addr, uint32_t &mapped_addr) override;
    bool cpuMapWrite(uint16_t addr, uint32_t &mapped_addr) override;
    bool ppuMapRead(uint16_t addr, uint32_t &mapped_addr) override;
    bool ppuMapWrite(uint16_t addr, uint32_t &mapped_addr) override;
};

#endif /* Mapper_000_h */
