// INF110 - Trabalho pratico 2
//
// programa para ler, modificar e gravar uma imagem no formato PNM
//
// Autores: Andre Gustavo dos Santos			(criado em 16/06/14)
//          Andre Gustavo dos Santos			(modificado em 22/05/18)
//					Andre Gustavo dos Santos			(modificado em 13/09/21)
//					Andre Gustavo dos Santos			(modificado em 6/05/26)
//                  Arthur Saraiva Alves - 124665 (modificado em)

#include <iostream>
#include <fstream>
#include <cstring>
#include<string>                        //coloquei string pra ler o nome do arquivo do usuario A.S
#include<cmath>							//coloquei para realizar o filtro de sobel - sqrt() A.S
const int MAXALTURA  = 500;				//tamanho maximo aceito (pode ser alterado)
const int MAXLARGURA = 500;

using namespace std;

int main() {
	unsigned char imagem[MAXALTURA][MAXLARGURA][3];	//a imagem propriamente dita //Implementação da terceira dimensão para imagens coloridas
	int largura, altura;						//dimensoes da imagem
	char tipo[4];										//tipo da imagem
	ifstream arqentrada;						//arquivo que contem a imagem original
	ofstream arqsaida;							//arquivo que contera a imagem modificada
	char comentario[200], c;				//auxiliares
	int i, j, valor;								//auxiliares
	string arquivo;
//*** LEITURA DA IMAGEM ***//
//esta parte le a imagem de um arquivo; voce pode deixar para olhar isso depois
//e iniciar a olhar o codigo a partir da linha 75 que de fato le os dados;
//a diferenca e' que le do arquivo (arqentrada) em vez de ler com cin

while(true){															//Loop pra que o nome seja perguntado enquanto ele nao for o nome certo
    cout << "Digite o nome do arquivo: (nome.pnm) \n";                  //Le o nome do arquivo.pnm por meio de uma string e aloca ela como condicao na abertura do arquivo 
    cin >> arquivo;
    
	//*** Abertura do arquivo ***//
	arqentrada.open(arquivo,ios::in); //Abre arquivo para leitura
	if (!arqentrada) {
		cout << "Nao consegui abrir arquivo imagem.pnm" << endl;
	}
	else 
		break;
}
//***************************//


//*** Leitura do cabecalho ***//
	arqentrada >> tipo;	//Le o tipo de arquivo
	arqentrada.get();		//Le e descarta o \n do final da 1a. linha

	if (strcmp(tipo,"P2")==0) {
		cout << "Imagem em tons de cinza\n";
	}
	else if (strcmp(tipo,"P3")==0) {                        //Se for uma imagem colorida (P3), a matriz deve ter 3 dimensoes
		cout << "Imagem colorida\n";
	}
	else if (strcmp(tipo,"P1")==0) {
		cout << "Imagem preto e branco\n";
		cout << "Desculpe, nao trabalho com esse tipo de imagem.\n";
		arqentrada.close();
		return 0;
	}
	else if (strcmp(tipo,"P4")==0 || strcmp(tipo,"P5")==0 || strcmp(tipo,"P6")==0) {
		cout << "Imagem no formato RAW\n";
		cout << "Desculpe, nao trabalho com esse tipo de imagem.\n";
		arqentrada.close();
		return 0;
	}

	while((c = arqentrada.get()) == '#')	//Enquanto for comentario
		arqentrada.getline(comentario,200);	//Le e descarta a linha "inteira"

	arqentrada.putback(c);	//Devolve o caractere lido para a entrada, pois como
													//nao era comentario, era o primeiro digito da largura

	arqentrada >> largura >> altura;	//Le as dimensoes da imagem, numero de pixels da horizontal e da vertical
	cout << "Tamanho: " << largura << " x " << altura << endl;
	if (largura > MAXLARGURA) {
		cout << "Desculpe, ainda nao trabalho com imagens com mais de " << MAXLARGURA << " pixels de largura.\n";
		arqentrada.close();
		return 0;
	}
	if (altura > MAXALTURA) {
		cout << "Desculpe, ainda nao trabalho com imagens com mais de " << MAXALTURA << " pixels de altura.\n";
		arqentrada.close();
		return 0;
	}

	arqentrada >> valor;	//Valor maximo do pixel (temos que ler, mas nao sera usado, assumimos 255)
//****************************//

//*** Leitura dos pixels da imagem cinza (P2)  ***//
	if (strcmp(tipo,"P2")==0)
        for(i=0;i<altura;i++)
		    for(j=0;j<largura;j++) {					//Apenas lê o valor do pixel na dimensao [0] e atribui ele a todas as outras
			arqentrada >> valor;
			imagem[i][j][0] = (unsigned char)valor;
            imagem[i][j][1] = (unsigned char)valor;
            imagem[i][j][2] = (unsigned char)valor;  	//Guarda no formato unsigned char
		}

//*** Leitura dos pixels da imagem colorida (P3)  ***//
    else if (strcmp(tipo,"P3")==0)
        for(i=0;i<altura;i++)
		    for(j=0;j<largura;j++) {
            int r, g, b;                                    //Variaveis pra cada cor (red,green,blue) ou seja, pra cada dimensao
			arqentrada >> r >> g >> b;                      //Leitura do valor de cada pixel r - g - b
			imagem[i][j][0] = (unsigned char)r;
            imagem[i][j][1] = (unsigned char)g;             //Atribui o valor de cada cor (rgb) em uma dimensao diferente
            imagem[i][j][2] = (unsigned char)b; 
            }
//************************************//

	arqentrada.close();  //Fecha arquivo apos a leitura

//*** FIM DA LEITURA DA IMAGEM ***//


//*** TRATAMENTO DA IMAGEM ***//
//inicialmente sera nesta parte do codigo que voce vai trabalhar
    
    //***Pergunta qual operação sera aplicada***//
	
    int opcao;
    cout << "O que deseja fazer?\n";
    cout << "1 - Escurecer\n";
    cout << "2 - Clarear\n";
    cout << "3 - Negativo\n";
    cout << "4 - Espelhar\n";
	cout << "5 - Filtro de Sobel\n";
	cout << "6 - Realcar\n";
	cout << "7 - Tons de cinza\n";
	cout << "8 - Simulacao de Daltonismo\n";
	cout << "9 - Daltonizacao\n";
    cin >> opcao;
	
	while(true){												//Impede que o usuário digite um valor que não corresponde a alguma operação
	if(opcao>=1 && opcao<=9){
		break;
	}
	else{
		cout << "Digite uma opcao valida:\n";
		cin >> opcao;
	}
	}
        
		
		
		
		if(opcao==1){
 //*** Escurece a imagem ***//
    int fator;
	cout << "Qual o fator de escurecimento (1-100)?\n";
	cin >> fator;

	for(i=0;i<altura;i++)
		for(j=0;j<largura;j++)
            for(int k=0;k<3;k++) {
			valor = (int)imagem[i][j][k];			//pega o valor do pixel
			valor -= fator;									//escurece o pixel
			if (valor < 0)									//se der negativo
				valor = 0;										//  deixa preto
			imagem[i][j][k] = (unsigned char)valor;	//modifica o pixel
		}
    }
        



        else if(opcao==2){
//*** Clareia a imagem ***// 
    int fator;
	cout << "Qual o fator de clareamento (1-100)? \n";
	cin >> fator;
     
    for(i=0;i<altura;i++)
		for(j=0;j<largura;j++)
            for(int k=0;k<3;k++) {
			valor = (int)imagem[i][j][k];						//pega o valor do pixel
			valor += fator;										//enclarece o pixel
			if (valor > 255)									//se der > 255
				valor = 255;									//deixa branco
			imagem[i][j][k] = (unsigned char)valor;				//modifica o pixel
        }}



        else if(opcao==3){
//*** Efeito negativo ***//       
   
    for(i=0;i<altura;i++)
		for(j=0;j<largura;j++)
            for(int k=0;k<3;k++) {
			valor = (int)imagem[i][j][k];				//Pega o valor do pixel
			valor = 255-valor;					       	//Negativa o pixel							
			imagem[i][j][k] = (unsigned char)valor;		//Modifica o pixel
        }
	}



        else if(opcao==4){
//*** Espelha a imagem ***//  
        for(i=0;i<altura;i++)
		for(j=0;j<largura/2;j++)
            for(int k=0;k<3;k++) {
			unsigned char temp = imagem[i][j][k];		    //Pega o valor do pixel	e grava em uma variavel auxiliar	
			imagem[i][j][k] = imagem[i][largura-1-j][k];	//Pega o pixel mais a direita e coloca no pixel mais a esquerda
            imagem[i][largura-1-j][k] = temp;              //Pega o valor gravado na variavel auxiliar e coloca no pixel da direita
            }
		}
		
		
		else if(opcao==5){
//*** Filtro de Sobel ***// 

		int Gx[3][3] = {1,0,-1,2,0,-2,1,0,-1};           //Matrizes do filtro de sobel
    	int Gy[3][3] = {1,2,1,0,0,0,-1,-2,-1};

			static int temp [MAXALTURA][MAXLARGURA][3];                 //Preenche a matriz temp com 0 para remover o lixo
        	for(int i=0;i<altura;i++)
           	 for(int j=0;j<largura;j++)
			 	for(int k=0;k<3;k++)
            	temp[i][j][k]=0;

//Calculando a matriz gx e gy * matriz da imagem
        int valorx=0;
        int valory=0;
        int valorp=0;
        for(int i=1;i<altura-1;i++){                                             //Loop para percorrer a matriz da imagem
            for(int j=1;j<largura-1;j++){
			 for(int k=0;k<3;k++){
                valorx=0;
                valory=0;
                valorp=0;
                for(int a=0;a<3;a++)                                        //Loop para percorrer as matrizes gx e gy do filtro
                    for(int b=0;b<3;b++){
                        valorx += Gx[a][b] * (int)imagem[i+(a-1)][j+(b-1)][k];           //Faz o calculo de ambos gx e gy, le um valor da matriz do filtro e percorre todos os pixels de um bloco 3x3 da imagem
                        valory += Gy[a][b] * (int)imagem[i+(a-1)][j+(b-1)][k];
                    }
        
        //Calcula o valor do pixel pela formula do filtro de sobel e atribui ele como char em uma matriz temporaria
            valorp = sqrt((valorx*valorx) +(valory*valory));
                    if(valorp>255)
                        valorp=255;
                    else if(valorp<0)
                        valorp=0;
            temp[i][j][k]=(unsigned char)valorp;
                }
}	
		}
			for(i=0;i<altura;i++)
				for(j=0;j<largura;j++)
            		for(int k=0;k<3;k++) {
					imagem[i][j][k] = (unsigned char)temp[i][j][k];
					}
				}

		else if(opcao==6){
//*** Filtro de Realce***//
    int fr[3][3] = {0, -1, 0, -1, 5, -1, 0, -1, 0 };        //Matriz do filtro de realce
	
	static int temp [MAXALTURA][MAXLARGURA][3];                                    //Preenche a matriz temp com 0 para remover o lixo
    	for(int i=0;i<altura;i++)
        	for(int j=0;j<largura;j++)
				for(int k=0;k<3;k++)
            	temp[i][j][k]=0;

	int valor = 0;
    for(int i=1;i<altura-1;i++){                                             //Loop para percorrer a matriz da imagem
            for(int j=1;j<largura-1;j++){
			 for(int k=0;k<3;k++){                   
            		valor =0;
            				for(int m=0;m<3;m++)                                        //Loop para percorrer a matriz do filtro e aplicar o resultado em uma matriz temp
                    			for(int n=0;n<3;n++){
                       				 valor += fr[m][n] * (int)imagem[i+(m-1)][j+(n-1)][k];	//Faz o calculo, le um valor da matriz do filtro e percorre todos os pixels de um bloco 3x3 da imagem	
                    }
                        				if(valor>255)
                            				valor=255;
                        				else if(valor<0)
                            				valor=0;
                        			temp[i][j][k]=(unsigned char)valor;					//Atribui o resultado do cálculo a uma matriz temporária
}
			 }
			}

			for(i=0;i<altura;i++)												//Atribui a matriz imagem os valores da matriz temporária
				for(j=0;j<largura;j++)
            		for(int k=0;k<3;k++) {
					imagem[i][j][k] = (unsigned char)temp[i][j][k];
					}
		}



		else if (opcao==7){
//*** Colorida para cinza ***//
 	

double mediap=0;
	for(i=0;i<altura;i++)																					//Percorre a matriz	
		for(j=0;j<largura;j++){
			mediap=(imagem[i][j][0] * 0.299) + (imagem[i][j][1] * 0.587) +   (imagem[i][j][2] * 0.114);			//Média ponderada dos valores dos pixel r,g,b
			
            		for(int k=0;k<3;k++)
					imagem[i][j][k]=(unsigned char)mediap;													//Atribui o resultado da média aos 3 pixels r,g,b, assim, a imagem fica em tons de cinza
		}
		}
			
	
		else if (opcao==8){
//*** Daltonismo ***//
	
	cout << "Escolha um tipo de daltonismo:\n";									//Pergunta qual o tipo de daltonismo
	cout << "1 - Protanopia(Vermelho)\n";
	cout << "2 - Deuteranopia(Verde)\n";
	cout << "3 - Tritanopia(Azul e Amarelo)\n";

	int tipo;
	cin >> tipo;

	while (tipo < 1 || tipo > 3){												//Impede que seja escolhida uma opção não existente
                cout << "Opcao invalida. Digite 1, 2 ou 3: ";
                cin >> tipo;
            }

	for(i=0;i<altura;i++){
		    for(j=0;j<largura;j++) {
            double r, g, b;                                    //Variaveis pra cada cor (red,green,blue) ou seja, pra cada dimensao            
			r = imagem[i][j][0]; 
			g = imagem[i][j][1];          
            b = imagem[i][j][2];

			double rd=0,gd=0,bd=0;							//Declaração das variáveis de cada cor na visão com daltonismo
            

	if(tipo==1){														//Dependendo do tipo de daltonismo selecionado, faz o cálculo dos valores de cada pixel rgb seguindo valores predeterminados
			rd = (r * 0.567) + (g * 0.433) + (b * 0.000);
            gd = (r * 0.558) + (g * 0.442) + (b * 0.000);
            bd = (r * 0.000) + (g * 0.242) + (b * 0.758);
            }
		
	else if (tipo==2){
			rd = (r * 0.625) + (g * 0.375) + (b * 0.000);
			gd = (r * 0.700) + (g * 0.300) + (b * 0.000);
			bd = (r * 0.000) + (g * 0.300) + (b * 0.700);
		}
	else if(tipo==3){
			rd = (r * 0.950) + (g * 0.050) + (b * 0.000);
			gd = (r * 0.000) + (g * 0.433) + (b * 0.567);
			bd = (r * 0.000) + (g * 0.475) + (b * 0.525);
	}

	if (rd > 255) 														//Garante que o valor máximo e mínimo de cada pixel seja respeitado
		rd = 255; 
	if (rd < 0) 
		rd = 0;
	if (gd > 255) 
		gd = 255; 
	if (gd < 0) 
		gd = 0;
    if (bd > 255) 
		bd = 255; 
	if (bd < 0) 
		bd = 0;

	imagem[i][j][0] = (unsigned char)rd;								//Atribui a matriz da nova imagem os valores encontrados usando o cálculo da visão com daltonismo
    imagem[i][j][1] = (unsigned char)gd;
	imagem[i][j][2] = (unsigned char)bd;
	}}
}

	else if(opcao==9){
//** Daltonização (Realce para daltonicos) **//

	int tipo;
	cout << "Para qual tipo de daltonismo deseja otimizar a imagem?\n";					//Pergunta o tipo de daltonismo
	cout << "1 - Protanopia (Vermelho)\n";
	cout << "2 - Deuteranopia (Verde)\n";
	cout << "3 - Tritanopia (Azul e Amarelo)\n";

	cin >> tipo;

		while (tipo < 1 || tipo > 3){													//Impede que o usuário selecione uma opção inexistente
                cout << "Opcao invalida. Digite 1, 2 ou 3: ";
                cin >> tipo;
            }
			
		for(i=0;i<altura;i++){
		    for(j=0;j<largura;j++) {
            double r, g, b;                                    //variaveis pra cada cor (red,green,blue) ou seja, pra cada dimensao            
			r = imagem[i][j][0]; 
			g = imagem[i][j][1];          
            b = imagem[i][j][2];

			double rd=0,gd=0,bd=0;								//Declaração das variáveis de cada cor na visão com daltonismo

			if(tipo==1){										//Dependendo do tipo de daltonismo selecionado, faz o cálculo dos valores de cada pixel rgb seguindo valores predeterminados
			rd = (r * 0.567) + (g * 0.433) + (b * 0.000);
            gd = (r * 0.558) + (g * 0.442) + (b * 0.000);
            bd = (r * 0.000) + (g * 0.242) + (b * 0.758);
            }
		
	else if (tipo==2){
			rd = (r * 0.625) + (g * 0.375) + (b * 0.000);
			gd = (r * 0.700) + (g * 0.300) + (b * 0.000);
			bd = (r * 0.000) + (g * 0.300) + (b * 0.700);
		}
	else if(tipo==3){
			rd = (r * 0.950) + (g * 0.050) + (b * 0.000);
			gd = (r * 0.000) + (g * 0.433) + (b * 0.567);
			bd = (r * 0.000) + (g * 0.475) + (b * 0.525);
	}																//Até aqui apenas utiliza o mesmo algoritmo da simulação de daltonismo 

	double erroR = r - rd;					//Calculando o erro da visão, ou seja, a diferença entre a cor original e a cor vista com daltonismo
	double erroG = g - gd;
	double erroB = b - bd;

	
	double corrigeR = 0, corrigeG = 0, corrigeB = 0;		//Declaração de variáveis de correção/realce de cor
			
	if(tipo == 1 || tipo == 2){											//Calcula a correção de cor	
		corrigeR = (erroR * 0.0) + (erroG * 0.0) + (erroB * 0.0);
		corrigeG = (erroR * 0.7) + (erroG * 1.0) + (erroB * 0.0);
		// AUMENTA O PESO DO ERRO NO AZUL DE 0.7 PARA 2.5
		corrigeB = (erroR * 2.5) + (erroG * 0.0) + (erroB * 1.0); 
	}
	else if(tipo == 3){
		corrigeR = (erroR * 1.0) + (erroG * 0.0) + (erroB * 0.7);
		corrigeG = (erroR * 0.0) + (erroG * 1.0) + (erroB * 0.7);
		corrigeB = (erroR * 0.0) + (erroG * 0.0) + (erroB * 0.0);
    }

	double novoR = r + corrigeR;									//Variáveis das novas cores, ou seja, a cor original somada a correção realizada
    double novoG = g + corrigeG;
    double novoB = b + corrigeB;

	if (novoR > 255) novoR = 255; if (novoR < 0) novoR = 0;			
    if (novoG > 255) novoG = 255; if (novoG < 0) novoG = 0;
    if (novoB > 255) novoB = 255; if (novoB < 0) novoB = 0;

	imagem[i][j][0] = (unsigned char)novoR;							//Atribui as novas cores a matriz da nova imagem gerada
    imagem[i][j][1] = (unsigned char)novoG;
    imagem[i][j][2] = (unsigned char)novoB;
		}}
	}

		//*************************//
		
	
		


//*** FIM DO TRATAMENTO DA IMAGEM ***//


//*** GRAVACAO DA IMAGEM ***//
//esta parte grava a imagem em um arquivo; voce pode deixar para entender isso depois
//a diferenca e' que escreve no arquivo (arqsaida) em vez de escrever com cout
	
	//*** Grava a nova imagem ***//
	
	
	string nome;
//Agora o programa pergunta o nome do arquivo que sera gerado e impede que seja igual ao original, assim nao ira sobrescrever acidentalmente o arquivo original
	while(true){
		cout << "Digite o novo nome da imagem modificada (exemplo.pnm) :\n";
		cin >> nome;
			if(nome==arquivo)
				cout << "Nome não pode ser igual ao do arquivo original\n" << "Escolha um novo nome diferente.\n";
			else
				break;
	}
	arqsaida.open(nome,ios::out);	//Abre arquivo para escrita
	if (!arqsaida) {
		cout << "Nao consegui criar" << nome << endl;
		return 0;
	}

	
		arqsaida << "P3" << endl;							//tipo
	arqsaida << "# TP2-INF110, by AGS e ASA\n";	//comentario
	arqsaida << largura << " " << altura;	//dimensoes
	arqsaida << " " << 255 << endl;				//maior valor
	for(i=0;i<altura;i++){
		for(j=0;j<largura;j++){
            for(int k=0;k<3;k++){
			arqsaida << (int)imagem[i][j][k] << " "; //pixels
		}
	}	
	arqsaida << endl;													//Mudei o endl de lugar pra que o programa imprima os 3 valores de toda as colunas e pule uma linha so quando mudar uma linha da imagem
}
	arqsaida.close();		//fecha o arquivo
	//***************************//

//*** FIM DA GRAVACAO DA IMAGEM ***//

	return 0;
}

