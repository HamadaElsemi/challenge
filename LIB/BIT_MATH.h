#ifndef BIT_MATH_H
#define BIT_MATH_H

#define SET_BIT(Reg,BIT_num)  Reg|=1<<BIT_num;
#define CLR_BIT(Reg,BIT_num)  Reg&=~(1<<BIT_num);
#define Toggle_BIT(Reg,BIT_num) Reg^=1<<BIT_num;
#define GET_BIT(Reg,BIT_num) ((Reg>>BIT_num)&(1))

#endif
