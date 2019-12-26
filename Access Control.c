/* -- Observações:

	<adicione neste espaço>

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

//Declaração das constantes que formam a matriz do teatro UNIP : cadeiras[FILEIRAS][COLUNAS]
#define FILEIRAS 30
#define COLUNAS 20

//------------------------------Procedimentos e funções------------------------------
//Imprimi borda horizontal
void bordas(){
	printf("__________________________________________________________________________________________________");
}

//Imprime cabeçalho
void menuNavegacao(char titulo[]){
	printf("\n\n\t\\\\\\\\\\>  \"AC - Access Control - Teatro UNIP\" >%s  <\\\\\\\\\\\n", titulo);
	bordas();
}

//Imprimi rodapé e comando de saída "Pressione qualquer tecla para continuar"
void rodapeSaida(){
	printf("\n\n");
	bordas();
	printf("\n\n\n\n ");
	system("pause");
	system("cls");
}

//Tela 2  : Informações do Evento
void infEvento(char horarioEvento[]){
	char titulo[] = "Informacoes";
	
	bordas();
	menuNavegacao(titulo);
	printf("\n\n\n Informacoes do evento:\n\n ");
	printf("\n >>> Tema: Direitos Humanos \"Feminicidio\"\n");
	printf("\n >>> Palestrante: Secretario \"Marcos Rodrigues\" - ONU Brasil\n");
	printf("\n >>> Data: "); system ("date /t");
	printf("\n *O teatro dispoe de %d lugares (%d Fileiras e %d Colunas) - Sendo que a numeracao\n", FILEIRAS * COLUNAS, FILEIRAS, COLUNAS);
	printf("     inicia-se em 0, temos: Fileiras (de 0 ate %d) e Colunas (de 0 ate %d)\n\n", FILEIRAS - 1, COLUNAS - 1); bordas();
	printf("\n\n\n >>> Informe o horario de inicio:  *Formato 00:00");
	printf("\n\n\n > ");
	gets (horarioEvento);
    system("cls");
	bordas();
	menuNavegacao(titulo);
	printf("\n\n\n\n >>> Carregamento das informacoes concluido!\n");
	rodapeSaida();
}

//Confirma que o teatro está vazio: a matriz cadeiras[FILEIRAS][COLUNAS] não trará lixo de memória
void zeraTeatro(int cadeiras[][COLUNAS]){
	int lin, col;

	for(lin = 0; lin < FILEIRAS; lin++){
		for(col = 0; col < COLUNAS; col++){
			cadeiras[lin][col] = 0;
		}
	}
}

//Verifica se a cadeira desejada existe
int cadeiraInexistente(int lin, int col){
	int erro;

	if (lin >= FILEIRAS || col >= COLUNAS || lin < 0 || col < 0){
		printf("\n\n\n\a-------------- Erro, cadeira inexistente! --------------\n\n");
		bordas();
		printf("\n\n\n\n ");
		system("pause");
		system("cls");
		return erro = 1;
	}else return erro = 0;
}

//Emite Ticket de confirmação após a reserva
void emitiTicket(int lin, int col, int cadeiras[][COLUNAS], char horarioEvento[]){
	char titulo[] = "Menu de opcoes >Emissao ticket";
	
	system("cls");
	menuNavegacao(titulo);
	printf("\n\n\n | Ticket :\n");
	printf("\n\n | Data - - - - - - - - - - - "); system ( "date /t" );
	printf("\n | Horario de inicio - - - - - %s", horarioEvento);
	printf("\n\n | Numero do assento - - - - -  %d%d : Fileira %d \\ Coluna %d\n\n\n", lin, col, lin, col);
	bordas();
}

//Realiza o sorteio de brindes entre participantes
void sorteiaBrindes(int cadeiras[][COLUNAS], int ocupacao[]){
	int i, op, qtdBrindes, lin, col;
	char titulo[] = "Sorteio";
	
	menuNavegacao(titulo);
	if ((ocupacao[1] + ocupacao[3]) == 0){
		printf("\n\n\n\a Erro, nao a participantes (*Nao VIP) no teatro!");
		rodapeSaida();
		return;		
	}
	
	printf("\n\n\n A palestra acabou?\n\n\n");
	printf(" [1] Sim\n\n");
	printf(" [2] Nao\n");
	printf("\n\n\n > ");
	scanf(" %d", &op);
	system("cls");
	
	if (op == 1 ){
		menuNavegacao(titulo);
		printf("\n\n\n- - - - - - - - - - - *Apenas participantes (*Nao VIP) concorrem\n\n");
		printf("\n Quantos brindes deseja sortear?\n\n\n");
		printf("\n\n > ");
		scanf(" %d", &qtdBrindes);
		system("cls");
		menuNavegacao(titulo);
		printf("\n\n\n Aguarde... Os premiados sao:\n\n\n");
  
		/* srand(time(NULL)) -- Objetiva inicializar o gerador de números aleatórios com o valor da função time(NULL).
		Desta forma, a cada execução o valor da "semente" será diferente. */
		srand(time(NULL));
	
		//Realiza o sorteio
		for (i = 0; i < qtdBrindes; i++){
		SORTEAR:
			lin = rand() % FILEIRAS;
			if (lin > 1){
				col = rand() % COLUNAS;
					if (cadeiras[lin][col] != 0){
						printf(" %d premiado: Numero do assento - - - - -  %d%d : Fileira %d \\ Coluna %d\n\n", i + 1, lin, col, lin, col);
					}else goto SORTEAR;
			}else goto SORTEAR;	
		}
		rodapeSaida();
	}else if (op == 2){
		menuNavegacao(titulo);
		printf("\n\n\n\a Erro, o sorteio so podera ser realizado ao fim da palestra!");
		rodapeSaida();
		return;
	}
	else{
		system("cls");
			menuNavegacao(titulo);
			printf("\n\n\n\n\a-------------- Erro, a opcao '%d' requerida nao existe! --------------\n\n", op); 
			rodapeSaida();
	}
}

