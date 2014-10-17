package ai.search.uninformed;

import ai.elements.*;

public interface UninformedSearch
{
	public Node doSearch(State initialState, State goalState, AiAction[] AiActionArray, boolean isPruning, boolean isDisplayNodes);

	public Node doSearch(State initialState, State goalState, AiAction AiActionObject, boolean isPruning, boolean isDisplayNodes);	
	
	public int totalNodesGenerated();
	
	public int maxNodesStored();

}