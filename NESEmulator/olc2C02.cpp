//
//  olc2C02.cpp
//  NESEmulator
//
//  Created by Ivaylo Alekseev on 4.04.23.
//

#include "olc2C02.h"
#include <cstdint>


olc2C02::olc2C02()
{
    //pallette from nes dev
    palScreen[0x00] = olc::Pixel(84, 84, 84);
    palScreen[0x01] = olc::Pixel(0, 30, 116);
    palScreen[0x02] = olc::Pixel(8, 16, 144);
    palScreen[0x03] = olc::Pixel(48, 0, 136);
    palScreen[0x04] = olc::Pixel(68, 0, 100);
    palScreen[0x05] = olc::Pixel(92, 0, 48);
    palScreen[0x06] = olc::Pixel(84, 4, 0);
    palScreen[0x07] = olc::Pixel(60, 24, 0);
    palScreen[0x08] = olc::Pixel(32, 42, 0);
    palScreen[0x09] = olc::Pixel(8, 58, 0);
    palScreen[0x0A] = olc::Pixel(0, 64, 0);
    palScreen[0x0B] = olc::Pixel(0, 60, 0);
    palScreen[0x0C] = olc::Pixel(0, 50, 60);
    palScreen[0x0D] = olc::Pixel(0, 0, 0);
    palScreen[0x0E] = olc::Pixel(0, 0, 0);
    palScreen[0x0F] = olc::Pixel(0, 0, 0);

    palScreen[0x10] = olc::Pixel(152, 150, 152);
    palScreen[0x11] = olc::Pixel(8, 76, 196);
    palScreen[0x12] = olc::Pixel(48, 50, 236);
    palScreen[0x13] = olc::Pixel(92, 30, 228);
    palScreen[0x14] = olc::Pixel(136, 20, 176);
    palScreen[0x15] = olc::Pixel(160, 20, 100);
    palScreen[0x16] = olc::Pixel(152, 34, 32);
    palScreen[0x17] = olc::Pixel(120, 60, 0);
    palScreen[0x18] = olc::Pixel(84, 90, 0);
    palScreen[0x19] = olc::Pixel(40, 114, 0);
    palScreen[0x1A] = olc::Pixel(8, 124, 0);
    palScreen[0x1B] = olc::Pixel(0, 118, 40);
    palScreen[0x1C] = olc::Pixel(0, 102, 120);
    palScreen[0x1D] = olc::Pixel(0, 0, 0);
    palScreen[0x1E] = olc::Pixel(0, 0, 0);
    palScreen[0x1F] = olc::Pixel(0, 0, 0);

    palScreen[0x20] = olc::Pixel(236, 238, 236);
    palScreen[0x21] = olc::Pixel(76, 154, 236);
    palScreen[0x22] = olc::Pixel(120, 124, 236);
    palScreen[0x23] = olc::Pixel(176, 98, 236);
    palScreen[0x24] = olc::Pixel(228, 84, 236);
    palScreen[0x25] = olc::Pixel(236, 88, 180);
    palScreen[0x26] = olc::Pixel(236, 106, 100);
    palScreen[0x27] = olc::Pixel(212, 136, 32);
    palScreen[0x28] = olc::Pixel(160, 170, 0);
    palScreen[0x29] = olc::Pixel(116, 196, 0);
    palScreen[0x2A] = olc::Pixel(76, 208, 32);
    palScreen[0x2B] = olc::Pixel(56, 204, 108);
    palScreen[0x2C] = olc::Pixel(56, 180, 204);
    palScreen[0x2D] = olc::Pixel(60, 60, 60);
    palScreen[0x2E] = olc::Pixel(0, 0, 0);
    palScreen[0x2F] = olc::Pixel(0, 0, 0);

    palScreen[0x30] = olc::Pixel(236, 238, 236);
    palScreen[0x31] = olc::Pixel(168, 204, 236);
    palScreen[0x32] = olc::Pixel(188, 188, 236);
    palScreen[0x33] = olc::Pixel(212, 178, 236);
    palScreen[0x34] = olc::Pixel(236, 174, 236);
    palScreen[0x35] = olc::Pixel(236, 174, 212);
    palScreen[0x36] = olc::Pixel(236, 180, 176);
    palScreen[0x37] = olc::Pixel(228, 196, 144);
    palScreen[0x38] = olc::Pixel(204, 210, 120);
    palScreen[0x39] = olc::Pixel(180, 222, 120);
    palScreen[0x3A] = olc::Pixel(168, 226, 144);
    palScreen[0x3B] = olc::Pixel(152, 226, 180);
    palScreen[0x3C] = olc::Pixel(160, 214, 228);
    palScreen[0x3D] = olc::Pixel(160, 162, 160);
    palScreen[0x3E] = olc::Pixel(0, 0, 0);
    palScreen[0x3F] = olc::Pixel(0, 0, 0);
/*
    sprScreen = new olc::Sprite(256, 240);
    sprNameTable[0] = new olc::Sprite(256, 240);
    sprNameTable[1] = new olc::Sprite(256, 240);
    sprPatternTable[0] = new olc::Sprite(128, 128);
    sprPatternTable[1] = new olc::Sprite(128, 128);
 */
}
olc2C02::~olc2C02()
{
    /*
    delete sprScreen;
    delete sprNameTable[0];
    delete sprNameTable[1];
    delete sprPatternTable[0];
    delete sprPatternTable[1];
     */
}

