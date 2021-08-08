import java.net.*;
import java.io.*;
import java.util.*;

class Servidor80 {
  public static void main(String[] args) {
    ServerSocket serverSocket = null;

    try {
      serverSocket = new ServerSocket(80);
    } catch (IOException e) {
      System.out.println("Could not listen on port: " + 80 + ", " + e);
      System.exit(1);
    }

    Socket clientSocket = null;
    try {
      clientSocket = serverSocket.accept();
    } catch (IOException e) {
      System.out.println("Accept failed: " + 80 + ", " + e);
      System.exit(1);
    }

    System.out.println("Accept Funcionou!");

    try {
      Scanner is = new Scanner(clientSocket.getInputStream());

      PrintStream os = new PrintStream(clientSocket.getOutputStream(), false);
      String inputLine;

      while (!(inputLine = is.nextLine()).equals("")) {
        System.out.println(inputLine);
      }

      os.print("HTTP/1.1 200 OK\nContent-Type: text/html\n\n<H2>Este texto aparecer&aacute; no browser!</H2>\n");
      os.flush();

      os.close();
      is.close();
      clientSocket.close();
      serverSocket.close();

    } catch (IOException e) {
      e.printStackTrace();
    }
  }
}
