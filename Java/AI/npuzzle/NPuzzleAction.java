package npuzzle;

import ai.elements.*;

public class NPuzzleAction implements AiAction
{
	private char value;
	
	public NPuzzleAction(char c)
	{
		value=c;
	}
	
	public int getStepCost(State curState)
	{
		return 1;
	}
	
	public char getAction()
	{
		return value;
	}
	
	public AiAction[] createActionArray()
	{
		char[] actionValues={'l','r','u','d'};	
		
		NPuzzleAction[] actArray=new NPuzzleAction[actionValues.length];
		
		for(int i=0;i<actionValues.length; ++i)
			actArray[i]=new NPuzzleAction(actionValues[i]);
			
		return actArray;			
		
	}
	public AiAction[] createActionArray(State curState)
	{
		return createActionArray();
	}
	
	public void display()
	{
		switch(value)
		{
		case 'l':
			System.out.println("left");
			break;
		case 'r':
			System.out.println("right");
			break;		
		case 'u':
			System.out.println("up");
			break;		
		case 'd':
			System.out.println("down");
			break;								
		default:
			System.out.println("Invalid Action Object");
		}
		System.out.println("");		
	}	


}