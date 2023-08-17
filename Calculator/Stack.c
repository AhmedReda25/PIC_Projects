


#include <xc.h>
#include "Stack.h"

void StakInit(Stak *st_ptr){
    st_ptr->top = -1;
}

int IsEmtyStak(Stak st){
    return (st.top == -1);
}
int IsFullStak(Stak st){
    if(st.top == (MAX -1))
        return 1;
    return 0;
}

int push(datatype elmnt, Stak *st){
    if(st->top == MAX - 1)
        return 0;
    st->top++;
    st->elements[st->top] = elmnt;
    return 1;
}

int pop(Stak *st,datatype *elmnt){
    if(st->top == -1)
        return 0;
    *elmnt = st->elements[st->top];
    st->top--;
    return 1;
}
void staktop(Stak *ps,datatype *item){
    *item = ps->elements[ps->top];
}


int StakSiz(Stak st){
    return (st.top+1);
}
/*----------------------------------------------------------------*/
uint8_t Precedent(char a, char b){
    if(a=='^')
        return 1;
    else if(a=='*' || a=='/')
        return (b != '^');
    else if(a=='+' || a=='-')
        return (b != '^' && b != '*' && b != '/');

    return 0;
}
/*----------------------------------------------------------------*/
uint8_t Isdigit(char a){
    return (a>='0' && a<='9');
}
/*----------------------------------------------------------------*/
uint8_t operation_MultiDigit(uint8_t a, uint8_t b, uint8_t c){

    switch(c){
    case '+':
        return ((a)+(b));
    case '*':
        return ((a)*(b));
    case '-':
        return ((a)-(b));
    case '/':
        return ((a)/(b));
    }
    return 0;
}
/*----------------------------------------------------------------*/
void TORPN_MutiDigit(char exp[], char rpn[]){
    uint8_t i=0,j=0;
    char c,op;
    Stak st;
    StakInit(&st);

    //c = exp[i++];
    while((c = exp[i++])!='\0'){
        if(Isdigit(c))
            rpn[j++] = c;
        else{/*operator*/
            rpn[j++] = ' ';
            if(!(IsEmtyStak(st))){
                staktop(&st,&op);
                while(Precedent(op,c) && !(IsEmtyStak(st))){
                    pop(&st,&op);
                    rpn[j++]=op;
                    rpn[j++] = ' ';
                    if(!(IsEmtyStak(st)))
                        staktop(&st,&op);
                }
            }
            push(c,&st);
        }

    }
    rpn[j++] = ' ';
    while(!(IsEmtyStak(st))){
            pop(&st,&op);
            rpn[j++] = op;
            rpn[j++] = ' ';
        }
    rpn[j]=0;
}
/*------------------------------------------------------*/
uint8_t Calc_RPN_MutiDigit(char rpn[]){
    uint8_t i=0, digit_couner=0;
    uint8_t num=0, digit;
    uint8_t x, y;
    unsigned  char c;
    uint16_t result;

    Stak st;
    StakInit(&st);

    while((c=rpn[i]) != '\0'){
        if(Isdigit(c))
            {
                push((c),&st);
                digit_couner++;

            }
        else if(c == '*' || c == '+' || c == '-' || c == '/'){/*operator encountered*/


            pop(&st,&x);
            pop(&st,&y);
            push(operation_MultiDigit(y,x,c),&st);
        }
        else {/*Space encountered*/
            if( Isdigit(rpn[i-1]) ){
                for(int j=0; j<digit_couner; j++){
                    pop(&st,&digit);
                    num += ( (digit - 48)*(pow(10,j)) );
            }
            push(num,&st);
            num = 0;
            digit_couner = 0;
            }

        }
        i++;
    }

    pop(&st,&result);
    return result;
}
