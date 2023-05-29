//
//  Slot.cpp
//  Project2CacheSimulator
//
//  Created by Giuseppe Guarino on 9/30/22.
//

#include "Slot.hpp"

short Slot::slotCount = 0x0;            // initializing the static variable that will hold the count of the slots

Slot::Slot(){
    
    this->slotNum = slotCount;              // the constructor assigns the slot counter to slotNum that acts as its identifier
    slotCount++;                            // the counter is increased
}

// setters

void Slot::setValidBit(short validBit) {
    
    this->validBit = validBit;
}

void Slot::setDirtyBit(short dirtyBit) {
    
    this->dirtyBit = dirtyBit;
}

void Slot::setTag(short tag) {
    
    this->tag = tag;
}

void Slot::setData(const short *data) {
    
    for (int i = 0 ;i < BLOCK_SIZE; i++) {           // set data copies the values from an array and stores its values
                                                    // in the array that holds the data for the slot
        this->data[i] = data[i];
    }
}

void Slot::setBlockBeing(short blockBegin) {
    
    this->blockBegin = blockBegin;
}

// getters

short Slot::getValidBit() {
    
    return validBit;
}

short Slot::getDirtyBit() {
    
    return dirtyBit;
}

short Slot::getTag() {
    
    return tag;
}

short Slot::getSlotNum() {
    
    return slotNum;
}

short Slot::getBlockBegin() {
    
    return blockBegin;
}

short* Slot::getData() {
    
    return data;
}
