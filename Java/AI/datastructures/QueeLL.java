package datastructures;

public class QueeLL
{	
	
	private MyLinkedList ll;
	
	public QueeLL()
	{
		ll= new MyLinkedList();
	}
	
	public QueeLL(Object first)
	{
		if(first!=null)
			ll= new MyLinkedList(first);
		else
			ll=new MyLinkedList();
	}	
	
	public QueeLL(Object[] obArray)
	{
		try
		{
			ll=new MyLinkedList();		
			for(int i=0;i<obArray.length;++i)
				if(obArray[i]!=null)
					ll.addLast(obArray[i]);
		}
		catch(NullPointerException e)
		{
		}		
	}	
	
	
	public void add(Object o)
	{
		if(o!=null)
			ll.addLast(o);
	}
	
	public void add(Object[] obArray)
	{
		try
		{
		for(int i=0;i<obArray.length;++i)
			if(obArray[i]!=null)
				ll.addLast(obArray[i]);
		}
		catch(NullPointerException e)
		{
		}		
	}
	public Object serviceFirst()
	{	
		return ll.removeFirst();		
			
	}
	public Object serviceLast()
	{	
			return ll.removeLast();
			
	}
	
	public Object viewFirst()
	{
		
		return ll.getFirstObject();

	}
	public Object viewLast()
	{
		return ll.getLastObject();
	}	
	

	
	public boolean isEmpty()
	{
		return ll.isEmpty();
	}
	
}