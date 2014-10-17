import java.util.ArrayList;
import java.util.Iterator;


public class AL_2009054 {

	public double sortList(ArrayList<Double> randnum){
		//implementation of a heap sort

		int i,start, toSwap, root, size ;
		int left, right;
		Double temp;
		
		size=randnum.size();

		//CREATE THE HEAP, INPLACE
		if (size < 2)
			return 0;

		long l1 = System.currentTimeMillis();
		//using shift operators to multiply
		start = (size-2) >> 1;

		for (i=start; i >= 0 ; --i) {
			root=i;

			do {
				left = (root<<1) + 1;

				if (left < size) {
					if ((right = left + 1) < size){
						toSwap = (randnum.get(left)>randnum.get(right))?left:right;
					} else {
						toSwap = left;
					}
					if (randnum.get(root) < randnum.get(toSwap)) {
						temp=randnum.get(root);
						randnum.set(root,randnum.get(toSwap));
						randnum.set(toSwap,temp);
					}
				} else  {
					break;
				}
				//new root is its child with which it was swapped
				root = toSwap;
			}while (root <= start);
		}

		//Now we have constructed the heap, its time to sort

		do {
			size--;
			temp=randnum.get(0);
			randnum.set(0,randnum.get(size));
			randnum.set(size,temp);

			if (size<2)
				return ((double)(System.currentTimeMillis()-l1)/1000);
			start = (size-2) >> 1;
			root=0;
			do {
				left = (root<<1) + 1;
				if (left < size) {
					if ((right = left + 1) < size){
						toSwap = (randnum.get(left)>randnum.get(right))?left:right;
					} else {
						toSwap = left;
					}
					if (randnum.get(root) < randnum.get(toSwap)) {
						temp=randnum.get(root);
						randnum.set(root, randnum.get(toSwap));
						randnum.set(toSwap,temp);
					}
				} else  {
					break;
				}
				//new root is its child with which it was swapped
				root = toSwap;
			}while (root <= start);
		}while (true);
	}
	
