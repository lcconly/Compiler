#include"../include/Node.h"
void CreateNode(struct TreeNode **node,char* name,char* sub_name,int line){
	*node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
	strcpy((*node)->data, name);
    strcpy((*node)->sub_data,sub_name);
	(*node)->line = line;
	(*node)->childnum=-1;
	int i;
	for(i=0;i<MAXCHILD;i++)
		(*node)->childNode[i]=NULL;
}
void addNodeToParent(struct TreeNode **parent,struct TreeNode *child){
	if(child == NULL) return;
	if((*parent)->childNode[(*parent)->childnum+1] == NULL){
		(*parent)->childNode[(*parent)->childnum+1] = (struct TreeNode*)malloc(sizeof(struct TreeNode));
		(*parent)->childNode[(*parent)->childnum+1] = child;
		(*parent)->childNode[(*parent)->childnum+1]->line = child->line;
		(*parent)->childNode[(*parent)->childnum+1]->childnum = child->childnum;
		strcpy((*parent)->childNode[(*parent)->childnum+1]->data,child->data);
        strcpy((*parent)->childNode[(*parent)->childnum+1]->sub_data,child->sub_data);
		((*parent)->childnum)++;
		//printf("Name: %s line: %d childNum:%d\n",(*parent)->data,(*parent)->line,(*parent)->childnum);	
		return;
	}
}
void printTree(struct TreeNode* root){
    int i,j;
    for(i=0;i<=root->childnum;i++){
        if(root->childNode[i]!=NULL){
            for(j=0;j<tab;j++)
                printf("  ");
            printf("%s",(root->childNode[i]->data));
            if(strcmp(root->childNode[i]->sub_data,"")!=0)
                printf(":%s",root->childNode[i]->sub_data);
            if(root->childNode[i]->childnum!=-1)
                printf(" (%d)",root->childNode[i]->line);
            printf("\n");
            tab++;
            printTree(root->childNode[i]);
            tab--;
        }
    }
}
