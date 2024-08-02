#include <stdio.h>
#include <string.h>



int main(void) {
    int numPedidos = 5;      // Quantidades de pedidos
    char sexos[5];           // Sexo dos clientes
    float valores[5];        // Valores dos pedidos
    int codigos[5];          // Codigos dos pedidos
    int quantidadeItens[5];  // Quantidade de itens dos pedidos
    int qtdF = 0;           // Quantidade de pedidos femininos
    int qtdH = 0;           // Quantidade de pedidos masculinos
    float valorH = 0;       // Valor total dos pedidos masculinos
    float valorF = 0;       // Valor total dos pedidos femininos
    float valorTotalGeral = 0; // Valor total geral dos pedidos
    float maisBarata = 0;   // Valor mais barato dos pedidos
    int codigoPesquisa;      // Codigo do pedido a ser pesquisado
    float valorLimite;        // Valor limite para pesquisa
    int quantidadeItensTotal = 0; // Quantidade total de itens dos pedidos
    int codigoExistente = 0;      //Não poder ser o mesmo código

    //Leitura dos dados dos pedidos
    for (int i = 0; i < numPedidos; i++) {
        printf("Cadastro de Pedido %d:\n", i + 1);


        // Sexo
      do {
          printf("Digite o sexo do cliente (m/f): ");
          scanf(" %c", &sexos[i]);

          if (sexos[i] != 'm' && sexos[i] != 'f') {
              printf("Não pode cadastrar um sexo com esse valor. Informe outro com (m ou f).\n");
          } else {
              if (sexos[i] == 'f') {
                  qtdF++;
              } else {
                  qtdH++;
              }
              break;
          }
      } while (1);

        // Codigo
      do {
          printf("Digite o código do pedido (1-10): ");
          scanf("%d", &codigos[i]);

          codigoExistente = 0; 

          for (int j = 0; j < i; j++) {
              if (codigos[i] == codigos[j]) {
                  codigoExistente = 1;
                  printf("Código de pedido já existente. Digite outro código.\n");
                  break;
              }
          }

          if (codigos[i] < 1 || codigos[i] > 10 || codigoExistente) {
              printf("Código de pedido inválido ou já existente. Deve ser de 1 a 10 e único.\n");
          } else {
              break;
          }
      } while (1);

        // Valor total
        do {
            printf("Digite o valor total do pedido: ");
            scanf("%f", &valores[i]);

            if (valores[i] < 0) {
                printf("Não pode cadastrar um valor negativo. Informe outro valor.\n");
            } else {
                if (maisBarata == 0 || valores[i] < maisBarata) {
                    maisBarata = valores[i];
                }
                valorTotalGeral += valores[i];
                if (sexos[i] == 'm') {
                    valorH += valores[i];
                } else {
                    valorF += valores[i];
                }
                break;
            }
        } while (1);

        // Quantidade de itens
        do {
            printf("Digite a quantidade de itens no pedido: ");
            scanf("%d", &quantidadeItens[i]);

            if (quantidadeItens[i] < 0) {
                printf("Não pode cadastrar uma quantidade de itens negativa. Informe outra quantidade.\n");
            } else {
                quantidadeItensTotal += quantidadeItens[i]; 
                break;
            }
        } while (1);

        printf("Pedido cadastrado com sucesso!\n");
        printf("\n------------------------------------------------------\n\n");
    }

    char resposta = 's';
    int opcao = 0;

    while (opcao != 3 && resposta != 'n') {
        printf("\n------------------------------------------------------\n\n");
        printf("\n\t\t\t\t\t\tMenu\n\n");
        printf("1 - Pesquisar um pedido por código\n");
        printf("2 - Ver informações de todos os pedidos\n");
        printf("3 - Encerrar o programa\n\n");
        printf("Qual das opções acima deseja fazer? ");
        scanf("%d", &opcao);
        printf("\n------------------------------------------------------\n\n");

        switch (opcao) {
           case 1:
           printf("Digite o código do pedido que deseja pesquisar: ");
           scanf("%d", &codigoPesquisa);

           int encontrado = 0;

           for (int i = 0; i < numPedidos; i++) {
               if (codigos[i] == codigoPesquisa) {
                   printf("Pedido %d:\n", codigos[i]);
                   printf("Sexo do Cliente: %c\n", sexos[i]);
                   printf("Valor do Pedido: %.2f\n", valores[i]);
                   printf("Quantidade de Itens: %d\n",quantidadeItens[i] );
                   encontrado = 1;
                   break; 
               }
           }

           if (!encontrado) {
               printf("Nenhum pedido encontrado com o código %d.\n", codigoPesquisa);
           }
           break;


            case 2:

                printf("Digite um valor para exibir pedidos acima deste valor: ");
                scanf("%f", &valorLimite);

                int pedidosAbaixo40 = 0;

                for (int i = 0; i < numPedidos; i++) {
                    if (valores[i] < valorLimite) {
                        pedidosAbaixo40++;
                    }
                }

                printf("Quantidade de pedidos abaixo de %.2f reais: %d\n", valorLimite, pedidosAbaixo40);
                printf("Quantidade de compradoras mulheres: %d\n", qtdF);
                printf("Valor total comprado pelos homens: %.2f\n", valorH);
                printf("Valor médio de um pedido: %.2f\n", valorTotalGeral / numPedidos);
                printf("Quantidade total de itens vendidos: %d\n", numPedidos);
                int quantidadeItensNaoInformado = 0;
                for (int i = 0; i < numPedidos; i++) {
                    if (sexos[i] == 'n') {
                        quantidadeItensNaoInformado += quantidadeItens[i];
                    }
                }
                printf("Quantidade de itens comprados por pessoas que preferiram não falar o sexo: %d\n", quantidadeItensNaoInformado);

                int codigoMaisVendido[11] = {0};
                for (int i = 0; i < numPedidos; i++) {
                    if (codigos[i] >= 1 && codigos[i] <= 10) {
                        codigoMaisVendido[codigos[i]]++;
                    }
                }

                int codigoMaisVendidoIndex = 1;
                for (int i = 2; i <= 10; i++) {
                    if (codigoMaisVendido[i] > codigoMaisVendido[codigoMaisVendidoIndex]) {
                        codigoMaisVendidoIndex = i;
                    }
                }
                printf("Código mais vendido: %d\n", codigoMaisVendidoIndex);
                break;

            case 3:
                printf("Programa encerrado.\n");
                break;

            default:
                printf("Opção inválida. Tente novamente.\n");
        }

        if (opcao != 3) {
            printf("Deseja retornar ao menu principal? (s/n): ");
            scanf(" %c", &resposta);
        }
    }

    return 0;
}
