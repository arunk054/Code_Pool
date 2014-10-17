
public class Gen1
{
	private byte value;
	private static final byte maxInBoat;	
	
	public Gen1(byte value)
	{
		maxInBoat=1;		
		this.value=value;
	}
	
	public void getVal()
	{

		System.out.println(value);
	}
	
	public static void main(String args[])
	{
		Gen1 g1=new Gen1((byte)2);
		g1.getVal();
	}
}