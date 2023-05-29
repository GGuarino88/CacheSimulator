//
//  Cache.hpp
//  Project2CacheSimulator
//
//  Created by Giuseppe Guarino on 9/29/22.
//

#ifndef Cache_hpp
#define Cache_hpp

#include "Slot.hpp"

class Cache {
    
protected:
    
    static const short CACHE_SIZE = 16;
    short *MM;        // pointer will hold the address of the beginning of Main Memory acting
                      // as the link from cache to Main memory
    
    // variables that will hold the information decoded from the address provided by the user
    short tag;
    short slotNum;
    short offset;
    short blockBegin;
    Slot cacheSlots[CACHE_SIZE];
    
    //setter
    void setAddress(short);
    // helper functions used to retrieve and write back to Main Memory data
    void readBlockFromMM(const short*);
    void writeBackToMM(short*);
    
public:
    
    Cache(short*);
    bool read(short);
    bool write(short,short);
    // getters
    short getValueAtAddress(const short&);
    Slot* getCacheSlots();
    
    ~Cache(){};
    
    
};
#endif /* Cache_hpp */
