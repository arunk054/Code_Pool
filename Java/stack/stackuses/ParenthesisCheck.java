package stackuses;

import stacks.*;

public  class ParenthesisCheck
{	
	//fields
	private Stack myStack;
	private int expressionSize;
	
	//constructor
	public ParanthesisCheck(String s)
	{
		int i;
		
		myStack=new Stack();	
		
		for (i=0;i<s.length();++i)
		{
			myStack.push(s.charAt(i));
		}
		expressionSize = s.length();
		
	}
	
	//members
	public void checkExpression() throws InvalidExpressionException
	{	
		int i,count=0;

		for (i=0;i<expressionSize;++i)
		{	
				if(myStack.top()==')')
				count++;
				else if(myStack.top()=='(')
				count--;
				
				if (count<0)
				{
					throw new InvalidExpressionException();
				}
				myStack.pop();
		}
		if (count!=0)
		{
			throw new InvalidExpressionException();
		}
	}
	
}