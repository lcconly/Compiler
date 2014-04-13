/*************************************************************************
	> File Name: semantic_analysis.c
	> Author: liucheng
	> Mail: 1035377294@qq.com 
	> Created Time: Thu 10 Apr 2014 10:30:49 PM CST
 ************************************************************************/

#include"semantic_analysis.h"
void travel_grammer_tree(struct TreeNode *root){
	int i=0;
	struct TreeNode *temp=NULL;
	for(i=0;i<root->childnum;i++){
		temp=root->childNode[i];
		if(!strcmp(temp->data,"Def") || !strcmp(temp->data,"ExtDef")){
			travel_def_tree(temp);
			continue;
		}
		else if(!strcmp(temp->data,"Stmt")){
			travel_stmt_tree(temp);
			continue;
		}
		travel_grammer_tree(root);
	}
}

void travel_specifier_tree(struct TreeNode *root){

}
void travel_vardec_tree(struct TreeNode *root){

}
void travel_def_tree(struct TreeNode *root){
	struct TreeNode *specifier_node=root->childNode[0];
	struct TreeNode *declist_node=root->childNode[1];
}
void travel_declist_tree(struct TreeNode *root){

}
void travel_fundec_tree(struct TreeNode *root){

}
void travel_exp_tree(struct TreeNode *root){
	
}
void travel_stmt_tree(struct TreeNode *root){
	
}

