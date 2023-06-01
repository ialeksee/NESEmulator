//
//  Bus.h
//  NESEmulator
//
//  Created by Ivaylo Alekseev on 2.04.23.
//

#ifndef Bus_h
#define Bus_h

#include <cstdint>
#include <array>

#include "olc6502.h"
#include "olc2C02.h"
#include "olc2A03.h"
#include "Cartridge.h"

class Bus
{
public:
    Bus();
    ~Bus();
    
public: //devices on the bus
    olc6502 cpu;
    
    // The 2C02 Picture Processing Unit
    olc2C02 ppu;
    //The "2A03" Audio processing unit
    olc2A03 apu;
    
    std::array<uint8_t, 2048> cpuRam;
    
    std::shared_ptr<Cartridge> cart;
    
    uint8_t controller[2];
    
    double dAudioSample = 0.0;
    void SetSampleFrequency(uint32_t sample_rate);
    
private:
    double dAudioTimePerSystemSample = 0.0f;
    double dAudioTimePerNESClock = 0.0;
    double dAudioTime = 0.0;
    
public: //Bus read and write
    void cpuWrite(uint16_t addr, uint8_t data);
    uint8_t cpuRead(uint16_t addr, bool bReadOnly = false);
    
public: // System Interface
    void InsertCartridge(const std::shared_ptr<Cartridge>& cartridge);
    void reset();
    
    //returns true if new audio sample was played this cycle.
    bool clock();
    
private:
    //A count of how many clocks have passed
    uint32_t nSystemClockCounter = 0;
    
    uint8_t controller_state[2];
    
    uint8_t dma_page = 0x00;
    uint8_t dma_addr = 0x00;
    uint8_t dma_data = 0x00;
    
    bool dma_transfer = false;
    bool dma_dummy = true;
};

#endif /* Bus_h */
