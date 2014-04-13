/*************************************************************************
	> File Name: semantic_analysis.c
	> Author: liucheng
	> Mail: 1035377294@qq.com
	> Created Time: Thu 10 Apr 2014 10:30:49 PM CST
 ************************************************************************/

#include"semantic_analysis.h"
void travel_grammer_tree(struct TreeNode *root)
{
    int i=0;
    struct TreeNode *temp=NULL;
    for(i=0; i<=root->childnum; i++)
    {
        temp=root->childNode[i];
        if(!strcmp(temp->data,"Def") || !strcmp(temp->data,"ExtDef"))
        {
            travel_def_tree(temp);
            continue;
        }
        else if(!strcmp(temp->data,"Stmt"))
        {
            travel_stmt_tree(temp);
            continue;
        }
        travel_grammer_tree(root);
    }
}

Type* travel_specifier_tree(struct TreeNode *root)
{
    struct TreeNode* type_node=root->childNode[0];
    if(!strcmp(type_node->data,"TYPE"))
    {
        Type* type=(Type *)malloc(sizeof(Type));
        (*type)->kind=basic;
        if(!strcmp(type_node->sub_data,"int"))
            ((*type)->u).basic=0;
        else
            ((*type)->u).basic=1;
        return type;
    }
    else
    {
        struct TreeNode *tag_node=type_node->childNode[1];
        Type *type=(Type *)malloc(sizeof(Type));
        (*type)->kind=structure;
        if(!strcmp(tag_node->data,"OptTag"))
        {
            struct TreeNode *deflist_node=type_node->childNode[3];
            FieldList *field=(FieldList *)malloc(sizeof(FieldList));

        }
    }
    return NULL;
}
FieldList* travel_vardec_tree(struct TreeNode *root)
{
    FieldList *var=(FieldList *)malloc(sizeof(FieldList));
    if(root->childnum==1)
    {
        struct TreeNode *id_node=root->childNode[0];
        (*var)->name=id_node->sub_data;
        return var;
    }
    else
    {
        var=travel_vardec_tree(root->childNode[0]);
        struct TreeNode *int_node=root->childNode[2];
        Type *type=(Type*)malloc(sizeof(Type));
        ((*type)->u).array.size=atoi(int_node->sub_data);
        ((*type)->u).array.elem=NULL;
        (*type)->kind=array;
        if((*var)->type==NULL)
            (*var)->type=(*type);
        else
        {
            Type *p=&((*var)->type);
            while(((*p)->u).array.elem!=NULL)
                (*p)=((*p)->u).array.elem;
            ((*p)->u).array.elem=*type;
        }
        return var;
    }
}
void travel_def_tree(struct TreeNode *root)
{
    struct TreeNode *specifier_node=root->childNode[0];
    struct TreeNode *declist_node=root->childNode[1];

    if(1);
}
void travel_declist_tree(struct TreeNode *root,Type *type,FieldList* field)
{
    int i;
    for(i=0; i<=root->childnum;i++) {
        if(!strcmp(root->data,"VarDec")){
            FieldList *var=(FieldList *)malloc(sizeof(FieldList));
            var=travel_vardec_tree(root);
            if((*var)->type==NULL)
                (*var)->type=*type;
            else{
                Type *p=&((*var)->type);
                while(((*p)->u).array.elem!=NULL)
                    (*p)=((*p)->u).array.elem;
                ((*p)->u).array.elem=*type;
            }
            if((*field)->type==NULL){
                Type *temp=(Type*)malloc(sizeof(Type));
                (*temp)->kind=structure;
                ((*temp)->u).structure=*var;
                (*field)->type=*temp;
            }
            else{
                FieldList *p,*q;
                *p=(((*field)->type)->u).structure;
                while(p!=NULL){
                    q=p;
                    if(!strcmp((*p)->name,(*var)->name)){
                        printf("Error type 15 at line %d: Redefined field '%s'",
                               root->line,(*var)->name);
                        return;
                    }
                    (*p)=(*p)->tail;
                }
                (*q)->tail=*var;
                (*var)->tail=NULL;
            }
            type=NULL;
            field=NULL;
            break;
        }
        travel_declist_tree(root->childNode[i],type,field);
    }

}
void travel_extdeclist_tree(struct TreeNode *root)
{

}
void travel_fundec_tree(struct TreeNode *root)
{

}
void travel_exp_tree(struct TreeNode *root)
{

}
void travel_stmt_tree(struct TreeNode *root)
{

}