//Imprimi como esta a ocupacao do teatro UNIP
void ocupacaoTotal(int ocupacao[]){
	char titulo[] = "Menu de opcoes >Ocupacao";
	
	menuNavegacao(titulo);
	printf("\n\n\n Detalhes da ocupacao:\n\n\n");
	printf(" -- Quantidade de participantes cadastrados *nao VIP: %d\n\n", ocupacao[1] + ocupacao[3]);
	printf(" -- Quantidade de Professores e Convidados *VIP: %d \n\n\n", ocupacao[5]);
	printf(" -- Ocupacao total: %d", ocupacao[1] + ocupacao[3] + ocupacao[5]);	
	rodapeSaida();
}

//Verifica se a cadeira desejada está disponível para reserva
void veDisposicao(int cadeiras[][COLUNAS]){
	int lin, col, op, erro;
	char titulo[] = "Menu de opcoes >Ver disposicao";
	
	menuNavegacao(titulo);
	printf("\n\n\n Escolha uma opcao:\n\n\n");
	printf(" [1] Realizar consulta\n\n");
	printf(" [2] Imprimir lista dos lugares disponiveis\n");
	printf("\n\n\n > ");
	scanf(" %d", &op);
	system("cls");

	switch(op){
		case 1:
			menuNavegacao(titulo);
			printf("\n\n\n Informe por qual lugar procura: \n\n");
			printf("\n\n Fila: ");
			scanf(" %d", &lin);
			printf("\n\n Coluna: ");
			scanf(" %d", &col);
			erro = cadeiraInexistente(lin, col);
			if (erro == 0){
				if (cadeiras[lin][col] == 0) printf("\n\n\n >>> Cadeira disponivel!");
				else printf("\n\n\n >>> Cadeira ocupada!");
			rodapeSaida();
			}break;
		case 2:
			menuNavegacao(titulo);
			printf("\n\n\n Lista dos lugares disponiveis:\n\n Posicao:\n\n");
			for(lin = 0; lin < FILEIRAS; lin++){
				for(col = 0; col < COLUNAS; col++){
					if (cadeiras[lin][col] == 0) printf(" -- Fileira %d - Coluna %d\n", lin, col);
				} 
			}rodapeSaida(); break;
		default :	
			menuNavegacao(titulo);
			printf("\n\n\n\n\a-------------- Erro, a opcao '%d' requerida nao existe! --------------\n\n", op);
			rodapeSaida();
	}
}

