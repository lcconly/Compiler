#ifndef __SEMANTIC_ANALYSIS_H__
#define __SEMANTIC_ANALYSIS_H__
/*************************************************************************
	> File Name: semantic_analysis.h
	> Author: liucheng
	> Mail: 1035377294@qq.com 
	> Created Time: Thu 10 Apr 2014 10:34:21 PM CST
 ************************************************************************/

#include"hash_table.h"
#include"Node.h"
FieldList* varList[MAXHARSHSIZE];
FieldList* structList[MAXHARSHSIZE];
FieldList* funcList[MAXHARSHSIZE];
Type *funType;
FieldList *func;
static int sem_error=0;
/*遍历语法树*/
void travel_grammer_tree(struct TreeNode *root);
/*遍历specifier_node返回类型*/
Type* travel_specifier_tree(struct TreeNode *root);
/*遍历vardec到最后一层识别ID*/
FieldList* travel_vardec_tree(struct TreeNode *root);
/*遍历所有的定义*/
void travel_def_tree(struct TreeNode *root);
/*遍历deflist的declist*/
FieldList* travel_declist_tree(struct TreeNode *root,Type *type,FieldList *field,int tag);
/*遍历fundc*/
FieldList* travel_fundec_tree(struct TreeNode *root,FieldList *structfield);
/*遍历exp的子树*/
Type* travel_exp_tree(struct TreeNode *root);
/*遍历stmt的子树*/
void travel_stmt_tree(struct TreeNode *root);
/*遍历全局变量列表*/
void travel_extdeclist_tree(struct TreeNode *root,Type *type);
/*遍历deflist节点，包含全局变量和函数内变量*/
FieldList* travel_deflist_tree(struct TreeNode *root,FieldList *field);
/*分组2.3判断结构内部定义相等则两个结构相同*/
bool charge_struct_equal(Type *type1,Type *type2);
/*判断两个type是否相等*/
bool charge_type_equal(Type *type1,Type *type2);
/*判断函数参数是否一致*/
bool charge_args_equal(FieldList *args1,FieldList *args2);
/*遍历args的子树*/
FieldList*  travel_args_tree(struct TreeNode *root,FieldList *args);
/*获取函数参数类型，传递到str*/
void copyStr(FieldList* myStr, char *str);
/*args遍历传递参数类型到str*/
void copyStr_args(FieldList* myStr, char *str);
/*左值操作判断*/
bool charge_lefthand_variable(struct TreeNode *root);
#endif
