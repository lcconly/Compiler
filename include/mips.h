/*************************************************************************
	> File Name: mips.h
	> Author: liucheng
	> Mail: 1035377294@qq.com 
	> Created Time: Thu 12 Jun 2014 06:40:43 PM CST
 ************************************************************************/

#ifndef __MIPS_H__
#define __MIPS_H__
#include"list.h"
#include"../include/semantic_analysis.h"
typedef struct OPOFFSET{
	Operand op;
	int offset;
	ListHead queue;	
}opoffset;

ListHead opoff;
/*mips打印函数*/
void mips_print(char *name);
/*设置便宜量*/
void set_offset(Operand op);
/*获取偏移量*/
void get_offset(Operand op);
#endif
