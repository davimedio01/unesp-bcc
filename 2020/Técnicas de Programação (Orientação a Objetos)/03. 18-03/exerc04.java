import java.awt.*;
import javax.swing.*;

class Calculadora3 extends JFrame {
     //Botão
     Button btnCalcular = new Button("Calcular");
     // Campos de Texto
     JTextField txfNum1 = new JTextField(15);
     JTextField txfNum2 = new JTextField(15);
     // Label's
     JLabel lbIgual = new JLabel(" = ");
     JLabel lbResultado = new JLabel("0");
     // JComboBox (Seletor)
     JComboBox cbxOperacao = new JComboBox();

     Calculadora3() {
          super("Calculadora");
          // Criando os Panel's
          JPanel pnlSuperior = new JPanel(new FlowLayout());
          JPanel pnlInferior = new JPanel(new FlowLayout());
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
          pnlInferior.add(btnCalcular);
          // Adicionando na Interface Visual
          add(pnlSuperior, BorderLayout.NORTH);
          add(pnlInferior, BorderLayout.SOUTH);
          // Configs Finais
          pack();
          setVisible(true);
     }

     public static void main(String[] args) {
          new Calculadora3();
     }
}