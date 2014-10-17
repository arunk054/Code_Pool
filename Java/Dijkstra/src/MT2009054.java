import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Iterator;


public class MT2009054 {
	//Graph has 6 nodes, same as the example Das sir's ppt (Talk_6.ppt/13)
	private final int maxNodes=6;
	//Numbers imply -- 0==>A, 1==>B, 2==>C and so on
	Node nodes[];
	private final char names[];
	//These entries are basically the routing table D(v) and p(v) respectively
	private int minCostBetween[][], prevNodeInPath[][];
	
	//If two nodes are not connected then their weight is assumed to be -1 (infinite)
	private final int INFINITY=-1;

	/*
	 * This is the constructor, used to initialize the complete graph
	 * Here we are constructing the graph as given in fig4.4 of kurose & ross
	 */
	public MT2009054() {
		nodes=new Node[maxNodes];
		names=new char[maxNodes];

		minCostBetween=new int[maxNodes][maxNodes];
		prevNodeInPath= new int[maxNodes][maxNodes];

		for (int i = 0; i < nodes.length; i++) {
			//We create each node and assign a character to each
			nodes[i]=new Node(i);
			//Hence 0==>A, 1==>B and so on...
			names[i]=(char)((int)'A'+i);
		}

		//A has 3 adjacent nodes, viz. B, C & D
		nodes[0].addAdjacentNode(new AdjacentNode(nodes[1], 2));
		nodes[0].addAdjacentNode(new AdjacentNode(nodes[2], 5));
		nodes[0].addAdjacentNode(new AdjacentNode(nodes[3], 1));

		//B has 3 adjacent nodes, viz. A, D, C
		nodes[1].addAdjacentNode(new AdjacentNode(nodes[0], 2));
		nodes[1].addAdjacentNode(new AdjacentNode(nodes[2], 3));
		nodes[1].addAdjacentNode(new AdjacentNode(nodes[3], 2));

		//C has 5 adjacent nodes, viz. A, B, D, E, F
		nodes[2].addAdjacentNode(new AdjacentNode(nodes[0], 5));
		nodes[2].addAdjacentNode(new AdjacentNode(nodes[1], 3));
		nodes[2].addAdjacentNode(new AdjacentNode(nodes[3], 3));
		nodes[2].addAdjacentNode(new AdjacentNode(nodes[4], 1));
		nodes[2].addAdjacentNode(new AdjacentNode(nodes[5], 5));

		//D has 4 adjacent nodes, viz. A, B, C, E
		nodes[3].addAdjacentNode(new AdjacentNode(nodes[0], 1));
		nodes[3].addAdjacentNode(new AdjacentNode(nodes[1], 2));
		nodes[3].addAdjacentNode(new AdjacentNode(nodes[2], 3));
		nodes[3].addAdjacentNode(new AdjacentNode(nodes[4], 1));

		//E has 3 adjacent nodes, viz. D, C, F
		nodes[4].addAdjacentNode(new AdjacentNode(nodes[2], 1));
		nodes[4].addAdjacentNode(new AdjacentNode(nodes[3], 1));
		nodes[4].addAdjacentNode(new AdjacentNode(nodes[5], 2));

		//F has 2 adjacent nodes, viz. C, E
		nodes[5].addAdjacentNode(new AdjacentNode(nodes[2], 5));
		nodes[5].addAdjacentNode(new AdjacentNode(nodes[4], 2));
	}

	//A method to return the corresponding node Name based on value
	public String getName(int value){
		try {
			return Character.toString(names[value]);
		} catch (Exception e) {
			return "UNKNOWN";
		}
	}
	
	public int getMaxNodes(){
		return maxNodes;
	}
	
