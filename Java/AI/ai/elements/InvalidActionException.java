package ai.elements;

public class InvalidActionException extends Exception
{
	public InvalidActionException()
	{
		super("An invalid action was applied to a state");
	}
	
	public InvalidActionException(String s)
	{
		super(s);
	}

}