import ai.elements.*;
import ai.search.heuristic.*;
import npuzzle.*;

public class NPuzzleProblem
{

	public static void main(String args[])
	{
		NPuzzleHeuristicState initialState,goalState;
		int n=3;
		short tempAr[]={1,2,3,6,0,4,7,8,5};
		short [][] initialStateValue=new short[n][n];
		for(short i=0;i<n;++i)
			for(short j=0;j<n;++j)
				initialStateValue[i][j]=tempAr[i*n+j];
				
		initialState=new NPuzzleHeuristicState(initialStateValue,(short)3);
		goalState=new NPuzzleHeuristicState((short)8,(short)3);
		
		NPuzzleAction a= new NPuzzleAction('l');
		AiAction[] actArray=a.createActionArray();		
		Node solutionNode;
		AStarSearch b1=new AStarSearch(2000);
		solutionNode=b1.doSearch(initialState,goalState,actArray,true,true);
		System.out.println("");
		System.out.print("Total nodes generated is: ");
		System.out.println(b1.totalNodesGenerated());		
	}

}