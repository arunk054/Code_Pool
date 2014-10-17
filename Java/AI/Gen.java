import datastructures.*;

public class Gen implements Prioritized
{
	private int value;
	
	public Gen(int value)
	{
		this.value=value;
	}
	
	public Gen()
	{
		this.value=0;
	}	
	public static void main(String args[])
	{
		Gen g=new Gen(0);
		PriorityQuee p1= new PriorityQuee(g);		
		
		p1.add(g);
		for (int i=25000;i>0;--i)
		{
			g=new Gen(i);
			if(i!=21)
			p1.add(g);
		}
		for(int i=0;i<11;++i)
		{
			g=new Gen(i);
			p1.add(g);
		
		}
		
		g=new Gen(22);
		p1.add(g);
		g=new Gen(2);		
		p1.add(g);
		
		Gen gTem=(Gen)p1.serviceFirst();
		while(gTem!=null)
		{
			System.out.println(gTem.getKey());
			gTem= (Gen)p1.serviceFirst();
			
		}
		
	}
	
	public int getKey()
	{
		return value;
	}
}