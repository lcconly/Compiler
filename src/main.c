#include<stdio.h>
#include<stdlib.h>
#include"../include/semantic_analysis.h"
#include"../include/IR.h"
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
        printf("%s (%d)\n",root->data,root->line);
        printTree(root);
        add_func_read_and_write();
		travel_grammer_tree(root);
        if(sem_error==0){
		//	list_init(&ir_head);
		}
	}
    return 0;
}
