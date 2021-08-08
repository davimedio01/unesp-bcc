import java.awt.event.*;
import java.awt.*;
import javax.swing.*;

class Calculadora2 extends JFrame {
     // Campos de Texto
     JTextField txfNum1 = new JTextField("0", 10);
     JTextField txfNum2 = new JTextField("0", 10);
     // Label's
     JLabel lbIgual = new JLabel(" = ");
     JLabel lbResultado = new JLabel("0             ");
     // JComboBox (Seletor)
     JComboBox cbxOperacao = new JComboBox();
     //Botão Calcular
     Button btnCalcular = new Button("Calcular");

     Calculadora2() {
          super("Calculadora");
          // Criando os Panel's
          JPanel pnlSuperior = new JPanel(new FlowLayout());
          JPanel pnlNum2 = new JPanel(new BorderLayout());
          // Configurando o ComboBox
          cbxOperacao.addItem("Soma");
          cbxOperacao.addItem("Subtrai");
          cbxOperacao.addItem("Multiplica");
          cbxOperacao.addItem("Divide");
          // Configurando os Panel's
          pnlNum2.add(txfNum2, BorderLayout.WEST);
          pnlNum2.add(lbIgual, BorderLayout.CENTER);
          pnlNum2.add(lbResultado, BorderLayout.EAST);
          pnlSuperior.add(txfNum1);
          pnlSuperior.add(cbxOperacao);
          pnlSuperior.add(pnlNum2);
          // Adicionando na Interface Visual
          add(pnlSuperior, BorderLayout.NORTH);
          add(btnCalcular, BorderLayout.SOUTH);
          // Configs Finais
          pack();
          setLocationRelativeTo(null); //Posição central
          setVisible(true);

          // Tratamento do Fechamento (Padrão)
          addWindowListener(new WindowAdapter() {
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
          //Botão Calcular
          btnCalcular.addActionListener(new ActionListener(){
               public void actionPerformed(ActionEvent e){
                    //Recuperando valores para calculo
                    int num1 = Integer.parseInt(txfNum1.getText());
                    int num2 = Integer.parseInt(txfNum2.getText());
                    
                    //Verificando cada campo do ComboBox
                    if(cbxOperacao.getSelectedIndex() == 0){
                         //Soma
                         lbResultado.setText(Integer.toString(num1+num2));
                    }
                    else if(cbxOperacao.getSelectedIndex() == 1){
                         //Subtração
                         lbResultado.setText(Integer.toString(num1 - num2));
                    }
                    else if (cbxOperacao.getSelectedIndex() == 2) {
                         // Multiplicação
                         lbResultado.setText(Integer.toString(num1 * num2));
                    }
                    else if (cbxOperacao.getSelectedIndex() == 3) {
                         // Divisão
                         try{
                              lbResultado.setText(Integer.toString(num1 / num2));
                         }catch(ArithmeticException ar){
                              JOptionPane.showMessageDialog(null, "Erro de operação aritmética. Tente novamente.",
                                        "Erro de Operação", JOptionPane.ERROR_MESSAGE);
                         }
                    }

               }
          });
          
     }

     public static void main(String[] args) {
          new Calculadora2();
     }
}