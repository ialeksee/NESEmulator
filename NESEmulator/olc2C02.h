//
//  olc2C02.h
//  NESEmulator
//
//  Created by Ivaylo Alekseev on 4.04.23.
//

#ifndef olc2C02_h
#define olc2C02_h
#include <cstdint>
#include <memory>
#include "Cartridge.h"

#include "olcPixelGameEngine.h"

class olc2C02
{
public:
    olc2C02();
    ~olc2C02();

private:
    // Nametables
    uint8_t tblName[2][1024];
    //Palette
    uint8_t tblPalette[32];
    uint8_t tblPattern[2][4096]; //Pattern from the cartridge for future projects
    
public:
    // Communications with Main Bus
    uint8_t cpuRead(uint16_t addr, bool rdonly = false);
    void    cpuWrite(uint16_t addr, uint8_t  data);
    
    // Communications with PPU Bus
    uint8_t ppuRead(uint16_t addr, bool rdonly = false);
    void    ppuWrite(uint16_t addr, uint8_t data);
    
private:
    //The Cartridge
    std::shared_ptr<Cartridge> cart;
    
public:
    //Interface
    void ConnectCartridge(const std::shared_ptr<Cartridge>& cartridge);
    void clock();
    
private:
    olc::Pixel palScreen[0x40];
    olc::Sprite sprScreen = olc::Sprite(256, 240);
    olc::Sprite sprNameTable[2] = {olc::Sprite(256, 254), olc::Sprite(256, 240)};
    olc::Sprite sprPatternTable[2] = {olc::Sprite(128, 128), olc::Sprite(128, 128)};

    
public:
    //Debugging Utilities
    olc::Sprite& GetScreen();
    olc::Sprite& GetNameTable(uint8_t i);
    olc::Sprite& GetPatternTable(uint8_t i, uint8_t palette);
    bool frame_complete = false;
    olc::Pixel& GetColourFromPaletteRam(uint8_t palette, uint8_t pixel);
    
private:
    int16_t scanline = 0;
    int16_t cycle = 0;
};
#endif /* olc2C02_h */
