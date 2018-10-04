/* OS Design & UNIX Programming Assignment 2 - Question 1 - Client
   Authors: John Hebb & Matthew Souter
   Date: Monday, October 8th, 2018
   Description: Echo client program.
*/
import java.io.*;
import java.net.*;

public class EchoClient {
    public static void main(String[] args) throws IOException {
        
        // Error if too many or too few arguments
        if (args.length != 1) {
            System.err.println(
                "Usage: EchoClient <host name>");
            System.exit(1);
        }

        // Initialize host and port
        String hostName = args[0];
        int portNum = 9999;

        // Open sockets, buffers, and streams
        try (
            Socket echoSocket = new Socket(hostName, portNum);
            PrintWriter out = new PrintWriter(echoSocket.getOutputStream(), true);
            BufferedReader in = new BufferedReader(new InputStreamReader(echoSocket.getInputStream()));
            BufferedReader stdIn = new BufferedReader(new InputStreamReader(System.in))
        ) {
            // Output the input to the server and grab echo and print to console
            String input;
            while ((input = stdIn.readLine()) != null) {
                if (input.equals(".")){
                    System.exit(1);
                } else {
                    out.println(input);
                    System.out.println("Server: " + in.readLine());
                }
            }
        } catch (UnknownHostException e) {
            System.err.println("Unknown host: " + hostName);
            System.exit(1);
        } catch (IOException e) {
            System.err.println("I/O for host " + hostName);
            System.exit(1);
        } 
    }
}