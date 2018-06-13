
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define size 100
typedef struct
{
char symbol[100];
float value;
struct node *next;
} node;

typedef struct
{
 node *head ;
 node *tail ;
} linkedList;

node* newNode(char symbol[],float value){
    node* n=( node*) malloc(sizeof(node));
   strcpy(n->symbol,symbol);
    n->value=value;
    n->next=NULL;
    return n;
}

void initializeLinkedList(linkedList *list){
    list->head=NULL;
    list->tail=NULL;
}

void addTail(linkedList *list,char symbol[],float value){
    node* n=newNode(symbol,value);

    if(list->tail)
        list->tail->next=n;

    list->tail=n;

    if(!list->head)
        list->head=n;
}

 node* search(linkedList *list,char symbol[]){
    node *n=list->head;
    while(n){
        if(strcmp(n->symbol,symbol)==0)
            return n;

        n=n->next;
    }
    return NULL;
}
/////////////////////////////////////////////////////////////////////////////////
typedef struct{
float items[size];
int top;
}stack;

 void initialize(stack*s){
 s->top=0;
 }

 void push(stack*s,float item){

     s->items[s->top]=item;
     s->top++;
 }

 float pop(stack*s){
    s->top--;
    return s->items[s->top];

 }

 int isempty(stack*s){
   if(s->top==0)
    return 1;
   else return 0;
 }

 int isfull(stack*s){
  if(s->top==size)
    return 1;
  else return 0;

 }

 float top(stack*s){
    float res = pop(s);
    push(s,res);
    return res;

 }
 ////////////////////////////////////////////////////////////////////////////////
 int order(char c)
{
 switch(c){
 case'(':
 case')':
    return 2;
 case'*':
 case'/':
     return 1;
 case'+':
 case'-':
     return 0;
 }
}
/////////////////////////////////////////////////////////////////////////////////
 char* topostfix(char infix[]){
 stack s;
 initialize(&s);
 char* postfix;
 postfix=(char*)malloc(100*sizeof(char));
 char c;
 int i=0; int j=0;
 while(infix[i]!='\0')

 {
     c=infix[i];
     //////////////////////////////////////
    if(infix[i]>='0'&&infix[i]<='9'){
         postfix[j]=c;
            j++;

    if(!(infix[i+1]>='0'&&infix[i+1]<='9')){
       if(infix[i+1]!='.'){
        postfix[j]=' ';
        j++;
       }
    }
    }

    /////////////////////////////////////
     if(isalpha(c)){
         postfix[j]=c;
            j++;

    if(!isalpha(infix[i+1])){
       if(infix[i+1]!='.'){
        postfix[j]=' ';
        j++;
       }
    }
    }
    //////////////////////////////////
    else if(c=='.'){
        postfix[j]=c;
            j++;
    }
    else if(c=='('){
      push(&s,c);
      }
    else if(c==')'){
        if(isempty(&s)){printf("error");start();}
        while(top(&s)!='(')
    {
        postfix[j]=pop(&s);
        j++;
         postfix[j]=' ';
        j++;
    }
    pop(&s);
    }
    else if(c=='+'||c=='-'||c=='*'||c=='/'){
    if(isempty(&s))
        push(&s,c);
    else{
        while(!isempty(&s)&&order(top(&s))>=order(c)&&top(&s)!='(')
    {
      postfix[j]=pop(&s);
      j++;
       postfix[j]=' ';
        j++;
    }

    push(&s,c);}
   }
   else{}
    i++;}
    while(!isempty(&s))
    {
        postfix[j]=pop(&s);
        j++;
         postfix[j]=' ';
        j++;

    }
    postfix[j]='\0';
    return postfix;
    }
/////////////////////////////////////////////////////////////////////////////////
char* removeSpace(char infix[]){
    int i=0,j;
while(infix[i]!='\0'){
        j=i;
    if(infix[i]==' '){
    while(infix[j]!='\0'){
        infix[j]=infix[j+1];
        j++;
        i=-1;
    }
}
    i++;
}
return infix;
}
//////////////////////////////////////////////////////////////////////////////
int equal(char infix[]){
    int count=0,i=0;
while(infix[i]!='\0'){
    if(infix[i]=='=')
       {
        count++;
       }
        i++;
}
if(count!=1)
    return 0;
else { i=0;
    while(infix[i]!= '='){
        if(!isalpha(infix[i]))
            return 0;
           else
            i++;
    }

}
return 1;
}
//////////////////////////////////////////////////////////////////////////////
void split(char*symbol,char*value,char infix[]){
int i=0,j=0;
while(infix[i]!='='){
    symbol[i]=infix[i];
    i++;
}
symbol[i]='\0';
while(infix[i+1]!='\0'){
    value[j]=infix[i+1];
    i++;
    j++;
}
value[j]='\0';
}
////////////////////////////////////////////////////////////////////////////////////////
linkedList list;
///////////////////////////////////////////////////////////////////////////////////////////

