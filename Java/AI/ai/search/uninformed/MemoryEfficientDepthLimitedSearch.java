package ai.search.uninformed;

import ai.elements.*;
import datastructures.Stack;
import java.io.*;
import java.util.Vector;

// This is called memory efficient because it does not maintain a closed list for pruning, but checks
// the path to the root from the current node 
public class MemoryEfficientDepthLimitedSearch implements UninformedSearch 
{
	
	private int totalNumberOfNodes;
	private int stateSpaceEstimate;
	private int depthLimit;

	
	public MemoryEfficientDepthLimitedSearch()
	{
		totalNumberOfNodes=0;
		stateSpaceEstimate=1000;
		depthLimit=10;
	}
	public MemoryEfficientDepthLimitedSearch(int passDepthLimit)
	{
		totalNumberOfNodes=0;
		depthLimit=passDepthLimit;
		stateSpaceEstimate=1000;
	}	
	public MemoryEfficientDepthLimitedSearch(int passDepthLimit, int passStateSpaceEstimate)
	{
		totalNumberOfNodes=0;
		depthLimit=passDepthLimit;
		stateSpaceEstimate=passStateSpaceEstimate;
	}
	public Node doSearch(State initialState, State goalState, AiAction[] AiActionArray, boolean isPruning, boolean isDisplayNodes)
	{
	
		//initializations
		Node[] tempNodeAr=new Node[AiActionArray.length];		
		totalNumberOfNodes=0;
		Node.resetCountOfNodes();
		Node curNode=new Node(null,initialState,null,0,0);
		Stack stack=new Stack(stateSpaceEstimate,stateSpaceEstimate/2);
			
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
		if(curNode.getDepth()<depthLimit)
		{
			tempNodeAr=curNode.createSuccessors(AiActionArray);
			//add the successors in the stack
			stack.push(tempNodeAr);
		}

		
		try
		{		
			do
			{
				//extract the top in stack
				curNode=(Node) stack.pop();					
				//prune if repeated state			
			}while(isPruning &&  isAlreadyExpanded(curNode));
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
		Stack stack=new Stack(stateSpaceEstimate,stateSpaceEstimate/2);
			
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
		if(curNode.getDepth()<depthLimit)
		{
			tempNodeAr=curNode.createSuccessors(AiActionArray);
			//add the successors in the stack
			stack.push(tempNodeAr);
		}	
				

		//update total number of nodes generated
		totalNumberOfNodes=Node.getCountOfNodes();

		
		try
		{		
			do
			{
				//extract the top in stack
				curNode=(Node) stack.pop();					
				//prune if repeated state			
			}while(isPruning &&  isAlreadyExpanded(curNode));

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
	
	private boolean isAlreadyExpanded(Node n)
	{
		State s= n.getCurState();
		Node parentNode = n.getParentNode();
		
		while(parentNode!=null)
		{
			if(s.equals(parentNode.getCurState()))
				return true;
			
			parentNode=parentNode.getParentNode();
		}
		
		return false;
		
	}
	
	public int getDepthLimit()
	{
		return depthLimit;
	}
	public void setDepthLimit(int value)
	{
		depthLimit=value;
	}	
}

