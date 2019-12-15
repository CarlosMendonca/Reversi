/*******************************************************************/
/**                                                               **/
/**   Carlos Henrique Esteves Mendonça           3729190          **/
/**   Exercício-Programa 03                                       **/
/**   Professor: Carlos Eduardo Ferreira                          **/
/**   Turma: 2                                                    **/
/**                                                               **/
/*******************************************************************/

/*Todas as variáveis deste EP, para facilitar na hora de executar
  um debug, foram nomeadas com as iniciais da função, exceto no
  caso da função main().*/

#include <stdio.h>

/*Bibliotecas stdlib.h e time.h são necessárias para executar a
  escolha de jogada aleatória.                                     */
#include <stdlib.h>
#include <time.h>

/*As matrizes tabuleiro usadas são do tipo int e por isso já
  recebem constantes numéricas que auxiliam no entendimento do
  código.                                                          */
#define FALSO 0
#define VERDADEIRO 1
#define ESTRELA -1
#define VAZIO 0
#define BOLA 1

/*Constante utilizada para a gravação e leitura de arquivos
  conforme instruções do EP2.                                      */
#define POTHELO "pothelo.txt"

/*Função void que recebe o endereço da matriz tab da função main()
  e conforme o decimal guardado (-1, 0 ou 1) imprime na tela um ' '
  (espaço vazio), um '*' ou uma 'o'.                               */
void imprime_tab(int it_tab[8][8]) {
	int it_i = 0, it_j, it_lin = 1;
	printf("\n   | A | B | C | D | E | F | G | H |");
	while(it_i <= 7) {
		it_j = 0;
		printf("\n---+---+---+---+---+---+---+---+---+");
		printf("\n %d |",it_lin);
		it_lin ++;
		while(it_j <= 7) {
			switch(it_tab[it_i][it_j]) {
			case ESTRELA:
				printf(" * |");
				break;
			case VAZIO:
				printf("   |");
				break;
			case BOLA:
				printf(" o |");
				break;
			}
			it_j ++;
		}
		it_i ++;
	}
}

/*Função void que ao ser chamada na main() imprime um texto de
  ajuda para o usuário que explica o programa e define as regras
  sendo as mesmas do Othello (ou Reversi) derivados do Go!.        */
void imprime_ajuda() {
	printf("\n\n\n\n\n\n\n\n\nAJUDA: Bem vindo ao Pothelo de MAC-2166, EP3 de 2002.\n\nPara jogar, digite uma letra de 'a-h' seguida de um numero de '1-8' e pressione\n<ENTER>. Para sair do Pothelo, digite 't', para reiniciar o jogo 'z', para\nsalvar 's', para restaurar um jogo antigo 'r' e para sugestao de jogada 'u',\ntodos seguidos de <ENTER>.\n\nAs regras do jogo sao as originais do Othello ou Reversi, derivados do Go!. Seu\nobjetivo e capturar o maximo de pecas do inimigo sem perder as\
 suas. Boa sorte!\n\nEste jogo foi criado por Carlos Henrique Esteves Mendonca\ncarlos.henrique@poli.usp.br\n");
}

/*Função void que recebe a matriz tab de main() e zera a matriz em
  todas as posições, que neste programa representa um espaço vazio
  e ao final define as quatro posições centrais com o movimento
  incial do jogo.                                                  */
void novo_tab(int nt_tab[8][8]) {
	int nt_i = 0, nt_j;
	while(nt_i <= 7) {
		nt_j = 0;
		while(nt_j <= 7) {
			nt_tab[nt_i][nt_j] = 0;
			nt_j ++;
		}
		nt_i ++;
	}
	nt_tab[3][3] = ESTRELA;
	nt_tab[4][4] = ESTRELA;
	nt_tab[3][4] = BOLA;
	nt_tab[4][3] = BOLA;
}

/*Função void que recebe a matriz valor de main() e preenche esta
  matriz com os valores de cada poisção de um tabuleiro de Othello.
  Estes valores foram definidos pelo autor e faz parte da
  estratégia do jogo explicada mais tarde.                         */