int check(char infix[]){
    int i=0,count1=0,count2=0;
    if(!(infix[i]>='0'&&infix[i]<='9'))
      if(!isalpha(infix[i]))
        if(infix[i]!='(')
        return 0;
    while(infix[i]!='\0'){
            char c = infix[i];
            char x =infix[i+1];
            //checking invalid symbol
    if(!(c>='0'&&c<='9')){
      if(!(c=='+'||c=='-'||c=='*'||c=='/'||c=='%'||c=='('||c==')'||c=='.')) {
        if(!isalpha(c)){
           return 0;}}}
     //checking numbers
    if(c>='0'&&c<='9'){
         if(x=='('||isalpha(x)){
               return 0;}}
   //checking strings
   if(isalpha(c))
   if((x>='0'&&x<='9')||x=='.'||x=='('){
         return 0;
      }

 //checking operators
  if(c=='+'||c=='-'||c=='*'||c=='/'||c=='%'){
        if(x=='+'||x=='-'||x=='*'||x=='/'||x=='%'||x==')'||x=='.'){
            return 0;
        }
   }
//checking maths error
  if(c=='/'){
       if(x=='0'){
            return 0;}}
//checking floating point
  if(infix[i]=='.'){
           if(!(x>='0'&&x<='9')){
               return 0;}}
   //checking brackets
if(c=='('){

if(x=='+'||x=='-'||x=='*'||x=='/'||x=='%'||x==')'||x=='.'){
      return 0;
}
  count1++;
}

if(c==')'){
    if(x=='.'||x=='('||(x>='0'&&x<='9')||isalpha(x)){
     return 0;
   }
   count2++;
}

if(count1<count2)
    return 0;

        i++;

    }
if(count1!=count2){
        return 0;
    }
    return 1;
}
////////////////////////////////////////////////////////////////////////////////////////////////
float evaluate(char postfix[]){
     stack s;
     initialize(&s);
     int i=0;
     int flag=0;
     int count;
 char symbol[10];

 while(postfix[i]!='\0'){
    if(postfix[i]>='0'&&postfix[i]<='9'){
        if(flag==0){
        push(&s,postfix[i]-'0');
        flag=1;
        }
    else if(flag==1){
        float num1;
        num1=pop(&s);
        push(&s,(postfix[i]-'0')+(10*num1));
        }
   else if(flag==2){

     float num2;
     float num3;
     num2=pop(&s);
     num3=postfix[i]-'0';
     push(&s,num2+(num3/pow(10,count)));
     count++;
   }

   }
   ///////////////////////////////////////
   else if(isalpha(postfix[i]))
    {
        int j=0;
        while(isalpha(postfix[i]))
       {
            symbol[j]=postfix[i];
            j++;
            i++;
        }
       symbol[j]='\0';
      if(search(&list,symbol)!=NULL){
          push(&s,search(&list,symbol)->value);
         }
         else{
         printf("ERROR\n");
         start();}
}
  /////////////////////////////////////////
   else if(postfix[i]=='.'){
        flag=2;
        count=1;

   }

   else if(postfix[i]==' ') {flag=0;}
   else{
       flag=0;
        float a,b;
        a=pop(&s);
       b=pop(&s);
switch(postfix[i]){
    case'+':push(&s,a+b);break;
    case'*':push(&s,a*b);break;
    case'/':push(&s,b/a);break;
    case'-':push(&s,b-a);break;}
   }


i++;

 }
return pop(&s);
 }

////////////////////////////////////////////////
void calculate(char infix[]){
char symbol[10];
char value[50];
char postfix[50];

strcpy(infix,removeSpace(infix));

if(equal(infix)==0){
    printf("ERROR\n");
    start();
}

 split(symbol,value,infix);

if(check(value)==0){
    printf("error\n");
    start();}


 strcpy(postfix,topostfix(value));

float res=evaluate(postfix);
printf("The value of the entered expression is %.3f\n",res);

node*n=search(&list,symbol);
if(n!=NULL)
{
    n->value=res;
}
else
addTail(&list,symbol,res);
start();
}

//////////////////////////////////////////////////////////////////////////////////////////////////
void start(){
char infix[50];
printf("Enter the expression or 'end' to exit:\t");
  gets(infix);
  if(strcmp(infix,"end")==0)
    exit(-1);
  else
    calculate(infix);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
initializeLinkedList(&list);
start();

    return 0;
}
