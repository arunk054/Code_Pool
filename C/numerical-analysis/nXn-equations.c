#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

//function declarations
float myAbs(float f);
void moveUp(char *s);
void findPivot(int k,int n,int *p,float **a);

float myAbs(float f)
{
	if (f>=0)
		return f;
	else
	{
		return (f-(f*2));
	}
}
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

void findPivot(int k,int n,int *p,float **a)
{
	int i,pivotRow,temp;

	pivotRow=k;
	for(i=k+1;i<n;++i)
	if(myAbs(a[p[pivotRow]][k])<myAbs(a[i][k]))
	{
		pivotRow=i;
	}

	//swap the pivot vector values
	temp=p[k];
	p[k]=p[pivotRow];
	p[pivotRow]=temp;

}


int main()
{

	int n,i,j,k;
	char *buffer,tempChar;
	float **a;//elements of matrix A
	int *p;//pivot vector
	float *d,*b;//scaling factors, b -vector
	printf("\n*************************************************************************\n");
	printf("\nThis program will find the solution of an nXn system of linear equations.\n");
	printf("\n*************************************************************************\n\n");
	printf("Enter the size of the coefficient matrix A: ");
	fflush(stdin);
	scanf("%d",&n);
	printf("\nEnter the elements of the the matrix A - one row at a time\n");

	//allocating memory
	a=(float **)calloc(n,sizeof(int));
	for(i=0;i<n;++i)
	{
		a[i]=(float *)calloc(n,sizeof(float));
	}
	p=(int *)calloc(n,sizeof(int));
	d=(float *)calloc(n,sizeof(float));
	b=(float *)calloc(n,sizeof(float));	
	
	//allocate some memory to buffer
	buffer=(char *)calloc(n*16,sizeof(char));

	//initialize the pivot vector
	for(i=0;i<n;++i)
		p[i]=i;

	//getting input
	for(i=0;i<n;++i)
	{
		printf("\nEnter the elements of row %d (seperated by space or tab or comma):\n",i);
		scanf("%[^\n]",buffer);//this is to prevent the effect extra characters input earlier	
		getc(stdin);//used in place of fflush(stdin) to remove '\n' from the stdin
		scanf("%[^\n]",buffer);

		for(j=0;j<n;++j)
		{
			sscanf(buffer,"%f",&a[i][j]);
			moveUp(buffer);
		}
	}
	printf("\nPerforming Gauss Elimination on the matrix A......\n\n");


	//find scale factors
	for(i=0;i<n;++i)
	{
		d[i]=myAbs(a[i][0]);

		for(j=1;j<n;++j)
		{
			if(d[i] < myAbs(a[i][j]))
			{
				d[i]=myAbs(a[i][j]);
			}
		}
        }


	//divide each row by their scale factors
	for(i=0;i<n;++i)
	{
		for(j=0;j<n;++j)
		{
			a[i][j] =a[i][j]/d[i];
		}
	}


	//start the gauss elimination process
	for(k=0;k<n-1;++k)
	{
		//find the pivot vector
		findPivot(k,n,p,a);

		//compute multipliers and do subtractions
		for(i=k+1;i<n;++i)
		{
			a[p[i]][k] = a[p[i]][k]/a[p[k]][k];
			for(j=k+1;j<n;++j)
			{
				a[p[i]][j] = a[p[i]][j] - a[p[i]][k] * a[p[k]][j];
			}
		}
	}
	
	printf("\nThe matrix A after gauss elimination is\n\n");
	for(i=0;i<n;++i)
	{
 			for(j=0;j<n;++j)
 			{
 				printf("%g ",a[i][j]);
			}
			printf("\n");
  	}	
do
{
	//getting the b-vector input
		printf("\nEnter the elements of the b vector(seperated by space or tab or comma):\n");
		scanf("%[^\n]",buffer);//this is to prevent the effect extra characters input earlier	
		getc(stdin);//used in place of fflush(stdin) to remove '\n' from the stdin
		scanf("%[^\n]",buffer);

		for(i=0;i<n;++i)
		{
			sscanf(buffer,"%f",&b[i]);
			moveUp(buffer);
		}

	printf("\nPerforming Forward Substitution......\n\n");
	
	//start forward substitution
	//divide each element of the b-vector by their corresonding scale factors
	for(i=0;i<n;++i)
	{
			b[i] = b[i]/d[i];
	}
	
	//compute the b- vector values
	for(i=1;i<n;++i)
	{
		for(j=0;j<i;++j)
		{
		  b[p[i]]= b[p[i]] - (a[p[i]][j]*b[p[j]]);
		}
	} 
	
	printf("\nPerforming Backward Substitution......\n\n");

    //start backward substitution
    for(i = n-1;i >= 0;--i)
    {
        //using the memory location of b to store x
        for(j=i+1;j<n;++j)
        {
                b[p[i]]=b[p[i]] - (a[p[i]][j]*b[p[j]]);        
        }
        b[p[i]] = b[p[i]]/a[p[i]][i];         

    }

	printf("\nThe solution to the given system of %dX%d linear equations is\n\n",n,n);
	//display the solution
    for(i=0;i<n;++i)
        printf("x%d = %g; ",i+1,b[p[i]]);
    
printf("\n\nDo u want to find the solution for a new set of b - vector values (Y/N): ");

getc(stdin);//used in place of fflush(stdin) to remove '\n' from the stdin
scanf("%c",&tempChar);//get the user option
}while (toupper(tempChar)!='N' && tempChar!=27);//esc key

//freeing the memory
for(i=0;i<n;++i)
    free(a[i]);
free(a);
free(b);
free(d);
free(p);
free(buffer);
return 0;
}

