import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.ArrayList;
import java.util.Date;
import java.util.Iterator;

public class SortingTCPClient extends Socket {

	private int port;
	private String serverAddress;
	private final static int SLEEP_TIME = 100;
	private static SortingTCPClient sortingSocket;
	private static BufferedOutputStream dataToServer;
	private static BufferedInputStream dataFromServer;
	private static int length;
	private static byte data[];
	
	public SortingTCPClient(String ip, int port) throws UnknownHostException,
			IOException {
		super(ip, port);
		this.serverAddress = ip;
		this.port = port;
	}

	private static void shortSleep() {
		try {
			Thread.sleep(SLEEP_TIME);
		} catch (InterruptedException e) {
		}
	}

	//A utility method to close the streams
	private static void cleanUp() {
		try {
			dataFromServer.close();
			dataToServer.close();
			sortingSocket.close();
		} catch (IOException e) {
		}
	}

	private static boolean getInputAndStore(){
		BufferedReader stdIn=new BufferedReader(new InputStreamReader(System.in));
		String input;
		int index=0;
		char temp;
		char delim=' ';
		//Create this list to dynamically allocate the buffer size
		ArrayList<Byte> inputList=new ArrayList<Byte>();
		
		length=0;
		System.out.print("Enter the alphabets seperated by space: ");
		try {
			//The delimiter is space here, read the input as a single string
			input=stdIn.readLine();
		} catch (IOException e) {
			System.out.println("Invalid Input");
			return false;
		}

		//Traverse through each character and store it in a byte array
		while (index < input.length()) {
			temp = input.charAt(index);
			if (Character.isLetter(temp)) {
				inputList.add(new Byte((byte) temp));
			} else if (temp == delim){
				--index;
			} else {//Implies some other character other than [a-z][A-Z]
				System.out.println("Invalid input");
				return false;				
			}
			
			try {
				//if the user has give some other delim or characters w/o space
				if (input.charAt(++index) != delim) {
					System.out.println("Invalid Input");
					return false;
				}
				while ((temp = input.charAt(++index)) == delim) {
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
		//Iterate the list and store it in a byte array
		for (Iterator<Byte> iterator = inputList.iterator(); iterator.hasNext();) {
			Byte byte1 = (Byte) iterator.next();
			data[index++]=byte1.byteValue();
		}

		return true;
		
	}

	public static void main(String[] args) throws IOException {
		String ip = "192.16.9.54";
		int port = 2111, count;
		String s="n";

		//The user can enter the ip and port of server as cmd line args
		System.out.println("Initializing Sorting client program");
		if (args.length > 0) {
			ip = args[0];
			try {
				port = Integer.parseInt(args[1]);
			} catch (Exception e) {
			}
		}

		System.out.println("Establishing connection with sorting server at - "
				+ ip + ":" + port);

		try {
			sortingSocket = new SortingTCPClient(ip, port);
		} catch (Exception e) {
			System.out.println("Unable to connect to server - " + ip + ":"
					+ port + " - Error: " + e.getMessage());
			e.printStackTrace();
			return;
		}
		System.out.println("Successfully established connection.");

		dataToServer = new BufferedOutputStream(sortingSocket
				.getOutputStream());
		dataFromServer = new BufferedInputStream(sortingSocket
				.getInputStream());
		
		do {
			// Get the input from user and store it in bytes
			if (!getInputAndStore() || length == 0) {
				continue;
			}
			try {

				System.out.println("Sending data to server...");
				byte temp[] = new byte[1];
				//1 implies sorting characters, as per the protocol
				temp[0] = 1;
				dataToServer.write(temp);
				dataToServer.flush();
				//then send the number of bytes to be sorted
				temp[0] = (byte) length;
				dataToServer.write(temp);
				dataToServer.flush();
				dataToServer.write(data);
				dataToServer.flush();

				count = 0;
				while (count < length) {
					while ((data[count] = (byte) dataFromServer.read()) == -1) {
						//Wait for sometime before reading from the stream again
						shortSleep();
					}
					count++;
				}

				System.out.println("The sorted data returned by server is: ");
				System.out.println();
				for (int i = 0; i < data.length; i++) {
					System.out.print((char) data[i] + " ");
				}
				System.out.println();
				System.out.println();

			} catch (IOException e) {
				System.out
						.println("Error sending / receiving data to server - "
								+ ip + ":" + port + " - Error: "
								+ e.getMessage());
			}
			System.out.print("Do you want to quit (y/n): ");
			s = new BufferedReader(new InputStreamReader(System.in)).readLine();
		} while (!s.equalsIgnoreCase("y"));
		cleanUp();
	}

}
