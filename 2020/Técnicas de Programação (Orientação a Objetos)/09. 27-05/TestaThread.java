import java.awt.*;
import javax.swing.*;
import java.awt.event.*;
import java.lang.reflect.InvocationTargetException;

public class TestaThread extends JFrame implements Runnable, ActionListener {
  JProgressBar pBar = new JProgressBar(JProgressBar.HORIZONTAL, 0, 10);
  JButton b = new JButton("Inicia");
  int cont = 0;

  TestaThread() {
    super("Thread com Swing");
    setLayout(new FlowLayout());
    add(b);
    add(pBar);
    b.addActionListener(this);
    pack();
    setVisible(true);
  }

  public void actionPerformed(ActionEvent e) {
    cont = 0;
    pBar.setValue(cont);
    new Thread(this).start();
  }

  public void run() {
    try {
      while (cont <= 10) {
        try {
          SwingUtilities.invokeAndWait(new Runnable() {
            public void run() {
              pBar.setValue(cont++);
            }
          });
        } catch (InvocationTargetException e) {
          e.printStackTrace();
        }
        Thread.sleep(1000);
      }
    } catch (InterruptedException e) {}
  }

  static public void main(String[] args) {
    new TestaThread();
  }

}
