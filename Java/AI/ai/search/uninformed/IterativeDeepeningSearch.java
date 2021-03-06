 package ai.search.uninformed;

import ai.elements.*;
import datastructures.Stack;
import java.io.*;
import java.util.Vector;

public class IterativeDeepeningSearch implements UninformedSearch
{
	
	private int totalNumberOfNodes;
	private int maxNumberOfNodes;
	private int stateSpaceEstimate;

	
	public IterativeDeepeningSearch()
	{
		totalNumberOfNodes=0;
		maxNumberOfNodes=0;
		stateSpaceEstimate=1000;
	}
	
	public IterativeDeepeningSearch(int passStateSpaceEstimate)
	{
		totalNumberOfNodes=0;
		maxNumberOfNodes=0;		
		stateSpaceEstimate=passStateSpaceEstimate;
	}
	
	public Node doSearch(State initialState, State goalState, AiAction[] AiActionArray, boolean isPruning, boolean isDisplayNodes)
	{
	
		//initializations
		Node[] tempNodeAr=new Node[AiActionArray.length];		
		Node.resetCountOfNodes();		
		totalNumberOfNodes=0;		
		int depthLimit = 0;
		
		do
		{
		maxNumberOfNodes=Node.getCountOfNodes();
		totalNumberOfNodes=totalNumberOfNodes+maxNumberOfNodes;
		Node.resetCountOfNodes();		
		Node curNode=new Node(null,initialState,null,0,0);
		Stack stack=new Stack(stateSpaceEstimate,stateSpaceEstimate/2);
//		if(isPruning)
			Vector closedList=new Vector(stateSpaceEstimate);
			
		if(isDisplayNodes)
			System.out.println("The nodes displayed are in the order in which they are subjected to goal test");
			
		do
		{
				

		//display the current node
		if(isDisplayNodes)
			curNode.display();

		//subject to goal test
		if(curNode.goalTest(goalState))
		{
			//update total number of nodes generated		
			totalNumberOfNodes=totalNumberOfNodes+Node.getCountOfNodes();
			maxNumberOfNodes=(maxNumberOfNodes>=Node.getCountOfNodes())?maxNumberOfNodes:Node.getCountOfNodes();	
			return curNode;
		}
		
		//create successors
		if(curNode.getDepth()<depthLimit)
		{
			tempNodeAr=curNode.createSuccessors(AiActionArray);
			//add the successors in the stack
			stack.push(tempNodeAr);
		}			
				
		//add curNode's state to closedList--already  expanded nodes
		if(isPruning)
			closedList.add(curNode.getCurState());		

		try
		{		
			do
			{
				//extract the top in stack
				curNode=(Node) stack.pop();				
				//prune if repeated state
			}while(isPruning && isAlreadyExpanded(curNode.getCurState(),closedList));
		}
		catch(NullPointerException e)
		{
		}				
				
		}while(curNode!=null);	
		
		
		++depthLimit;

		// check for termination of the state space when the same number of nodes are generated for two depth limits		
		}while(	maxNumberOfNodes!=Node.getCountOfNodes()); 		
		
		totalNumberOfNodes=totalNumberOfNodes+Node.getCountOfNodes();
		return null;
		
	}

	public Node doSearch(State initialState, State goalState, AiAction AiActionObject, boolean isPruning, boolean isDisplayNodes)
	{
				
		//initializations	
		Node.resetCountOfNodes();		
		totalNumberOfNodes=0;		
		int depthLimit = 0;
		
		do
		{
		AiAction[] AiActionArray=AiActionObject.createActionArray(initialState);		
		Node[] tempNodeAr=new Node[AiActionArray.length];	
			
		maxNumberOfNodes=Node.getCountOfNodes();
		totalNumberOfNodes=totalNumberOfNodes+maxNumberOfNodes;
		Node.resetCountOfNodes();		
		Node curNode=new Node(null,initialState,null,0,0);
		Stack stack=new Stack(stateSpaceEstimate,stateSpaceEstimate/2);
//		if(isPruning)	
			Vector closedList=new Vector(stateSpaceEstimate);
			
		if(isDisplayNodes)
			System.out.println("The nodes displayed are in the order in which they are subjected to goal test");
			
		do
		{
				

		//display the current node
		if(isDisplayNodes)
			curNode.display();

		//subject to goal test
		if(curNode.goalTest(goalState))
		{
			//update total number of nodes generated		
			totalNumberOfNodes=totalNumberOfNodes+Node.getCountOfNodes();
			maxNumberOfNodes=(maxNumberOfNodes>=Node.getCountOfNodes())?maxNumberOfNodes:Node.getCountOfNodes();	
			return curNode;
		}
		
		//create successors
		if(curNode.getDepth()<depthLimit)
		{
			tempNodeAr=curNode.createSuccessors(AiActionArray);
			//add the successors in the stack
			stack.push(tempNodeAr);
		}			
		
		//add curNode's state to closedList--already  expanded nodes
		if(isPruning)
			closedList.add(curNode.getCurState());
		
		try
		{		
			do
			{
				//extract the top in stack
				curNode=(Node) stack.pop();					
				//prune if repeated state			
			}while(isPruning &&  isAlreadyExpanded(curNode.getCurState(),closedList));

			//Create Action Array	
			AiActionArray=AiActionObject.createActionArray(curNode.getCurState());	
			tempNodeAr=new Node[AiActionArray.length];				
			
		}
		catch(NullPointerException e)
		{
		}				
				
		}while(curNode!=null);	
		
		
		++depthLimit;

		// check for termination of the state space when the same number of nodes are generated for two depth limits		
		}while(	maxNumberOfNodes!=Node.getCountOfNodes()); 		
		
		totalNumberOfNodes=totalNumberOfNodes+Node.getCountOfNodes();
		return null;
	
	}	
	
	public int totalNodesGenerated()
	{
		return totalNumberOfNodes;
	}
	
	public int maxNodesStored()
	{
		return maxNumberOfNodes;
	}
	
	private boolean isAlreadyExpanded(State s,Vector closedList)
	{
		for(int i=0;i<closedList.size();++i)
		{
		
				if(s.equals((State)closedList.get(i)))
				return true;

		}
		return false;
		
	}
	
}

