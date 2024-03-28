#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//链栈节点结构
typedef struct Node{
    char data;
    struct Node* next;
} Node;

//链栈结构
typedef struct Stack{
    int size;
    Node* top;
}Stack;

//初始化
Stack* initStack(){
    Stack* istack=(Stack*)malloc(sizeof(Stack));
    if(istack!=NULL){
        istack->top=NULL;
        istack->size=0;
    }
    return istack; 
}

//判断链栈是否为空
int isEmpty(Stack* istack){
    if(istack->top==NULL){
        return 1;//空 
    }
        return 0;//不为空 
}

//获取栈顶元素的数据节点
Node* topstack(Stack* istack){
    if(istack->size!= 0){
        return istack->top;
    }
    return NULL;
}

//压栈
void push(Stack* istack,char x){
    
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = x;
    temp->next = istack->top;
    istack->top = temp;
    istack->size++;
    return;
}

//弹栈
Node* pop(Stack* istack){
    if(isEmpty(istack)==0)
    {
        Node* account = istack->top;
        istack->top = istack->top->next;
        istack->size--;
        return account;
    }
    
    return NULL;
}

//释放链栈内存
void clear(Stack* stack){
    while(stack->top != NULL){
        Node* temp = stack->top;
        stack->top = stack->top->next;
        free(temp);
    }
}
char buffer[256] = {0};
void charput(char ch){
    static int index = 0;
    buffer[index++] = ch;
}
int priority(char ch){
    int ret = 0;
    switch(ch)
    {
        case '+':
        case '-':
            ret = 1;
            break;
        case '*':
        case '/':
            ret = 2;
            break;
        default:
            break;
    }
    return ret;
}

int number(char ch){
    return(ch>='0'&&ch<='9');
}

int is_operator(char ch){
    return(ch=='+'||ch=='-'||ch=='*'||ch=='/');
}

int left(char ch){
    return(ch=='(');
}

int right(char ch){
    return(ch==')');
}

int transform(char str[]){
    Stack* istack=initStack();
    int i=0;
    while(str[i]!='\0'){
        if(number(str[i])==1){
            if(number(str[i+1])==1){//判断后面的1是不是数字
                charput(str[i]);
            }
            else{
                charput(str[i]);
                charput(' ');
            }
        }
        else if(is_operator((str[i]))==1){
            if(str[i+1]=='0'&&str[i]=='/'){
                printf("错误！\n");
                return 0;
            }
            if(isEmpty(istack)==0){
                while((isEmpty(istack)==0)&&(priority(str[i])<=(priority(topstack(istack)->data)))){
                    charput(topstack(istack)->data);
                    charput(' ');
                }
            }
            push(istack,str[i]);
        }
        else if(left(str[i])){
            push(istack,str[i]);
        }
        else if(right(str[i])){
            while(left(topstack(istack)->data)!=1)
            {
                charput(pop(istack)->data);
                if(isEmpty(istack)==1){
                    printf("没有匹配到左括号\n");
                    return -1;
                }
            }
            pop(istack);
        }
        else{
            printf("有不能识别的字符\n");
            return -1;
        }
        i++;
    }
    if(str[i]=='\0')
    {
        while(isEmpty(istack)==0)
        {
            if(topstack(istack)->data=='('){
                printf("没有匹配的'(',缺少')'\n");
                return -1;
            }
            charput(pop(istack)->data);
        }
    }
    else{
        printf("遍历没有完成！\n");
    }
    return 1;
}

//计算后缀表达式 
//整型 
typedef struct Node1{
    int data;
    struct Node1* next;
}pNode1;

//
typedef struct Stack1{
    int size;
    pNode1* top;
}pStack1;

//初始化 
pStack1* initStack1(){
    pStack1* istack = (pStack1*)malloc(sizeof(pStack1));
    if(istack!= NULL){
        istack->top = NULL;
        istack->size = 0;
    }
    return istack;
}

//判断栈是否为空 
int isEmpty1(pStack1* istack){
    if(istack->top==NULL){
        return 1;
    }
    return 0;
}
//获取栈顶元素 
int top1(pStack1* istack){
    if(istack->size!=0){
        return istack->top->data;
    }
    return 99999;
}
//弹栈 
int pop1(pStack1* istack){
    if(isEmpty1(istack)==0){
        int account=istack->top->data;
        istack->top=istack->top->next;
        istack->size--;
        return account;
    }
    return 99999;
}
//压栈 
void push1(pStack1* istack,int x){
    pNode1* temp;
    temp = (pNode1*)malloc(sizeof(pNode1));
    temp->data = x;
    temp->next = istack->top;
    istack->top = temp;
    istack->size++;
    return;
}

//
int express(int left,int right,char op){
    switch(op)
    {
        case '+':
            return left+right;
        case '-':
            return left-right;
        case '*':
            return left*right;
        case '/':
            if(right==0){
                return 999;
            }
            return left/right;
        default:
            break;
    }
    return -1;
}

int getsize(pStack1* stack){
    return stack->size;
}
//计算 
int calculate(char str[])
{
    pStack1* istack2 = initStack1();
    int i = 0;
    while(str[i]!='\0'){
        char a[6] = {0};
        int index=0;
        if(number(str[i])==1)
        {
            while(number(str[i])==1){
                a[index]=str[i];
                index++;
                i++;
            }
            push1(istack2,atoi(a));
        }
        else if(is_operator(str[i])==1){
            int right = pop1(istack2);
            int left = pop1(istack2);
            int ret = express(left,right,str[i]);
            if(ret==999)
            {
                printf("错误！\n");
                return 999;
            }
            push1(istack2,ret);
        }
        else if(str[i]==' '){
        }
        else{
            printf("错误!\n");
            break;
        }
        i++;
    }
    if(str[i]=='\0'&&getsize(istack2)){
        return top1(istack2);
    }
    return 0;
}

int main()
{
    char str[1024]={0};
    printf("请输入四则运算表达式:\n");
    scanf("%s",str);
    int num=transform(str);
    if(num==-1)
    {
        printf("表达式转换错误：\n");
    }
    else if(num==1)
    {
        printf("转化后的表达式：%s\n",buffer);
    }
    else{
    	printf("无效的表达式\n");
        return 0;
    }
    int num1=calculate(buffer);
    if(num1==999)
    {
    	printf("除数不能为0\n"); 
        return 0;
    }
    printf("%d\n",num1);
}