void novo_valor(int nv_valor[8][8]) {
	int nv_i = 0, nv_j, nv_aux1 = 1, nv_aux2 = 6, nv_aux3 = -1;

	//Inicialização da matriz valor com aplicação dos números 1 e
	//depois dos valores de canto.
	nv_i = 0;
	while(nv_i <= 7) {
		nv_j = 0;
		while(nv_j <= 7) {
			nv_valor[nv_i][nv_j] = 1;
			nv_j ++;
		}
		nv_i ++;
	}

	nv_valor[0][0] = 50;
	nv_valor[0][7] = 50;
	nv_valor[7][0] = 50;
	nv_valor[7][7] = 50;

	while(nv_aux3 <= 5) {
		nv_valor[0][nv_aux1] = nv_aux3;
		nv_valor[nv_aux1][0] = nv_aux3;
		nv_valor[7][nv_aux1] = nv_aux3;
		nv_valor[nv_aux1][7] = nv_aux3;

		nv_valor[0][nv_aux2] = nv_aux3;
		nv_valor[nv_aux2][0] = nv_aux3;
		nv_valor[7][nv_aux2] = nv_aux3;
		nv_valor[nv_aux2][7] = nv_aux3;

		nv_aux1 ++;
		nv_aux2 --;
		nv_aux3 += 3;
	}

	nv_valor[1][1] = -10;
	nv_valor[1][6] = -10;
	nv_valor[6][1] = -10;
	nv_valor[6][6] = -10;
}

/*Função void que recebe a matriz tab e o jogador da vez de main()
  e abrindo o arquivo pothelo.txt (ou criando-o) imprime o jogador
  e o valor de cada posição do tabuleiro. É importante notar que
  como o formato da matriz do EP de MAC é diferente deste há uma
  conversão para que este aceite arquivos de jogo do outro.        */
void salva_jogo(int sj_tab[8][8], int sj_computador) {
	int sj_i = 0, sj_j = 0, sj_posicao = 0;
	FILE *pothelo;

	pothelo = fopen(POTHELO,"w");
	if(sj_posicao == 0) {
		switch(sj_computador) {
			case ESTRELA:
				fprintf(pothelo,"o");
				break;
			case BOLA:
				fprintf(pothelo,"*");
				break;
		}
		sj_posicao ++;
	}
	while(sj_i <= 7) {
		sj_j = 0;
		while(sj_j <= 7) {
			switch(sj_tab[sj_i][sj_j]) {
				case ESTRELA:
					fprintf(pothelo,"*");
					break;
				case VAZIO:
					fprintf(pothelo," ");
					break;
				case BOLA:
					fprintf(pothelo,"o");
					break;
			}
			sj_j ++;
		}
		sj_i ++;
	}
	fclose(pothelo);
}

/*Função int que recebe a matriz tab e o jogador da vez de main()
  e preenche a matriz conforme as posições do arquivo pothelo.txt.
  É importante notar que como a matriz do EP de MAC é do tipo char
  e a deste EP do tipo int, é feita uma conversão na hora do
  preenchimento da matriz. A função retorna 0 se a operação foi bem
  sucedida (arquivo existia) e retorna 1 se o arquivo não existir. */
int recarrega_jogo(int rj_tab[8][8], int *rj_computador) {
	int rj_i = 0, rj_j, rj_posicao = 0;
	char rj_vez, rj_peca;
	FILE *pothelo;

	pothelo = fopen(POTHELO,"r");
	if(pothelo == NULL)
		return(1);
	if(rj_posicao == 0) {
		fscanf(pothelo,"%c",&rj_vez);
		rj_posicao ++;
	}
	while(rj_i <= 7) {
		rj_j = 0;
		while(rj_j <= 7) {
			fscanf(pothelo,"%c",&rj_peca);
			switch(rj_peca) {
				case '*':
					rj_tab[rj_i][rj_j] = -1;
					break;
				case ' ':
					rj_tab[rj_i][rj_j] = 0;
					break;
				case 'o':
					rj_tab[rj_i][rj_j] = 1;
					break;
			}
			rj_j ++;
		}
		rj_i ++;
	}
	switch(rj_vez) {
		case '*':
			*rj_computador = BOLA;
			break;
		case 'o':
			*rj_computador = ESTRELA;
	}
	fclose(pothelo);
	return(0);
}

