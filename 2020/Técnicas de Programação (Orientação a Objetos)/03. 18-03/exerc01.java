import java.awt.*;
import javax.swing.*;

class EditTexto extends JFrame{
     //Botões
     JButton btnAbrir = new JButton("Abrir");
     JButton btnSalvar = new JButton("Salvar");
     JButton btnSalvarComo = new JButton("Salvar Como");
     JButton btnFechar = new JButton("Fechar");
     //Área de Texto com Várias Linhas
     JTextArea txtArea = new JTextArea(20, 40);

     //Modificando o Construtor
     EditTexto(){
          super("Editor de Texto");
          //Painel contendo os botões
          JPanel painel = new JPanel(new GridLayout(4,1));
          painel.add(btnAbrir);
          painel.add(btnSalvar);
          painel.add(btnSalvarComo);
          painel.add(btnFechar);
          //Painel contendo o painel anterior
          JPanel painel2 = new JPanel(new BorderLayout());
          painel2.add(painel, BorderLayout.NORTH);

          //Adicionando o JPanel na Interface Visual
          add(painel2, BorderLayout.WEST);
          //Adicionando o JTextArea na Interface Visual
          add(txtArea);
          //Arrumando design na inicialização
          pack();
          setVisible(true);
     }

     public static void main(String[] args) {
          //Executando a função
          new EditTexto();
     }
}