package ai.elements;

public interface AiAction
{
	public int getStepCost(State curState);
	
	public void display();
	
	public AiAction[] createActionArray();

	public AiAction[] createActionArray(State curState);
}