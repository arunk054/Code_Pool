package datastructures;

public class PriorityQueeLL
{
	private MyLinkedList ll;
	
	public PriorityQueeLL()
	{
		ll= new MyLinkedList();
	}
	
	public PriorityQueeLL(Prioritized first)
	{
		if(first!=null)
			ll= new MyLinkedList(first);
		else
			ll= new MyLinkedList();
	
	}	
	
	public PriorityQueeLL(Prioritized[] obArray)
	{
		try
		{
			ll=new MyLinkedList();
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
			if(ll.isEmpty())
			{
				ll.addLast(o);
				return;
			}
		
			int key= o.getKey();
			MyLinkedList llTemp=new MyLinkedList(ll);
			ll.resetCurLink(true);
			llTemp.resetCurLink(false);
			
			do
			{
				Prioritized pTem=(Prioritized)llTemp.getCurObject();
				if (key>=pTem.getKey())
				{
					ll=llTemp;
					ll.insertNext(o);
					return;
				}
				pTem=(Prioritized)ll.getCurObject();
				if(key<pTem.getKey())
				{
					ll.insertPrevious(o);
					return;
				}
			}while(ll.getNext()!=null && llTemp.getPrevious()!=null);
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