	/*
	 * This is the actual implementation of the Dijkstra's algorithm.
	 * The idea here is to find the minimum cost (D(v)) from the startNode to all nodes
	 * in the graph, this is basically to construct the routing table which is nothing but
	 * populating the values D(v) & p(v) for all nodes w.r.t the startNode.
	 */
	public void runDijkstraForNode(int startNode){
		//just simple error checking
		if (startNode<0 || startNode>=maxNodes) {
			System.out.println("Invalid start node!!");
			return;	
		}

		//maintain a boolean array to know whether a node has been visited or not
		boolean isVisitedNode[]=new boolean[maxNodes];
		
		//Populate isVisitedNode, initially all are false except startNode
		isVisitedNode[startNode]=true;
		for (int i = (startNode+1)%maxNodes; i != startNode; i=(i+1)%maxNodes) {
			isVisitedNode[i]=false;
		}
		
		//Initialize the D(v) for all nodes, basically D(v) = infinite and p(v)=startNode
		for (int i = 0; i < maxNodes; i++) {
			minCostBetween[startNode][i]=INFINITY;
			prevNodeInPath[startNode][i]=startNode;
		}
		//Initialize the D(v) w.r.t startNode, i.e all adj nodes get D(v) = cost between startNode and adj node
		for (Iterator iterator = nodes[startNode].getIterator(); iterator.hasNext();) {
			AdjacentNode adj = (AdjacentNode) iterator.next();
			minCostBetween[startNode][adj.node.getValue()]=adj.weight;
			prevNodeInPath[startNode][adj.node.getValue()]=startNode;
		}

		/*
		 * Now run the loop for (maxNodes - 1) times, so that we compute distance,
		 * from start node to all remaining nodes. 
		 */
		for (int count = 1; count < maxNodes; count++) {

			int minNode=-1,temp;

			//find the unvisited node which has minimum cost.
			//loop through all nodes and find the minimum value.
			for (int i = 0; i < maxNodes; i++) {
				if(isVisitedNode[i])
					continue;
				temp=minCostBetween[startNode][i];
				//if minNode is -1 it implies we haven't even selected one node.
				if (temp != INFINITY && (minNode==-1 || temp < minCostBetween[startNode][minNode])){
					minNode=i;
				}
			}

			//Mark the minNode as visited
			try {
				isVisitedNode[minNode]=true;
			} catch (ArrayIndexOutOfBoundsException e) {
				//Implies all nodes visited except isolated nodes.
				return;
			}

			int newCost=0;
			/*loop thru all unvisited adjacent adjacent to the minNode.
			 * and find the min cost from startNode to those adj nodes.
			 */
			for (Iterator iterator = nodes[minNode].getIterator(); iterator.hasNext();) {
				AdjacentNode adj = (AdjacentNode) iterator.next();
				if (isVisitedNode[adj.node.getValue()])
					continue;
				temp=adj.node.getValue();

				//commented the following because the minCostBetween startNode and minNode cannot be infinite
				//newCost=(minCostBetween[startNode][minNode]!=INFINITY)?adj.weight + minCostBetween[startNode][minNode] :  adj.weight;
				newCost=adj.weight + minCostBetween[startNode][minNode];
				
				//If it is infinity, it implies we are discovering this node for the first time.
				if (minCostBetween[startNode][temp] == INFINITY || newCost < minCostBetween[startNode][temp]) {
					minCostBetween[startNode][temp]=newCost;
					prevNodeInPath[startNode][temp]=minNode;
				}
			}
		}
	}

	public int getMinimumCost(int startNode, int destNode){
		//Just error checking
		if (startNode<0 || startNode>=maxNodes || destNode<0 || destNode>=maxNodes)
			return -2;

		return minCostBetween[startNode][destNode];
	}

	/*This method just returns the optimal path from startNode to destNode using already
	 * constructed routing table, hence before calling we need to call runDijkstraForNode(startNode). 
	 */

	public int displayGoodPath(int startNode, int destNode){
		if (startNode<0 || startNode>=maxNodes || destNode<0 || destNode>=maxNodes)
			return -2;

		if (startNode==destNode) {
			System.out.println("Source and destination nodes are same!!");
		}

		System.out.print(names[startNode]);
		recursivePrevNode(startNode,destNode);
		System.out.println(" ===> "+names[destNode]);
		return 0;
	}

	//This is to just dump the values in the routing table that was already generated Dijkstra's
	public void displayRoutingTable(int startNode){
		for (int i = 0; i < maxNodes; i++) {
			if (i!=startNode){
				char ch=names[i];
				System.out.print("D("+ch+"),p("+ch+") = ");
				System.out.print(minCostBetween[startNode][i]+","+names[prevNodeInPath[startNode][i]]+"; ");
			}
		}
		System.out.println("");
	}

