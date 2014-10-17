#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

//function declarations
void moveUp(char *s);
void forwardDifference(float *f,int n,float x0,float h);
int findN(char *s);
float findDerivative(float *f,int n,int order,float x);
int* findBinomialCoefficients(int n);
void differentiate(int *f,int n);
float substitute(int *f,int n,float x);
int fact(int n);

void moveUp(char *s)
{

	int i,count=0,len=strlen(s);
	for(i=0;i<len;++i)
	{
	if(s[i]!=' ' && s[i]!='\t' && s[i]!=',')
		break;
	}
	
	for(i=i+1;i<len;++i)
	{
		if(s[i]==' ' || s[i]=='\t' || s[i]==',')
			break;
	}
	for(i=i+1;i<len;++i)
	{
		if(s[i]!=' ' && s[i]!='\t' && s[i]!=',')
			break;
	}

	for(i=i;i<=len;++i)
	{
		s[count++]=s[i];
	}

}

int findN(char *s)
{
	int i=0,count=0,len=strlen(s);

do
{
	for(i=i;i<len;++i)
	{
	   if(s[i]!=' ' && s[i]!='\t' && s[i]!=',')
	   {
		   ++count;
             break;
	   }
	}
	for(i=i+1;i<len;++i)
	{
		if(s[i]==' ' || s[i]=='\t' || s[i]==',')
			break;
	}
	}while(i<len);
	return count;

}
void forwardDifference(float *f,int n,float x0,float h)
{
    int i;
    float temp;
    
    temp=f[0]; //store the first value in temporary, will be later pushed to last
    
    for(i=0;i<n-1;++i)
    {
                
        f[i]=f[i+1]-f[i];
    }

    f[n-1]=temp; //f0 is stored at last position, del f0 is before it and so on 
    if(n==1)
        return;
        
    forwardDifference(f,n-1,x0,h);
}

float findDerivative(float *f,int n,int order,float x)
{
	int i,j,k,*coeff;
	float val=0;
	
	for(i=n-1;i>=0;--i) //f[n-1] is f0
	{
		coeff = findBinomialCoefficients(n-1-i); //returns the coefficients array of len n-i

			//display
			printf("\n\n");
			for(k=n-i-1;k>=0;--k)
				printf("%dS%d ",coeff[k],k);		
	
		for(j=0;j<order;++j)
		{
			//returns coefficients after differentiation
			differentiate(coeff,n-i); //coeff size is n-1-i + 1
		}
		
			//display
			printf("\n");
			for(k=n-i-1;k>=0;--k)
				printf("%dS%d ",coeff[k],k);		

		val = val + (substitute(coeff,n-i,x)*f[i]/fact(n-1-i));
		printf("val=%g",val);
	}
	free(coeff);
	return val;
}

int fact(int n)
{
	if(n==0)
		return 1;
		
	return n*fact(n-1);
}

int* findBinomialCoefficients(int n)
{
	int *f;
	int i,j;
	
	f=calloc(n+1,sizeof(int));
	
	if(n<=0)
		f[0]=1;
	else
	{
		f[1]=1;
		f[0]=0;
	}
	
	for(i=1;i<n;++i)
	{
		for(j=i;j>0;--j)
		{
			f[j]=f[j-1]+(f[j]*(0-i));
		}
		f[i+1]=1;
	}
	
	return f;
	
}

void differentiate(int *f,int n)
{
	int i;
	for(i=1;i<n;++i)
	{
		f[i-1]= f[i]*i;
	}
	f[n-1]=0; //differentiation decreases the order by 1
}

float substitute(int *f,int n,float x)
{
	float temp=0;
	float mul;
	int i,j;
	
	for(i=0;i<n;++i)
	{
		mul=1;
  		for(j=0;j<i;++j)
		{
			mul=mul*x;
		}
		temp=temp+(mul*f[i]);
	}
	return temp;
}

int main()
{

	int n,i,j,k;
	float x0,*f; // are the xo and f values
	char *buffer,tempChar;
	float x,h; //the spacing and the point at which derivative is found
	int o;//order of derivative

	printf("\n*****************************************************************************\n");
	printf("\nThis program will find the nth derivative of a function given in tabular form.\n");
	printf("\n******************************************************************************\n\n");
	
	printf("\nEnter the starting value of abscissa (x0): ");
	fflush(stdin);
	scanf("%f",&x0);
	printf("\nEnter the value of spacing h: ");
	fflush(stdin);
	scanf("%f",&h);	
	printf("\nEnter an estimate of the number of data values: ");
	fflush(stdin);
	scanf("%d",&n);

	//allocate memory
	buffer=(char *)calloc((n+5)*14,sizeof(char)); //allocating space that is required to get input, n+5 is allowed

	//getting input
	printf("\nEnter the values of fi(seperated by space or tab or comma):\n",n);
	scanf("%[^\n]",buffer);//this is to prevent the effect extra characters input earlier	
	getc(stdin);//used in place of fflush(stdin) to remove '\n' from the stdin
	scanf("%[^\n]",buffer);
	n=findN(buffer);
	
	//allocate memory for f
	f=(float *)calloc(n,sizeof(float));
  	
  	//tokenize the buffer to float values
	for(i=0;i<n;++i)
	{
		sscanf(buffer,"%f",&f[i]);
		moveUp(buffer);
	}
	
  	printf("\nGenerating Forward Differences.....\n");
	forwardDifference(f,n,x0,h);
	printf("\n");
	for(i=n-1;i>=0;--i)
	{
		printf("%g ",f[i]);
	}
	printf("\n");
	
	do
	{
		printf("\nEnter the order of derivative to be computed: ");
		fflush(stdin);
		scanf("%d",&o);
		
		printf("\nEnter the point x at which the derivatie is to be computed: ");
		fflush(stdin);
		scanf("%f",&x);		
		
		printf("\n\nComputing the derivative.......\n");
		x = (x-x0)/h; //x is used to store 's'
		x=findDerivative(f,n,o,x); //now x is used as temporary to store the nth derivative
		for(i=0;i<o;++i) // to compute the derivative/ h raised to the power o
			x=x/h;
		printf("\n\nThe value of the derivative for the given order and x is : %g\n",x) ;		

		printf("\n\nDo u want to find the derivative for another x and order (Y/N): ");
		getc(stdin);//used in place of fflush(stdin) to remove '\n' from the stdin
		scanf("%c",&tempChar);//get the user option
	}while (toupper(tempChar)!='N' && tempChar!=27);//esc key
	
   free(f);
   free(buffer);		
   return 0;
}

