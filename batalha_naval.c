#include <stdio.h>

struct Matriz //Usamos para definir a stuct da matriz 10x10
{
  char dados[10][10];
};

struct Matriz inicializarMatriz() //Usamos para colocar agua na matriz ~
{
  struct Matriz m;
  for (int i = 0; i < 10; i++) 
  {
    for (int j = 0; j < 10; j++) 
    {
      m.dados[i][j] = '~';
    }
  }
  return m;
}

void imprimirMatriz(struct Matriz m) //Imprime a matriz 10x10 
{
  for (int i = 0; i < 10; i++) 
  {
    for (int j = 0; j < 10; j++) 
    {
      printf(" %c ", m.dados[i][j]);
    }
    printf("\n");
  }
}

int validarCoordenadas(int linha, int coluna) //Usamos para testar se o valor digitado esta dentro dos 10x10 do tabuleiro
{
  return (linha >= 0 && linha < 10 && coluna >= 0 && coluna < 10);
}

int validarAlocacao(struct Matriz m, int linha, int coluna, char valor, char vh) //Usamos para testar se o valor digitado ja esta ocupado resolvendo o problema da sobreposicao dos barcos deixando colocar apenas se tiver ~
{
  int tamanho;

  switch (valor)
  {
  case 'S':
    tamanho = 2;
    break;
  case 'C':
    tamanho = 3;
    break;
  case 'T':
    tamanho = 4;
    break;
  case 'A':
    tamanho = 5;
    break;
  default:
    return 0;
  }

  if (vh == 'h') 
  {
    if (coluna + tamanho > 10)
      return 0;
    for (int i = 0; i < tamanho; i++) 
    {
      if (m.dados[linha][coluna + i] != '~') 
      {
        return 0;
      }
    }
  } else if (vh == 'v') 
   {
    if (linha + tamanho > 10)
      return 0;
    for (int i = 0; i < tamanho; i++) 
    {
      if (m.dados[linha + i][coluna] != '~') 
      {
        return 0;
      }
    }
  }

  return 1;
}

struct Matriz alocarBarco(struct Matriz m, int linha, int coluna, char valor, char vh, int contadorS, int contadorC, int contadorT, int contadorA) //Usamos essa funcao para colocar os barcos no tabuleiro apos verificar e usamos a mesma para ver o limite de cada tipo de barco
 {
  int tamanho;

  switch (valor) 
  {
  case 'S':
    if (contadorS >= 4)
    {
      printf("\nO limite de barcos do tipo S (4) foi atingido. Digite outro.");
      printf("\n");
      break;
    }
    tamanho = 2;
    break;
  case 'C':
    if (contadorC >= 3)
    {
      printf("\nO limite de barcos do tipo C (3) foi atingido. Digite outro.");
      printf("\n");
      break;
    }
    tamanho = 3;
    break;
  case 'T':
    if (contadorT >= 2)
    {
      printf("\nO limite de barcos do tipo T (2) foi atingido. Digite outro.");
      printf("\n");
      break;
    }
    tamanho = 4;
    break;
  case 'A':
    if (contadorA >= 1)
    {
      printf("\nO limite de barcos do tipo A (1) foi atingido. Digite outro.");
      printf("\n");
      break;
    }
    tamanho = 5;
    break;
  default:
    return m;
  }

  if (vh == 'h') 
  {
    for (int i = 0; i < tamanho; i++) 
    {
      m.dados[linha][coluna + i] = valor;
    }
  }

  else if (vh == 'v') 
  {
    for (int i = 0; i < tamanho; i++) 
    {
      m.dados[linha + i][coluna] = valor;
    }
  }
  return m;
}

int verificarConclusao(int contadorA, int contadorS, int contadorC, int contadorT) //Aqui vemos que se todos os tipos foram completados o tabuleiro foi completo
{
  return (contadorA == 1 && contadorS == 4 && contadorC == 3 && contadorT == 2);
}

struct Jogo //Usamos para armazenas os nomes e os tabuleiros
{
  struct Matriz tabuleiro1;
  struct Matriz tabuleiro2;
  char nomeJogador1[50];
  char nomeJogador2[50];
};

