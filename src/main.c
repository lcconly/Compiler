#include<stdio.h>
#include<stdlib.h>
#include"../include/semantic_analysis.h"
extern int hasError;
int main(int argc,char** argv){
    if(argc<=1) return 1;
	FILE *f =fopen(argv[1],"r");
	if(!f){
		perror(argv[1]);
		return 1;
	}
	yyrestart(f);
	//yydebug=1;
    yyparse();
	if(hasError==0){
		//printf("%s (%d)\n",root->data,root->line);
		//printTree(root);
		travel_grammer_tree(root);
	}
    return 0;
}