//Reserva-Cadastra participantes: não VIP
void reserva(int cadeiras[][COLUNAS], char horarioEvento[], int ocupacao[]){
	int op, lin, col, erro;
	char titulo[] = "Menu de opcoes >Reservar cadeira";

	menuNavegacao(titulo);
	printf("\n\n\n Possui necessidades especiais?\n\n\n");
	printf(" [1] Sim\n\n");
	printf(" [2] Nao\n");
	printf("\n\n\n > ");
	scanf(" %d", &op);
	system("cls");

	switch (op){
		case 1:
			menuNavegacao(titulo);
			printf("\n\n\n Informe o lugar que deseja reservar: *As fileiras 0 e 1 sao VIP\n\n");
			printf("\n\n Fila: ");
			scanf(" %d", &lin);
			printf("\n\n Coluna: ");
			scanf(" %d", &col);
			erro = cadeiraInexistente(lin, col);
			if (erro == 0){	
				if (lin > 1){
					if (ocupacao[1] < ocupacao[0]){
						if (cadeiras[lin][col] == 0){
							cadeiras[lin][col] = 2;
							emitiTicket(lin, col, cadeiras, horarioEvento);
							ocupacao[1]++;
							printf("\n\n\n >>> Obrigado pela reserva!");
						}else printf("\n\n\n >>> Cadeira ocupada!");
					}else printf("\n\n\n\a >>> Erro, nao ha mais vagas disponiveis para portadores de necessidades especiais!");	
				}else printf("\n\n\n\a >>> Cadeira VIP, apenas para professor ou convidado!");	
				rodapeSaida();	
			}break;
		case 2:
			menuNavegacao(titulo);
			printf("\n\n\n Informe o lugar que deseja reservar: *As fileiras 0 e 1 sao VIP\n\n");
			printf("\n\n Fila: ");
			scanf(" %d", &lin);
			printf("\n\n Coluna: ");
			scanf(" %d", &col);
			erro = cadeiraInexistente(lin, col);
			if (erro == 0){
				if (lin > 1){
					if (ocupacao[3] < ocupacao[2]){
						if (cadeiras[lin][col] == 0){
							cadeiras[lin][col] = 1;
							emitiTicket(lin, col, cadeiras, horarioEvento);
							ocupacao[3]++;
							printf("\n\n\n >>> Obrigado pela reserva!");
						}else printf("\n\n\n >>> Cadeira ocupada!");
					}else printf("\n\n\n\a >>> Erro, nao ha mais vagas disponiveis para nao portadores de necessidades especiais!");
				}else printf("\n\n\n\a >>> Cadeira VIP, apenas para professor ou convidado!");	
				rodapeSaida();
			}break;
		default :
			menuNavegacao(titulo);
			printf("\n\n\n\n\a-------------- Erro, a opcao '%d' requerida nao existe! --------------\n\n", op);
			rodapeSaida();
	}
}

