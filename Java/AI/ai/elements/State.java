package ai.elements;

public interface State
{
	public boolean goalTest(State goalState);
	
	public State nextState(AiAction a) throws InvalidActionException;
	
	public void display();
	
	public boolean equals(State anotherState);

}
