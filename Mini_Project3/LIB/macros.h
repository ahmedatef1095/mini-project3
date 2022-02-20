
#ifndef MACROS_H_
#define MACROS_H_

/******Bit Operation****/
#define SET_BIT(REG,Bit)        ((REG) |= (1<<Bit))
#define CLR_BIT(REG,Bit)        ((REG) &=~(1<<Bit))
#define TOGGLE_BIT(REG,Bit)     ((REG) ^= (1<<Bit))                //xor
#define GET_BIT(REG,Bit)        (((REG) >> Bit) & 0x01)            //return 0 or 1
#define BIT_IS_SET(REG,Bit)     ((REG) & (1<<Bit))                 //return True(number not 1) if bit is 1
#define BIT_IS_CLR(REG,Bit)     (!((REG) & (1<<Bit)))             //return false(zero) if bit is 0

#define ROR(REG,NUM)            ((REG) = (((REG) >> NUM) | ((REG) << (sizeof(REG)*8-NUM))))
#define ROL(REG,NUM)            ((REG) = (((REG) << NUM) | ((REG) >> (sizeof(REG)*8-NUM))))


#endif /* LIB_MACROS_H_ */