//Reserva-Cadastra participantes: VIP
void reservaVIP(int cadeiras[][COLUNAS], char horarioEvento[], int ocupacao[]){
	int lin, col, erro;
	char titulo[] = "Menu de opcoes >Reservar cadeira VIP";

	menuNavegacao(titulo);	
	printf("\n\n\n Informe o lugar que deseja reservar: *As fileiras 0 e 1 sao VIP\n\n");
	printf("\n\n Fila: ");
	scanf(" %d", &lin);
	printf("\n\n Coluna: ");
	scanf(" %d", &col);
	erro = cadeiraInexistente(lin, col);
	if (erro == 0){
		if (lin <= 1){
			if (ocupacao[5] < ocupacao[4]){
				if (cadeiras[lin][col] == 0){
					cadeiras[lin][col] = 1;
					emitiTicket(lin, col, cadeiras, horarioEvento);
					ocupacao[5]++;
					printf("\n\n\n >>> Obrigado pela reserva!");
				}else printf("\n\n\n >>> Cadeira ocupada!");
			}else printf("\n\n\n\a >>> Erro, nao ha mais vagas VIPs disponiveis!"); 
		}else printf("\n\n\n\a >>> Cadeira nao VIP, apenas para participantes!");
		rodapeSaida();
	}
}

//Cancela reserva-cadastro: VIP e não VIP
void cancela(int cadeiras[][COLUNAS], int ocupacao[]){
	int op, aux, lin, col, erro;
	char titulo[] = "Menu de opcoes >Cancelar reserva";
	
	menuNavegacao(titulo);		
	printf("\n\n\n Informe o lugar que deseja cancelar:\n\n");
	printf("\n\n Fila: ");
	scanf(" %d", &lin);
	printf("\n\n Coluna: ");
	scanf(" %d", &col);
	erro = cadeiraInexistente(lin, col);
	if (erro == 0){	
		if (lin <=1){
			if (cadeiras[lin][col] == 1){
				cadeiras[lin][col] = 0;
				printf("\n\n\n >>> Reserva cancelada!");
				ocupacao[5]--;
			}else printf("\n\n\n\a >>> Esta cadeira ja esta disponivel!"); 
		}else if(cadeiras[lin][col] == 2){
				cadeiras[lin][col] = 0;
				printf("\n\n\n >>> Reserva cancelada!");
				ocupacao[1]--;
			}else if (cadeiras[lin][col] == 1){
				cadeiras[lin][col] = 0;
				printf("\n\n\n >>> Reserva cancelada!");
				ocupacao[3]--;
			}else printf("\n\n\n\a >>> Esta cadeira ja esta disponivel!");	
		rodapeSaida();
	}
}


