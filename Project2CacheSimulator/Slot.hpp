//
//  Slot.hpp
//  Project2CacheSimulator
//
//  Created by Giuseppe Guarino on 9/30/22.
//

#ifndef Slot_hpp
#define Slot_hpp

class Slot {
    
private:
    // private variables
    static short slotCount;
    const static short BLOCK_SIZE = 16;
    short slotNum = 0x0;
    short validBit = 0x0;
    short dirtyBit = 0x0;
    short tag = 0x0;
    short blockBegin = 0x0;
    short data[BLOCK_SIZE] = {0x0};
    
public:
    Slot();
    // setters
    void setValidBit(short);
    void setDirtyBit(short);
    void setTag(short);
    void setData(const short*);
    void setBlockBeing(short);
    
    // getters 
    short getValidBit();
    short getDirtyBit();
    short getTag();
    short getSlotNum();
    short getBlockBegin();
    short* getData();
    
    ~Slot() {};
};

#endif /* Slot_hpp */
