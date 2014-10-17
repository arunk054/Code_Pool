package datastructures;

import java.lang.*;
import java.util.Vector;

public class Stack
{
	private Vector  al;
	
	public Stack()
	{
		al=new Vector();

	}
	public Stack(Object first)
	{
		al= new Vector();
		if(first!=null)
			al.add(first);
	}
	public Stack(int initialCapacity,int capacityIncrement)
	{
		al= new Vector(initialCapacity,capacityIncrement);
	}
	public Stack(int initialCapacity)
	{
		al= new Vector(initialCapacity);
	}	
	public Stack(Object[] obArray)
	{
		try
		{
		al=new Vector(obArray.length*2);
		for(int i=0;i<obArray.length;++i)
			if(obArray[i]!=null)
				al.add(obArray[i]);
		}
		catch(NullPointerException e)
		{
		}
	}		
	
	public void push(Object o)
	{
		if(o!=null)
			al.add(o);
	}
	
	public void push(Object[] obArray)
	{
		try
		{		
		for(int i=0;i<obArray.length;++i)
			if(obArray[i]!=null)
				al.add(obArray[i]);
		}
		catch(NullPointerException e)
		{
		}		
	}
	
	public Object pop()
	{
		try
		{
			return al.remove(al.size()-1);		
		}
		catch(IndexOutOfBoundsException e)
		{
			return null;
		}
			
	}
	public Object top()
	{
		try
		{
			return al.get(al.size()-1);		
		}
		catch(IndexOutOfBoundsException e)
		{
			return null;		
		}
		
	}
	
	public int length()
	{
		return al.size();
	}
	
	public Object[] toArray(Object[] tempO)
	{
		return al.toArray(tempO);
	
	}
	
	public boolean isEmpty()
	{
		return al.isEmpty();
	}
	
}