package npuzzle;

import ai.elements.*;

public class NPuzzleState implements State
{
	protected short value[][];
	
	public NPuzzleState(short n)
	{
		//default state created is the goalstate for  'n' puzzle problem
		n=(short)Math.sqrt((double)(n+1));
		value=new short[n][n];
		for(short i=0;i<n;++i)
		{
			for(short j=0;j<n;++j)
			{
				value[i][j]=(short)((((i*n)+j)+1)%(n*n));
			}
		}
	}	
	public NPuzzleState(short[][] passValue)
	{
		//default is Eight Puzzle and the state created is the goalstate
		value=new short[passValue.length][passValue.length];
		for(short i=0;i<value.length;++i)
		{
			for(short j=0;j<value.length;++j)
			{
				value[i][j]=passValue[i][j];
			}
		}
	}
	
	public boolean goalTest(State goalState)
	{
		NPuzzleState nPuzzleGoalState=(NPuzzleState)goalState;
		short[][] goalValue=nPuzzleGoalState.getState();
		for(short i=0;i<value.length;++i)
		{
			for(short j=0;j<value.length;++j)
			{
				try
				{
					if(value[i][j]!=goalValue[i][j])
						return false;	
				}
				catch(Exception e)
				{
					System.out.println("Your goal State is not a valid state");
					System.exit(0);
				}
			}
		}
	
		return true;
	}
	public State nextState(AiAction a) throws InvalidActionException
	{
	
		
		NPuzzleAction aTemp =(NPuzzleAction)a;
		char actionValue=aTemp.getAction();
		short blankTileRow=0,blankTileColumn=0;
		short nextStateValue[][]= new short[value.length][value.length];

		for(short i=0;i<value.length;++i)
		{
			for(short j=0;j<value.length;++j)
			{
				if(value[i][j]==0)		
				{
					blankTileRow=i;
					blankTileColumn=j;
				}
				nextStateValue[i][j]=value[i][j];
			}
		}
	
		switch(actionValue)
		{
		
		case 'l':

			if(blankTileColumn>0)
			{
				nextStateValue[blankTileRow][blankTileColumn]=value[blankTileRow][blankTileColumn-1];
				
				nextStateValue[blankTileRow][blankTileColumn-1]=0;
			}
			else
				throw new InvalidActionException();							
//				return null;
			break;
			
		case 'r':

			if(blankTileColumn<nextStateValue.length-1)
			{
				nextStateValue[blankTileRow][blankTileColumn]=value[blankTileRow][blankTileColumn+1];
				nextStateValue[blankTileRow][blankTileColumn+1]=0;
			}
			else
				throw new InvalidActionException();
//				return null;
			break;						
			
		case 'u':
			if(blankTileRow>0)
			{
				nextStateValue[blankTileRow][blankTileColumn]=value[blankTileRow-1][blankTileColumn];
				nextStateValue[blankTileRow-1][blankTileColumn]=0;
			}
			else
				throw new InvalidActionException();			
//				return null;
			break;			
			
		case 'd':

			if(blankTileRow<nextStateValue.length-1)
			{
				nextStateValue[blankTileRow][blankTileColumn]=value[blankTileRow+1][blankTileColumn];
				nextStateValue[blankTileRow+1][blankTileColumn]=0;
			}			
			else
				throw new InvalidActionException();
//				return null;
			break;		
		}
		
		return new NPuzzleState(nextStateValue);
	}	
	
	public void display()
	{
		System.out.println();		
		for(short i=0;i<value.length;++i)
		{
			for(short j=0;j<value.length;++j)
			{
				System.out.print(value[i][j]+" ");
			}
			System.out.println();
		}
		System.out.println();	
	}
			
	public short[][] getState()
	{
		return value;
	}

	public boolean equals(State anotherState)
	{
		NPuzzleState s=(NPuzzleState)anotherState;
		short[][] anotherValue=s.getState();		
		try
		{
			for(short i=0;i<value.length;++i)
			{
				for(short j=0;j<value.length;++j)
				{
					if(anotherValue[i][j]!=value[i][j])
						return false;
				}
				
			}
		}
		catch(IndexOutOfBoundsException e)
		{
			System.out.println("Your States are not of the same type");
			System.exit(0);
		}
		
		return true;
	}
}