int main() 
{
  struct Jogo jogo;
  jogo.tabuleiro1 = inicializarMatriz();
  jogo.tabuleiro2 = inicializarMatriz();

  printf("\n------Bem-vindo ao jogo de batalha naval!-----");
  printf("\nCoordenadas [x][y] comecam em 0 e vao a 9");
  printf("\nAo terminar o tabuleiro 1 pressione s para sair e ir para o 2 o tabuleiro ficara salvo");
  printf("\n");
  
  printf("\nJogador 1, por favor insira seu nome: ");
  scanf("%s", jogo.nomeJogador1);

  printf("\nJogador 2, por favor insira seu nome: ");
  scanf("%s", jogo.nomeJogador2);

  printf("\n%s, vamos começar!\n", jogo.nomeJogador1);
  printf("\nTabuleiro do Jogador 1:\n");
  imprimirMatriz(jogo.tabuleiro1);

  printf("\nTabuleiro do Jogador 2:\n");
  imprimirMatriz(jogo.tabuleiro2);

  int linha, coluna;
  int contadorS = 0;
  int contadorC = 0;
  int contadorT = 0;
  int contadorA = 0;
  char vh;

  while (1) 
  {
    printf("\nDigite se deseja posicionar o barco na vertical ou horizontal (v "
           "ou h) e se deseja sair (s) : ");
    scanf(" %c", &vh);

    if (vh == 's') 
    {
      break;
    }

    printf("\nDigite as coordenadas (linha coluna) e o tipo de barco que "
           "deseja adicionar S C T A: ");
    scanf("%d", &linha);
    scanf("%d", &coluna);

    char valor;
    scanf(" %c", &valor);

    if (validarCoordenadas(linha, coluna)) 
    {
      if (validarAlocacao(jogo.tabuleiro1, linha, coluna, valor, vh)) 
      {
        jogo.tabuleiro1 = alocarBarco(
            jogo.tabuleiro1, linha, coluna, valor, vh, contadorS, contadorC,
            contadorT, contadorA);

        switch (valor) 
        {
        case 'S':
          contadorS++;
          break;
        case 'C':
          contadorC++;
          break;
        case 'T':
          contadorT++;
          break;
        case 'A':
          contadorA++;
          break;
        }

        printf("\nTabuleiro do Jogador 1 Após Modificação:\n");
        imprimirMatriz(jogo.tabuleiro1);

        if (verificarConclusao(contadorA, contadorS, contadorC, contadorT)) 
        {
          printf("\nParabéns! O tabuleiro 1 foi completado.\n");
          break;
        }
      } 

      else 
      {
        printf(
            "\nEspaço ocupado ou coordenadas inválidas, tente novamente.");
      }
    } else 
    {
      printf("\nCoordenadas inválidas, tente novamente.");
    }
  }

  // Segundo jogador repetimos a mesma estrutura do primeiro jogador

  printf("\n------Vez do %s-----", jogo.nomeJogador2);
  printf("\nTabuleiro do Jogador 1:\n");
  imprimirMatriz(jogo.tabuleiro1);
  printf("\nTabuleiro do Jogador 2:\n");
  imprimirMatriz(jogo.tabuleiro2);

  printf("\nPressione Enter para continuar...");
  getchar();

  int linha2, coluna2;
  int contadorS2 = 0;
  int contadorC2 = 0;
  int contadorT2 = 0;
  int contadorA2 = 0;
  char vh2;

  while (1) 
  {
    printf("\nDigite se deseja posicionar o barco na vertical ou horizontal "
           "(v ou h) e se deseja sair (s) : ");
    scanf(" %c", &vh2);

    if (vh2 == 's') 
    {
      break;
    }

    printf("\nDigite as coordenadas (linha coluna) e o tipo de barco que "
           "deseja adicionar S C T A: ");
    scanf("%d", &linha2);
    scanf("%d", &coluna2);

    char valor2;
    scanf(" %c", &valor2);

    if (validarCoordenadas(linha2, coluna2)) 
    {
      if (validarAlocacao(jogo.tabuleiro2, linha2, coluna2, valor2, vh2)) 
      {
        jogo.tabuleiro2 = alocarBarco(
            jogo.tabuleiro2, linha2, coluna2, valor2, vh2, contadorS2, contadorC2,
            contadorT2, contadorA2);

        switch (valor2)
        {
        case 'S':
          contadorS2++;
          break;
        case 'C':
          contadorC2++;
          break;
        case 'T':
          contadorT2++;
          break;
        case 'A':
          contadorA2++;
          break;
        }

        printf("\nTabuleiro do Jogador 2 Após Modificação:\n");
        imprimirMatriz(jogo.tabuleiro2);

        if (verificarConclusao(contadorA2, contadorS2, contadorC2, contadorT2)) 
        {
          printf("\nParabéns! O tabuleiro 2 foi completado.\n");
          break;
        }
      } 
      else 
      {
        printf("\nEspaço ocupado ou coordenadas inválidas, tente novamente.");
      }
    } 
    else 
    {
      printf("\nCoordenadas inválidas, tente novamente.");
    }
  }
  return 0;
}
