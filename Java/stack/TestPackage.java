import stackuses.*;

public class TestPackage
{

	public static void main(String args[]) throws InvalidExpressionException
	{
		ParanthesisCheck exp1,exp2;
		
	//	exp1 = new ParanthesisCheck("p(x)=a0+x0(a+x(a2+x0(a3+x0a4)))(()))");
	//	exp2= new ParanthesisCheck("(a2-b2)=(a+b a-b))");
		
		try
		{
			exp1=new ParanthesisCheck(args[0]);
			exp1.checkExpression();
		}
	//	catch (InvalidExpressionException e)
	//	{
	//		System.out.println("The expression is invalid");
	//	}
		catch (ArrayIndexOutOfBoundsException e)
		{
			System.out.println("please give an expression as argument");		
		}
	}
}