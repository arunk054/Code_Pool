import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.UnknownHostException;
import java.util.ArrayList;
import java.util.Iterator;

public class SortingUDPClient extends DatagramSocket {

	private static SortingUDPClient sortingSocket;
	private static DatagramPacket dataFromServer,dataToServer;
	private static int length;
	private static byte data[];
	
	public SortingUDPClient()throws UnknownHostException, IOException {
		super();
	}

	private static boolean getInputAndStore(){
		BufferedReader stdIn=new BufferedReader(new InputStreamReader(System.in));
		String input;
		int index=0;
		char temp;
		ArrayList<Byte> inputList=new ArrayList<Byte>();
		
		length=0;
		System.out.print("Enter the alphabets seperated by space: ");
		try {
			input=stdIn.readLine();
		} catch (IOException e) {
			System.out.println("Invalid Input");
			return false;
		}

		while (index < input.length()) {
			temp = input.charAt(index);
			if (Character.isLetter(temp)) {
				inputList.add(new Byte((byte) temp));
			} else if (temp == ' '){
				--index;
			} else {
				System.out.println("Invalid input");
				return false;				
			}
			
			try {
				if (input.charAt(++index) != ' ') {
					System.out.println("Invalid Input");
					return false;
				}
				while ((temp = input.charAt(++index)) == ' ') {
				}
			} catch (IndexOutOfBoundsException e) {
				break;
			}
		}
		if (length>127){
			System.out.println("Invalid data");
			return false;
		}
		length=inputList.size();
		data=new byte[length];
		index=0;
		for (Iterator<Byte> iterator = inputList.iterator(); iterator.hasNext();) {
			Byte byte1 = (Byte) iterator.next();
			data[index++]=byte1.byteValue();
		}

		return true;
		
	}

	public static void main(String[] args) throws IOException {
		String ip = "192.16.9.54";
		int port = 3222;
		InetAddress ipAddr;
		String s="n";

		System.out.println("Initializing UDP Sorting client program");
		//The user can enter the ip and port of server as cmd line args
		if (args.length > 0) {
			ip = args[0];
			try {
				port = Integer.parseInt(args[1]);
			} catch (Exception e) {
			}
		}

		System.out.println("Data will be sent to UDP sorting server at - "
				+ ip + ":" + port);

		ipAddr=InetAddress.getByName(ip);
		
		sortingSocket = new SortingUDPClient();
		
		do {
			// Get the input from user and store it in bytes
			if (!getInputAndStore() || length == 0) {
				continue;
			}
			try {

				System.out.println("Sending data to server...");
				dataToServer=new DatagramPacket(data, length, ipAddr,port);
				sortingSocket.send(dataToServer);

				System.out.println("Reading bytes from data sent by server");
				dataFromServer=new DatagramPacket(data,length);
				sortingSocket.receive(dataFromServer);
				length=dataFromServer.getLength();

				System.out.println("The server returned "+length+" bytes of data");
				System.out.println("The sorted data returned by server is: ");
				System.out.println();
				for (int i = 0; i < length; i++) {
					System.out.print((char) data[i] + " ");
				}
				System.out.println();
				System.out.println();

			} catch (IOException e) {
				System.out
						.println("Error sending / receiving data to UDP server - "
								+ ip + ":" + port + " - Error: "
								+ e.getMessage());
			}
			System.out.print("Do you want to quit (y/n): ");
			s = new BufferedReader(new InputStreamReader(System.in)).readLine();
		} while (!s.equalsIgnoreCase("y"));
	}

}