//------------------------------Função principal------------------------------
int main(){ 
	/* -- Descrição das variáveis:

	op -- Guarda a opção requerida

	cadeiras[FILEIRAS][COLUNAS] -- Matriz das cadeiras do teatro UNIP

	ocupacao[] -- Vetor que gerencia a ocupação do teatro UNIP onde:
	{
	ocupacao[0] = Qtd de cadeiras reservadas aos portadores de necessidades especiais
	ocupacao[1] = Qtd de cadeiras ocupadas por portadores de necessidades especiais
	ocupacao[2] = Qtd de cadeiras reservadas aos que não são portadores de necessidades especiais
	ocupacao[3] = Qtd de cadeiras ocupadas pelos que não são portadores de necessidades especiais
	ocupacao[4] = Qtd de cadeiras reservadas para os professores e convidados: VIP
	ocupacao[5] = Qtd de cadeiras ocupadas pelos professores e convidados: VIP
	} */


	//Declaração das variáveis
	int op, cadeiras[FILEIRAS][COLUNAS], ocupacao[5];
	char horarioEvento[6], titulo[] = "Menu de opcoes";

	//Inicia vetor ocupação[] - descrição acima
	ocupacao[0] = (FILEIRAS * COLUNAS - 2 * COLUNAS) * 0.05;
	ocupacao[1] = 0;
	ocupacao[2] = (FILEIRAS * COLUNAS - 2 * COLUNAS) - ocupacao[0];
	ocupacao[3] = 0;
	ocupacao[4] = 2 * COLUNAS;
	ocupacao[5] = 0;
	
	/* -- Espaço adequado para gerenciar testes:
	
	Ex.: ocupacao[0] = "28" -- Para ver se o sistema imprime o aviso "Erro, nao ha mais vagas disponiveis para portadores de necessidades especiais!" 
	
		ocupacao[3] = "532" -- Para ver se o sistema imprime o aviso "Erro, nao ha mais vagas disponiveis para nao portadores de necessidades especiais!"
	
		ocupacao[5] = "40" -- Para ver se o sistema imprime o aviso "Erro, nao ha mais vagas VIPs disponiveis!" */
	
	//------------------------------Tela 1  : Bem vindo
	bordas();
	printf("\n\n\n\t\t\\\\\\\\\\>  Bem vindo ao \"AC - Access Control - Teatro UNIP\"  <\\\\\\\\\\\n\n\n");
	bordas();
	printf("\n\n\n\n  *Dica de uso: \n\n  O sistema utiliza na maioria dos casos a entrada de numeros para o direcionamento as\n  opcoes requeridas, caso possivel, utilize o teclado numerico para melhor experiencia.\n\n\n\n");
	bordas();
	printf("\n\n\n\n  ");
	system("pause");
	system("cls");
	
	//------------------------------Tela 2  : Informações do Evento
	infEvento(horarioEvento);

	//Confirma que o teatro está vazio - a matriz cadeiras[FILEIRAS][COLUNAS] não trará lixo de memória
	zeraTeatro(cadeiras);

	//------------------------------Tela 3: Menu de opções
	do{
		menuNavegacao(titulo);
		printf("\n\n\n Escolha uma opcao:\n\n\n");
		printf(" [1] Ver disposicao das cadeiras - - - - - - - - - - -  (Se encontra reservada ou nao)\n\n");
		printf(" [2] Cadastrar participante - - - - - - - - - - - - - - (Nao VIP)\n\n");
		printf(" [3] Cadastrar professor ou convidado - - - - - - - - - (VIP)\n\n");
		printf(" [4] Cancelar reserva\n\n");
		printf(" [5] Realizar sorteio - - - - - - - - - - - - - - - - - (Apos a palestra)\n\n");
		printf(" [6] Imprimir ocupacao\n\n");
		printf(" [0] Sair\n");
		printf("\n\n\n > ");
		scanf(" %d", &op);
		system("cls");

		switch (op){
			case 1:
				veDisposicao(cadeiras); break; //Verifica se a cadeira desejada está disponível para reserva
			case 2:
				reserva(cadeiras, horarioEvento, ocupacao); break; //Reserva-Cadastra participantes: não VIP
			case 3:
				reservaVIP(cadeiras, horarioEvento, ocupacao); break; //Reserva-Cadastra participantes: VIP
			case 4:
				cancela(cadeiras, ocupacao); break; //Cancela reserva-cadastro: VIP e não VIP
			case 5:
				sorteiaBrindes(cadeiras, ocupacao); break; //Realiza sorteio de brindes (após a palestra)
			case 6:
				ocupacaoTotal(ocupacao); break; //Imprimi detalhes da ocupação do teatro UNIP
			case 0:
				menuNavegacao(titulo);
				printf("\n\n\n\n Voce escolheu sair... tem certeza?\n\n\n");
				printf(" [1] Cancelar\n\n");
				printf(" [0] Sair\n");
				printf("\n\n\n > ");
				scanf(" %d", &op);
				if (op == 1 ) rodapeSaida();
				else if (op == 0) printf("\n\n\n\n\a-------------- Fim da execucao! --------------\n\n\n"); 
				else{
					system("cls");
					menuNavegacao(titulo);
					printf("\n\n\n\n\a-------------- Erro, a opcao '%d' requerida nao existe! --------------\n\n", op); 
					rodapeSaida();
				}break;
			default :
				if (op != 0){
					menuNavegacao(titulo);
					printf("\n\n\n\n\a-------------- Erro, a opcao '%d' requerida nao existe! --------------\n\n", op);
					rodapeSaida();
				}
		}

		if (op != 0 ) system("cls");

	}while (op != 0);

	return 0;
}
