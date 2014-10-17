package datastructures;

import java.util.Vector;

public class PriorityQuee
{
	private Vector al;
	
	public PriorityQuee()
	{
		al= new Vector();
	}
	
	public PriorityQuee(Prioritized first)
	{
		al= new Vector();
		if(first!=null)
			al.add(first);
	}	
	
	public PriorityQuee(int initialCapacity,int capacityIncrement)
	{
		al= new Vector(initialCapacity,capacityIncrement);
	}
	
	public PriorityQuee(int initialCapacity)
	{
		al= new Vector(initialCapacity);
	}	
	
	public PriorityQuee(Prioritized[] obArray)
	{
		try
		{
		al=new Vector(obArray.length*2);
		for(int i=0;i<obArray.length;++i)
			this.add(obArray[i]);
		}
		catch(NullPointerException e)
		{
		}		
	}

	public void add(Prioritized[] obArray)
	{
		try
		{
		for(int i=0;i<obArray.length;++i)
			this.add(obArray[i]);
		
		}
		catch(NullPointerException e)
		{
		}		
	}
	
	
	public void add(Prioritized o)
	{
		if(o!=null)
		{
			if(al.size()==0)
			{
				al.add(o);
				return;
			}
		
			int key= o.getKey();
			int j=al.size()-1,i;
			for(i=0;i<al.size();++i)
			{
				Prioritized pTem=(Prioritized)al.get(j);
				if (key>=pTem.getKey())
				{
					al.add(j+1,o);
					return;
				}
				pTem=(Prioritized)al.get(i);
				if(key<pTem.getKey())
				{
					al.add(i,o);	
					return;
				}
				--j;				
			}

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