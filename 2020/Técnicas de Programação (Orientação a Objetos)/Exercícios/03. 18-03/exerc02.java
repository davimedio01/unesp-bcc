import java.awt.*;
import javax.swing.*;

class Calculadora1 extends JFrame{
     //Botões
     JButton btnSoma = new JButton("Soma");
     JButton btnSubtrai = new JButton("Subtrai");
     JButton btnMultiplica = new JButton("Multiplica");
     JButton btnDivide = new JButton("Divide");
     //TextFields
     JTextField txfTexto1 = new JTextField(15);
     JTextField txfTexto2 = new JTextField(15);
     //Label's
     JLabel lbIgual = new JLabel(" = ");
     JLabel lbResultado = new JLabel("0");

     //Modificando o Construtor
     Calculadora1(){
          super("Calculadora");
          setLayout(new FlowLayout());
          //Criando os JPanel's
          JPanel painelNum1 = new JPanel(new BorderLayout());
          JPanel painelBotao = new JPanel(new GridLayout(4,1));
          JPanel painelResultado = new JPanel(new BorderLayout());
          //Modificando Panel's
          painelNum1.add(txfTexto1, BorderLayout.CENTER);
          painelBotao.add(btnSoma);
          painelBotao.add(btnSubtrai);
          painelBotao.add(btnMultiplica);
          painelBotao.add(btnDivide);
          painelResultado.add(txfTexto2, BorderLayout.WEST);
          painelResultado.add(lbIgual, BorderLayout.CENTER);
          painelResultado.add(lbResultado, BorderLayout.EAST);
          //Acrescentando na Interface
          add(painelNum1);
          add(painelBotao);
          add(painelResultado);
          //Automatização
          pack();
          setVisible(true);

     }
     public static void main(String[] args) {
          // Executando a função
          new Calculadora1();
     }
}