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
  	int line;
	int childnum;
	struct TreeNode* childNode[MAXCHILD];
};
struct TreeNode *root;
void addNodeToParent(struct TreeNode **parent,struct TreeNode *child);
void CreateNode(struct TreeNode **Node,char* name,int line);
void printTree(struct TreeNode* root);
#endif
