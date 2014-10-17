#include<stdio.h>
#include<iostream.h>
#include<conio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
/*
  Important Rule:Always do (A/E) first if the other is (I/O)
*/
struct regions{
  char name;
  char value;//this can be = n,s,i,d
};
class terms{
public:
  char name;
  regions exr;
  regions ir[2];
  regions cr;
  terms(char name='a',char exr='a',char x1='a',char x2='a',char x3='a');
}t[3];


int getcs(char *cs);
void perform(char *cs);
void doA(char pos1,char pos2);
void doE(char pos1,char pos2);
void doI(char pos1,char pos2);
void doO(char pos1,char pos2);
char verifyA();
char verifyE();
char verifyI();
char verifyO();
char exintersect(terms *a,terms *b);
void print (char ch);
void makecr(char ch);
char figure[4][5]={"mpsm","pmsm","mpms","pmms"};

void main(){
  char cs[6],ch;
//  clrscr();
    do{
    fflush(stdin);
    t[2]=terms('m','0','1','5','6');
    t[1]=terms('p','4','3','5','6');
    t[0]=terms('s','2','1','3','6');
    printf("\n\nEnter the form of CS(eg:AIA-3):");
    if(getcs(cs))
    perform(cs);
    else
    printf("\nERROR INPUT\n");
    cout<<"\nDo you want to do more(Y\\N):";
    putch('y');
    ch=getch();
  }while(ch!='n' && ch!='N' && ch!=27);
}

terms::terms(char nam,char xr,char x1,char x2,char x3){
name=nam;
exr.name=xr;
ir[0].name=x1;
ir[1].name=x2;
cr.name=x3;
exr.value='n';
ir[0].value='n';
ir[1].value='n';
cr.value='n';
}
int getcs(char *cs){
scanf("%[^\n]",cs);
if (strlen(cs)==5 && cs[3]=='-' && cs[4]>48 && cs[4]<53)
return 1;
else
return 0;
}
void perform(char *cs){
int i;
for (i=0;i<3;++i){
 switch(toupper(cs[i])){
   case 'A':
    if (i!=2)
      doA(cs[4],i*2);
    else
    print(verifyA());
     break;
    case 'E':
    if (i!=2)
      doE(cs[4],i*2);
    else
     print(verifyE());
     break;
    case 'I':
    if (i!=2)
      doI(cs[4],i*2);
    else
    print(verifyI());
     break;
    case 'O':
    if (i!=2)
      doO(cs[4],i*2);
    else
     print(verifyO());
     break;
    default:
     print('z');
     i=4;

 }
}
}
void doA(char pos1, char pos2){
int i,j;
char ch;
pos1=pos1-48-1;
for (i=0;i<3;++i){
  if(figure[pos1][pos2]==t[i].name){
    t[i].exr.value='s';
    for (j=0;j<3;++j){
      if(figure[pos1][pos2+1]!=t[j].name && t[j].name!=t[i].name)
      {
	ch=exintersect(&t[i],&t[j]);
      }
    }
  }
}
for (i=0;i<3;++i){
   for (j=0;j<2;++j){
    if (t[i].ir[j].name==ch)
      t[i].ir[j].value='s';
   }
}
}

void doE(char pos1,char pos2){
int i,j;char ch;
pos1=pos1-48-1;
makecr('s');
for (i=0;i<3;++i){
  if(figure[pos1][pos2]==t[i].name){
    for (j=0;j<3;++j){
      if(figure[pos1][pos2+1]==t[j].name)
      {
	ch=exintersect(&t[i],&t[j]);
      }
    }
  }
}
for (i=0;i<3;++i){
   for (j=0;j<2;++j){
    if (t[i].ir[j].name==ch)
      t[i].ir[j].value='s';
   }
}

}
void doI(char pos1,char pos2){
int i,j;char ch;
int problem;
pos1=pos1-48-1;
for (i=0;i<3;++i){
  if(figure[pos1][pos2]==t[i].name){
     for (j=0;j<3;++j){
      if(figure[pos1][pos2+1]==t[j].name)
      {
	ch=exintersect(&t[i],&t[j]);
      }
    }
  }
}
if(t[0].cr.value!='s')
problem=1;
else
problem=0;
for (i=0;i<3;++i){
   for (j=0;j<2;++j){
    if (t[i].ir[j].name==ch){
       if(problem){
	  if(t[i].ir[j].value!='s'){
	     t[i].ir[j].value='i';
	      makecr('i');
	  }
	   else{
	       makecr('d');
	     }
	}
	else{//no problem
	   if(t[i].ir[j].value!='s')
	     t[i].ir[j].value='d';
	}
     }
    }
}
}

void doO(char pos1,char pos2){
int i,j;char ch;
int temp;
pos1=pos1-48-1;
for (i=0;i<3;++i){
  if(figure[pos1][pos2]==t[i].name){
     temp=i;
     for (j=0;j<3;++j){
      if(figure[pos1][pos2+1]!=t[j].name && t[j].name!=t[i].name)
      {
	if (t[i].exr.value!='s')
	  t[i].exr.value='d';
	  ch=exintersect(&t[i],&t[j]);
      }
    }
  }
}
for (i=0;i<3;++i){
   for (j=0;j<2;++j){
    if (t[i].ir[j].name==ch){
      if(t[i].ir[j].value!='s'){
	 if(t[temp].exr.value!='s'){
	   t[temp].exr.value='i';
	   t[i].ir[j].value='i';
	 }
	 else
	   t[i].ir[j].value='d';
      }
      else{
	if(t[temp].exr.value!='s')
	   t[temp].exr.value='d';
      }
    }
   }
}


}
char verifyA(){
int i,j;
char ch;
ch=exintersect(&t[0],&t[2]);
for (i=0;i<3;++i){
   for (j=0;j<2;++j){
    if (t[i].ir[j].name==ch)
      if(t[i].ir[j].value=='s' && t[0].exr.value=='s')
       return 'v';
   }
}
return 'i';
}
char verifyE(){
int i,j;char ch;
ch=exintersect(&t[0],&t[1]);
for (i=0;i<3;++i){
   for (j=0;j<2;++j){
    if (t[i].ir[j].name==ch)
      if(t[i].ir[j].value=='s' && t[0].cr.value=='s')
       return 'v';
   }
}
return 'i';
}
char verifyI(){
int i,j;
char ch;
ch=exintersect(&t[0],&t[1]);
for (i=0;i<3;++i){
   for (j=0;j<2;++j){
    if (t[i].ir[j].name==ch)
      if(t[i].ir[j].value=='d' || t[0].cr.value=='d')
       return 'v';
   }
}
return 'i';

}
char verifyO(){
int i,j;
char ch;
ch=exintersect(&t[0],&t[2]);
for (i=0;i<3;++i){
   for (j=0;j<2;++j){
    if (t[i].ir[j].name==ch)
      if(t[0].exr.value=='d' || t[i].ir[j].value=='d')
       return 'v';
   }
}
return 'i';

}
char exintersect(terms *a,terms *b){
int i,j;
for (i=0;i<2;++i){
  for (j=0;j<2;++j){
    if(a->ir[i].name==b->ir[j].name){
       return a->ir[i].name;
    }
  }
}
return 'z';
}

void print(char ch){
 if (ch=='v')
cout<<"\nYes!The specified form is a Valid CS\n";
 else if (ch=='i')
cout<<"\nSorry!The specified form is an Invalid CS\n";
 else
cout<<"\nERROR INPUT\n";
}
void makecr(char ch){
int i;
 for (i=0;i<3;++i)
  t[i].cr.value=ch;
}