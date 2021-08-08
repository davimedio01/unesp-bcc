import javax.swing.*;
import javax.swing.plaf.ColorUIResource;

import java.awt.*;
//import java.awt.event.*;
import java.util.Random;
import java.util.concurrent.TimeUnit;

class Paisagem extends JPanel {

  /*
   //TESTE (Coordenadas pelo Mouse) 
   private int x, y;
   */

  // Tamanho da Tela
  public final int WIDTH = 600;
  public final int HEIGHT = 400;

  ///////////////////
  // Desenho Estático
  ///////////////////

  // Montanha
  private final int X_Montanha = 0 - WIDTH / 4;
  private final int Y_Montanha = HEIGHT - (HEIGHT / 3);
  private final int WIDTH_Montanha = WIDTH + 300;
  private final int HEIGHT_Montanha = HEIGHT + 200;

  // Poça d'Água
  private final int[] X_PocaAgua = { 130, 90, 65, 90, 150, 160 };
  private final int[] Y_PocaAgua = { 315, 325, 350, 368, 345, 335 };
  private final int[] X_ContornoPocaAgua = { 130, 80, 45, 90, 162, 180 };
  private final int[] Y_ContornoPocaAgua = { 305, 320, 350, 380, 356, 330 };
  private final int QtdPontos_PocaAgua = 6;

  // Madeira (Fogueira)
  private final int X_MadeiraFogueira = 270;
  private final int Y_MadeiraFogueira = 310;
  private final int WIDTH_MadeiraFogueira = 75;
  private final int HEIGHT_MadeiraFogueira = 30;
  private final int ARCWIDHT_MadeiraFogueira = 20;
  private final int ARCHEIGHT_MadeiraFogueira = 20;

  // Fogo
  private final int[] X_Fogo = { 310, 300, 288, 280, 270, 290, 325, 340, 330, 335, 328, 318 };
  private final int[] Y_Fogo = { 270, 295, 277, 290, 285, 325, 325, 303, 293, 288, 270, 298 };
  private final int QtdPontos_Fogo = 12;

  // Gravetos
  private final int[] X1_Gravetos = { 400, 450, 450, 450, 425, 450 };
  private final int[] Y1_Gravetos = { 315, 315, 315, 315, 330, 330 };
  private final int[] X2_Gravetos = { 450, 450, 470, 430, 410, 490 };
  private final int[] Y2_Gravetos = { 345, 375, 295, 295, 355, 345 };
  private final int QtdRetas_Gravetos = 6;

  ///////////////////
  // Desenho Dinâmico
  ///////////////////

  // Estrela
  private int X_Estrela;
  private int Y_Estrela;
  private final int WIDTH_Estrela = 2;
  private final int HEIGHT_Estrela = 2;
  private final int Qtd_Estrela = 120;
  private final int X_LIMIT_Estrela = WIDTH;
  private final int Y_LIMIT_Estrela = Y_Montanha - 20;

  // Lua
  private Lua lua;
  private final int INICIO_X_Lua = -50;
  private final int INICIO_Y_Lua = HEIGHT - 100;
  private final int MOVEPOSICAO_X = 20;
  private int MOVEPOSICAO_Y = 30;

  // Construtor
  Paisagem() {
    setBorder(BorderFactory.createLineBorder(Color.BLACK));
    lua = new Lua();
    // Posições iniciais da Lua
    lua.setXPos(INICIO_X_Lua);
    lua.setYPos(INICIO_Y_Lua);

    /*
     // TESTE (Coordenadas pelo Mouse) addMouseMotionListener(new MouseMotionAdapter() {
      @Override 
      public void mouseDragged(MouseEvent e) 
      { 
        x = e.getX(); 
        y = e.getY(); 
        repaint(); 
        super.mouseDragged(e); 
      }
     @Override 
     public void mouseMoved(MouseEvent e) 
     { 
        x = e.getX(); 
        y = e.getY();
        repaint(); 
        super.mouseMoved(e); 
      } 
    });
     */

  }

  // Setar o tamanho do JPanel
  @Override
  public Dimension getPreferredSize() {
    return new Dimension(WIDTH, HEIGHT);
  }

  // paintComponent: método para desenhar/pintar componentes
  @Override
  public void paintComponent(Graphics g) {
    super.paintComponent(g);

    ///////////////////
    // Desenho Estático
    ///////////////////
    fundoTela(g);
    Montanha(g);
    PocaAgua(g);
    MadeiraFogueira(g);
    FogoFogueira(g);
    Gravetos(g);

    /*
     //TESTE (Coordenadas pelo Mouse) 
     g.setColor(Color.RED); g.drawString("(" + x + "," + y + ")", x, y);
    */

    ///////////////////
    // Desenho Dinâmico
    ///////////////////
    Estrelas(g);
    lua.pintar(g);

  }

  ///////////////////
  // Desenho Estático
  ///////////////////

  // Fundo da Tela
  void fundoTela(Graphics g) {
    g.setColor(Color.BLACK);
    g.fillRect(0, 0, WIDTH, HEIGHT);
  }

  // Montanha
  void Montanha(Graphics g) {
    Color cor = new ColorUIResource(0, 51, 0);
    g.setColor(cor);
    g.fillOval(X_Montanha, Y_Montanha, WIDTH_Montanha, HEIGHT_Montanha);
  }

