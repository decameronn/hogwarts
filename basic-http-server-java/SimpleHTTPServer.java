import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Date;

public class SimpleHTTPServer {

	public static void main(String[] args) throws IOException {

		ServerSocket server = new ServerSocket(8080);
		System.out.println("Listening for connections on port 8080 ...");

		while (true) {

			Socket clientSocket = server.accept();
			InputStreamReader isr = new InputStreamReader(clientSocket.getInputStream());
			BufferedReader reader = new BufferedReader(isr);
			String line = reader.readLine();
			while (!line.isEmpty()) {
				System.out.println(line);
				line = reader.readLine();
			}

			try (Socket socket = server.accept()) {
				Date today = new Date();
				String httpResponse = "HTTP/1.1 200 OK\r\n\r\n" + today;
				socket.getOutputStream().write(httpResponse.getBytes("UTF-8"));
			} 
			finally {
				server.close();
			}

			// 1. read http request from the client socket
			// 2. prepare http response
			// 3. send http response to client
			// 4. close the socket
		}
	}
}
