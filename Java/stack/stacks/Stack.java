package stacks;

import java.lang.*;
import java.util.ArrayList;

public class Stack
{
	private ArrayList  contents;
	private Character c1;
	
	public Stack()
	{
		contents=new ArrayList();

	}
	public char top()
	{
		c1=(Character) contents.get(0);
		return c1.charValue();
	}
	
	public void push(char c)
	{
		c1=new Character(c);
		contents.add(0,c1);
	}
	
	public char pop()
	{
		c1= (Character) contents.get(0);
		contents.remove(0);
		return c1.charValue();
	}
	
	public int getSize()
	{
		return contents.size();
	}
}