/*Função int que recebe as coordenadas linha e coluna, a matriz
  tabuleiro, a matriz valores do tabuleiro, o jogador da vez, a
  direção x e y que deve procurar para encontrar uma jogada válida
  e o parâmetro muda, que especifica se deve-se capturar as peças
  (mudando-as para o valor do jogador da vez) ou se é apenas um
  teste e as peças devem permanecer com seu valor original. A
  função retorna o valor da jogada feita pelo usuário em função de
  quantas peças ele capturou e em função da matriz de valoes de
  cada posição do tabuleiro.*/
int verifica_peca(int vp_i, int vp_j, int vp_tab[8][8], int vp_valor[8][8], int vp_jogador, int vp_dir_x, int vp_dir_y, int vp_muda) {
	int vp_valor_pecas, vp_i_aux, vp_j_aux, vp_peca_final;
	vp_valor_pecas = 0;
	vp_i_aux = vp_i;
	vp_j_aux = vp_j;
	vp_peca_final = FALSO;

	vp_i = vp_i + vp_dir_y;
	vp_j = vp_j + vp_dir_x;
	while(vp_i >= 0 && vp_i <= 7 && vp_j >= 0 && vp_j <= 7 && vp_peca_final == FALSO) {
		if(vp_tab[vp_i][vp_j] == vp_jogador) {
			vp_peca_final = VERDADEIRO;
		}
		else {
			if(vp_tab[vp_i][vp_j] == VAZIO) {
				break;
			}
			else {
				vp_valor_pecas += vp_valor[vp_i][vp_j];
			}
		}
		vp_i = vp_i + vp_dir_y;
		vp_j = vp_j + vp_dir_x;
	}
	if(vp_peca_final == VERDADEIRO) {
		if(vp_muda == VERDADEIRO) {
			while( vp_i != vp_i_aux || vp_j != vp_j_aux) {
				vp_i = vp_i - vp_dir_y;
				vp_j = vp_j - vp_dir_x;
				vp_tab[vp_i][vp_j] = vp_jogador;
			}
		}
		vp_valor_pecas += vp_valor[vp_i_aux][vp_j_aux];
		return vp_valor_pecas;
	}
	else
		return 0;
}


/*Função int que recebe as coordenadas da jogada, a matriz
  tabuleiro, o jogador da vez, o parâmetro muda que é diretamente
  passado para a função verifica_pecas() e a matriz valor do
  tabuleiro. A função devolve o valor da jogada da jogada do
  usuário somando o valor que a função verifica_pecas() retorna.
  Assim, tem-se o valor da jogada em todas as direções. Ela retorna
  0 se a jogada não captura nenhuma peça, o que inclui a
  possibilidade do jogador tentar jogar em uma casa ocupada.*/
int verifica_jogada(int vj_i, int vj_j, int vj_tab[8][8], int vj_jogador, int vj_muda, int vj_valor[8][8]) {
	int vj_valor_pecas, vj_oponente;
	vj_valor_pecas = 0;
	vj_oponente = vj_jogador*-1;

	if(vj_tab[vj_i][vj_j] != VAZIO)
		return(0);

	if(vj_j > 0){
		//Verifica diagonal superior esquerda.
		if(vj_i > 0)
			if(vj_tab[vj_i-1][vj_j-1] == vj_oponente)
				vj_valor_pecas += verifica_peca(vj_i,vj_j,vj_tab,vj_valor,vj_jogador,-1,-1,vj_muda);
		//Verfica esquerda.
		if(vj_tab[vj_i][vj_j-1] == vj_oponente)
			vj_valor_pecas += verifica_peca(vj_i,vj_j,vj_tab,vj_valor,vj_jogador,-1,0,vj_muda);
		//Verifica diagol inferior esquerda.
		if(vj_i < 7)
			if(vj_tab[vj_i+1][vj_j-1] == vj_oponente)
				vj_valor_pecas += verifica_peca(vj_i,vj_j,vj_tab,vj_valor,vj_jogador,-1,1,vj_muda);
	}

	//Verifica posição superior.
	if(vj_i > 0)
		if(vj_tab[vj_i-1][vj_j] == vj_oponente)
			vj_valor_pecas += verifica_peca(vj_i,vj_j,vj_tab,vj_valor,vj_jogador,0,-1,vj_muda);

	//Verifica posição inferior.
	if(vj_i < 7)
		if(vj_tab[vj_i+1][vj_j] == vj_oponente)
			vj_valor_pecas += verifica_peca(vj_i,vj_j,vj_tab,vj_valor,vj_jogador,0,1,vj_muda);

	if(vj_j < 7){
		//Verifica diagonal superior direita.
		if(vj_i > 0)
			if(vj_tab[vj_i-1][vj_j+1] == vj_oponente)
				vj_valor_pecas += verifica_peca(vj_i,vj_j,vj_tab,vj_valor,vj_jogador,1,-1,vj_muda);
		//Verifica direita.
		if(vj_tab[vj_i][vj_j+1] == vj_oponente)
			vj_valor_pecas += verifica_peca(vj_i,vj_j,vj_tab,vj_valor,vj_jogador,1,0,vj_muda);
		//Verifica diagonal inferior direita.
		if(vj_i < 7)
			if(vj_tab[vj_i+1][vj_j+1] == vj_oponente)
				vj_valor_pecas += verifica_peca(vj_i,vj_j,vj_tab,vj_valor,vj_jogador,1,1,vj_muda);
	}
	return vj_valor_pecas;
}

