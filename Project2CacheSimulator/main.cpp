//
//  main.cpp
//  Project2CacheSimulator
//
//  Created by Giuseppe Guarino on 9/29/22.
//  Due date 11/02

#include <stdio.h>
#include <cctype>
#include "Cache.hpp"

// helper functions
void initializeMM(short*, const short);
void displayCache(Cache&);

//void displayMM(const short[]);

int main() {
    
    const short MM_SIZE = 2048;
    short MM[MM_SIZE] = {};
    initializeMM(MM, MM_SIZE);
    
    
    Cache cache(MM);
    
    bool repeat = true;
    char choice = ' ';
    
    // program control flow
    do {
        
        short address = 0x0;
        short value = 0x0;
        bool hit = false;
        
        // user is prompted to make a choice, the loop will iterate until the user decides to Exit
        printf("(R)ead, (W)rite, or (D)isplay Cache?\t(E)xit\n");
        scanf(" %c", &choice);
        fflush(stdin);
        
        switch (toupper(choice)) {
                
            case 'R':
                // an adderss will be entered and based on the entry
                // a cache hit or a miss and the value stored in the address at that time will be displayed
                
                printf("What address would you like read?\n");
                scanf(" %hX", &address);
                
                // validate address
                while (address < 0 || address >= MM_SIZE) {
                    fflush(stdin);
                    printf("Please enter an address between \"0\" and \"%X\":\n", MM_SIZE - 1);
                    scanf(" %hX", &address);
                }
                
                hit = cache.read(address);
                
                printf("At that byte there is the value \"%X\" (Cache %s)\n", cache.getValueAtAddress(address), hit? "Hit" : "Miss");
                
                break;
                
            case 'W':
                //an address and a value to be written will be entered and based on the entries
                // a cache hit or a miss and the value written to the address will be displayed
                
                printf("What address would you like to write to?\n");
                scanf(" %hX", &address);
                
                // validate address
                while (address < 0 || address >= MM_SIZE) {
                    fflush(stdin);
                    printf("Error!\nPlease enter an address between \"0\" and \"%X\":\n", MM_SIZE - 1);
                    scanf(" %hX", &address);
                }

                printf("What data would you like to write at that address?\n");
                scanf(" %hX", &value);
                
                // validate value
                while (value < 0 || value > 0xFF) {
                    fflush(stdin);
                    printf("\nError!\nPlease enter a value between \"0\" and \"FF\":\n");
                    scanf(" %hX", &value);
                }
                
                hit = cache.write(address,value);
                
                printf("Value \"%X\" has been written to address \"%X\". (Cache %s)\n", cache.getValueAtAddress(address), address, hit? "Hit" : "Miss");
                              
                break;
                
            case 'D':
                // the whole cache will be displayed
                printf("Slot  Valid  Tag  D-Bit   Data\n");
                
                displayCache(cache);
                
                break;
                
            case 'E':
                printf("Goodbye\n");
                
                repeat = false;
                
                break;
                
            default:
                printf("Not a Valid Operation\n");
                
                break;
        }

        printf("\n");
        
    } while (repeat);

    return 0;
}

// the function initializes Main Memory with values from 0x0 to 0xFF
void initializeMM(short *MM, const short MM_SIZE) {
    
    short x = 0x0;
    
    for (int i = 0; i < MM_SIZE; i++) {
        
        MM[i] = x;
        x++;
        if (x > 0xFF)
            x = !x;
    }
} // end initializeMM

// the function will display the whole cache
void displayCache(Cache &cache) {
    
    for (int i = 0; i < 16;i++) {
        printf("  %X     %X     %X     %X     ", cache.getCacheSlots()[i].getSlotNum(), cache.getCacheSlots()[i].getValidBit(), cache.getCacheSlots()[i].getTag(), cache.getCacheSlots()[i].getDirtyBit());
        
        for (int j = 0; j < 16; j++) {
            printf("%2X ",cache.getCacheSlots()[i].getData()[j]);
        }
        
        printf("\n");
    }
} // end displayCache

//void displayMM(const short MM[]) {
//
//    for (int i = 0; i < 2048; i++) {
//
//        printf("%x ",MM[i]);
//
//        if ((i + 1) % 16 == 0) printf("\n");
//    }
//    printf("\n\n");
//}
