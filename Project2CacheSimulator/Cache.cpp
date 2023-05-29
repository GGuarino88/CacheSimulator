//
//  Cache.cpp
//  Project2CacheSimulator
//
//  Created by Giuseppe Guarino on 9/29/22.
//

#include "Cache.hpp"

// constructor takes a pointer as argument to create the connection to Main Memory
Cache::Cache(short *MM) {
    this->MM = MM;
}

// the function decodes the address provided by the user 
void Cache::setAddress(short address) {
    
    this->tag = (address & 0xF00) >> 8;
    this->slotNum = (address & 0x0F0) >> 4;
    this->offset = address & 0x00F;
    this->blockBegin = address & 0xFF0;
    
}

// the function reads the address and returns true with a cache hit and false with a cache miss
bool Cache::read(short address) {
    
    setAddress(address);
    
    // for a hit the valid bit should be set to 1 and the tag should match with the current block present in the cache
    bool isHit = (getCacheSlots()[slotNum].getValidBit() == 1) && (getCacheSlots()[slotNum].getTag() == tag) ? true : false;
    
    // the function checks if the block is dirty, hence data has beem modified at one of the address in the block
    bool isDirty = getCacheSlots()[slotNum].getDirtyBit() == 1? true : false;
    
    // if there is a cache miss than the function gets the block from main memory at the specified address
    if (!isHit)  {
        
        // before reading data from main memory the function checks if the slot is dirty
        if (isDirty) {
            writeBackToMM(MM);                                  // the block gets written back to main memory
            getCacheSlots()[slotNum].setDirtyBit(0);            // the dirty bit will be resetted to zero (not dirty)
        }
        readBlockFromMM(MM);    //function call to read a block from main memory
    }
    
    return isHit;
} // end read

// the function writes to a speficied address and returns true with a cache hit and false with a cache miss
bool Cache::write(short address, short value) {
    
    // before writing the function reads from the cache to check if there is a cache hit or a cache miss
    bool isHit = read(address);
    
    getCacheSlots()[slotNum].getData()[offset] = value;     // setting the new value to the speficied address
    getCacheSlots()[slotNum].setDirtyBit(1);                // setting the dirty bit to 1 (modified data)
    
    return isHit;
} // end write

// the function copies a block from main memory and copies its data into the cache block
void Cache::readBlockFromMM(const short *mMemory) {
    
    static short block[CACHE_SIZE];             // static array containing the block copied from memory
    
    for (int i = 0; i < CACHE_SIZE; i++) {
        
        block[i] = mMemory[blockBegin + i];
    }
    // the block gets copied to the slot number, valid bit gets set to one to indicate that the data is valid
    getCacheSlots()[slotNum].setData(block);
    getCacheSlots()[slotNum].setValidBit(1);
    getCacheSlots()[slotNum].setTag(tag);
    getCacheSlots()[slotNum].setBlockBeing(blockBegin);
    
} // end readBlockFromMM

// the function takes the block into the cache and writes back the data to main memory
void Cache::writeBackToMM(short *mMemory) {
    
    short blockStart = getCacheSlots()[slotNum].getBlockBegin();
    
    for (int i = 0; i < 16; i++, blockStart++) {
        
        mMemory[blockStart] = getCacheSlots()[slotNum].getData()[i];
    }
    // after the block is written back to main mameory the dirty bit gets set to zero again
    getCacheSlots()[slotNum].setDirtyBit(0);
    
} // end writeBackToMM

// the function returns the value present in cache at a specific address
short Cache::getValueAtAddress(const short &address) {
    
    setAddress(address);
    
    short value = getCacheSlots()[slotNum].getData()[offset];
        
    return value;
} // end getValueAtAddress

// the function returns the pointer to the slots in the cache
Slot* Cache::getCacheSlots() {
    
    return cacheSlots;
} // end getCacheSlots
