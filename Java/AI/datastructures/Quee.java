package datastructures;


import java.util.Vector;

public class Quee
{	
	
	private Vector al;
	
	public Quee()
	{
		al= new Vector();
	}
	
	public Quee(Object first)
	{
		al= new Vector();
		if(first!=null)
			al.add(first);
	}	
	public Quee(int initialCapacity,int capacityIncrement)
	{
		al= new Vector(initialCapacity,capacityIncrement);
	}
	public Quee(int initialCapacity)
	{
		al= new Vector(initialCapacity);
	}	
	public Quee(Object[] obArray)
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
	
	
	public void add(Object o)
	{
		if(o!=null)
			al.add(o);
	}
	public void add(Object[] obArray)
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
	public Object serviceFirst()
	{	
		try
		{
			return al.remove(0);		
		}
		catch(IndexOutOfBoundsException e)
		{
			return null;		
		}
			
	}
	public Object serviceLast()
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
	
	public Object viewFirst()
	{
		try
		{
			return al.get(0);		
		}
		catch(IndexOutOfBoundsException e)
		{
			return null;		
		}
	}
	public Object viewLast()
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