/*************************************************************************
	> File Name: semantic_analysis.c
	> Author: liucheng
	> Mail: 1035377294@qq.com
	> Created Time: Thu 10 Apr 2014 10:30:49 PM CST
 ************************************************************************/

#include"../include/semantic_analysis.h"
/*遍历语法树*/
void travel_grammer_tree(struct TreeNode *root){
    int i=0;
    struct TreeNode *temp=NULL;
    for(i=0; i<=root->childnum; i++){
        temp=root->childNode[i];
        if(!strcmp(temp->data,"Def") || !strcmp(temp->data,"ExtDef")){
            //printf("travel_grammer_tree\n");
            travel_def_tree(temp);
            continue;
        }
        else if(!strcmp(temp->data,"Stmt")&&root->childnum>0){
            travel_stmt_tree(temp);
            //continue;
        }
        travel_grammer_tree(temp);
    }
}

/*遍历specifier_node返回类型*/
Type* travel_specifier_tree(struct TreeNode *root){
    struct TreeNode* type_node=root->childNode[0];
    //printf("name %s  childnum : %d\n",root->data,root->childnum);
    //printf("travel_specifier_tree\n");
    if(!strcmp(type_node->data,"TYPE")){//普通类型
        //printf("Type\n");
        Type* type=(Type *)malloc(sizeof(Type));
        type->kind=basic;
        if(!strcmp(type_node->sub_data,"int"))
            (type->u).basic=0;
        else
            (type->u).basic=1;
        return type;
    }
    else{//结构类型
        //printf("struct\n");
        struct TreeNode *tag_node=type_node->childNode[1];
        Type *type=(Type *)malloc(sizeof(Type));
        type->kind=structure;
        if(!strcmp(tag_node->data,"OptTag")){
            struct TreeNode *deflist_node=type_node->childNode[3];
            FieldList *field=(FieldList *)malloc(sizeof(FieldList));
            field=travel_deflist_tree(deflist_node,field);
            (type->u).structure=field;
            //if(field==NULL)printf("!!!!!!\n");
            if(tag_node->childnum==0){
                struct TreeNode *id_node=tag_node->childNode[0];
                //printf("sub_data:++++++++++:%s\n",id_node->sub_data);
                ((type->u).structure)->name=id_node->sub_data;
                //printf("insert+++++++ %s\n",id_node->sub_data);
                if(!insert(((type->u).structure),structList)){
                    printf("Error type 16 at line %d: Duplicated name '%s'\n"
                           ,type_node->line,id_node->sub_data);
                    return NULL;
                }
            }
            return type;
        }
        else{
            struct TreeNode* id_node=tag_node->childNode[0];
            //printf("fetch %s\n",id_node->sub_data);
            FieldList *p=fetch(id_node->sub_data,structList);
            if(p==NULL){
                printf("Error type 17 at line %d: Undefined struct '%s'\n",
                       type_node->line,id_node->sub_data);
                return NULL;
            }
            (type->u).structure=p;
            return type;
        }
    }
    return NULL;
}
/*遍历vardec到最后一层识别ID*/
FieldList* travel_vardec_tree(struct TreeNode *root){
    FieldList *var=(FieldList *)malloc(sizeof(FieldList));
    //printf("name %s  childnum : %d\n",root->data,root->childnum);
    
    if(root->childnum==0){
        struct TreeNode *id_node=root->childNode[0];
        var->name=id_node->sub_data;
        return var;
    }
    else{
        //printf("travel_vardec_tree\n");
        var=travel_vardec_tree(root->childNode[0]);
        struct TreeNode *int_node=root->childNode[2];
        Type *type=(Type*)malloc(sizeof(Type));
        (type->u).array.size=atoi(int_node->sub_data);
        (type->u).array.elem=NULL;
        type->kind=array;
        if(var->type==NULL)
            var->type=type;
        else{
            Type *p=var->type;
            while((p->u).array.elem!=NULL)
                p=(p->u).array.elem;
            (p->u).array.elem=type;
        }
        return var;
    }
}
/*遍历所有的定义*/
void travel_def_tree(struct TreeNode *root){
    //printf("travel_def_tree\n");
    //printf("name %s  childnum : %d\n",root->data,root->childnum);
    struct TreeNode *specifier_node=root->childNode[0];
    struct TreeNode *declist_node=root->childNode[1];
    Type *type=travel_specifier_tree(specifier_node);
    FieldList *field=(FieldList*)malloc(sizeof(FieldList));
    if(type==NULL)
        return;
    if(!strcmp(declist_node->data,"DecList")||
        !strcmp(declist_node->data,"ExtDecList"))
        travel_extdeclist_tree(declist_node,type);
    else if(!strcmp(declist_node->data,"FunDec")){
        //printf("travel_fundec_tree");
        FieldList *func=(FieldList*)malloc(sizeof(FieldList));
        func->name=declist_node->childNode[0]->sub_data;
        func->type=type;
        funType=type;
        if(declist_node->childnum==2)
            func->tail=NULL;
        else{
            field=NULL;
            field=travel_fundec_tree(declist_node->childNode[2],field);
            func->tail=field;
        }
        if(!insert(func,funcList))
            printf("Error type 4 at line %d: Redefined function \"%s\"\n",root->line,func->name);
        travel_grammer_tree(root->childNode[2]);
    }
}
/*遍历deflist节点，包含全局变量和函数内变量*/
FieldList* travel_deflist_tree(struct TreeNode *root,FieldList *field){
    int i;
    if(root!=NULL)
        for(i=0;i<=root->childnum;i++){
            if(!strcmp(root->data,"Def")){
                struct TreeNode *specifier_node=root->childNode[0];
                struct TreeNode *declist_node=root->childNode[1];
                Type *type=travel_specifier_tree(specifier_node);
                field=travel_declist_tree(declist_node,type,field);
                break;
            }
            else if (!strcmp(root->data, "ParamDec"))
            {
                struct TreeNode* specifier_node = root->childNode[0];
                struct TreeNode* declist_node = root->childNode[1];
                Type *type=travel_specifier_tree(specifier_node);
                field=travel_declist_tree(declist_node,type,field);
                break;                            
            }
            field=travel_deflist_tree(root->childNode[i],field);
        }
    return field;
}
/*遍历deflist的declist*/
FieldList* travel_declist_tree(struct TreeNode *root,Type *type,FieldList* field){
    int i;
    //printf("name %s  childnum : %d\n",root->data,root->childnum);
    for(i=0; i<=root->childnum;i++) {
        if(!strcmp(root->data,"VarDec")){
            FieldList *var=(FieldList *)malloc(sizeof(FieldList));
            //printf("travel_declist_tree\n");
            var=travel_vardec_tree(root);
            if(var->type==NULL)
                var->type=type;
            else{
                Type *p=var->type;
                while((p->u).array.elem!=NULL)
                    p=(p->u).array.elem;
                (p->u).array.elem=type;
            }
            if(field->type==NULL){
                Type *temp=(Type*)malloc(sizeof(Type));
                temp->kind=structure;
                (temp->u).structure=var;
                field->type=temp;
                //printf("~~~~~~~~~~~~~~~~~~~\n");
            }
            else{
                FieldList *p,*q;
                p=((field->type)->u).structure;
                while(p!=NULL){
                    q=p;
                    if(!strcmp(p->name,var->name)){
                        printf("Error type 15 at line %d: Redefined field '%s'\n",
                               root->line,var->name);
                        return field;
                    }
                    p=p->tail;
                }
                q->tail=var;
                var->tail=NULL;
            }
            break;
        }
        field=travel_declist_tree(root->childNode[i],type,field);
    }
    //if(field==NULL) printf("~~~~~~~~~~~\n");
    return field;
}
/*遍历全局变量列表*/
void travel_extdeclist_tree(struct TreeNode *root,Type *type){
    int i;
    //printf("travel_extdeclist_tree\n");
    //printf("name %s  childnum : %d\n",root->data,root->childnum);
    for(i=0;i<=root->childnum;i++){
        if(!strcmp(root->data,"VarDec")){
            FieldList *var=(FieldList*)malloc(sizeof(FieldList));
            //printf("travel_extdeclist_tree\n");
            var=travel_vardec_tree(root);
            if(var->type==NULL)
                var->type=type;
            else{
                Type *p=var->type;
                while((p->u).array.elem!=NULL)
                    p=(p->u).array.elem;
                (p->u).array.elem=type;
            }
            //printf("name : %s\n",var->name);
            if(fetch(var->name,structList)!=NULL){
                printf("Error type 3 at line %d:Redefined variable \"%s\"\n",root->line,var->name);
            }
            else if(!insert(var,varList)){ 
                printf("Error type 3 at line %d:Redefined variable \"%s\"\n",root->line,var->name);
            }
            break;
        }
        travel_extdeclist_tree(root->childNode[i],type);
    }
}
/*遍历fundc*/
FieldList* travel_fundec_tree(struct TreeNode *root,FieldList *structfield){
    int i;
    if(root!=NULL)
        for(i=0;i<=root->childnum;i++){
            if(!strcmp(root->data,"ParamDec")){
                struct TreeNode *specifier_node=root->childNode[0];
                struct TreeNode *vardec_node=root->childNode[1];
                Type *type=travel_specifier_tree(specifier_node);
                FieldList *var=(FieldList *)malloc(sizeof(FieldList));
                //printf("travel_fundec_tree\n");
                var=travel_vardec_tree(vardec_node);
                if(var->type==NULL){
                    var->type=type;
                }
                else{
                    Type *p=var->type;
                    while((p->u).array.elem!=NULL)
                        p=(p->u).array.elem;
                    (p->u).array.elem=type; 
                }
                if(structfield==NULL){
                    structfield=var;
                    structfield->tail=NULL;
                }
                else{
                    FieldList *p=structfield;
                    while(p->tail!=NULL)
                        p=p->tail;
                    p->tail=var;
                    var->tail=NULL;
                }
                break;
            }
            structfield=travel_fundec_tree(root->childNode[i],structfield);
        }
    return structfield;
}
/*分组2.3判断结构内部定义相等则两个结构相同*/
bool charge_struct_equal(Type *type1,Type *type2){
    if(!strcmp((type1->u).structure->name,(type2->u).structure->name))
        return true;
    else{
        FieldList *f1=((type1->u).structure->type->u).structure;
        FieldList *f2=((type2->u).structure->type->u).structure;
        while(f1!=NULL&&f2!=NULL){
            if(!charge_struct_equal(f1->type,f2->type))
                return false;
            f1=f1->tail;
            f2=f2->tail;
        }
        if(f1!=NULL&&f2!=NULL)
            return false;
        return true;
    }
}
bool charge_type_equal(Type *type1,Type *type2){
    if(type1==NULL||type2==NULL)
        return false;
    else if(type1->kind!=type2->kind)
        return false;
    else{
        int count1=0,count2=0;
        Type *p1=type1;
        Type *p2=type2;
        switch(type1->kind){
            case 0:{
                if((type1->u).basic!=(type2->u).basic)
                    return false;
                break;
            }
            case 1:{
                while(p1->kind==1){
                    count1++;
                    p1=(p1->u).array.elem;
                }
                while(p2->kind==1){
                    count2++;
                    p2=(p2->u).array.elem;
                }
                if(count1!=count2)
                    return false;
                if(p1->kind!=p2->kind)
                    return false;
                else if(p1->kind==0){
                    if((p1->u).basic!=(p2->u).basic)
                        return false;
                }
                else
                    return charge_type_equal(type1,type2);
                break;
            }
            case 2:{
                return charge_struct_equal(type1,type2);
                break;
            }
        }
    }
    return true;
}

Type* ravel_exp_tree(struct TreeNode *root){
    
    return NULL;
}
void travel_stmt_tree(struct TreeNode *root){
    if(root->childnum==1){
        Type *type=travel_exp_tree(root->childNode[0]);
        if(type==NULL){
            if(root->childNode[0]->childnum==2){
                if(!strcmp(root->childNode[0]->childNode[1]->data,"ASSIGNOP"))
                    printf("Error type 5 at %d: Type mismached\n",root->line);
                else if(!strcmp(root->childNode[0]->childNode[1]->data,"Exp"))
                    printf("Error type 7 at %d: Operands type mismached\n",root->line);
            }
        }
    }
    else if(root->childnum==2){
        Type *type=travel_exp_tree(root->childNode[1]);
        if(type==NULL||!charge_type_equal(funType,type)){
            printf("Error type 8 at line %d: The return type mismached\n",root->line);
        } 
    }
    else if(root->childnum==4){
        travel_exp_tree(root->childNode[2]);
        travel_grammer_tree(root->childNode[4]);
    }
    else if(root->childnum==6){
        travel_exp_tree(root->childNode[2]);
        travel_grammer_tree(root->childNode[4]);
        travel_grammer_tree(root->childNode[6]);
    }
}