/*Função int que recebe a matriz tabuleiro, o jogador da vez, as
  coordenadas i e j e a matriz valor do tabuleiro. Esta função é
  parte da estratégia do jogo. Ela recebe cada jogada possível e,
  copia ela para um tabuleiro auxiliar e calcula quantas opções de
  jogada aquela deixará para o oponente. A idéia é realizar a
  jogada que deixo o mínimo possível de opções de captura para o
  oponente, sendo tudo isso calculado em função da matriz valor do
  do tabuleiro. Desta forma a função devolve o valor total de
  "pontos" que estarão disponíveis para o adversário e cabe ao
  programa escolher a jogada que deixe o mínimo possível.*/
int valor_oponente(int vo_tab1[8][8], int vo_jogador, int vo_i, int vo_j, int vo_valor[8][8]) {
	int vo_tab2[8][8], vo_resultado, vo_i_aux, vo_j_aux;
	vo_resultado = 0;

	vo_i_aux = 0;
	while(vo_i_aux <= 7) {
		vo_j_aux = 0;
		while(vo_j_aux <= 7) {
			vo_tab2[vo_i_aux][vo_j_aux] = vo_tab1[vo_i_aux][vo_j_aux];
			vo_j_aux ++;
		}
		vo_i_aux ++;
	}

	verifica_jogada(vo_i,vo_j,vo_tab2,vo_jogador,VERDADEIRO,vo_valor);

	vo_i_aux = 0;
	while(vo_i_aux <= 7) {
		vo_j_aux = 0;
		while(vo_j_aux <= 7) {
			vo_resultado += verifica_jogada(vo_i_aux,vo_j_aux,vo_tab2,vo_jogador*-1,FALSO,vo_valor);
			vo_j_aux ++;
		}
		vo_i_aux ++;
	}

	return(vo_resultado);
}


/*Função int que recebe a matriz tabuleiro, o jogador da vez, o
  endereço do placar das estrelas e do das bolas, a matriz que
 armazena a coordenada das melhores jogadas e a matriz de valores
 do tabuleiro. Esta é a mais importante e complexa função do EP mas
 que depende muito das outras. Ela retorna verdadeiro ou falso para
 o fim do jogo, que é calculado verificando quantas jogadas ainda o
 jogador pode fazer naquela rodada. Ao mesmo tempo que varre o
 tabuleiro em busca de jogadas possíveis, calcula o placar contando
 o número de estrelas e de bolas. Das jogadas possíveis que a
 função levantou, verifica-se cada uma delas para saber quantos
 "pontos" retornam em função da matriz de valores e, logo depois,
 subtrai-se desse valor a quantidade de "pontos" que as jogadas
 deixam para o oponente com a função valor_oponente(). Nesta
 contagem, os "pontos" conseguidos tem peso 2 e os "pontos" cedidos
 tem peso 1. Os pares de coordenadas que tem então o valor mais
 alto de "pontos" são armazenados para serem sorteados depois pela
 função main(). Esta é a estratégia do jogo.                       */
