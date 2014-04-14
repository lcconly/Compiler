%{
#include"syntax.tab.h"
#include"include/Node.h"
static int yycolumn=1;
int hasError=0;
#define YY_USER_ACTION yylloc.first_line=yylloc.last_line=yylineno;\
    yylloc.first_column=yycolumn;yylloc.last_column=yycolumn+yyleng-1;\
    yycolumn+=yyleng;
%}
/*regular definitions*/
delim       [ \t] 
ws          {delim}+
digit       [0-9]
_letter     [_a-zA-Z]
id          {_letter}({_letter}|{digit})*
int         0|([1-9]{digit}*)
float       (({digit}*\.{digit}+)|({digit}+\.))|(({digit}*\.{digit}+)|({digit}+\.))(("E"|"e")[+-]?({digit}+))|({digit}+)(("E"|"e")[+-]?({digit}+))

%option yylineno
%%
\n                              {
                                   yycolumn=1;
                                }
"    "                          {//yycolumn+=4;
                                }
" "                             {//yycolumn++;
                                }
{ws}                            {}
";"                             {
                                    //printf("SEMI at line %d at column %d\n",yylineno,yycolumn);
                                    //yycolumn+=yyleng;
                                    CreateNode(&yylval.Node,"SEMI","",yylineno);
                                    return SEMI;
                                }
","                             {
                                    //printf("COMMA at line %d at column %d\n",yylineno,yycolumn);
                                    //yycolumn+=yyleng;
                                    CreateNode(&yylval.Node,"COMMA","",yylineno);
                                    return COMMA;
                                }
"="                             {
                                    //printf("ASSIGNOP at line %d at column %d\n",yylineno,yycolumn);
                                    //yycolumn+=yyleng;
                                    CreateNode(&yylval.Node,"ASSIGNOP","",yylineno);
                                    return ASSIGNOP;
                                }
">"|"<"|">="|"<="|"=="|"!="     {
                                    //printf("RELOP at line %d at column %d\n",yylineno,yycolumn);
                                    //yycolumn+=yyleng;
                                    //strcpy(yylval.type_char,yytext);
									//char str[64]="RELOP: ";
                                    //strcat(str,yytext);
                                    CreateNode(&yylval.Node,"RELOP",yytext,yylineno);
                                    return RELOP;
                                }
"+"                             {
                                    //printf("PLUS at line %d at column %d\n",yylineno,yycolumn);
                                    //yycolumn+=yyleng;
                                    CreateNode(&yylval.Node,"PLUS","",yylineno);
                                    return PLUS;
                                }
"-"                             {
                                    //printf("MINUS at line %d at column %d\n",yylineno,yycolumn);
                                    //yycolumn+=yyleng;
                                    CreateNode(&yylval.Node,"MINUS","",yylineno);
                                    return MINUS;
                                }
"*"                             {
                                    //printf("STAR at line %d at column %d\n",yylineno,yycolumn);
                                    //yycolumn+=yyleng;
                                    CreateNode(&yylval.Node,"STAR","",yylineno);
                                    return STAR;
                                }
"/"                             {
                                    //printf("DIV at line %d at column %d\n",yylineno,yycolumn);
                                    //yycolumn+=yyleng;
                                    CreateNode(&yylval.Node,"DIV","",yylineno);
                                    return DIV;
                                }
"&&"                            {
                                    //printf("AND at line %d at column %d\n",yylineno,yycolumn);
                                    //yycolumn+=yyleng;
                                    CreateNode(&yylval.Node,"AND","",yylineno);
                                    return AND;
                                }
"||"                            {
                                    //printf("OR at line %d at column %d\n",yylineno,yycolumn);
                                    //yycolumn+=yyleng;
                                    CreateNode(&yylval.Node,"OR","",yylineno);
                                    return OR;
                                }
"."                             {
                                    //printf("DOT at line %d at column %d\n",yylineno,yycolumn);
                                    //yycolumn+=yyleng;
                                    CreateNode(&yylval.Node,"DOT","",yylineno);
                                    return DOT;
                                }
"!"                             {
                                    //printf("NOT at line %d at column %d\n",yylineno,yycolumn);
                                    //yycolumn+=yyleng;
                                    CreateNode(&yylval.Node,"NOT","",yylineno);
                                    return NOT;
                                }
