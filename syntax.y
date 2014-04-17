%{
#include<stdio.h>
#include"lex.yy.c"
#include"include/Node.h"
#define YYDEBUG 1
%}

/*declare types*/
%union{
	struct TreeNode *Node;		
}
/*declare tokens*/
%token <Node> INT
%token <Node> FLOAT
%token <Node> ID
%token <Node> SEMI COMMA
%token <Node> ASSIGNOP
%token <Node> RELOP
%token <Node> PLUS MINUS STAR DIV
%token <Node> AND OR DOT NOT
%token <Node> TYPE
%token <Node> LP RP
%token <Node> LB RB
%token <Node> LC RC
%token <Node> STRUCT
%token <Node> RETURN
%token <Node> IF ELSE
%token <Node> WHILE 

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE
%nonassoc LOWER_THAN_ERROR
%nonassoc error
%right ASSIGNOP
%left OR
%left AND
%left RELOP
%left MINUS PLUS
%left DIV STAR
%right NOT
%right UNARY
%left DOT
%left LB RB
%left LP RP

%type <Node> Program ExtDefList ExtDef ExtDecList
%type <Node> Specifier StructSpecifier OptTag Tag
%type <Node> VarDec FunDec VarList ParamDec
%type <Node> CompSt StmTList Stmt
%type <Node> DefList Def DecList Dec
%type <Node> Exp Args


%%
Program			:	ExtDefList					{
                                                    CreateNode(&$$,"Program","",@1.first_line);
													addNodeToParent(&$$,$1);
													root=$$;
                                                }
				;
ExtDefList		:	ExtDef ExtDefList			{
                                                    CreateNode(&$$,"ExtDefList","",@1.first_line);
													addNodeToParent(&$$,$1);
													addNodeToParent(&$$,$2);
                                                }
                |	/*empty*/                   {
                                                    $$=NULL;
                                                }
				;
ExtDef			:	Specifier ExtDecList SEMI	{
													CreateNode(&$$,"ExtDef","",@1.first_line);
													addNodeToParent(&$$,$1);
													addNodeToParent(&$$,$2);
													addNodeToParent(&$$,$3);
                                                }
                |	Specifier SEMI              {
                                                    CreateNode(&$$,"ExtDef","",@1.first_line);
													addNodeToParent(&$$,$1);
													addNodeToParent(&$$,$2);
                                                }             
                |	Specifier FunDec CompSt		{
                                                    CreateNode(&$$,"ExtDef","",@1.first_line);
													addNodeToParent(&$$,$1);
													addNodeToParent(&$$,$2);
													addNodeToParent(&$$,$3);
                                                }
                |   error SEMI                  {
                                                    //CreateNode("ERROR",0,0);
                                                }
				;
ExtDecList		:	VarDec						{
                                                    CreateNode(&$$,"ExtDecList","",@1.first_line);
													addNodeToParent(&$$,$1);    
                                                }
                |	VarDec COMMA ExtDecList		{
                                                    CreateNode(&$$,"ExtDecList","",@1.first_line);
													addNodeToParent(&$$,$1);
													addNodeToParent(&$$,$2);
													addNodeToParent(&$$,$3);
                                                }
				;
Specifier		:	TYPE						{
                                                    CreateNode(&$$,"Specifier","",@1.first_line);
													addNodeToParent(&$$,$1);
                                                }
                |	StructSpecifier				{
                                                    CreateNode(&$$,"Specifier","",@1.first_line);
													addNodeToParent(&$$,$1);
                                                }
				;
StructSpecifier	:	STRUCT OptTag LC DefList RC	{
                                                    CreateNode(&$$,"StructSpecifier","",@1.first_line);
													addNodeToParent(&$$,$1);
													addNodeToParent(&$$,$2);
													addNodeToParent(&$$,$3);
													addNodeToParent(&$$,$4);
													addNodeToParent(&$$,$5);

                                                }
                |	STRUCT Tag                  {
                                                    CreateNode(&$$,"StructSpecifier","",@1.first_line);
													addNodeToParent(&$$,$1);
													addNodeToParent(&$$,$2);
                                                }
				;
