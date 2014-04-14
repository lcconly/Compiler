#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__
/*************************************************************************
	> File Name: semantic_analysis.h
	> Author: liucheng
	> Mail: 1035377294@qq.com 
	> Created Time: Thu 10 Apr 2014 10:34:21 PM CST
 ************************************************************************/

#include"hash_table.h"
#include"Node.h"
FieldList varList[MAXHARSHSIZE];
FieldList structList[MAXHARSHSIZE];
FieldList funcList[MAXHARSHSIZE];
void travel_grammer_tree(struct TreeNode *root);
Type* travel_specifier_tree(struct TreeNode *root);
FieldList* travel_vardec_tree(struct TreeNode *root);
void travel_def_tree(struct TreeNode *root);
FieldList* travel_declist_tree(struct TreeNode *root,Type *type,FieldList *field);
FieldList* travel_fundec_tree(struct TreeNode *root,FieldList *structfield);
void travel_exp_tree(struct TreeNode *root);
void travel_stmt_tree(struct TreeNode *root);
void travel_extdeclist_tree(struct TreeNode *root,Type *type);
FieldList* travel_deflist_tree(struct TreeNode *root,FieldList *field);
#endif
