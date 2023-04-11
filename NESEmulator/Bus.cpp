//
//  Bus.cpp
//  NESEmulator
//
//  Created by Ivaylo Alekseev on 2.04.23.
//
#include <stdio.h>
#include <cstdint>
#include "olc6502.h"
#include <array>
#include "Bus.h"

Bus::Bus()
{
    for(auto &i : cpuRam) i = 0x00;
    
    cpu.ConnectBus(this);
}

Bus::~Bus()
{
    
}

void Bus::cpuWrite(uint16_t addr, uint8_t data)
{
    if(cart->cpuWrite(addr, data))
    {
        //for extension. To change the way the NES behaves
    }
    else if(addr >= 0x0000 && addr <= 0x1FFF)
    {
        cpuRam[addr & 0x7FF] = data;
    }
    else if(addr >= 0x2000 && addr <= 0x3FFF)
    {
        ppu.cpuWrite(addr&0x0007, data);
    }
}

uint8_t Bus::cpuRead(uint16_t addr, bool bReadOnly)
{
    uint8_t data = 0x00;
    
    if(cart->cpuRead(addr, data))
    {
        //Cartridge Address Range
    }
    else if(addr >= 0x0000 && addr <= 0x1FFF)
    {
        data = cpuRam[addr & 0x7FF];
    }
    else if (addr >= 0x2000 && addr <= 0x3FFF)
    {
        data = ppu.cpuRead(addr & 0x0007, bReadOnly);
    }
    
    return data;
}

void Bus::reset()
{
    cpu.reset();
    nSystemClockCounter = 0;
}

void Bus::clock()
{
    ppu.clock();
    if (nSystemClockCounter % 3 == 0)
    {
        cpu.clock();
    }
    
    if(ppu.nmi)
    {
        ppu.nmi = false;
        cpu.nmi();
    }
    
    nSystemClockCounter++;
}

void Bus::InsertCartridge(const std::shared_ptr<Cartridge>& cartridge)
{
    this->cart = cartridge;
    ppu.ConnectCartridge(cartridge);
}
