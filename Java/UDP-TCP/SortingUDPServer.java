import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Arrays;


public class SortingUDPServer extends DatagramSocket{

	private int port;
	private ServerSocket serverSocket;
	
	

	public SortingUDPServer(int port) throws IOException {
		super(port);
		this.port=port;
	}

	public static void main(String[] args) {
		SortingUDPServer sortingServer;
		int port=3222;
		TransferPackets udpTransfer;
		
		//The default port is 3222, but user can change it by passing via cmd line arg
		if (args.length>0){
			try {
				port=Integer.parseInt(args[0]);
			} catch (NumberFormatException e) {
			}
		}
		
		try {
			sortingServer = new SortingUDPServer(port);
		} catch (IOException e) {
			System.out.println("ERROR: Unable to create socket at port "+port+" - "+e.getMessage());
			return;
		}
		System.out.println("Initializing UDP Sorting server program");
		System.out.println("UDP Server listening on port: "+port);
		
		//A custom class which takes care of all transfers
		udpTransfer = new TransferPackets(sortingServer);
		udpTransfer.run();
	}
	
}
class TransferPackets {
	private static final int MAX_BUFFER=100;
	private DatagramSocket serverSocket;
	private int length;
	private byte[] data;
	private DatagramPacket dataFromClient,dataToClient;
	private InetAddress clientIpAddr;
	int clientPort;
	
	public TransferPackets(DatagramSocket serverSocket) {
		this.serverSocket=serverSocket;
		data=new byte[MAX_BUFFER];
	}
	
	private void sortCharacters(byte b[], int length){
		Arrays.sort(b,0,length);
	}
	
	public void run (){

		System.out.println("Getting ready to read data.");
		
		do {
			try {
				dataFromClient=new DatagramPacket(data, data.length);
				serverSocket.receive(dataFromClient);
				//Received no data from client hence we continue the loop
				if ((length=dataFromClient.getLength())==0)
					continue;
				clientIpAddr = dataFromClient.getAddress();
				clientPort=dataFromClient.getPort();
				System.out.println("Got "+length+" bytes of data from client - "+clientIpAddr.getHostAddress()+":"+clientPort);
				sortCharacters(data,length);
				
				System.out.println("Sending the sorted data back to client.");

				dataToClient = new DatagramPacket(data,length,clientIpAddr,clientPort);

				serverSocket.send(dataToClient);

			} catch (IOException e) {
				System.out.println("Error: IO Exception " + e.getMessage());
				e.printStackTrace();
				
			}
		} while (true);
		
	}
}