uint8_t olc2C02::cpuRead(uint16_t addr, bool rdonly)
{
    uint8_t data = 0x00;
    if(cart->cpuRead(addr, data))
    {
        
    }
    
    switch (addr)
    {
    case 0x0000:              // Control
        break;
    case 0x0001:              // Mask
        break;
    case 0x0002:              // Status
        data = (status.reg & 0xE0) | (ppu_data_buffer & 0x1F);
        status.vertical_blank = 0;
        address_latch = 0;
        break;
    case 0x0003:              // OAM Address
        break;
    case 0x0004:              // OAM Data
        break;
    case 0x0005:              // Scroll
        break;
    case 0x0006:              // PPU Address
        break;
    case 0x0007:              // PPU Data
            data = ppu_data_buffer;
            ppu_data_buffer = ppuRead(ppu_address);
            
            if(ppu_address > 0x3f00) data = ppu_data_buffer;
            ppu_address++;
        break;

    }
    return 0;
}

void olc2C02::cpuWrite(uint16_t addr, uint8_t  data)
{
    if(cart->cpuWrite(addr, data))
    {
        
    }
    
    switch (addr)
    {
    case 0x0000:              // Control
        control.reg = data;
        break;
    case 0x0001:              // Mask
            mask.reg = data;
        break;
    case 0x0002:              // Status
        break;
    case 0x0003:              // OAM Address
        break;
    case 0x0004:              // OAM Data
        break;
    case 0x0005:              // Scroll
        break;
    case 0x0006:              // PPU Address
        if( address_latch == 0)
        {
            ppu_address = (ppu_address & 0x00FF) | (data << 8);
            address_latch = 1;
        }
        else
        {
            ppu_address = (ppu_address & 0xFF00) | data;
            address_latch = 0;
        }
        break;
    case 0x0007:              // PPU Data
            ppuWrite(ppu_address, data);
            ppu_address++;
        break;
    }
}

// Communications with PPU Bus
uint8_t olc2C02::ppuRead(uint16_t addr, bool rdonly)
{
    uint8_t data = 0x00;
    
    addr &= 0x3FFF;
    if (cart->ppuRead(addr, data))
    {
        
    }
    else if(addr >= 0x0000 && addr <= 0x1FFF)
    {
        data = tblPattern[(addr&0x1000) >> 12][addr&0x0FFF];
    }
    else if(addr >= 0x2000 && addr <= 0x3EFF)
    {
        
    }
    else if(addr >= 0x3F00 && addr <= 0x3FFF)
    {
        addr &= 0x001F;
        if (addr == 0x0010) addr = 0x0000;
        if (addr == 0x0014) addr = 0x0004;
        if (addr == 0x0018) addr = 0x0008;
        if (addr == 0x001C) addr = 0x000C;
        data = tblPalette[addr];
    }
    return  data;
}

void    olc2C02::ppuWrite(uint16_t addr, uint8_t data)
{
    addr &= 0x3FFF;
    if (cart->ppuWrite(addr, data))
    {
        
    }
    else if(addr >= 0x0000 && addr <= 0x1FFF)
    {
        tblPattern[(addr&0x1000) >> 12][addr&0x0FFF] = data;
    }
    else if(addr >= 0x2000 && addr <= 0x3EFF)
    {
        
    }
    else if(addr >= 0x3F00 && addr <= 0x3FFF)
    {
        addr &= 0x001F;
        if (addr == 0x0010) addr = 0x0000;
        if (addr == 0x0014) addr = 0x0004;
        if (addr == 0x0018) addr = 0x0008;
        if (addr == 0x001C) addr = 0x000C;
        tblPalette[addr] = data;
    }

}

void olc2C02::ConnectCartridge(const std::shared_ptr<Cartridge>& cartridge)
{
    this->cart = cartridge;
}

