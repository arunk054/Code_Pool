import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Arrays;


public class SortingTCPServer extends ServerSocket{
	
	//We extend the ServerSocket class and override the constructor
	public SortingTCPServer(int port) throws IOException {
		super(port);
	}

	public static void main(String[] args) {
		SortingTCPServer sortingServer;
		int port=2111, clientsConnected=0;
		int MAX_CONNECTIONS=5;

		//The default port is 2111, but user can change it by passing via cmd line arg
		if (args.length>0){
			try {
				port=Integer.parseInt(args[0]);
			} catch (NumberFormatException e) {
			}
		}
		
		try {
			sortingServer = new SortingTCPServer(port);
		} catch (IOException e) {
			System.out.println("ERROR: Unable to create socket at port "+port+" - "+e.getMessage());
			return;
		}
		System.out.println("Initializing Sorting server program");
		System.out.println("Server listening on port: "+port);
		
		try {
			//We are implementing a way to accept multiple connections(default max is 5)
			while(clientsConnected<MAX_CONNECTIONS){
				//To do so create a thread and service the client in a separate thread
				new ServerThread(sortingServer.accept()).start();
				clientsConnected++;
			}
		} catch (Exception e) {
			System.out.println("Error accepting connections on port "+port);
			return;
		}
		
	}
	
}
class ServerThread extends Thread {
	
	private Socket clientSocket;
	private BufferedInputStream dataFromClient;
	private BufferedOutputStream dataToClient;
	private int sortingDataType;
	private int length;
	private byte input[];
	private String id;
	private final int CHAR_TYPE=1,INT_TYPE=2,SLEEP_TIME=100,INACTIVITY_TIMEOUT=60000;
	
	public ServerThread(Socket clientSocket) {
		this.clientSocket=clientSocket;
	}
	//The actual sort logic
	private void sortCharacters(byte b[]){
		Arrays.sort(b);
	}
	//This method is to close all the streams, as of now it is not called anywhere 
	private void cleanUp(){
		try {
			dataFromClient.close();
			dataToClient.close();
		} catch (IOException e) {
		}
		try {
			clientSocket.close();
		} catch (IOException e) {

		}
	}
	
	public void run (){
		int count;
		id=clientSocket.getInetAddress().toString();
		id=id+":"+clientSocket.getPort();
		System.out.println("Got a connection from client at "+id);
		
		try {
			dataFromClient=new BufferedInputStream(clientSocket.getInputStream());
			dataToClient=new BufferedOutputStream(clientSocket.getOutputStream());
		} catch (IOException e) {
			System.out.println("ERROR "+e);
			return;
		}

		//In this protocol - first byte contains the kind of input eg: 1=char, 2=int
		//The second byte contains the size of the input 
		//Followed by data
		do {
			try {

				//Wait till the input has arrived
				while ((sortingDataType = dataFromClient.read()) == -1) {
					shortSleep();
				}

				System.out.println(id + ": Sorting data type is "
						+ getTypeString(sortingDataType));
				//The second byte contains the size of the input 
				while ((length = dataFromClient.read()) == -1) {
					//we go to a short sleep to avoid a single thread consuming all cpu
					shortSleep();
				}

				System.out.println(id+ ": The number of characters to be sorted - "+ length);

				//The rest of the input contains the actual data
				System.out.println("Reading the data got from client " + id);
				input = new byte[length];
				count = 0;
				while (count < length) {
					while ((input[count] = (byte) dataFromClient.read()) == -1) {
						System.out
								.println("got inp frm client " + input[count]);
						shortSleep();
					}
					count++;
				}

				System.out.println(id + ": Sorting the input data");
				sortCharacters(input);

				System.out.println(id+ ": Sending the sorted data back to client");
				dataToClient.write(input);
				//need to call flush to send the data from buffer to network
				dataToClient.flush();
				shortSleep();

			} catch (IOException e) {
				System.out.println("IO Exception " + e.getMessage());
				e.printStackTrace();
			}
		} while (true);
		
	}
	
	private void shortSleep(){
		try {
			Thread.sleep(SLEEP_TIME);
		} catch (InterruptedException e) {
		}
	}
	
	/*This method will return the sorting type, but at present the implementation will work
	*only for characters.*/
	private String getTypeString(int type){
		switch(type){
			case CHAR_TYPE:
				return "Character";
			case INT_TYPE:
				return "Integer";
			default:
					return "UNKNOWN";
		}
	}
}
