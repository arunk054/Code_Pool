#include <stdio.h>
#include <math.h>

#ifndef f
#define f(x) (x*x)
#endif
#ifndef a1
#define a1(x) (2*x)
#endif
#ifndef a2
#define a2(x) (3)
#endif
#ifndef a0
#define a0(x) (2*x*x*x)
#endif

float f1(float x,float y,float z)
{
	return z;
}

float f2(float x,float y,float z)
{
	return (f(x)-a1(x)*z-a2(x)*y) / a0(x);
}
main()
{
float a=0;
float b=1;
float alpha=0;
float h=0.2;
float beta=0;

float n1;
int n;

float Z;
float z;
float x;
float y;
float Y;
float *Y_arr;
float *y_arr;

float k1,k2,l1,l2,m1,m2,p1,p2;
int i;
float K1,K2;
float final_y;

printf("Enter the value of 'a'\n");
scanf("%f",&a);
printf("Enter the value of 'b'\n");
scanf("%f",&b);
printf("Enter the value of 'h'\n");
scanf("%f",&h);
printf("Enter the value of alpha\n");
scanf("%f",&alpha);
printf("Enter the value of beta\n");
scanf("%f",&beta);
n1=(b-a)/h;
n=n1;
Z=-1; 
z=1; //alpha
x=a;
y=alpha;
Y=alpha;
Y_arr=(float *) malloc(sizeof(float)*(n+1));
y_arr=(float *) malloc(sizeof(float)*(n+1));
Y_arr[0]=Y;
y_arr[0]=y;

printf("%d\n",n);
for(i=1;i<=n;i++)
{
	k1=h*f1(x,y,z);
	k2=h*f2(x,y,z);
	l1=h*f1(x+h/2,y+k1/2,z+k2/2);
	l2=h*f2(x+h/2,y+k1/2,z+k2/2);
	m1=h*f1(x+h/2,y+l1/2,z+l2/2);
	m2=h*f2(x+h/2,y+l1/2,z+l2/2);
	p1=h*f1(x+h,y+m1,z+m2);
	p2=h*f2(x+h,y+m1,z+m2);
	x=x+h;
	y=y+((k1+2*l1+2*m1+p1)/6);
	z=z+((k2+2*l2+2*m2+p2)/6);
	y_arr[i]=y;
}
x=a;
for(i=1;i<=n;i++)
{
	k1=h*f1(x,Y,Z);
	k2=h*f2(x,Y,Z);
	l1=h*f1(x+h/2,Y+k1/2,Z+k2/2);
	l2=h*f2(x+h/2,Y+k1/2,Z+k2/2);
	m1=h*f1(x+h/2,Y+l1/2,Z+l2/2);
	m2=h*f2(x+h/2,Y+l1/2,Z+l2/2);
	p1=h*f1(x+h,Y+m1,Z+m2);
	p2=h*f2(x+h,Y+m1,Z+m2);
	x=x+h;
	Y=Y+((k1+2*l1+2*m1+p1)/6);
	Z=Z+((k2+2*l2+2*m2+p2)/6);
	Y_arr[i]=Y;
}
K1=(beta-y_arr[n])/(Y_arr[n]-y_arr[n]);
K2=(Y_arr[n]-beta)/(Y_arr[n]-y_arr[n]);


for(i=0;i<=n;i++)
{
	final_y = (K1*Y_arr[i])+ (K2*y_arr[i]);
	printf("y%d=%f\n",i+1,final_y);
}


return 0;

}

