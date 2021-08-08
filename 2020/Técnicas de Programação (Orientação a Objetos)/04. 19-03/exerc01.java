import java.io.*;
import java.util.Scanner;
import java.awt.*;
import javax.swing.*;
import java.awt.event.*;

class EditorTexto extends JFrame{
     // Botões
     JButton btnAbrir = new JButton("Abrir");
     JButton btnSalvar = new JButton("Salvar");
     JButton btnSalvarComo = new JButton("Salvar Como");
     JButton btnFechar = new JButton("Fechar");
     // Área de Texto com Várias Linhas
     JTextArea txtArea = new JTextArea(20, 40);
     //String para Nome do Arquivo
     String nomeArq = new String();
     //StringBuffer para Texto do Arquivo
     StringBuffer txtArq = new StringBuffer();

     // Modificando o Construtor
     EditorTexto(){
          super("Editor de Texto");
          //Painel contendo os botões
          final JPanel painel = new JPanel(new GridLayout(4,1));
          painel.add(btnAbrir);
          painel.add(btnSalvar);
          painel.add(btnSalvarComo);
          painel.add(btnFechar);
          //Painel contendo o painel anterior
          final JPanel painel2 = new JPanel(new BorderLayout());
          painel2.add(painel, BorderLayout.NORTH);

          //Adicionando o JPanel na Interface Visual
          add(painel2, BorderLayout.WEST);
          //Adicionando o JTextArea na Interface Visual
          add(txtArea);
          //Arrumando design na inicialização
          pack();
          setLocationRelativeTo(null);
          setVisible(true);
          
          //Tratamento do Fechamento (Padrão)
          addWindowListener(new fechaPrograma());
          setDefaultCloseOperation(DO_NOTHING_ON_CLOSE);

          //Tratamento do Texto no JTextArea
          txtArea.setFont(new Font(Font.MONOSPACED, Font.PLAIN, 20));

          //Tratamento dos Botões
          //Abrir: arquivo .txt
          btnAbrir.addActionListener(new ActionListener(){
               public void actionPerformed(ActionEvent e){
                    nomeArq = JOptionPane.showInputDialog(null, "Digite o nome do arquivo de texto", 
                    "Abrir", JOptionPane.QUESTION_MESSAGE);
                    if(nomeArq != null && nomeArq.isEmpty() == false){
                         nomeArq += ".txt";
                         //Abrindo arquivo e colocando conteúdo no JTextArea
                         try{
                              FileInputStream in = new FileInputStream(nomeArq);
                              Scanner scn = new Scanner(in);
                              //Lendo arquivo e colocando em uma stringbuffer
                              while(scn.hasNextLine()){
                                   txtArq.append(scn.nextLine());
                                   txtArq.append("\n");  
                              }
                              txtArea.setText(txtArq.toString());
                              txtArq.delete(0, txtArq.length());
                              in.close();
                              scn.close();

                         }catch(FileNotFoundException file){
                              JOptionPane.showMessageDialog(null, "Erro ao abrir arquivo. Tente novamente.",
                                        "Erro de Operação", JOptionPane.ERROR_MESSAGE);
                         }catch(IOException io){
                              JOptionPane.showMessageDialog(null, "Erro ao abrir arquivo. Tente novamente.",
                                        "Erro de Operação", JOptionPane.ERROR_MESSAGE);
                         }
                    }
               }
          });
          //Salvar: arquivo atual .txt
          btnSalvar.addActionListener(new ActionListener(){
               public void actionPerformed(ActionEvent e){
                    final int opcao = new JOptionPane().showConfirmDialog(null,
                    "Deseja realmente salvar o arquivo?", "Salvar",
                    JOptionPane.YES_NO_OPTION);
                    if(opcao == 0){
                         try{
                              //Salvando arquivo atual
                              FileOutputStream out = new FileOutputStream(nomeArq);
                              out.write(txtArea.getText().getBytes());
                              out.close();
                              //Criando um diálogo de sucesso na operação
                              JOptionPane.showMessageDialog(null, "Arquivo salvo com sucesso.",
                                        "Salvar", JOptionPane.INFORMATION_MESSAGE);

                         }catch(FileNotFoundException file){
                              JOptionPane.showMessageDialog(null, "Erro ao salvar arquivo. Tente novamente.",
                                        "Erro de Operação", JOptionPane.ERROR_MESSAGE);
                         }catch(IOException io){
                              JOptionPane.showMessageDialog(null, "Erro ao salvar arquivo. Tente novamente.",
                                        "Erro de Operação", JOptionPane.ERROR_MESSAGE);
                         }
                         
                    }
               }
          });
          //Salvar Como: novo arquivo .txt
          btnSalvarComo.addActionListener(new ActionListener() {
               public void actionPerformed(ActionEvent e) {
                    //Backup do NomeAtual
                    String nomeatualArq = nomeArq;
                    nomeArq = JOptionPane.showInputDialog(null, "Digite o novo nome do arquivo de texto", "Salvar Como",
                              JOptionPane.QUESTION_MESSAGE);
                    if(nomeArq != null && nomeArq.isEmpty() == false){
                         nomeArq += ".txt";
                         try{
                              //Salvando arquivo digitado
                              FileOutputStream out = new FileOutputStream(nomeArq);
                              out.write(txtArea.getText().getBytes());
                              out.close();
                              // Criando um diálogo de sucesso na operação
                              JOptionPane.showMessageDialog(null, "Arquivo salvo com sucesso.", "Salvar Como",
                                        JOptionPane.INFORMATION_MESSAGE);
                         }catch(FileNotFoundException file){
                              JOptionPane.showMessageDialog(null, "Erro ao salvar arquivo. Tente novamente.",
                                        "Erro de Operação", JOptionPane.ERROR_MESSAGE);
                         }catch(IOException io){
                              JOptionPane.showMessageDialog(null, "Erro ao salvar arquivo. Tente novamente.",
                                        "Erro de Operação", JOptionPane.ERROR_MESSAGE);
                         }
                    }
                    else{
                         nomeArq = nomeatualArq;
                    }
               }
          });
          //Fechar: fechar o arquivo .txt aberto
          btnFechar.addActionListener(new ActionListener() {
               public void actionPerformed(ActionEvent e) {
                    final int opcao = new JOptionPane().showConfirmDialog(null, "Deseja realmente fechar o arquivo atual?",
                              "Fechar", JOptionPane.YES_NO_OPTION);
                    if(opcao == 0){
                         //Zerando texto do JTextArea
                         txtArea.setText("");
                    }
               }
          });
     }

     //Listener para Tratamento do Fechamento
     class fechaPrograma extends WindowAdapter{
          //Método de Fechamento
          public void windowClosing(final WindowEvent e){
               final int opc = JOptionPane.showConfirmDialog(null, 
               "Deseja realmente fechar o programa?", "Fechar", 
               JOptionPane.YES_NO_OPTION);
               if(opc == 0){
                    System.exit(0);
               }
          }
     }
     public static void main(final String[] args) {
          new EditorTexto();
     }
}