	//This method is used by displayGoodPath to print the path recursively
	private void recursivePrevNode(int startNode, int destNode){
		if (prevNodeInPath[startNode][destNode] == startNode) {
			return;
		}
		recursivePrevNode(startNode, prevNodeInPath[startNode][destNode]);
		System.out.print(" ===> "+names[prevNodeInPath[startNode][destNode]]);		
	}

	public static void main(String[] args) throws IOException {
		System.out.println("Initializing the topology (graph) as given in fig:4.4 of the textbook.");
		MT2009054 ls=new MT2009054();

		System.out.println("Please wait while the routing table w.r.t each node is being computed...");
		//We first construct the routing table for each node.
		for (int j = 0; j < ls.getMaxNodes(); j++) {
			System.out.println("Constructing routing table for node "+ls.getName(j));
			ls.runDijkstraForNode(j);			
		}

		//Then display the routing table
		for (int i = 0; i < ls.getMaxNodes(); i++) {
			System.out.println("");
			System.out.println("Following is the routing table w.r.t Node "+ls.getName(i)+":");
			ls.displayRoutingTable(i);
		}

		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		String input;
		int source=0,dest=0, temp;
		System.out.println();
		
		//Just ask for user to input source and dest node, for as long as he wants.
		do {
			System.out.println();
			System.out.print("Enter the source node (A - "+ls.getName(ls.getMaxNodes()-1)+"): ");
			try {
				input=in.readLine();
				input=input.trim();
			} catch (IOException e) {
				System.out.println("Error reading i/o.");
				return;
			}
			try {
				if (input.length()>1 || input.length()==0){
					throw new Exception();
				}
				source = ((int)input.charAt(0)-(int)'A');
			} catch (Exception e) {
				System.out.println("Invalid Input!!");
				input="y";
				continue;
			}
			System.out.print("Enter the destination node (A - "+ls.getName(ls.getMaxNodes()-1)+"): ");
			try {
				input=in.readLine();
				input=input.trim();
			} catch (IOException e) {
				System.out.println("Error reading i/o.");
				return;
			}
			try {
				if (input.length()>1 || input.length()==0){
					throw new Exception();
				}
				dest = ((int)input.charAt(0)-(int)'A');
			} catch (Exception e) {
				System.out.println("Invalid Input!!");
				input="y";
				continue;
			}
			temp=ls.getMinimumCost(source, dest);
			
			//Special case to handle isolated or unreachable nodes.
			if (temp == ls.INFINITY){
				System.out.println("The node "+ ls.getName(dest)+" is unreachable from node "+ls.getName(source));
				input="y";
				continue;
			}else if (temp < 0){
				System.out.println("Invalid Input!!");
				input="y";
				continue;
			}
			
			System.out.println();
			System.out.println("The minimum cost from "+ls.getName(source)+" to "+ls.getName(dest)+" is "+temp);
			System.out.println("And following is the optimal path between them: ");
			ls.displayGoodPath(source, dest);
			System.out.println();
			System.out.print("Do you want to continue(y/n): ");
			input = in.readLine();
		}while(!"n".equalsIgnoreCase(input));
	}

}

//The class representing a node in the graph
class Node{

	//Adjacency list, to maintain all adjacent nodes
	private ArrayList<AdjacentNode> adjacent = new ArrayList<AdjacentNode>();
	/*This is just a unique integer value associated with a node,
	*typically in case of array of nodes, this is the index of the node in the array
	*/
	private int value;

	Node(int val){
		value=val;
	}
	//The method used to populate the adjacent nodes
	public void addAdjacentNode(AdjacentNode node){
		adjacent.add(node);
	}	
	public int getValue(){
		return value;
	}
	//Iterator used to iterate through the set of adjacent nodes
	public Iterator getIterator(){
		return adjacent.iterator();
	}
}

/*Class representating an adjacent node, We could have as well
*used Node class to represent each adjacent node but this is more simpler
*/
class AdjacentNode {
	//This is the cost between the node to which this node is adjacent
	int weight;
	//The reference to the node this actually belongs to
	Node node;

	public AdjacentNode(Node node, int weight) {
		this.node=node;
		this.weight=weight;
	}
}