int analisa_jogo(int aj_tab[8][8], int aj_jogador, int *aj_estrelas, int *aj_bolas, int aj_melhor_ij[30][2], int aj_valor[8][8]) {
	int aj_i, aj_j, aj_invalidos, aj_vazios, aj_oponente, aj_valor_antigo, aj_valor_novo, aj2_i;
	aj_i = 0;
	aj_invalidos = 0;
	aj_vazios = 0;
	aj_oponente = aj_jogador*-1;

	//Nenhuma jogada teria valor menor que -1000, então este é o
	//valor de inicialização.
	aj_valor_antigo = -1000;
	aj_valor_novo = 0;
	*aj_estrelas = 0;
	*aj_bolas = 0;

	aj_i = 0;
	while(aj_i <= 7) {
		aj_j = 0;
		while(aj_j <= 7) {
			switch(aj_tab[aj_i][aj_j]) {
				case ESTRELA:
					*aj_estrelas = *aj_estrelas + 1;
					aj_j ++;
					break;
				case VAZIO:
					aj_vazios ++;

					//A função retorna o número de peças que podem
					//ser capturadas. Se for zero, a jogada é
					//inválida.
					if(verifica_jogada(aj_i,aj_j,aj_tab,aj_jogador,FALSO,aj_valor) == 0)
						aj_invalidos ++;
					else {
						aj_valor_novo = 2*verifica_jogada(aj_i,aj_j,aj_tab,aj_jogador,FALSO,aj_valor);
						aj_valor_novo -= valor_oponente(aj_tab,aj_jogador,aj_i,aj_j,aj_valor);
						if(aj_valor_novo >= aj_valor_antigo) {
							if(aj_valor_novo > aj_valor_antigo) {
								aj2_i = 0;
								while(aj2_i <= 29) {
									aj_melhor_ij[aj2_i][0] = -1;
									aj_melhor_ij[aj2_i][1] = -1;
									aj2_i ++;
								}
								aj2_i = 0;
								aj_valor_antigo = aj_valor_novo;
							}
							aj_melhor_ij[aj2_i][0] = aj_i;
							aj_melhor_ij[aj2_i][1] = aj_j;
							aj2_i ++;
						}
					}
					aj_j ++;
					break;
				case BOLA:
					*aj_bolas = *aj_bolas + 1;
					aj_j ++;
					break;
			}
		}
	aj_i ++;
	}

	if(aj_vazios == aj_invalidos)
		//Não há jogadas, fim de jogo verdadeiro.
		return(VERDADEIRO);
	else
		//Há jogadas, fim de jogo falso.
		return(FALSO);
}

/*Função int que recebe a matriz tabuleiro, o jogador da vez e a
  matriz de valores. A função retorna o código de cada opção pois o
  usuário pode sair do jogo, pedir para o computador jogar por ele,
  pedir sugestão de jogada, salvar o jogo, restaurar um jogo, pedir
  ajuda e reiniciar o jogo. Além disso pode jogar entrando com uma
  coordenada de coluna e linha.                                    */
