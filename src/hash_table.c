/*************************************************************************
	> File Name: hash_table.c
	> Author: liucheng
	> Mail: 1035377294@qq.com 
	> Created Time: Thu 10 Apr 2014 02:43:21 PM CST
 ************************************************************************/

#include"../include/hash_table.h"
/*hash_pjw*/
unsigned int hash_pjw(char *name){
	unsigned int val=0,i;
	for(;*name;++name){
		val=(val<<2)+*name;
		if(i=val & ~0x3fff)
			val=(val^(i>>12)) & 0x3fff;
	}
	return val;
}
/*insert node to the list*/
bool insert(FieldList *node,FieldList **list){
	unsigned int index=hash_pjw(node->name);
	FieldList *head,*p,*q;
	head=list[index];
	if(head==NULL){
		printf("insert null\n");
		node->tail=NULL;
		list[index]=node;
	}
	else{
		p=head;
		while(p!=NULL){
			q=p;
			if(!strcmp(node->name,p->name)) return false;
			p=p->tail;
		}
		node->tail=NULL;
		q->tail=node;
	}
	return true;
}
/*fetch the node from the list*/
FieldList *fetch(char* name,FieldList **list){
	unsigned int index=hash_pjw(name);
	FieldList *p;
	p=list[index];
	//printf("get\n");
	while(p!=NULL){
		//printf("while\n");
		if(strcmp(p->name,name)==0)
			return p;
		p=p->tail;
	}
	//printf("get\n");
	return NULL;
}
/*print the whole list*/
void show_hash_table(FieldList **list){
	int i;
	for(i=0;i<MAXHARSHSIZE;i++){
		if(list[i]!=NULL){
			FieldList *p=list[i];
			while(p!=NULL){
				printf("%s\n",p->name);
                switch((p->type)->kind){
                    case 0:{
                        printf("basic: ");
                        if(((p->type)->u).basic==0)
                            printf("int!\n");
                        else if(((p->type)->u).basic==1)
                            printf("float!\n");
                        else 
                            printf("other!\n");
                        break;
                    }   
                    case 1:{
                        printf("array: ");
                        Type *temp=p->type;
                        while(temp->kind==array){
                            printf("size (%d) \n",(temp->u).array.size);
                            temp=(temp->u).array.elem;
                        }
                        printf("kind (%d) \n",(temp->u).basic);
                        break;
                    }
                    case 2:{
                        printf("structure: ");
                        FieldList *temp=(p->type->u).structure;
                        while(temp!=NULL){
                            printf("name= %s ",temp->name);
                            printf("kind= %d \n",temp->type->kind);
                            temp=temp->tail;
                        }
                        break;
                    }
                }
                p=p->tail;
			}
		}
	}
}