OptTag			:	ID							{
                                                    CreateNode(&$$,"OptTag","",@1.first_line);
													addNodeToParent(&$$,$1);
                                                }
                |	/*empty*/                   {
                                                    $$=NULL;    
                                                }
				;
Tag				:	ID							{
                                                    CreateNode(&$$,"Tag","",@1.first_line);
													addNodeToParent(&$$,$1);
                                                }
				;
VarDec			:	ID							{
                                                    CreateNode(&$$,"VarDec","",@1.first_line);
													addNodeToParent(&$$,$1);
                                                }
                |	VarDec LB INT RB			{
                                                    CreateNode(&$$,"VarDec","",@1.first_line);
													addNodeToParent(&$$,$1);
													addNodeToParent(&$$,$2);
													addNodeToParent(&$$,$3);
													addNodeToParent(&$$,$4);
                                                }
				;
FunDec			:	ID LP VarList RP			{
                                                    CreateNode(&$$,"FunDec","",@1.first_line);
													addNodeToParent(&$$,$1);
													addNodeToParent(&$$,$2);
													addNodeToParent(&$$,$3);
													addNodeToParent(&$$,$4);
                                                }
                |	ID LP RP					{
                                                    CreateNode(&$$,"FunDec","",@1.first_line);
													addNodeToParent(&$$,$1);
													addNodeToParent(&$$,$2);
													addNodeToParent(&$$,$3);
                                                }
                |   error RP                    {
                                                    //CreateNode("ERROR",0,0);			
                                                }
				;
VarList			:	ParamDec COMMA VarList		{
                                                    CreateNode(&$$,"VarList","",@1.first_line);
													addNodeToParent(&$$,$1);
													addNodeToParent(&$$,$2);
													addNodeToParent(&$$,$3);
                                                }
                |	ParamDec					{
                                                    CreateNode(&$$,"VarList","",@1.first_line);   
													addNodeToParent(&$$,$1);
                                                }	
                ;
ParamDec		:	Specifier VarDec			{
                                                    CreateNode(&$$,"ParamDec","",@1.first_line);   
													addNodeToParent(&$$,$1);
													addNodeToParent(&$$,$2);
                                                }
				;
CompSt			:	LC DefList StmTList RC		{
                                                    CreateNode(&$$,"CompSt","",@1.first_line);
													addNodeToParent(&$$,$1);
													addNodeToParent(&$$,$2);
													addNodeToParent(&$$,$3);
													addNodeToParent(&$$,$4);
                                                }
                |   error RC                    {
                                                    //CreateNode("ERROR",0,0);
                                                }
				|	error SEMI					{}
                ;
StmTList		:	Stmt StmTList   			{
                                                    CreateNode(&$$,"StmTList","",@1.first_line);
													addNodeToParent(&$$,$1);
													addNodeToParent(&$$,$2);
                                                }
                |	/*empty*/                   {
                                                    $$=NULL;
                                                }
				;