  // Poça d'Água
  void PocaAgua(Graphics g) {
    // Contorno da Água
    Color corContorno = new ColorUIResource(25, 18, 235);
    g.setColor(corContorno);
    g.fillPolygon(X_ContornoPocaAgua, Y_ContornoPocaAgua, QtdPontos_PocaAgua);

    // Poça
    Color corAgua = new ColorUIResource(15, 94, 156);
    g.setColor(corAgua);
    g.fillPolygon(X_PocaAgua, Y_PocaAgua, QtdPontos_PocaAgua);

  }

  // Madeira (Fogueira)
  void MadeiraFogueira(Graphics g) {
    Color cor = new ColorUIResource(150, 75, 0);
    g.setColor(cor);
    g.fillRoundRect(X_MadeiraFogueira, Y_MadeiraFogueira, WIDTH_MadeiraFogueira, HEIGHT_MadeiraFogueira,
        ARCWIDHT_MadeiraFogueira, ARCHEIGHT_MadeiraFogueira);
  }

  // Fogo
  void FogoFogueira(Graphics g) {
    Color corFora = new ColorUIResource(204, 204, 0);
    g.setColor(corFora);
    g.fillPolygon(X_Fogo, Y_Fogo, QtdPontos_Fogo);
  }

  // Gravetos
  void Gravetos(Graphics g) {
    Color cor = new ColorUIResource(139, 69, 19);
    g.setColor(cor);

    // Colocando retas
    for (int i = 0; i < QtdRetas_Gravetos; i++) {
      g.drawLine(X1_Gravetos[i], Y1_Gravetos[i], X2_Gravetos[i], Y2_Gravetos[i]);
    }
  }

  ///////////////////
  // Desenho Dinâmico
  ///////////////////

  // Estrelas
  void Estrelas(Graphics g) {
    Color cor = new ColorUIResource(224, 224, 224);
    g.setColor(cor);
    // Gerando Estrelas no Range aleatório
    Random rand = new Random();
    // Colocando algumas
    for (int i = 1; i <= Qtd_Estrela; i++) {
      X_Estrela = rand.nextInt(X_LIMIT_Estrela);
      Y_Estrela = rand.nextInt(Y_LIMIT_Estrela);

      // Gerando
      g.fillRect(X_Estrela, Y_Estrela, WIDTH_Estrela, HEIGHT_Estrela);
    }
  }

  // Lua (Mover)
  public void moverLua() {
    int ATUAL_X, ATUAL_Y;

    while (true) {
      // Recuperando coordenadas atuais
      ATUAL_X = lua.getXPos();
      ATUAL_Y = lua.getYPos();

      // Antes da metade: aumentar
      if ((ATUAL_X < (WIDTH / 2) - 30)) {
        lua.setXPos(ATUAL_X + MOVEPOSICAO_X);
        lua.setYPos(ATUAL_Y - MOVEPOSICAO_Y);
        MOVEPOSICAO_Y -= 2;
      }
      // Se chegou na metade, começar a diminuir
      else if ((ATUAL_X >= (WIDTH / 2) - 30)) {
        lua.setXPos(ATUAL_X + MOVEPOSICAO_X);
        lua.setYPos(ATUAL_Y + MOVEPOSICAO_Y);
        MOVEPOSICAO_Y += 2;
      }

      // Repintando a tela
      repaint();

      // Delay (TimeUnit)
      try {
        TimeUnit.MILLISECONDS.sleep(500);
      } catch (InterruptedException e) {
        e.printStackTrace();
      }

      // Verificando se ultrapassou o limite (voltar para o início)
      if ((ATUAL_X > WIDTH) || (ATUAL_Y > HEIGHT)) {
        lua.setXPos(INICIO_X_Lua);
        lua.setYPos(INICIO_Y_Lua);
        MOVEPOSICAO_Y = 30;
      }
    }

  }

}

// Classes Dinâmicas
class Lua {
  // Atributos
  private int xPos;
  private int yPos;
  private final int WIDTH = 50;
  private final int HEIGHT = 50;
  private final Color cor = new ColorUIResource(125, 123, 103);

  // Métodos
  public int getXPos() {
    return this.xPos;
  }

  public void setXPos(int xPos) {
    this.xPos = xPos;
  }

  public int getYPos() {
    return this.yPos;
  }

  public void setYPos(int yPos) {
    this.yPos = yPos;
  }

  public int getWIDTH() {
    return this.WIDTH;
  }

  public int getHEIGHT() {
    return this.HEIGHT;
  }

  // Pintar
  public void pintar(Graphics g) {
    g.setColor(cor);
    g.fillOval(xPos, yPos, WIDTH, HEIGHT);
  }

}

public class PP_Alterado extends JFrame {
  Paisagem paisagem = new Paisagem();

  PP_Alterado() {
    super("Paisagem: Translação da Lua");
    add(paisagem);
    pack();
    // Bloqueando redimensionamento
    setResizable(false);
    // Colocando para o meio da tela
    setLocationRelativeTo(null);
    setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    setVisible(true);
  }

  static public void main(String[] args) {
    PP_Alterado aux = new PP_Alterado();

    // Movimentação
    aux.paisagem.moverLua();
  }
}