	/*public static void main(String[] args) {
		AL_2009054 a = new AL_2009054();
		ArrayList ab = new ArrayList();
		ab.add(new Double(12.3452));
		ab.add(new Double(13.3452));
		ab.add(new Double(21.3452));
		ab.add(new Double(19.3452));
		ab.add(new Double(17.3452));
		ab.add(new Double(22.3452));
		ab.add(new Double(3.342252));
		ab.add(new Double(12.34521));
		ab.add(new Double(0.3452));
		ab.add(new Double(1.3452));
		ab.add(new Double(34.3452));
		ab.add(new Double(1234.3452));
		ab.add(new Double(11.3452));
		ab.add(new Double(0.34521));
		ab.add(new Double(12.3452));
		ab.add(new Double(13.3452));
		ab.add(new Double(21.3452));
		ab.add(new Double(19.3452));
		ab.add(new Double(17.3452));
		ab.add(new Double(22.3452));
		ab.add(new Double(3.342252));
		ab.add(new Double(12.34521));
		ab.add(new Double(0.3452));
		ab.add(new Double(1234.3452));
		ab.add(new Double(11.3452));
		ab.add(new Double(0.34521));
		ab.add(new Double(12.3452));
		ab.add(new Double(13.3452));
		ab.add(new Double(21.3452));
		ab.add(new Double(19.3452));
		ab.add(new Double(17.3452));
		ab.add(new Double(22.3452));
		ab.add(new Double(3.342252));
		ab.add(new Double(12.34521));
		ab.add(new Double(0.3452));
		ab.add(new Double(1.3452));
		ab.add(new Double(34.3452));
		ab.add(new Double(1234.3452));
		ab.add(new Double(11.3452));
		ab.add(new Double(0.34521));
		ab.add(new Double(12.3452));
		ab.add(new Double(13.3452));
		ab.add(new Double(21.3452));
		ab.add(new Double(19.3452));
		ab.add(new Double(17.3452));
		ab.add(new Double(22.3452));
		ab.add(new Double(3.342252));
		ab.add(new Double(12.34521));
		ab.add(new Double(0.3452));
		ab.add(new Double(1.3452));
		ab.add(new Double(34.3452));
		ab.add(new Double(1234.3452));
		ab.add(new Double(11.3452));
		ab.add(new Double(0.34521));
		ab.add(new Double(12.3452));
		ab.add(new Double(13.3452));
		ab.add(new Double(21.3452));
		ab.add(new Double(19.3452));
		ab.add(new Double(17.3452));
		ab.add(new Double(22.3452));
		ab.add(new Double(3.342252));
		ab.add(new Double(12.34521));
		ab.add(new Double(0.3452));
		ab.add(new Double(1.3452));
		ab.add(new Double(34.3452));
		ab.add(new Double(1234.3452));
		ab.add(new Double(11.3452));
		ab.add(new Double(0.34521));
		ab.add(new Double(12.3452));
		ab.add(new Double(13.3452));
		ab.add(new Double(21.3452));
		ab.add(new Double(19.3452));
		ab.add(new Double(17.3452));
		ab.add(new Double(22.3452));
		ab.add(new Double(3.342252));
		ab.add(new Double(12.34521));
		ab.add(new Double(0.3452));
		ab.add(new Double(1.3452));
		ab.add(new Double(34.3452));
		ab.add(new Double(1234.3452));
		ab.add(new Double(11.3452));
		ab.add(new Double(0.34521));
		ab.add(new Double(12.3452));
		ab.add(new Double(13.3452));
		ab.add(new Double(21.3452));
		ab.add(new Double(19.3452));
		ab.add(new Double(17.3452));
		ab.add(new Double(22.3452));
		ab.add(new Double(3.342252));
		ab.add(new Double(12.34521));
		ab.add(new Double(17.3452));
		ab.add(new Double(22.3452));
		ab.add(new Double(3.342252));
		ab.add(new Double(12.34521));
		ab.add(new Double(0.3452));
		ab.add(new Double(1.3452));
		ab.add(new Double(34.3452));
		ab.add(new Double(1234.3452));
		ab.add(new Double(11.3452));
		ab.add(new Double(22.3452));
		ab.add(new Double(3.342252));
		ab.add(new Double(12.34521));
		ab.add(new Double(0.3452));
		ab.add(new Double(1.3452));
		ab.add(new Double(34.3452));
		ab.add(new Double(1234.3452));
		ab.add(new Double(11.3452));
		ab.add(new Double(0.34521));
		ab.add(new Double(12.3452));
		ab.add(new Double(13.3452));
		ab.add(new Double(21.3452));
		ab.add(new Double(22.3452));
		ab.add(new Double(3.342252));
		ab.add(new Double(12.34521));
		ab.add(new Double(0.3452));
		ab.add(new Double(1.3452));
		ab.add(new Double(34.3452));
		ab.add(new Double(1234.3452));
		ab.add(new Double(11.3452));
		ab.add(new Double(0.34521));
		ab.add(new Double(12.3452));
		ab.add(new Double(13.3452));
		ab.add(new Double(21.3452));
		ab.add(new Double(19.3452));
		ab.add(new Double(17.3452));
		ab.add(new Double(22.3452));
		ab.add(new Double(3.342252));
		ab.add(new Double(12.34521));
		ab.add(new Double(0.3452));
		ab.add(new Double(1.3452));
		ab.add(new Double(34.3452));
		ab.add(new Double(1234.3452));
		ab.add(new Double(11.3452));
		ab.add(new Double(0.34521));
		ab.add(new Double(12.3452));
		ab.add(new Double(13.3452));
		ab.add(new Double(21.3452));
		ab.add(new Double(19.3452));
		ab.add(new Double(17.3452));
		ab.add(new Double(22.3452));
		ab.add(new Double(3.342252));
		ab.add(new Double(12.34521));
		ab.add(new Double(0.3452));
		ab.add(new Double(1.3452));
		ab.add(new Double(34.3452));
		ab.add(new Double(1234.3452));
		ab.add(new Double(11.3452));
		ab.add(new Double(0.34521));
		System.out.println(a.sortList(ab));
		System.out.println("List");
		for (Iterator iterator = ab.iterator(); iterator.hasNext();) {
			Double object = (Double) iterator.next();
			System.out.println(object);
			
		}
	}*/
	
}
