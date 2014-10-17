package datastructures;

public class MyLinkedList
{
	private Link first;
	private Link last;
	private Link current;
	
	public MyLinkedList()
	{
		first=null;
		last=null;
		current=null;	
	}
	public MyLinkedList(MyLinkedList mLL)
	{
		first=mLL.getFirstLink();
		last=mLL.getLastLink();
		current=first;
	}
	public MyLinkedList(Object firstObject)
	{
		this.first=new Link(firstObject,null,null);
		this.last=first;
		current=first;
	}		
	
	public void addFirst(Object o)
	{
	
	Link temp=new Link(o,null,first);
	try
	{
		first.setPrevious(temp);
	}
	catch(NullPointerException e)
	{
		last=temp;
		current=temp;
	}
	first=temp;
	}
	
	public Object removeFirst()
	{
		Object tempO=null;
		try
		{
			Link tempNext=first.getNext();
			tempO=first.getCurObject();			
			if(current==first)
				current=tempNext;
			first=tempNext;
			first.setPrevious(null);
		}
		catch(NullPointerException e)
		{
			first=null;
			last=null;
		}
		return tempO;
	}

	public Object removeLast()
	{
		Object tempO=null;
		try
		{
			Link tempPrevious=last.getPrevious();
			tempO=last.getCurObject();			
			if(current==last)
				current=tempPrevious;
			last=tempPrevious;
			last.setNext(null);
		}
		catch(NullPointerException e)
		{
			first=null;
			last=null;
		}
		return tempO;
		
	}	
	
	public void addLast(Object o)
	{
		Link temp=new Link(o,last,null);
		try
		{
			last.setNext(temp);
		}
		catch(NullPointerException e)
		{
			first=temp;
			current=temp;			
		}
		last=temp;
	}
	
	public void insertPrevious(Object o)
	{

		if(current==first)
		{
			addFirst(o);
			return;
		}
		try
		{		
			Link tempPrevious=current.getPrevious();
			Link temp=new Link(o,tempPrevious,current);
			current.setPrevious(temp);
			tempPrevious.setNext(temp);
			
		}
		catch(NullPointerException e)
		{
			System.out.println("fatal Error in insertion");
		}

	}
	
	public void insertNext(Object o)
	{

		if(current==last)
		{
			addLast(o);
			return;
		}
		try
		{		
			Link tempNext=current.getNext();
			Link temp=new Link(o,current,tempNext);
			current.setNext(temp);
			tempNext.setPrevious(temp);
		}
		catch(NullPointerException e)
		{
			System.out.println("fatal Error in insertion");
		}
	}
	
	public Object removeCurrentLink()
	{

		if(current==first)
		{
			return removeFirst();
		}
		else if(current==last)
		{
			return removeLast();
		}
		
		try
		{		
			Link tempNext=current.getNext();
			Link tempPrevious=current.getPrevious();				
			tempNext.setPrevious(tempPrevious);
			tempPrevious.setNext(tempNext);
			return current.getCurObject();
				
		}
		catch(NullPointerException e)
		{
			System.out.println("fatal Error in removal");
			return null;
		}
	}
	
	public Object getNext()
	{	
		try
		{
			Link tempLink=current.getNext();
			current=tempLink;
			return tempLink.getCurObject();
			
		}
		catch(NullPointerException e)
		{
			return null;
		}
			
	}
	
	public Object getPrevious()
	{	
		try
		{
			Link tempLink=current.getPrevious();
			current=tempLink;
			return tempLink.getCurObject();			
		}
		catch(NullPointerException e)
		{
			return null;
		}
	}	
	
	public void resetCurLink(boolean toFirst)
	{
		if(toFirst)
		{
			current=first;
		}
		else
		{
			current=last;
		}
	}
	public Link getFirstLink()
	{
		return first;
	}
	
	public Link getLastLink()
	{
		return last;
	}
	
	public Link getCurLink()
	{
		return current;
	}
	public Object getCurObject()
	{
		try
		{
			return current.getCurObject();
		}
		catch(NullPointerException e)
		{
			return null;
		}
	}	
	public Object getFirstObject()
	{
		try
		{
			return first.getCurObject();
		}
		catch(NullPointerException e)
		{
			return null;
		}
	}	
	public Object getLastObject()
	{
		try
		{
			return last.getCurObject();
		}
		catch(NullPointerException e)
		{
			return null;
		}
	}	

	public boolean isEmpty()
	{
		if (first==null)
			return true;
		else
			return false;
			
	}

private class Link
	{
	
		private Object curObject;
		private	 Link next;
		private Link previous;
	
		public Link(Object curObject,Link previous,Link next)
		{
			this.curObject=curObject;
			this.next=next;
			this.previous=previous;
		}
		public Link(Object curObject,Link previous)
		{
			this.curObject=curObject;
			this.next=null;
			this.previous=previous;
		}
		
		//mutators
		
		public void setNext(Link next)
		{
		this.next=next;
		}
		public void setPrevious(Link previous)
		{
			this.previous=previous;
		}	
		
		//accessors
		
		public Link getNext()
		{
			return next;
		}
		public Link getPrevious()
		{
			return previous;
		}	
		public Object getCurObject()
		{
			return curObject;
		}	
	}
	

}