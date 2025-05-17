#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "estruturas.h"


// FUNCOES DO COMBOIO
int getNextComboioAutoID()
{
	FILE *fp;
	COMBOIO comboio;
	int nextID = 1;

	fp = fopen("DEFESA.DAT", "rb");

	//usei para direcionar o ponteiro
	rewind(fp);
	
	while( fread(&comboio, sizeof(COMBOIO), 1, fp) == 1)
	{	
		nextID++;
	}
		
	fclose( fp );
	
	return nextID;
}

void pedirDadosComboio(COMBOIO *comboio)
{
	 
	system("cls");
	
	printf("\n\t\t PREENCHA OS CAMPOS DA COMBOIO\n");
	printf("\t------------------------------------------------\n");

	comboio -> id = getNextComboioAutoID();
	fflush(stdin);
		
	printf("\t\tAdicione o nome do Comboio:  ");
	gets(comboio->nomeComboio);
	
	fflush(stdin);

	printf("\t\tAdicione a capacidade Total:  ");
	scanf("%d", &comboio->capacidadeTotal);
	
	comboio->lugaresDisponiveis = comboio->capacidadeTotal;
}


void salvarComboio()
{
	FILE *fp;
	COMBOIO comboio;
	
	//abrir ou criar o ficheiro 
	fp = fopen("COMBOIO.DAT", "ab");
	
	//movimentar o File Pointer
	fseek(fp, 0L, SEEK_END);	//SEEK_SET, SEEK_CUR, SEEK_END
	
	//pedir dados ao utilizador
	pedirDadosComboio(&comboio);
	
	//escrever os dados da estrutura para o ficheiro
	if( fwrite(&comboio, sizeof(COMBOIO), 1, fp) == 1)
	{
		system("cls");
		puts("Registo adicionado com sucesso no Ficheiro");
	}
	
	// fechar o ficheiro
	fclose( fp );
}


void mostrarComboio(COMBOIO comboio)
{
	
	printf("\tID: %d\n", comboio.id);
	
	printf("\tNome: %s\n", comboio.nomeComboio);
		
	printf("\tcapacidade de Passageiros: %d\n", comboio.capacidadeTotal);

	printf("\tLugares Disponiveis: %d\n", comboio.lugaresDisponiveis);
	
}

void listarComboio()
{
	FILE *fp;
	COMBOIO comboio;
	
	//abrir ou criar o ficheiro 
	fp = fopen("COMBOIO.DAT", "rb");
	
	//movimentar o File Pointer
	fseek(fp, 0L, SEEK_SET);	
//	rewind(fp);
		
	system("cls");
	
	puts("\n\t\tLISTAGEM DE COMBOIOS");
	
	//escrever os dados da estrutura para o ficheiro
	while( fread(&comboio, sizeof(COMBOIO), 1, fp) == 1)
	{		
		printf("****************************************\n");
		mostrarComboio(comboio);		
	}
		
	fclose( fp );
}

void pesquisarComboioPorNome()
{
	FILE *fp;
	COMBOIO comboio;
	char nomeProcurado[50];
	
	//abrir ou criar o ficheiro 
	fp = fopen("COMBOIO.DAT", "rb");
	
	//colocar o File Pointer no principio do ficheiro
	rewind(fp);
		
	system("cls");
	printf("\n\tPESQUISA POR NOME\n");
	printf("\t------------------------------------------------\n");
	printf("\n\tDigite o Nome do Comboio Procurado: ");
	getchar();
	gets(nomeProcurado);
		
	//escrever os dados da estrutura para o ficheiro
	while( fread(&comboio, sizeof(COMBOIO), 1, fp) == 1)
	{	
		printf("Nome = %s\n", nomeProcurado);
		
		if ( strcmp(comboio.nomeComboio, nomeProcurado) == 0)
		{	
			system("cls");
						
			printf("\n\tCOMBOIO ENCONTRADA!\n");
			printf("\t------------------------------------------------\n");
			mostrarComboio(comboio);
			
			fclose(fp);
			return;
		}
	}
	
	printf("%s nao Encontrado!...\n", nomeProcurado);
		
	fclose( fp );
}