Stmt			:	Exp	SEMI					{
                                                    CreateNode(&$$,"Stmt","",@1.first_line);
													addNodeToParent(&$$,$1);
													addNodeToParent(&$$,$2);
                                                }
                |	CompSt						{
                                                    CreateNode(&$$,"Stmt","",@1.first_line);
													addNodeToParent(&$$,$1);
                                                }
                |	RETURN Exp SEMI				{
                                                    CreateNode(&$$,"Stmt","",@1.first_line);
													addNodeToParent(&$$,$1);
													addNodeToParent(&$$,$2);
													addNodeToParent(&$$,$3);
                                                }
                |	IF LP Exp RP Stmt %prec LOWER_THAN_ELSE	{
                                                    CreateNode(&$$,"Stmt","",@1.first_line);
													addNodeToParent(&$$,$1);
													addNodeToParent(&$$,$2);
													addNodeToParent(&$$,$3);
													addNodeToParent(&$$,$4);
													addNodeToParent(&$$,$5);
                                                }
                |	IF LP Exp RP Stmt ELSE Stmt	{
                                                    CreateNode(&$$,"Stmt","",@1.first_line);
													addNodeToParent(&$$,$1);
													addNodeToParent(&$$,$2);
													addNodeToParent(&$$,$3);
													addNodeToParent(&$$,$4);
													addNodeToParent(&$$,$5);
													addNodeToParent(&$$,$6);
													addNodeToParent(&$$,$7);
                                                }
                |	WHILE LP Exp RP Stmt		{
                                                    CreateNode(&$$,"Stmt","",@1.first_line);
													addNodeToParent(&$$,$1);
													addNodeToParent(&$$,$2);
													addNodeToParent(&$$,$3);
													addNodeToParent(&$$,$4);
													addNodeToParent(&$$,$5);
                                                }
                |   error SEMI                  {
                                                    //CreateNode("ERROR",0,0);
                                                }
				|	error RP					{}
				;
DefList			:	Def DefList					{
                                                    CreateNode(&$$,"DecList","",@1.first_line);
													addNodeToParent(&$$,$1);
													addNodeToParent(&$$,$2);
                                                }
                |	/*empty*/ %prec LOWER_THAN_ERROR {
                                                    $$=NULL;
                                                }	
				;
Def				:	Specifier DecList SEMI		{
                                                    CreateNode(&$$,"Def","",@1.first_line);
													addNodeToParent(&$$,$1);
													addNodeToParent(&$$,$2);
													addNodeToParent(&$$,$3);
                                                }
                |   error SEMI                  {
                                                    //CreateNode("ERROR",0,0);
                                                }
				;
DecList			:	Dec							{
                                                    CreateNode(&$$,"DecList","",@1.first_line);
													addNodeToParent(&$$,$1);
                                                }
                |	Dec COMMA DecList			{
                                                    CreateNode(&$$,"DecList","",@1.first_line);
													addNodeToParent(&$$,$1);
													addNodeToParent(&$$,$2);
													addNodeToParent(&$$,$3);
                                                }
				;
Dec				:	VarDec						{
                                                    CreateNode(&$$,"Dec","",@1.first_line);
													addNodeToParent(&$$,$1);
                                                }
                |	VarDec ASSIGNOP Exp			{
                                                    CreateNode(&$$,"Dec","",@1.first_line);
													addNodeToParent(&$$,$1);
													addNodeToParent(&$$,$2);
													addNodeToParent(&$$,$3);
                                                }
				;
