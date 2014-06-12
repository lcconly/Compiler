/*************************************************************************
	> File Name: semantic_analysis.c
	> Author: liucheng
	> Mail: 1035377294@qq.com
	> Created Time: Thu 10 Apr 2014 10:30:49 PM CST
 ************************************************************************/

#include"../include/semantic_analysis.h"
//FieldList* varList[MAXHARSHSIZE];
//FieldList* structList[MAXHARSHSIZE];
//FieldList* funcList[MAXHARSHSIZE];
//Type *funType;
//FieldList *func;
/*遍历语法树*/
void travel_grammer_tree(struct TreeNode *root){
    int i=0;
    struct TreeNode *temp=NULL;
    for(i=0; i<=root->childnum; i++){
        temp=root->childNode[i];
        if(!strcmp(temp->data,"ExtDef")){
            //printf("travel_grammer_tree\n");
            travel_def_tree(temp);
            continue;
        }
        else if(!strcmp(temp->data,"Stmt")&&temp->childnum>0){
            //printf("num num : %d\n",temp->childnum);
            travel_stmt_tree(temp);
            continue;
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
            field=travel_deflist_tree(deflist_node,field,0,1);
            (type->u).structure=field;
            //printf("!!!!!!\n");
            //printf("childnum : %d\n",tag_node->childnum);
            if(tag_node->childnum==0){
                struct TreeNode *id_node=tag_node->childNode[0];
                //printf("sub_data:++++++++++:%s\n",id_node->sub_data);
                ((type->u).structure)->name=id_node->sub_data;
                //printf("insert+++++++ %s\n",id_node->sub_data);
                if(fetch(id_node->sub_data,varList)!=NULL){
					sem_error=1;
                    printf("Error type 3 at line %d: Redefined variable \"%s\"\n",root->line,id_node->sub_data);
                }
                //printf("type : %s\n",((type->u).structure->type->u).structure->name);
                if(!insert(((type->u).structure),structList)){
					sem_error=1;
                    printf("Error type 16 at line %d: Duplicated name '%s'\n"
                           ,type_node->line,id_node->sub_data);
                    return NULL;
                }
            }
            return type;
        }
        else if(!strcmp(tag_node->data,"LC")){//结构类型名为空的情况
            struct TreeNode *deflist_node=type_node->childNode[2];
            FieldList *field=(FieldList *)malloc(sizeof(FieldList));
            field=travel_deflist_tree(deflist_node,field,0,1);
            (type->u).structure=field;
            ((type->u).structure)->name="";
            //printf("!!!!!!\n");
            //printf("childnum : %d\n",tag_node->childnum);
            return type;
        }
        else{//类型使用的情况
            struct TreeNode* id_node=tag_node->childNode[0];
            //printf("fetch %s\n",id_node->sub_data);
            FieldList *p=fetch(id_node->sub_data,structList);
            if(p==NULL){
				sem_error=1;
                printf("Error type 17 at line %d: Undefined struct '%s'\n",
                       type_node->line,id_node->sub_data);
                return NULL;
            }
            //printf("type1 : %s\n",(p->type->u).structure->name);
            //printf("type2 : %s\n",(((p->type->u).structure->type->u)).structure->name);
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
    //printf("travel_vardec_tree!\n");
    if(root->childnum==0){//普通类型
        struct TreeNode *id_node=root->childNode[0];
        var->name=id_node->sub_data;
        return var;
    }
    else{//数组情况
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
    //if(!strcmp(declist_node->data,"DecList")||
	if(!strcmp(declist_node->data,"ExtDecList"))
        travel_extdeclist_tree(declist_node,type);//类型定义
    else if(!strcmp(declist_node->data,"FunDec")){//函数定义
        func=(FieldList*)malloc(sizeof(FieldList));
        func->name=declist_node->childNode[0]->sub_data;
        func->type=type;
        funType=type;//保存函数的全局变量
        if(declist_node->childnum==2)//函数参数为空
            func->variable=NULL;
        else{
			field=NULL;
            field=travel_fundec_tree(declist_node->childNode[2],field);
            func->variable=field;
            //printf("name : %s\n",field->name);
			//printf("kind : %d\n",field->type->kind);
        }
        if(!insert(func,funcList)){//插入函数
			sem_error=1;
            printf("Error type 4 at line %d: Redefined function \"%s\"\n",root->line,func->name);
		}
		//	printf("11111111\n");
        //if(field->type==NULL){
		//	printf("22222222!\n");
			//printf("-----%d\n",type->kind);
			//travel_extdeclist_tree(root->childNode[2],type);
			//travel_declist_tree(root->childNode[2],type,field,1);
			travel_deflist_tree(root->childNode[2],field,1,0);
		//}
        travel_grammer_tree(root->childNode[2]);
    }
}
/*遍历deflist节点，包含全局变量和函数内变量*/
FieldList* travel_deflist_tree(struct TreeNode *root,FieldList *field,int tag,int tag2){
    int i;
    //printf("travel_deflist_tree!\n");
    if(root!=NULL)
        for(i=0;i<=root->childnum;i++){
            if(!strcmp(root->data,"Def")){
                //printf("!!!!!!\n");
                struct TreeNode *specifier_node=root->childNode[0];
                struct TreeNode *declist_node=root->childNode[1];
                Type *type=travel_specifier_tree(specifier_node);
                //printf("type in def %d\n",type->kind);
                if(tag2==0)
					travel_extdeclist_tree(root,type);
                field=travel_declist_tree(declist_node,type,field,tag);
                //printf("type in def %s\n",field->name);
                break;
            }
            field=travel_deflist_tree(root->childNode[i],field,tag,tag2);
        }
    return field;
}
/*遍历deflist的declist*/
/*tag为1是函数内部定义，tag为0是结构内部定义*/
FieldList* travel_declist_tree(struct TreeNode *root,Type *type,FieldList* field,int tag){
    int i;
    //printf("travel_declist_tree!\n");
    //printf("name %s  childnum : %d\n",root->data,root->childnum);
    for(i=0; i<=root->childnum;i++) {
        if(!strcmp(root->data,"Dec")){
            //printf("~~~~~~~~\n");
            struct TreeNode *node=root->childNode[0];
            FieldList *var=(FieldList *)malloc(sizeof(FieldList));
            //printf("travel_declist_tree\n");
            var=travel_vardec_tree(node);
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
                //var->tail=NULL;
                field->type=temp;
                //printf("kind %d \n",(field->type->u).basic);
                //printf("var in declist--------- %s\n",var->name);
                //printf("type in declist------- %s\n",(field->type->u).structure->name);
                //printf("~~~~~~~~~~~~~~~~~~~\n");
            }
            else if(tag==0){
                FieldList *p,*q;
                p=((field->type)->u).structure;
                //if(p==NULL) printf("!!!!!!!!!!!!!!!!\n");
                while(p!=NULL){
                    q=p;
                    if(!strcmp(p->name,var->name)&&tag==0){
						sem_error=1;
                        printf("Error type 15 at line %d: Redefined field '%s'\n",
                               node->line,var->name);
                        return field;
                    }
                    p=p->tail;
                }
                //if(var==NULL) printf("!!!!!!!!!!!!!");
                q->tail=var;
                var->tail=NULL;
            }
            if(root->childnum==2){
                Type *ty=travel_exp_tree(root->childNode[2]);
                //printf("kind %d \n",(field->type->u).basic);
                if(!charge_type_equal(type,ty)&&tag==1){
                    sem_error=1;
                    printf("Error type 5 at line %d: Type mismached\n",node->line);
				}
                else if(field->type->kind==structure&&
                        !strcmp(root->childNode[1]->data,"ASSIGNOP")&&tag==0){
					sem_error=1;
                    printf("Error type 15 at line %d: Field '%s' defined error\n",
                           root->line,var->name);
                    
				}
			}
            //printf("var in declist %s\n",var->name);
            break;
        }
        field=travel_declist_tree(root->childNode[i],type,field,tag);
    }
    //printf("type in declist------- %s\n",(field->type->u).structure->name);
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
			var->intercode=NULL;
            //printf("name : %s\n",var->name);
            if(fetch(var->name,structList)!=NULL){
				sem_error=1;
                printf("Error type 3 at line %d: Redefined variable \"%s\"\n",root->line,var->name);
            }
            else if(!insert(var,varList)){ 
				sem_error=1;
                printf("Error type 3 at line %d: Redefined variable \"%s\"\n",root->line,var->name);
            }
			//show_hash_table(varList);
            break;
        }
        travel_extdeclist_tree(root->childNode[i],type);
    }
}
/*遍历fundc*/
FieldList* travel_fundec_tree(struct TreeNode *root,FieldList *structfield){
    int i;
    //printf("travel_fundec_tree!\n");
    if(root!=NULL)
        for(i=0;i<=root->childnum;i++){
            if(!strcmp(root->data,"ParamDec")){//遍历paramdec
                //printf("add ParamDec !!!!!!!!!!!!\n");
                struct TreeNode *specifier_node=root->childNode[0];
                struct TreeNode *vardec_node=root->childNode[1];
                Type *type=travel_specifier_tree(specifier_node);
                FieldList *var=(FieldList *)malloc(sizeof(FieldList));
                //printf("travel_fundec_tree\n");
                var=travel_vardec_tree(vardec_node);
                //if(var==NULL) printf("!!!!!!!!!\n");
				//printf("%d %s \n",type->kind,var->name);
                //if(type->kind!=2)
                if(!(!strcmp(root->childNode[0]->childNode[0]->data,"StructSpecifier")&&
                  root->childNode[0]->childNode[0]->childnum==4))
                    travel_extdeclist_tree(root,type);
                //printf("%d %s \n",type->kind,var->name);
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
					//printf("name : %s \n",var->name);
                    structfield->variable=NULL;
                }
                else{
                    FieldList *p=structfield;
                    while(p->variable!=NULL)
                        p=p->variable;
					//printf("name : %s \n",var->name);
                    p->variable=var;
                    var->variable=NULL;
                }
				//if(structfield==NULL) printf("!!!!!!!!!!\n");
                //printf("%s %d=======\n",structfield->name,structfield->type->kind);
				break;
            }
            structfield=travel_fundec_tree(root->childNode[i],structfield);
        }
    return structfield;
}
/*分组2.3判断结构内部定义相等则两个结构相同*/
bool charge_struct_equal(Type *type1,Type *type2){
    //printf("struct 1 : %s\n",(type1->u).structure->name);
    //printf("struct 2 : %s\n",(type2->u).structure->name);
    //printf("charge_struct_equal!\n");
    if(!strcmp((type1->u).structure->name,(type2->u).structure->name)
       &&strcmp((type1->u).structure->name,""))//名相同且不是空
        return true;
    else{//类型结构相同
        FieldList *f1=((type1->u).structure->type->u).structure;
        FieldList *f2=((type2->u).structure->type->u).structure;
        while(f1!=NULL&&f2!=NULL){//判断内部定义
            //printf("!!!!!!!!!!!!!!!!\n");
            if(!charge_type_equal(f1->type,f2->type))
                return false;
            //printf("!!!!!!!!!!!\n");
            f1=f1->tail;
            f2=f2->tail;
        }
        if(f1!=NULL||f2!=NULL)
            return false;
        return true;
    }
}
/*判断两个type是否相等*/
bool charge_type_equal(Type *type1,Type *type2){
    //printf("charge_type_equal!\n");
    if(type1==NULL||type2==NULL)
        return false;
    else if(type1->kind!=type2->kind)
        return false;
    else{
        int count1=0,count2=0;
        Type *p1=type1;
        Type *p2=type2;
        //printf("kind %d~~\n",type1->kind);
        switch(type1->kind){
            //printf("kind %d~~\n",type1->kind);
            case 0:{
                if((type1->u).basic!=(type2->u).basic)
                    return false;
                break;
            }
            case 1:{//数组情况
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
                //else if(p1->kind==2)
                //    return charge_struct_equal(p1,p2);
                else
                    return charge_type_equal(p1,p2);
                break;
            }
            case 2:{
                return charge_struct_equal(type1,type2);
                break;
            }
            default:{
                printf("type error!!!\n");
                break;
            }
        }
    }
    return true;
}
/*遍历exp的子树*/
Type* travel_exp_tree(struct TreeNode *root){
    FieldList *var=(FieldList *)malloc(sizeof(FieldList));
    //printf("travel_exp_tree!\n");
    if(root!=NULL){
        if(root->childnum==0 && !strcmp((root->childNode[0])->data,"ID")){//单独的id
            struct TreeNode *id_node=root->childNode[0];
            //printf("ID:   %s ~~~~~~~\n",id_node->sub_data);
            var=fetch(id_node->sub_data,varList);
            //if(func==NULL)printf("!!!!!!!!!!\n");
            if(var==NULL&&func!=NULL){
                FieldList *p=func->variable;
                while(p!=NULL){
                    if(!strcmp(p->name,id_node->sub_data)){
                        var=p;
                        break;
                    }
                    p=p->variable;
                }
            }
            if(var==NULL){//从表中获取该id的变量表为空，错误类型1
				//show_hash_table(varList);
				sem_error=1;
                printf("Error type 1 at line %d: Undefined variable \"%s\"\n",
                       root->line,id_node->sub_data);
                Type *type=(Type *)malloc(sizeof(Type));
                type->kind=basic;
                (type->u).basic=0;
                return NULL;
            }
            //printf("var : %s type : %d \n",var->name,(var->type->u).basic);
            return var->type;
        }
        else if(root->childnum==0 && !strcmp((root->childNode[0])->data,"INT")){//int型，赋值，返回
            Type* type=(Type *)malloc(sizeof(Type));
            type->kind=basic;
            (type->u).basic=0;
            return type;
        }
        else if(root->childnum==0 && !strcmp((root->childNode[0])->data,"FLOAT")){//flaot型
            Type* type=(Type *)malloc(sizeof(Type));
            type->kind=basic;
            (type->u).basic=1;
            return type;
        }
        //函数调用情况，第二位为（的都是
        else if((root->childnum==2||root->childnum==3)&&!strcmp((root->childNode[1])->data,"LP")){
            struct TreeNode *id_node=root->childNode[0];
            var=fetch(id_node->sub_data,funcList);
            //show_hash_table(funcList);
            //printf("func: %s ~~~~~~~\n",id_node->sub_data);
            FieldList *args=(FieldList *)malloc(sizeof(FieldList));
            if(var!=NULL){
                if(root->childnum==3){
					args=NULL;
                    args=travel_args_tree(root->childNode[2],args);//遍历参数
                    //printf("%x\n",args);
                }
                else args=NULL;
                //printf("%x\n",var->variable);
                if(!charge_args_equal(var->variable,args)){//判断参数是否和定义一致
                    //printf("%x",args);
                    char str1[MAXDATA],str2[MAXDATA];
                    memset(str1,0,sizeof(str1));
                    memset(str2,0,sizeof(str2));
                    FieldList *myStr=var->variable;
                    //printf("%x\n",var->variable);
                    copyStr(myStr,str1);
                    //printf("str: %s !!!!!!!!!!!\n",str1);
                    myStr=args;
                    copyStr_args(myStr,str2);
                    //printf("name : %s str2 : %s\n",myStr->name,str2);
					sem_error=1;
                    printf("Error type 9 at line %d: The method \"%s(%s)\" is"\
							" not applicable for the arguments \"(%s)\"\n",
							root->line,var->name,str1,str2);
                    return NULL;
                }
                //printf("kind %d \n",(var->type->u).basic);
                return var->type;
            }
            else if(fetch(id_node->sub_data,varList)!=NULL){//非函数的情况使用（）
				sem_error=1;
                printf("Error type 11 at line %d: \"%s\" must be a function\n"
                       ,id_node->line,id_node->sub_data);
                return NULL;
            }
            else{//函数未定义
				sem_error=1;
                printf("Error type 2 at line %d: Undefined function \"%s\"\n"
                       ,id_node->line,id_node->sub_data);
                Type *type=(Type *)malloc(sizeof(Type));
                type->kind=basic;
                (type->u).basic=0;
                return NULL;
            }
        }
        else if(root->childnum==1){//取负或者取反的情况
            Type *temp_not=travel_exp_tree(root->childNode[1]);
            if(!strcmp(root->childNode[0]->data,"NOT"))
                if(temp_not!=NULL&&(temp_not->kind==2||temp_not->kind==1||(temp_not->kind==0&&(temp_not->u).basic==1))){
					sem_error=1;
					printf("Error type 7 at line %d: Operands type mismached\n",root->line);
                    return NULL;
				}
            return temp_not;
        }
        else if(root->childnum==3){//数组的情况
            Type *type,*num;
            type=travel_exp_tree(root->childNode[0]);
            char name[MAXDATA];
            memset(name,0,sizeof(name));
            struct TreeNode *arr=root->childNode[0];
            while(arr!=NULL){
                //printf("!!!!!!!!!!!!!!!\n");
                if(!strcmp(arr->data,"ID")){
                    strcpy(name,arr->sub_data);
                    break;
                }
                arr=arr->childNode[0];
            }
            if(type==NULL||type->kind!=1){
				sem_error=1;
                printf("Error type 10 at line %d: \"%s\" must be an array\n",root->line,name);
                return NULL;
            }
            num=travel_exp_tree(root->childNode[2]);
            if((num->u).basic!=0){
				sem_error=1;
                printf("Error type 12 at line %d: Operands type mistaken\n",root->line);
			    return NULL;
            }
            return (type->u).array.elem;
        }
        else{//exp op exp的情况或者（exp）
            //printf("num: %d \n",root->childnum);
            if(!strcmp(root->childNode[1]->data,"DOT")){
                Type *type=travel_exp_tree(root->childNode[0]);
                if(type==NULL)
                    return NULL;
                else if(type->kind!=2){
					sem_error=1;
                    printf("Error type 13 at line %d:Illegal use of '.'\n" ,root->line);
                    return NULL;
                }
                FieldList *temp=(type->u).structure;
                temp=(temp->type->u).structure;
                while(temp!=NULL){
                    if(!strcmp(temp->name,(root->childNode[2])->sub_data))
                        return temp->type;
                    temp=temp->tail;
                }
				sem_error=1;
                printf("Error type 14 at line %d: Un-existed field \"%s\"\n",
                       root->line,(root->childNode[2])->sub_data);
                return NULL;
            } 
            else {
                if(!strcmp(root->childNode[1]->data,"Exp")){
                    return travel_exp_tree(root->childNode[1]);}
                Type *type1=travel_exp_tree(root->childNode[0]);
                //printf("name: %s \n",root->childNode[0]->childNode[0]->sub_data);
                Type *type2=travel_exp_tree(root->childNode[2]);
                if(!strcmp(root->childNode[1]->data,"ASSIGNOP")){
                    if(root->childNode[0]!=NULL&&type1!=NULL)
                        if(!charge_lefthand_variable(root->childNode[0])||type1->kind==array){
							sem_error=1;
                            printf("Error type 6 at line %d: The left-hand side"\
                               " of an assignment must be a variable\n",root->line);
                            return NULL;
					}
				}
                //printf("name :%s %d name : %s %d \n",root->childNode[0]->data,
                //       (type1->u).basic,root->childNode[2]->data,(type2->u).basic);
                if(!charge_type_equal(type1,type2)||
                  (charge_type_equal(type1,type2)&&type1->kind==structure)){
                    //return NULL; 
                    if(!strcmp(root->childNode[1]->data,"ASSIGNOP")&&!charge_type_equal(type1,type2)){
                        //printf("!!!!!\n");
						sem_error=1;
                        printf("Error type 5 at line %d: Type mismached\n",root->line);}
                    else if((type2!=NULL&&strcmp(root->childNode[1]->data,"ASSIGNOP"))
                           ||(type2!=NULL)&&(!strcmp(root->childNode[1]->data,"AND")||!strcmp(root->childNode[1]->data,"OR")&&(type1->u).basic!=0)){
						sem_error=1;
                        printf("Error type 7 at line %d: Operands type mismached\n",root->line);
					    return NULL;
                    }
                    return type1;
                }
                if(charge_type_equal(type1,type2)&&type2!=NULL&&
                   (!strcmp(root->childNode[1]->data,"AND")||
                    !strcmp(root->childNode[1]->data,"OR"))&&(type1->u).basic!=0){
						sem_error=1;
                        printf("Error type 7 at line %d: Operands type mismached\n",root->line);
                        return NULL;
                    }
                return type1;
            }
        }    
    }
}
/*判断左值操作*/
bool charge_lefthand_variable(struct TreeNode *root){
    //printf("charge_lefthand_variable!\n");
    if(!strcmp(root->childNode[0]->data,"INT")
        ||!strcmp(root->childNode[0]->data,"FLOAT")||
        (root->childNode[1]!=NULL&&!strcmp(root->childNode[1]->data,"AND"))||
        (root->childNode[1]!=NULL&&!strcmp(root->childNode[1]->data,"OR"))||
        (root->childNode[1]!=NULL&&!strcmp(root->childNode[1]->data,"RELOP"))||
        (root->childNode[1]!=NULL&&!strcmp(root->childNode[1]->data,"PLUS"))||
        (root->childNode[1]!=NULL&&!strcmp(root->childNode[1]->data,"MINUS"))||
        (root->childNode[1]!=NULL&&!strcmp(root->childNode[1]->data,"STAR"))||
        (root->childNode[1]!=NULL&&!strcmp(root->childNode[1]->data,"DIV"))||
        (root->childNode[1]!=NULL&&!strcmp(root->childNode[1]->data,"LP"))||
        (root->childNode[0]!=NULL&&!strcmp(root->childNode[0]->data,"NOT"))||
        (root->childNode[0]!=NULL&&!strcmp(root->childNode[0]->data,"MINUS")))
            return false;
    else if(root->childNode[0]!=NULL&&!strcmp(root->childNode[0]->data,"LP"))
            return charge_lefthand_variable(root->childNode[1]);
    return true;
}
/*获取函数参数类型，传递到str*/
void copyStr(FieldList* myStr, char *str){
    if(myStr!=NULL){
        switch((myStr->type)->kind){
            case 0:{
                if(((myStr->type)->u).basic==0)
                    strcpy(str,"int");
                else
                    strcpy(str,"float");
                break;
            }
            case 1:{
                strcpy(str,"array");
                break;
            }
            case 2:{
                strcpy(str,"struct ");
                strcat(str,(myStr->type)->u.structure->name);
                break;
            }
        }
        myStr=myStr->variable;
    }
    else strcpy(str,"");
    while(myStr!=NULL){
        switch(myStr->type->kind){
            case 0:{
                if((myStr->type->u).basic==0)
                    strcat(str," ,int");
                else
                    strcat(str," ,float");
                break;
            }
            case 1:{
                strcat(str," ,array");
                break;
            }
            case 2:{
                strcat(str," ,struct ");
                strcat(str,(myStr->type)->u.structure->name);
                break;
            }   
        }
        myStr=myStr->variable;   
    }
}
/*args遍历传递参数类型到str*/
void copyStr_args(FieldList* myStr, char *str){
    if(myStr!=NULL){
        switch((myStr->type)->kind){
            case 0:{
                if(((myStr->type)->u).basic==0)
                    strcpy(str,"int");
                else
                    strcpy(str,"float");
                break;
            }
            case 1:{
                strcpy(str,"array");
                break;
            }
            case 2:{
                strcpy(str,"struct ");
                strcat(str,(myStr->type)->u.structure->name);
                break;
            }
        }
        myStr=myStr->tail;
    }
    else strcpy(str,"");
    while(myStr!=NULL){
        switch(myStr->type->kind){
            case 0:{
                if((myStr->type->u).basic==0)
                    strcat(str," ,int");
                else
                    strcat(str," ,float");
                break;
            }
            case 1:{
                strcat(str," ,array");
                break;
            }
            case 2:{
                strcat(str," ,struct ");
                strcat(str,(myStr->type)->u.structure->name);
                break;
            }   
        }
        myStr=myStr->tail;   
    }
}
/*遍历stmt的子树*/
void travel_stmt_tree(struct TreeNode *root){
    //printf("travel_stmt_tree\n");
    //printf("num : %d\n",root->childnum);
    FieldList *var=(FieldList *)malloc(sizeof(FieldList));
    if(root->childnum==1){//exp semi
        Type *type=travel_exp_tree(root->childNode[0]);
        //if(type==NULL){
            //if(root->childNode[0]->childnum==2){
            //    if(!strcmp(root->childNode[0]->childNode[2]->data,"Exp"))
            //        printf("Error type 7 at line %d: Operands type mismached\n",root->line);
            //    else if(!strcmp(root->childNode[0]->childNode[1]->data,"ASSIGNOP"))
            //        printf("Error type 5 at line %d: Type mismached\n",root->line);
            //}
        //}
    }
    else if(root->childnum==2){//return exp semi
        Type *type=travel_exp_tree(root->childNode[1]);
        if(type==NULL||!charge_type_equal(funType,type)){
			sem_error=1;
            printf("Error type 8 at line %d: The return type mismached\n",root->line);
        } 
    }
    else if(root->childnum==4){//if lp exp rp stmt和while lp exp rp stmt
        //printf("name root : %d\n",root->childnum);
        travel_exp_tree(root->childNode[2]);
        //printf("name : %d\n",root->childNode[4]->childnum);
        travel_stmt_tree(root->childNode[4]);
        travel_grammer_tree(root->childNode[4]);
    }
    else if(root->childnum==6){//含有else 的if
        travel_exp_tree(root->childNode[2]);
        travel_stmt_tree(root->childNode[4]);
        travel_stmt_tree(root->childNode[6]);
        //travel_grammer_tree(root->childNode[4]);
        //travel_grammer_tree(root->childNode[6]);
    }
}
/*判断函数参数是否一致*/
bool charge_args_equal(FieldList *args1,FieldList *args2){
    FieldList *p,*q;
    p=args1;
    q=args2;
    //if(p==NULL)return false;
    while(p!=NULL){
        //printf("Func : %s\n",p->name);
        //printf("args : %d\n",q->type->kind);
        if(q==NULL)
            return false;
        switch(p->type->kind){
            case 0:{
                if(q->type->kind!=0)
                    return false;
                else if((q->type->u).basic!=(p->type->u).basic)
                    return false;
                break;
            }
            case 1:{
                if(q->type->kind!=1)
                    return false;
                break;
            }
            case 2:{
                if(q->type->kind!=2)
                    return false;
                if(!charge_struct_equal(q->type,p->type))
                    return false;
                break;
            }
        }
        //printf("args------ : %d\n",q->type->kind);
        p=p->variable;
        q=q->tail;
    }
    if(q!=NULL)
        return false;
    return true;
}
/*遍历args的子树*/
FieldList* travel_args_tree(struct TreeNode *root,FieldList *args){
    int i=0;
    //printf("travel_args_tree!\n");
    if(root!=NULL){
        FieldList *temp=NULL;
        /*if(!strcmp(root->data,"ID")){
            temp=fetch(root->sub_data,varList);
            if(temp==NULL){
				sem_error=1;
                printf("Error type 1 at line %d: Undefined variable \"%s\"\n",root->line,root->sub_data);
                temp=(FieldList *)malloc(sizeof(FieldList));
                temp->type=(Type *)malloc(sizeof(Type));
                temp->type->kind=basic;
                (temp->type->u).basic=0;
            }
        }
        else if(!strcmp(root->data,"INT")){
            temp=(FieldList *)malloc(sizeof(FieldList));
            temp->type=(Type *)malloc(sizeof(Type));
            temp->type->kind=basic;
            (temp->type->u).basic=0;
        }
        else if(!strcmp(root->data,"FLOAT")){
            temp=(FieldList *)malloc(sizeof(FieldList));
            temp->type=(Type *)malloc(sizeof(Type));
            temp->type->kind=basic;
            (temp->type->u).basic=1;
        }*/
		bool can_return=false;
        Type *temp_type;
        if(!strcmp(root->data,"Args"))
            if(!strcmp(root->childNode[0]->data,"Exp")){
                if((temp_type=travel_exp_tree(root->childNode[0]))!=NULL) {
                    temp=(FieldList *)malloc(sizeof(FieldList));
                    temp->type=temp_type;
					//printf("temp_type %d\n",temp->type->kind);
                }
				if(root->childNode[1]==NULL)
					can_return=true;
				else can_return=false;
            }
        if(temp!=NULL){
            if(args==NULL){
                temp->tail=NULL;
                args=temp;
            }
            else{
                FieldList *p=args;
                while(p->tail!=NULL)
                    p=p->tail;
                p->tail=temp;
                //printf("----------%d\n",temp->type->kind);
                temp->tail=NULL;
            }
        }
		if(can_return==true)
			return args;
        for(i=0;i<=root->childnum;i++)
            args=travel_args_tree(root->childNode[i],args);
    }
    return args;
}
