package stackuses;

public class InvalidExpressionException extends Exception
{
	public InvalidExpressionException(String s)
	{
		super(s);
	}
	
	public InvalidExpressionException()
	{
		super("The Expression is Invalid");
	}
	

}