"int"|"float"                   {
                                    //printf("TYPE at line %d at column %d\n",yylineno,yycolumn);
                                    //yycolumn+=yyleng;
                                    //strcpy(yylval.type_char,yytext);
									//char str[64]="TYPE: ";
                                    //strcat(str,yytext);
                                    CreateNode(&yylval.Node,"TYPE",yytext,yylineno);
                                    return TYPE;
                                }
"("                             {
                                    //printf("LP at line %d at column %d\n",yylineno,yycolumn);
                                    //yycolumn+=yyleng;
                                    CreateNode(&yylval.Node,"LP","",yylineno);
                                    return LP;
                                }
")"                             {
                                    //printf("RP at line %d at column %d\n",yylineno,yycolumn);
                                    //yycolumn+=yyleng;
                                    CreateNode(&yylval.Node,"RP","",yylineno);
                                    return RP;
                                }
"["                             {
                                    //printf("LB at line %d at column %d\n",yylineno,yycolumn);
                                    //yycolumn+=yyleng;
                                    CreateNode(&yylval.Node,"LB","",yylineno);
                                    return LB;
                                }
"]"                             {
                                    //printf("RB at line %d at column %d\n",yylineno,yycolumn);
                                    //yycolumn+=yyleng;
                                    CreateNode(&yylval.Node,"RB","",yylineno);
                                    return RB;
                                }
"{"                             {
                                    //printf("LC at line %d at column %d\n",yylineno,yycolumn);
                                    //yycolumn+=yyleng;
                                    CreateNode(&yylval.Node,"LC","",yylineno);
                                    return LC;
                                }
"}"                             {
                                    //printf("RC at line %d at column %d\n",yylineno,yycolumn);
                                    //yycolumn+=yyleng;
                                    CreateNode(&yylval.Node,"RC","",yylineno);
                                    return RC;
                                }
"struct"                        {
                                    //printf("STRUCT at line %d at column %d\n",yylineno,yycolumn);
                                    //yycolumn+=yyleng;
                                    CreateNode(&yylval.Node,"STRUCT","",yylineno);
                                    return STRUCT;
                                }
"return"                        {
                                    //printf("RETURN at line %d at column %d\n",yylineno,yycolumn);
                                    //yycolumn+=yyleng;
                                    CreateNode(&yylval.Node,"RETURN","",yylineno);
                                    return RETURN;
                                }
"if"                            {
                                    //printf("IF at line %d at column %d\n",yylineno,yycolumn);
                                    //yycolumn+=yyleng;
                                    CreateNode(&yylval.Node,"IF","",yylineno);
                                    return IF;
                                }
"else"                          {
                                    //printf("ELSE at line %d at column %d\n",yylineno,yycolumn);
                                    //yycolumn+=yyleng;
                                    CreateNode(&yylval.Node,"ELSE","",yylineno);
                                    return ELSE;
                                }
"while"                         {
                                    //printf("WHILE at line %d at column %d\n",yylineno,yycolumn);
                                    //yycolumn+=yyleng;
                                    CreateNode(&yylval.Node,"WHILE","",yylineno);
                                    return WHILE;
                                }
{id}                            {
                                    //printf("ID %s at line %d at column %d\n",yytext,yylineno,yycolumn);
                                    //yycolumn+=yyleng;
                                    //strcpy(yylval.type_char,yytext);
									//char str[64]="ID: ";
                                    //strcat(str,yytext);
                                    CreateNode(&yylval.Node,"ID",yytext,yylineno);
                                    return ID;
                                }
{int}                           {
                                    //printf("INT %s at line %d at column %d\n",yytext,yylineno,yycolumn);
                                    //yycolumn+=yyleng;
                                    //yylval.type_int=atoi(yytext);
									//char str[64]="INT: ";
                                    //strcat(str,yytext);
                                    CreateNode(&yylval.Node,"INT",yytext,yylineno);
                                    return INT;
                                }
{float}                         {
                                    //printf("FLOAT %s at line %d at column %d\n",yytext,yylineno,yycolumn);
                                    //yycolumn+=yyleng;
                                    //yylval.type_float=atof(yytext);
									//char str[64]="FLOAT: ";
									char str1[64];
									//ftoa(atof(yytext),str);
									gcvt(atof(yytext),64,str1);
									//strcat(str,str1);
                                    CreateNode(&yylval.Node,"FLOAT",str1,yylineno);
                                    return FLOAT;
                                }
.                               {
                                    hasError=1;
									printf("Error type A at line %d : Mysterious character \'%s\'\n",yylineno,yytext);
                                }
%%