int usuario(int u_tab[8][8], int u_usuario, int u_valor[8][8]) {
	char u_entrada_i, u_entrada_j;
	int u_jogada_valida = 0;

	//LOOP: Verifica se a jogada é valida.
	do {
		//LOOP: Verifica se u_entrada_j está no intervalo A-H (ou
		//a-h).
		do {
			if(u_usuario == ESTRELA)
				printf("\nVez das estrelas. ");
			else
				printf("\nVez das bolas. ");
			printf("Digite um comando ou jogada:\n[T]erminar | [Z]Novo Jogo | [S]alva | [R]ecarrega | [?]Ajuda | S[u]gestao |\n[(XY)] : ");
			scanf(" %c%c",&u_entrada_j,&u_entrada_i);

			//Transforma qualquer letra minúscula (97-122) para
			//maiúscula (65-90).
			if(u_entrada_j >= 97 && u_entrada_j <= 122)
				u_entrada_j -= 32;

			switch(u_entrada_j) {
				//O computador joga por você.
				case 'J':
					return(1);
					break;
				//O jogo termina.
				case 'T':
					return(2);
					break;
				//O jogo é salvo.
				case 'S':
					return(3);
					break;
				//O jogo é restaurado.
				case 'R':
					return(4);
					break;
				//O jogo reinicia.
				case 'Z':
					return(5);
					break;
				//Ajuda é mostrada.
				case '?':
					return(6);
					break;
				//Sugestão de jogada é mostrada.
				case 'U':
					return(7);
					break;
			}
			if(u_entrada_j < 65 || u_entrada_j > 72 || u_entrada_i < 49 || u_entrada_i > 56)
				printf("\nERRO: Jogada fora do tabuleiro.\n");
		} while (u_entrada_j < 65 || u_entrada_j > 72 || u_entrada_i < 49 || u_entrada_i > 56);

		if(verifica_jogada(u_entrada_i-49,u_entrada_j-65,u_tab,u_usuario,FALSO,u_valor) == 0)
			printf("\nERRO: Jogada invalida pois captura 0 pecas.\n");
		else {
			verifica_jogada(u_entrada_i-49,u_entrada_j-65,u_tab,u_usuario,VERDADEIRO,u_valor);
			u_jogada_valida = VERDADEIRO;
		}

	} while(u_jogada_valida == FALSO);
	return(0);
}

/*Função int. Esta função possui uma série de loops de forma que a
  interface funcione com o usuário por exemplo reiniciando o jogo
  ou mesmo restaurando-o, o que exige que processos sejam
  repetidos. Aqui também é implantada a jogada aleatória, de forma
  que se a matriz que armazena as melhores jogadas tenha mais de
  uma entrada o computador sorteia uma tanto para dar sugestão
  quanto para jogar conforme o esquema sugerido. A função organiza
  a impressão do tabuleiro, do placar e também do resultado do
  jogo, tenha ele terminado ou não.                                */
