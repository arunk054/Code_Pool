package ai.elements;

public interface HeuristicState extends State
{
	public int getHeuristicValue(State goalState);
}