Exp				:	Exp ASSIGNOP Exp			{
                                                    CreateNode(&$$,"Exp","",@1.first_line);
													addNodeToParent(&$$,$1);
													addNodeToParent(&$$,$2);
													addNodeToParent(&$$,$3);
                                                }
                |	Exp AND Exp					{
                                                    CreateNode(&$$,"Exp","",@1.first_line);
													addNodeToParent(&$$,$1);
													addNodeToParent(&$$,$2);
													addNodeToParent(&$$,$3);
                                                }
                |	Exp OR Exp					{
                                                    CreateNode(&$$,"Exp","",@1.first_line);
													addNodeToParent(&$$,$1);
													addNodeToParent(&$$,$2);
													addNodeToParent(&$$,$3);
                                                }
                |	Exp RELOP Exp				{
                                                    CreateNode(&$$,"Exp","",@1.first_line);
													addNodeToParent(&$$,$1);
													addNodeToParent(&$$,$2);
													addNodeToParent(&$$,$3);
                                                }
                |	Exp PLUS Exp				{
                                                    CreateNode(&$$,"Exp","",@1.first_line);
													addNodeToParent(&$$,$1);
													addNodeToParent(&$$,$2);
													addNodeToParent(&$$,$3);
                                                }
                |	Exp MINUS Exp				{
                                                    CreateNode(&$$,"Exp","",@1.first_line);
													addNodeToParent(&$$,$1);
													addNodeToParent(&$$,$2);
													addNodeToParent(&$$,$3);
                                                }
                |	Exp STAR Exp				{
                                                    CreateNode(&$$,"Exp","",@1.first_line);
													addNodeToParent(&$$,$1);
													addNodeToParent(&$$,$2);
													addNodeToParent(&$$,$3);
                                                }
                |	Exp DIV Exp					{
                                                    CreateNode(&$$,"Exp","",@1.first_line);
													addNodeToParent(&$$,$1);
													addNodeToParent(&$$,$2);
													addNodeToParent(&$$,$3);
                                                }
                |	LP Exp RP					{
                                                    CreateNode(&$$,"Exp","",@1.first_line);
													addNodeToParent(&$$,$1);
													addNodeToParent(&$$,$2);
													addNodeToParent(&$$,$3);
                                                }
                |	MINUS Exp %prec UNARY	    {
                                                    CreateNode(&$$,"Exp","",@1.first_line);
													addNodeToParent(&$$,$1);
													addNodeToParent(&$$,$2);
                                                }
                |	NOT Exp						{
                                                    CreateNode(&$$,"Exp","",@1.first_line);
													addNodeToParent(&$$,$1);
													addNodeToParent(&$$,$2);
                                                }
                |	ID LP Args RP				{
                                                    CreateNode(&$$,"Exp","",@1.first_line);
													addNodeToParent(&$$,$1);
													addNodeToParent(&$$,$2);
													addNodeToParent(&$$,$3);
													addNodeToParent(&$$,$4);
                                                }
                |	ID LP RP					{
                                                    CreateNode(&$$,"Exp","",@1.first_line);
													addNodeToParent(&$$,$1);
													addNodeToParent(&$$,$2);
													addNodeToParent(&$$,$3);
                                                }
                |	Exp LB Exp RB				{
                                                    CreateNode(&$$,"Exp","",@1.first_line);
													addNodeToParent(&$$,$1);
													addNodeToParent(&$$,$2);
													addNodeToParent(&$$,$3);
													addNodeToParent(&$$,$4);
                                                }
                |	Exp DOT ID					{
                                                    CreateNode(&$$,"Exp","",@1.first_line);
													addNodeToParent(&$$,$1);
													addNodeToParent(&$$,$2);
													addNodeToParent(&$$,$3);
                                                }
                |	ID							{
                                                    CreateNode(&$$,"Exp","",@1.first_line);
													addNodeToParent(&$$,$1);
                                                }
                |	INT							{
                                                    CreateNode(&$$,"Exp","",@1.first_line);
													addNodeToParent(&$$,$1);
                                                }
                |	FLOAT						{
                                                    CreateNode(&$$,"Exp","",@1.first_line);
													addNodeToParent(&$$,$1);
                                                }
                |   LP error RP                 {
                                                    //CreateNode("ERROR",0,0);
                                                }
                |   Exp LB error RB             {
                                                    //CreateNode("ERROR",0,0);
                                                }
                ;
Args			:	Exp COMMA Args				{
                                                    CreateNode(&$$,"Args","",@1.first_line);
													addNodeToParent(&$$,$1);
													addNodeToParent(&$$,$2);
													addNodeToParent(&$$,$3);
                                                }
                |	Exp							{
                                                    CreateNode(&$$,"Args","",@1.first_line);
													addNodeToParent(&$$,$1);
                                                }
				;
%%
yyerror(char* msg){
    hasError=1;
    fprintf(stderr,"Error type B at line %d : %s\n",yylineno,msg);
}


