package ai.search.heuristic;

import ai.elements.*;

public interface HeuristicSearch
{
	public Node doSearch(HeuristicState initialState, HeuristicState goalState, AiAction[] AiActionArray, boolean isPruning, boolean isDisplayNodes);

	public Node doSearch(HeuristicState initialState, HeuristicState goalState, AiAction AiActionObject, boolean isPruning, boolean isDisplayNodes);	
	
	public int totalNodesGenerated();
	
	public int maxNodesStored();
	
}
