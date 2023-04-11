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
    bool nmi = false;
    
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
    
    
    union
    {
        struct
        {
            uint8_t unused : 5;
            uint8_t sprite_overflow : 1;
            uint8_t sprite_zero_hit : 1;
            uint8_t vertical_blank : 1;
        };
        uint8_t reg;
    }status;
    
    union
    {
        struct
        {
            uint8_t grayscale : 1;
            uint8_t render_background_left : 1;
            uint8_t render_sprites_left : 1;
            uint8_t render_background : 1;
            uint8_t render_sprites : 1;
            uint8_t enhance_red : 1;
            uint8_t enhance_green : 1;
            uint8_t enhance_blue : 1;
        };
        uint8_t reg;
    }mask;
    
    union PPUCTRL
    {
        struct
        {
            uint8_t nametable_x : 1;
            uint8_t nametable_y : 1;
            uint8_t increment_mode : 1;
            uint8_t pattern_sprite : 1;
            uint8_t pattern_background : 1;
            uint8_t sprite_size : 1;
            uint8_t slave_mode : 1; // unused
            uint8_t enable_nmi : 1;
        };
        uint8_t reg;
    }control;
    
    
    uint8_t address_latch = 0x00;
    uint8_t ppu_data_buffer = 0x00;
    uint16_t ppu_address = 0x0000;
};
#endif /* olc2C02_h */
