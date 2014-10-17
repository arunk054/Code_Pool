import ai.elements.*;
import npuzzle.*;

public class testState
{

	public static void main(String args[]) throws InvalidActionException
	{

		NPuzzleState initialState,nextState;
		short tempAr[]={1,2,0,3,5,4,6,8,7};
		short [][] initialStateValue=new short[3][3];
		for(short i=0;i<3;++i)
			for(short j=0;j<3;++j)
				initialStateValue[i][j]=tempAr[i*3+j];
		
		initialState=new NPuzzleState(initialStateValue);
		Node n1=new Node(null,initialState,null,0);
		NPuzzleAction[] actArray=(NPuzzleAction[]) NPuzzleAction.createActionArray();
		Node nArray[];
		nArray=n1.createSuccessors(actArray);
		
		for(int i=0;i<nArray.length;++i)
		{
			if(nArray[i]!=null)
			{
			NPuzzleState s =(NPuzzleState)nArray[i].getCurState();
			s.display();
			}
		}
			
	}
}