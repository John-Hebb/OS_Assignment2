/* Assignment 2 - Question 1 - Server
   Authors: John Hebb & Matthew Souter
   Date: Monday, October 8th, 2018
   Description: Echo server program.
*/

import java.net.*;
import java.io.*;

public class EchoServer {
    public static void main(String[] args) throws IOException {
        
        // Set port number
        int portNum = 9999;

        // Open sockets, buffers and streams        
        try (
            ServerSocket serverSocket = new ServerSocket(portNum);
            Socket clientSocket = serverSocket.accept();     
            PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true);                   
            BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
        ) {
            // Read from and write to streams
            String s;
            while ((s = in.readLine()) != null) {
                out.println(s);
            }
        } catch (IOException e) {
            System.out.println("Exception caught when trying to listen on port " + portNum + " or listening for a connection");
            System.out.println(e.getMessage());
        }
    }
}