int main() {
	int tab[8][8], valor[8][8], estrelas, bolas, comando, fim_de_jogo[2], computador = BOLA, melhor_ij[30][2], i, ale, ale_fim;
	char comando_final;
	FILE *pothelo;

	novo_valor(valor);
	printf("\n\nBem vindo ao Pothelo.\n");

	//LOOP: Executa um jogo de cada vez. É reniciado quando o
	//usuário pede um novo jogo, e as posições iniciais são
	//zeradas.
	do {
		novo_tab(tab);
		computador = BOLA;
		imprime_tab(tab);

		//LOOP: Executado enquanto não é o fim do jogo para ambos
		//os jogadores.
		do {
			if(analisa_jogo(tab,computador*-1,&estrelas,&bolas,melhor_ij,valor) == FALSO) {
				fim_de_jogo[0] = FALSO;
				printf(" ESTRELAS %d x %d BOLAS\n",estrelas,bolas);

				//LOOP: Executado enquanto o usuário não pedir para
				//sair, não jogar, não pedir para que o computador
				//jogue ou o fim do jogo nesta rodada seja verdade
				//ao restaurar um jogo antigo.
				do {
					comando = usuario(tab,computador*-1,valor);
					switch(comando) {
						case 1:
							computador *= -1;
							comando = 0;
							break;
						case 3:
							salva_jogo(tab,computador);
							printf("\nJogo salvo.\n");
							comando = -1;
							break;
						case 4:
							if(recarrega_jogo(tab,&computador) == 1) {
								printf("\nERRO: Nenhum jogo salvo foi encontrado.\n");
								comando = -1;
							}
							else {
								if(analisa_jogo(tab,computador*-1,&estrelas,&bolas,melhor_ij,valor) == VERDADEIRO) {
									comando = 0;
									fim_de_jogo[0] = VERDADEIRO;
								}
								else {
									printf("\n\nJogo restaurado.\n");
									imprime_tab(tab);
									printf(" ESTRELAS %d x %d BOLAS\n",estrelas,bolas);
									comando = -1;
								}
							}
							break;
						case 6:
							imprime_ajuda();
							comando = -1;
							break;
						case 7:
							//Implementação da aleatoriedade quando
							//o usuário pede uma sugestão de jogada.
							ale_fim = 0;
							i = 0;
							while(melhor_ij[i][0] != -1) {
								ale_fim ++;
								i ++;
							}
							ale = 0+(ale_fim)*(double)rand()/(RAND_MAX+1);
							printf("\nSugiro %c%d.\n",melhor_ij[ale][1]+65,melhor_ij[ale][0]+1);
							comando = -1;
							break;
					}
				} while(comando == -1 && fim_de_jogo[0] == FALSO);

				//Se for para sair (comando 2) ou para reiniciar
				//(comando 5), termina o loop.
				if(comando == 2 || comando == 5)
					break;
			}
			else {
				fim_de_jogo[0] = VERDADEIRO;
				if(computador == BOLA)
					printf("\n\nNao ha jogadas para as estrelas.");
				else
					printf("\n\nNao ha jogadas para as bolas.");
			}

			if(analisa_jogo(tab,computador,&estrelas,&bolas,melhor_ij,valor) == FALSO) {

				//Implementação da aleatoriadade para o computador
				//jogar.
				ale_fim = 0;
				i = 0;
				while(melhor_ij[i][0] > -1) {
					ale_fim ++;
					i ++;
				}
				ale = 0+(ale_fim)*(double)rand()/(RAND_MAX+1);

				fim_de_jogo[1] = FALSO;
				verifica_jogada(melhor_ij[ale][0],melhor_ij[ale][1],tab,computador,VERDADEIRO,valor);
				printf("\nESTRELAS %d x %d BOLAS\n",estrelas,bolas);
				printf("Computador jogou %c%d.\n",melhor_ij[ale][1]+65,melhor_ij[ale][0]+1);
				imprime_tab(tab);
			}
			else {
				fim_de_jogo[1] = VERDADEIRO;
				if(computador == BOLA)
					printf("\n\nNao ha jogadas para as bolas.\n");
				else
					printf("\n\nNao ha jogadas para as estrelas.\n");
				imprime_tab(tab);
			}
		} while(fim_de_jogo[0] == FALSO || fim_de_jogo[1] == FALSO);

		switch(comando) {
			case 0:
				printf("\n\nO jogo terminou ESTRELAS %d x %d BOLAS. ",estrelas,bolas);
				if(estrelas >= bolas)
					if(estrelas == bolas)
						printf("Empatou!\n");
					else
						printf("Estrelas ganharam!\n");
				else
					printf("Bolas ganharam!\n");

				do {
					//Pergunta se quer reiniciar ou terminar.
					printf("\n[Z]Reiniciar | [T]erminar : ");
					scanf(" %c",&comando_final);
					if(comando_final >= 97 && comando_final <= 122)
						comando_final -= 32;
					switch(comando_final) {
						case 'Z':
							printf("\n\n\n");
							comando = 5;
							break;
						case 'T':
							printf("\nObrigado por jogar e ate logo!");
							return(0);
							break;
						//Se qualquer outra opção fora colocada é
						//perguntado novamente o comando.
						default:
							comando_final = 0;
							break;
					}
				} while(comando_final == 0);
				break;

			case 2:
				printf("\nVoce selecionou sair do jogo. ");
				if(fim_de_jogo[0] == FALSO || fim_de_jogo[1] == FALSO) {
					printf("A partida nao havia terminado e o placar era\nESTRELAS %d x %d BOLAS. ",estrelas,bolas);
					if(estrelas >= bolas)
						if(estrelas == bolas)
							printf("Estava empatado!\n");
						else
							printf("Estrelas estavam ganhando!\n");
					else
						printf("Bolas estavam ganhando!\n");
				}
				printf("\nObrigado por jogar e ate logo!");
				return(0);
				break;
			case 5:
				printf("\nVoce selecionou reiniciar o jogo. ");
				if(fim_de_jogo[0] == FALSO || fim_de_jogo[1] == FALSO) {
					printf("A partida nao havia terminado e o placar era\nESTRELAS %d x %d BOLAS. ",estrelas,bolas);
					if(estrelas >= bolas)
						if(estrelas == bolas)
							printf("Estava empatado!\n");
						else
							printf("Estrelas estavam ganhando!\n");
					else
						printf("Bolas estavam ganhando!\n");
				}
				break;
		}

	} while(comando == 5);
	return(0);
}
