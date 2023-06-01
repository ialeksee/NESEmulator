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

void Bus::SetSampleFrequency(uint32_t sample_rate)
{
    dAudioTimePerSystemSample = 1.0/ (double)sample_rate;
    dAudioTimePerNESClock = 1.0 / 5369318.0; // Magic number -> Core crystal frequency of the NES
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
    else if ((addr >= 0x4000 && addr <= 0x4013) || addr == 0x4015 || addr == 0x4017) // NES APU
    {
        apu.cpuWrite(addr, data);
    }
    else if (addr == 0x4014)
    {
        dma_page = data;
        dma_addr = 0x00;
        dma_transfer = true;
    }
    else if(addr >= 0x4016 && addr <= 0x4017)
    {
        controller_state[addr & 0x0001] = controller[addr & 0x001];
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
    else if(addr >= 0x4016 && addr <= 0x4017)
    {
        data = (controller_state[addr & 0x0001] & 0x80) > 0;
        controller_state[addr & 0x0001] <<= 1;
    }
    return data;
}

void Bus::reset()
{
    cpu.reset();
    nSystemClockCounter = 0;
}

bool Bus::clock()
{
    ppu.clock();

    apu.clock();
    
    if (nSystemClockCounter % 3 == 0)
    {
        if(dma_transfer)
        {
           if(dma_dummy)
           {
              if(nSystemClockCounter % 2 == 1)
              {
                  dma_dummy = false;
              }
           }
            else
            {
                if(nSystemClockCounter % 2 == 0)
                {
                    dma_data = cpuRead(dma_page << 8 | dma_addr);
                }
                else
                {
                    ppu.pOAM[dma_addr] = dma_data;
                    dma_addr++;
                    
                    if(dma_addr == 0x00)
                    {
                        dma_transfer = false;
                        dma_dummy = true;
                    }
                }
            }
        }
        else
        {
            cpu.clock();
        }
    }
    
    bool bAudioSampleReady = false;
    dAudioTime += dAudioTimePerNESClock;
    
    if(dAudioTime >= dAudioTimePerSystemSample)
    {
        dAudioTime -= dAudioTimePerSystemSample;
        dAudioSample = apu.GetOutputSample();
        bAudioSampleReady = true;
    }
    
    if(ppu.nmi)
    {
        ppu.nmi = false;
        cpu.nmi();
    }
    
    nSystemClockCounter++;
    
    return bAudioSampleReady;
}

void Bus::InsertCartridge(const std::shared_ptr<Cartridge>& cartridge)
{
    this->cart = cartridge;
    ppu.ConnectCartridge(cartridge);
}
