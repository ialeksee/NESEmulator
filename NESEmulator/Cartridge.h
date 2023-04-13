//
//  Cartridge.h
//  NESEmulator
//
//  Created by Ivaylo Alekseev on 4.04.23.
//

#ifndef Cartridge_h
#define Cartridge_h
#include <cstdint>
#include <string>
#include <fstream>
#include <vector>

#include "Mapper_000.h"
class Cartridge
{
public:
    Cartridge(const std::string& sFileName);
    ~Cartridge();
    
    bool ImageValid();
    
    enum MIRROR
    {
        HORIZONTAL,
        VERTICAL,
        ONESCREEN_LO,
        ONESCEEN_HI,
    } mirror = HORIZONTAL;
    
private:
    std::vector<uint8_t> vPRGMemory;
    std::vector<uint8_t> vCHRMemory;
    
    uint8_t nMapperID = 0;
    uint8_t nPRGBanks = 0;
    uint8_t nCHRBanks = 0;
    
    std::shared_ptr<Mapper> pMapper;
    bool bImageValid = false;
public:
    // Communications with Main Bus
    bool cpuRead(uint16_t addr, uint8_t &data);
    bool cpuWrite(uint16_t addr, uint8_t  data);
    
    // Communications with PPU Bus
    bool ppuRead(uint16_t addr, uint8_t &data);
    bool ppuWrite(uint16_t addr, uint8_t data);
};

#endif /* Cartridge_h */
