import java.io.*;
import java.util.*;

class NaoTemRaizesReaisException extends Exception {
};

class EquacaoPrimeiroGrauException extends Exception {
};

class RaizesRef {
    float x1, x2;
};

class CalculaRaizes {
  static void calculaRaizes(float a, float b, float c, RaizesRef r) 
        throws NaoTemRaizesReaisException, EquacaoPrimeiroGrauException {
    float d = b*b - 4*a*c;
    if (a == 0)
      throw new EquacaoPrimeiroGrauException();
    if (d < 0)
      throw new NaoTemRaizesReaisException();
    r.x1 = (-b + (float)Math.sqrt(d)) / (2 * a);
    r.x2 = (-b - (float)Math.sqrt(d)) / (2 * a);
  }
}

class Raizes {

  public static void main(String[] args) {
    float a, b, c;    
    RaizesRef raizes = new RaizesRef();

    try {
      Scanner in = new Scanner(System.in);

      a = in.nextFloat();
      b = in.nextFloat();
      c = in.nextFloat();
     
      CalculaRaizes.calculaRaizes(a, b, c, raizes);
      
      System.out.println("x1 = " + raizes.x1 + "\nx2 = " + raizes.x2);            
    } catch (InputMismatchException e) {
      System.out.println("Numero incorreto");
    } catch (NaoTemRaizesReaisException e) {
      System.out.println("Erro: " + e);
    } catch (EquacaoPrimeiroGrauException e) {
      System.out.println("Erro: " + e);
    }
  }
}
