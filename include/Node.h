#ifndef __NODE_H__
#define __NODE_H__
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXDATA 64
#define MAXCHILD 64
#define MAXTREENODE 256
static int tab=1;
struct TreeNode{
	char data[MAXDATA];
	char sub_data[MAXDATA];
  	int line;
	int childnum;
	struct TreeNode* childNode[MAXCHILD];
};
struct TreeNode *root;
/*将节点插入到父*/
void addNodeToParent(struct TreeNode **parent,struct TreeNode *child);
/*创建节点*/
void CreateNode(struct TreeNode **Node,char* name,char* sub_name,int line);
/*打印树*/
void printTree(struct TreeNode* root);
#endif
