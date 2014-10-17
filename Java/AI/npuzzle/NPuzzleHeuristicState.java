package npuzzle;

import ai.elements.*;

public class NPuzzleHeuristicState extends NPuzzleState implements HeuristicState
{
	
	private static short  type=0;
	private int hVal=0;
	private boolean firstTime=true;
	
	public NPuzzleHeuristicState(short n,short type)
	{
		super(n);
		this.type=type;
	}	
	public NPuzzleHeuristicState(short[][] passValue,short type)
	{
		super(passValue);
		this.type=type;		
	}
	public NPuzzleHeuristicState(short[][] passValue)
	{
		super(passValue);
	}	
	
	public int getHeuristicValue(State goalState)
	{
		
		firstTime=false;
		
		int n=value.length;
		
		NPuzzleState nPuzzleGoalState=(NPuzzleState)goalState;
		short[][] goalValue=nPuzzleGoalState.getState();		
		
		hVal=0;
		switch(type)
		{
			case 0: //no. of tiles misplaced
				for(int i=0;i<n;++i)
				{
					for(int j=0;j<n;++j)
					{
						if(value[i][j]!=goalValue[i][j])
							hVal++;
					}
				}
				return hVal;							
				
			case 1: //Manhattan distances
			
				boolean flag=false;
				int actualColumn=0,actualRow=0;
				
				for(int i=0;i<n;++i)
				{
					for(int j=0;j<n;++j)
					{
						for(actualRow=0;actualRow<n;++actualRow)
						{	
							for(actualColumn=0;actualColumn<n;++actualColumn)
							{
								if(value[i][j]==goalValue[actualRow][actualColumn])
								{
									flag=true;
									break;
								}
							}
							if(flag)
								break;
						}
						hVal=hVal+Math.abs(actualRow-i)+Math.abs(actualColumn-j);
						flag=false;						
					}
				}
				return hVal;
				
			default:
				System.out.println("Invalid Heuristic type");
				System.out.println("Setting type to 0....");
				type=0;
				return getHeuristicValue(goalState);
		}
	}
	
	//Overridden functions
	
	public State nextState(AiAction a) throws InvalidActionException
	{
		NPuzzleState ns = (NPuzzleState) super.nextState(a);
		return new NPuzzleHeuristicState(ns.getState());
	}
	public void display()
	{
		super.display();
		System.out.print("The heuristic value : ");
		if(!firstTime)
		System.out.println(hVal);
		else
		System.out.println("not yet computed");
		
	}
}