import java.awt.*;
import javax.swing.*;
import java.awt.event.*;
import java.io.*;
import java.net.*;
import java.util.*;

public class ClienteFrame extends JFrame implements Runnable, ActionListener {
  static PrintStream os = null;
  JTextField textField;
  JTextArea textArea;

  ClienteFrame() {
    super("Cliente do chat");
    add(textField = new JTextField(20), BorderLayout.NORTH);
    add(textArea = new JTextArea(5, 20), BorderLayout.CENTER);
    textField.addActionListener(this);
    textArea.setEditable(false);
    pack();
    setVisible(true);
  }

  public void actionPerformed(ActionEvent e) {
    os.println(textField.getText());
    textField.setText("");
  }

  public static void main(String[] args) {
    new Thread(new ClienteFrame()).start();
  }

  public void run() {
    Socket socket = null;
    Scanner is = null;

    try {
      socket = new Socket("127.0.0.1", 80);
      os = new PrintStream(socket.getOutputStream(), true);
      is = new Scanner(socket.getInputStream());
    } catch (UnknownHostException e) {
      System.err.println("Don't know about host.");
    } catch (IOException e) {
      System.err.println("Couldn't get I/O for the connection to host");
    }

    try {
      String inputLine;

      do {
        textArea.append((inputLine=is.nextLine())+"\n");
      } while (!inputLine.equals(""));

      os.close();
      is.close();
      socket.close();
    } catch (UnknownHostException e) {
      System.err.println("Trying to connect to unknown host: " + e);
    } catch (IOException e) {
      System.err.println("IOException:  " + e);
    }
  }
}


