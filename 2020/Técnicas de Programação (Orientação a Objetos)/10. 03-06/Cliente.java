import java.io.*;
import java.net.*;
import java.util.*;

public class Cliente implements Runnable {
  static PrintStream os = null;
  static boolean paraThread = false;

  public static void main(String[] args) {
    Socket socket = null;
    Scanner is = null;
    Thread t = new Thread(new Cliente());

    try {
      socket = new Socket("127.0.0.1", 80);
      os = new PrintStream(socket.getOutputStream(), true);
      is = new Scanner(socket.getInputStream());
    } catch (UnknownHostException e) {
      System.err.println("Don't know about host.");
    } catch (IOException e) {
      System.err.println("Couldn't get I/O for the connection to host");
    }

    t.start();

    try {
      String inputLine;

      do {
        System.out.println(inputLine=is.nextLine());
      } while (!inputLine.equals (""));

      paraThread = true;
      os.close();
      is.close();
      socket.close();
    } catch (UnknownHostException e) {
      System.err.println("Trying to connect to unknown host: " + e);
    } catch (IOException e) {
      System.err.println("IOException:  " + e);
    }
  }

  public void run() {
    Scanner tecl = new Scanner(System.in);
    do {
      System.out.print("Digite um texto: ");
      os.println(tecl.nextLine());
    } while (!paraThread);
  }
}

