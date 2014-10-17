package ai.search.uninformed;

import ai.elements.*;
import datastructures.QueeLL;
import java.io.*;
import java.util.Vector;

public class BreadthFirstSearch implements UninformedSearch
{
	
	private int totalNumberOfNodes;
	private int stateSpaceEstimate;
	
	public BreadthFirstSearch()
	{
		totalNumberOfNodes=0;
		stateSpaceEstimate=1000;
	}
	public BreadthFirstSearch(int passStateSpaceEstimate)
	{
		totalNumberOfNodes=0;
		stateSpaceEstimate=passStateSpaceEstimate;		
	}	
	public Node doSearch(State initialState, State goalState, AiAction[] AiActionArray, boolean isPruning, boolean isDisplayNodes)
	{
	
		//initializations
		Node[] tempNodeAr=new Node[AiActionArray.length];		
		totalNumberOfNodes=0;
		Node.resetCountOfNodes();
		Node curNode=new Node(null,initialState,null,0,0);
		QueeLL quee=new QueeLL();	
		
		//The technique of closed list is implemented for pruning , but this does not increase the space complexity
		//as all nodes, any way have to be in memory.	
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
			totalNumberOfNodes=Node.getCountOfNodes();
			return curNode;
		}
		
		//create successors
		tempNodeAr=curNode.createSuccessors(AiActionArray);
		
		//add curNode's state to closedList--already  expanded nodes
		if(isPruning)
			closedList.add(curNode.getCurState());
		
		//add the successors in the quee
		quee.add(tempNodeAr);			
		
		try
		{		
			do
			{
				//extract the first in quee
				curNode=(Node) quee.serviceFirst();					
				//prune if repeated state			
			}while(isPruning &&  isAlreadyExpanded(curNode.getCurState(),closedList));
		}
		catch(NullPointerException e)
		{
		}				
				
		}while(curNode!=null);		
		
		//update total number of nodes generated		
		totalNumberOfNodes=Node.getCountOfNodes();		
		return null;
		
	}

	public Node doSearch(State initialState, State goalState, AiAction AiActionObject, boolean isPruning, boolean isDisplayNodes)
	{
				
		//initializations
		AiAction[] AiActionArray=AiActionObject.createActionArray(initialState);
		Node[] tempNodeAr=new Node[AiActionArray.length];		
		totalNumberOfNodes=0;
		Node.resetCountOfNodes();
		Node curNode=new Node(null,initialState,null,0,0);
		QueeLL quee=new QueeLL();

		//The technique of closed list is implemented for pruning , but this does not increase the space complexity
		//as all nodes, any way have to be in memory.				
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
			totalNumberOfNodes=Node.getCountOfNodes();
			return curNode;
		}
		
		//create successors
		tempNodeAr=curNode.createSuccessors(AiActionArray);
				
		//add curNode's state to closedList--already  expanded nodes
		if(isPruning)
			closedList.add(curNode.getCurState());
		
		//add the successors in the quee
		quee.add(tempNodeAr);

		//update total number of nodes generated		
		totalNumberOfNodes=Node.getCountOfNodes();			
		
		try
		{		
			do
			{
				//extract the first in quee
				curNode=(Node) quee.serviceFirst();					
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
		
		//update total number of nodes generated		
		totalNumberOfNodes=Node.getCountOfNodes();		
		return null;
	}	
	
	public int totalNodesGenerated()
	{
		return totalNumberOfNodes;
	}
	
	public int maxNodesStored()
	{
		return totalNumberOfNodes;
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