olc::Sprite& olc2C02::GetScreen()
{
    return sprScreen;;
}

olc::Sprite& olc2C02::GetNameTable(uint8_t i)
{
    return sprNameTable[i];
}

olc::Sprite& olc2C02::GetPatternTable(uint8_t i, uint8_t palette)
{
    
    // This function draw the CHR ROM for a given pattern table into
    // an olc::Sprite, using a specified palette. Pattern tables consist
    // of 16x16 "tiles or characters". It is independent of the running
    // emulation and using it does not change the systems state, though
    // it gets all the data it needs from the live system. Consequently,
    // if the game has not yet established palettes or mapped to relevant
    // CHR ROM banks, the sprite may look empty. This approach permits a
    // "live" extraction of the pattern table exactly how the NES, and
    // ultimately the player would see it.

    // A tile consists of 8x8 pixels. On the NES, pixels are 2 bits, which
    // gives an index into 4 different colours of a specific palette. There
    // are 8 palettes to choose from. Colour "0" in each palette is effectively
    // considered transparent, as those locations in memory "mirror" the global
    // background colour being used. This mechanics of this are shown in
    // detail in ppuRead() & ppuWrite()

    // Characters on NES
    // ~~~~~~~~~~~~~~~~~
    // The NES stores characters using 2-bit pixels. These are not stored sequentially
    // but in singular bit planes. For example:
    //
     // 2-Bit Pixels       LSB Bit Plane     MSB Bit Plane
    // 0 0 0 0 0 0 0 0      0 0 0 0 0 0 0 0   0 0 0 0 0 0 0 0
    // 0 1 1 0 0 1 1 0      0 1 1 0 0 1 1 0   0 0 0 0 0 0 0 0
    // 0 1 2 0 0 2 1 0      0 1 1 0 0 1 1 0   0 0 1 0 0 1 0 0
    // 0 0 0 0 0 0 0 0 =  0 0 0 0 0 0 0 0 + 0 0 0 0 0 0 0 0
    // 0 1 1 0 0 1 1 0      0 1 1 0 0 1 1 0   0 0 0 0 0 0 0 0
    // 0 0 1 1 1 1 0 0      0 0 1 1 1 1 0 0   0 0 0 0 0 0 0 0
    // 0 0 0 2 2 0 0 0      0 0 0 1 1 0 0 0   0 0 0 1 1 0 0 0
    // 0 0 0 0 0 0 0 0      0 0 0 0 0 0 0 0   0 0 0 0 0 0 0 0
    //
    // The planes are stored as 8 bytes of LSB, followed by 8 bytes of MSB
    for(uint16_t nTileY = 0; nTileY < 16; nTileY++)
    {
        for(uint16_t nTileX = 0; nTileX < 16; nTileX++)
        {
            uint16_t nOffset = nTileY * 256 + nTileX * 16;
            
            for(uint16_t row = 0; row < 8; row++)
            {
                uint8_t tile_lsb = ppuRead(i * 0x1000 + nOffset + row + 0);
                uint8_t tile_msb = ppuRead(i * 0x1000 + nOffset + row + 8);
                for (uint16_t col = 0; col < 8; col++) {
                    uint8_t pixel = (tile_lsb & 0x01) + (tile_msb & 0x01);
                    tile_lsb >>=1;
                    tile_msb >>=1;
                    
                    sprPatternTable[i].SetPixel
                    (
                        nTileX * 8 + (7 - col),
                        nTileY * 8 + row,
                        GetColourFromPaletteRam(palette, pixel)
                     );
                }
            }
            
        }
    }
    return sprPatternTable[i];
}

void olc2C02::clock()
{
    if(scanline == -1 && cycle == 1)
    {
        status.vertical_blank = 0;
    }

    
    if(scanline == 241 && cycle == 1)
    {
        status.vertical_blank = 1;
        if(control.enable_nmi)
            nmi = true;
    }
    
    //Fake some noise for now
    sprScreen.SetPixel(cycle - 1, scanline, palScreen[((rand() % 2) ? 0x3F : 0x30)]);
    //The renderer never stops
    cycle++;
    
    //inner NES workings, rendere resets the scanline at this point
    if(cycle >= 341)
    {
        cycle = 0;
        scanline++;
        //A complete frame
        if(scanline >= 261)
        {
            scanline = -1;
            frame_complete = true;
        }
    }
}

olc::Pixel& olc2C02::GetColourFromPaletteRam(uint8_t palette, uint8_t pixel)
{
   return palScreen[ppuRead(0x3F00 + (palette << 2) + pixel)];
}
