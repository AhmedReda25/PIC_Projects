#ifndef BITMATH_H
#define BITMATH_H

#define SET_BIT(reg,bit)    (reg |= (1<<bit))
#define CLR_BIT(reg,bit)    (reg &= ~(1<<bit))
#define TOGGLE_BIT(reg,bit) (reg ^= (1<<bit))

#define GET_BIT(reg,bit)    ((reg &(1<<bit))>>bit)

#endif