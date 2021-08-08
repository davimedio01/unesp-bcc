import java.awt.event.*;
import java.awt.*;
import javax.swing.*;

class Calculadora1 extends JFrame{
     // Botões
     JButton btnSoma = new JButton("Soma");
     JButton btnSubtrai = new JButton("Subtrai");
     JButton btnMultiplica = new JButton("Multiplica");
     JButton btnDivide = new JButton("Divide");
     // TextFields
     JTextField txfTexto1 = new JTextField("0", 10);
     JTextField txfTexto2 = new JTextField("0", 10);
     // Label's
     JLabel lbIgual = new JLabel(" = ");
     JLabel lbResultado = new JLabel("0            ");

     // Modificando o Construtor
     Calculadora1() {
          super("Calculadora");
          setLayout(new FlowLayout());
          // Criando os JPanel's
          JPanel painelNum1 = new JPanel(new BorderLayout());
          JPanel painelBotao = new JPanel(new GridLayout(4, 1));
          JPanel painelResultado = new JPanel(new BorderLayout());
          // Modificando Panel's
          painelNum1.add(txfTexto1, BorderLayout.CENTER);
          painelBotao.add(btnSoma);
          painelBotao.add(btnSubtrai);
          painelBotao.add(btnMultiplica);
          painelBotao.add(btnDivide);
          painelResultado.add(txfTexto2, BorderLayout.WEST);
          painelResultado.add(lbIgual, BorderLayout.CENTER);
          painelResultado.add(lbResultado, BorderLayout.EAST);
          // Acrescentando na Interface
          add(painelNum1);
          add(painelBotao);
          add(painelResultado);
          // Automatização
          pack();
          setLocationRelativeTo(null); // Posição central
          setVisible(true);

          // Tratamento do Fechamento (Padrão)
          addWindowListener(new WindowAdapter(){
               public void windowClosing(final WindowEvent e) {
                    final int opc = JOptionPane.showConfirmDialog(null, "Deseja realmente fechar o programa?", "Fechar",
                              JOptionPane.YES_NO_OPTION);
                    if (opc == 0) {
                         System.exit(0);
                    }
               }
          });
          setDefaultCloseOperation(DO_NOTHING_ON_CLOSE);

          //Tratando os eventos
          //Soma
          btnSoma.addActionListener(new ActionListener(){
               public void actionPerformed(ActionEvent e){
                    //Recuperar TextField's
                    int num1 = Integer.parseInt(txfTexto1.getText());
                    int num2 = Integer.parseInt(txfTexto2.getText());
                    //Colocar resultado na label
                    lbResultado.setText(Integer.toString(num1+num2));
               }
          });
          //Subtração
          btnSubtrai.addActionListener(new ActionListener() {
               public void actionPerformed(ActionEvent e) {
                    // Recuperar TextField's
                    int num1 = Integer.parseInt(txfTexto1.getText());
                    int num2 = Integer.parseInt(txfTexto2.getText());
                    // Colocar resultado na label
                    lbResultado.setText(Integer.toString(num1 - num2));
               }
          });
          //Multiplicação
          btnMultiplica.addActionListener(new ActionListener() {
               public void actionPerformed(ActionEvent e) {
                    // Recuperar TextField's
                    int num1 = Integer.parseInt(txfTexto1.getText());
                    int num2 = Integer.parseInt(txfTexto2.getText());
                    // Colocar resultado na label
                    lbResultado.setText(Integer.toString(num1 * num2));
               }
          });
          //Divisão
          btnDivide.addActionListener(new ActionListener() {
               public void actionPerformed(ActionEvent e) {
                    // Recuperar TextField's
                    int num1 = Integer.parseInt(txfTexto1.getText());
                    int num2 = Integer.parseInt(txfTexto2.getText());
                    // Colocar resultado na label
                    try{
                         lbResultado.setText(Integer.toString(num1 / num2));
                    }catch(ArithmeticException ae){
                         JOptionPane.showMessageDialog(null, "Erro de operação aritmética. Tente novamente.",
                                   "Erro de Operação", JOptionPane.ERROR_MESSAGE);
                    }
                    
               }
          });
     }

     public static void main(String[] args) {
          // Executando a função
          new Calculadora1();
     }
}