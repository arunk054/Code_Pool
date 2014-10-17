#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>

//The function definition
#ifndef	f
#define f(x) (((x*x*x)*sin(x)) + (x*pow(2.7183,x)))  //in sin(x) - x is in radians
#endif
#ifndef	a0
#define a0(x) (pow(2.7183,x))
#endif
#ifndef	a1
#define a1(x) (x*x)
#endif
#ifndef	a2
#define a2(x) (1)
#endif

double computeF2(double x,double y,double z)
{
	return (f(x)-(a1(x)*z)-(a2(x)*y))/a0(x);
}
int main()
{
	int n,i;
	float x0,h,y0,z0,xf;
	float k1,l1,m1,p1,k2,l2,m2,p2;
	float x,y,z;
	char tempChar;

	printf("\n***************************************************************************\n");
	printf("\nThis program will find the solution of a second order differential equation\n");
	printf("\n***************************************************************************\n\n");
	
	do
	{
	printf("\nEnter the starting value of x (x0): ");
	fflush(stdin);
	scanf("%f",&x0);
	printf("\nEnter the value of y(x0): ");
	fflush(stdin);
	scanf("%f",&y0);
	printf("\nEnter the value of y'(x0): ");	
	fflush(stdin);
	scanf("%f",&z0);
	printf("\nEnter the value of the spacing h: ");
	fflush(stdin);
	scanf("%f",&h);	
	printf("\nEnter the number of steps to be carried out: ");	
	fflush(stdin);
	scanf("%d",&n);

	x=x0,z=z0,y=y0;
	printf("\nThe solution to the given differential equation at discrete points is\n\n");
	for(i=1;i<=n;++i)
	{
	
		k1=h*z;
		k2=h*computeF2(x,y,z);
		l1=h*(z+(k2/2));
		l2=h*computeF2(x+(h/2),y+(k1/2),z+(k2/2));
		m1=h*(z+(l2/2));
		m2=h*computeF2(x+(h/2),y+(l1/2),z+(l2/2));
		p1=h*(z+m2);
		p2=h*computeF2(x+h,y+m1,z+m2);
		x=x+h;
		y=y+((k1+(2*l1)+(2*m1)+p1)/6);
		z=z+((k2+(2*l2)+(2*m2)+p2)/6);
		printf("y(%g)=%g ",x,y);
		printf("z(%g)=%g\n\n",x,z);		
	}
	printf("\n\nDo u want to find the solution for another set of values (Y/N): ");	
	getc(stdin);//used in place of fflush(stdin) to remove '\n' from the stdin
	scanf("%c",&tempChar);//get the user option
	}while (toupper(tempChar)!='N' && tempChar!=27);//esc key

}
