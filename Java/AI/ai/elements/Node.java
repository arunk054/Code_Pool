package ai.elements;

public class Node
{
	private Node parentNode;
	private  int pathCost;
	private State curState;
	private AiAction a;
	private  int depth;
	private static int countOfNodes=0;
	
	public Node(Node passParentNode, State passCurState,   AiAction passA,   int passDepth, int passPathCost)
	{
	
	parentNode=passParentNode;
	pathCost=passPathCost;
	curState=passCurState;
	a=passA;
	depth=passDepth;
	Node.incrementCountOfNodes();
	}
	
	public Node(Node passParentNode, State passCurState,   AiAction passA,   int passDepth)
	{
	
	parentNode=passParentNode;
	pathCost=depth;
	curState=passCurState;
	a=passA;
	depth=passDepth;
	Node.incrementCountOfNodes();	
	}
	
	public Node[] createSuccessors(AiAction passA[])
	{
		Node[] nodeArray = new Node[passA.length];
		
		State sTem;

		for(int i=0;i<passA.length;++i)
		{
			try
			{
				sTem=curState.nextState(passA[i]);		
				nodeArray[i] = new Node(this,sTem,passA[i],depth+1,pathCost+passA[i].getStepCost(curState));
			}			
			catch(InvalidActionException e)
			{
				nodeArray[i]=null;
			}
			
		}				
		return nodeArray;
	
	}
	
	public Node createSuccessor(AiAction passA)
	{
		Node nodeTem;
		State sTem;
		try
		{
			sTem=curState.nextState(passA);
				nodeTem = new Node(this,sTem,passA,depth+1,pathCost+passA.getStepCost(curState));		
		}
		catch(InvalidActionException e)
		{
			nodeTem=null;
		}

		
		return nodeTem;
	}
	
	public boolean goalTest(State goalState)
	{
		return curState.goalTest(goalState);
	}
	public Node getParentNode()
	{
		return parentNode;
	}
	
	public State getCurState()
	{
		return curState;
	}
	
	public AiAction getCurAiAction()
	{
		return a;
	}
	public int getPathCost()
	{
		return pathCost;
	}
	
	public int getDepth()
	{
		return depth;	
	}
	public static void resetCountOfNodes()
	{
		countOfNodes=0;
	}
	public static void incrementCountOfNodes()
	{
		countOfNodes++;
	}
	public static int getCountOfNodes()
	{
		return countOfNodes;
	}
	public boolean equals(Node anotherNode)
	{
		State s=anotherNode.getCurState();
		
		return curState.equals(s);
	}
	public void display()
	{
		System.out.println("");	
		System.out.println("{");
		System.out.println("");		
		System.out.print("Its State: ");
		curState.display();
		try
		{
			System.out.print("Action: ");
			a.display();
		}
		catch(NullPointerException e)
		{
			System.out.println("NULL");
		}
		try
		{
			System.out.print("Parent node's State: ");	
			State s= parentNode.getCurState();
			s.display();
		}
		catch(NullPointerException e)
		{
			System.out.println("NULL");
		}
		
		System.out.println("Depth = "+depth);
		System.out.println("Pathcost = "+pathCost);
		System.out.println("");		
		System.out.println("}");
		
		
	}
}