import java.io.*;
import java.net.*;
import java.util.*;

public class Cliente80 {
  public static void main(String[] args) {
    Socket socket = null;
    PrintStream os = null;
    Scanner is = null;
    String host = null;

    try {
      //host = "127.0.0.1";
      host = "www.fc.unesp.br";
      socket = new Socket(host, 80);
      os = new PrintStream(socket.getOutputStream());
      is = new Scanner(socket.getInputStream());
    } catch (UnknownHostException e) {
      System.err.println("Don't know about host.");
      System.exit(0);
    } catch (IOException e) {
      System.err.println("Couldn't get I/O for the connection to host");
      System.exit(0);
    }


    try {
      os.print("GET / HTTP/1.1\nHost: "+host+"\n\n");
      os.flush();

      String inputLine;

      while ((inputLine = is.nextLine()) != null) {
        System.out.println(inputLine);
      }

      os.close();
      is.close();
      socket.close();
    } catch (UnknownHostException e) {
      System.err.println("Trying to connect to unknown host: " + e);
    } catch (IOException e) {
      System.err.println("IOException:  " + e);
    } catch (NoSuchElementException e) {
      System.out.println("Conexacao terminada.");
    }
  }
}
