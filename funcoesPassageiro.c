#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "estruturas.h"


int getNextPassageiroAutoID()
{
	FILE *fp;
	PASSAGEIRO passageiro;
	int nextID = 1;

	fp = fopen("PASSAGEIROS.DAT", "rb");

	rewind(fp);
	
	while( fread(&passageiro, sizeof(PASSAGEIRO), 1, fp) == 1)
	{	
		nextID++;
	}
		
	fclose( fp );
	
	return nextID;
}

void pedirDados(PASSAGEIRO *passageiro)
{
	 
	system("cls");
	 
	printf("\n\t\t PREENCHA OS CAMPOS DO PASSAGEIRO\n");
	printf("\t------------------------------------------------\n");
	
	passageiro -> id = getNextPassageiroAutoID();
	
	fflush(stdin);
	
	printf("\t\tAdicione o nome do Passageiro: ");
	gets(passageiro->nome);
	
	fflush(stdin);
	
	printf("\t\tAdicione o numero do BI:  ");
	gets(passageiro->bi);
	
	fflush(stdin);
	
	printf("\t\tAdicione o Genero:  ");
	gets(passageiro->genero);
	
	fflush(stdin);
		
	printf("\t\tAdicione a Data de Nascimento[DD-MM-AAAA]: ");
	scanf("%d%d%d", &passageiro->dataNascimento.dia, 
		&passageiro->dataNascimento.mes, &passageiro->dataNascimento.ano);
	
	fflush(stdin);
			
	printf("\t\tAdicione o Telefone: ");
	scanf("%d", &passageiro->telefone);

}


void apagarPassageiro() {
    FILE *fp, *fpTemp;
	PASSAGEIRO passageiro;
   	
    int idApagar, encontrado = 0;

    // Abrir o arquivo original para leitura
    fp = fopen("PASSAGEIROS.DAT", "rb");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo original.\n");
        return;
    }

    // Criar um arquivo temporário para escrita
    fpTemp = fopen("temp.dat", "wb");
    if (fpTemp == NULL) {
        printf("Erro ao criar o arquivo temporário.\n");
        fclose(fp);
        return;
    }

	system("cls");
	printf("\n\t\t ELIMINAR REGISTRO DE PASSAGEIRO\n");
	printf("\t------------------------------------------------\n");
    printf("\n\t\tDigite o ID do registro que deseja apagar: ");
    scanf("%d", &idApagar);

    // Ler todos os registros do arquivo original
    while (fread(&passageiro, sizeof(PASSAGEIRO), 1, fp) == 1) {
        if (passageiro.id == idApagar) {
            encontrado = 1;
            printf("Registro apagado: ID = %d, Nome = %s\n", passageiro.id, passageiro.nome);
        } else {
            // Copiar o registro para o arquivo temporário (exceto o que será apagado)
            fwrite(&passageiro, sizeof(PASSAGEIRO), 1, fpTemp);
        }
    }


    fclose(fp);
    fclose(fpTemp);

    // Verificar se o registro foi encontrado e apagado
    if (!encontrado) {
        printf("Registro com ID %d não encontrado.\n", idApagar);
        remove("temp.dat"); // Excluir o arquivo temporário, pois não houve alterações
    } else {
        // Substituir o arquivo original pelo temporário
        remove("PASSAGEIROS.DAT");               
        rename("temp.dat", "PASSAGEIROS.DAT");   
        printf("Registro apagado com sucesso!\n");
    }
}


void editarPassageiro() {
    FILE *fp;
	PASSAGEIRO passageiro;
	
	//abrir ou criar o ficheiro 
	fp = fopen("PASSAGEIROS.DAT", "r+b");
    int idEditar, encontrado = 0;


	system("cls");
	printf("\n\t\t EDITE OS CAMPOS DO PASSAGEIRO\n");
	printf("\t------------------------------------------------\n");
    printf("\n\t\tDigite o ID do passageiro que deseja editar: ");
    scanf("%d", &idEditar);

    while (fread(&passageiro, sizeof(PASSAGEIRO), 1, fp)) {
        if (passageiro.id == idEditar) {
            encontrado = 1;

            printf("\t\tPassageiro %s encontrado!\n", passageiro.nome);

            printf("\t\tDigite o novo nome: ");
            fflush(stdin);
            
            gets(passageiro.nome);
            printf("\t\tAdicione o numero do BI:  ");
			gets(passageiro.bi);
	
			fflush(stdin);
	
			printf("\t\tAdicione o Genero:  ");
			gets(passageiro.genero);
	
			fflush(stdin);
		
			printf("\t\tAdicione a Data de Nascimento[DD-MM-AAAA]: ");
			scanf("%d%d%d", &passageiro.dataNascimento.dia, 
			&passageiro.dataNascimento.mes, &passageiro.dataNascimento.ano);
	
			fflush(stdin);
			
			printf("\t\tAdicione o Telefone: ");
			scanf("%d", &passageiro.telefone);

            fseek(fp, -sizeof(PASSAGEIRO), SEEK_CUR); // Volta para sobrescrever
            fwrite(&passageiro, sizeof(PASSAGEIRO), 1, fp);

            printf("\t\tPassageiro atualizado com sucesso!\n");
            break;
        }
    }

    if (!encontrado) {
        printf("\t\tPassageiro não encontrado ou já excluído!\n");
    }

    fclose(fp);
}



void salvarDadosPassageiro()
{
	FILE *fp;
	PASSAGEIRO passageiro;
	
	//abrir ou criar o ficheiro 
	fp = fopen("PASSAGEIROS.DAT", "ab");
	
	//movimentar o File Pointer
	fseek(fp, 0L, SEEK_END);	//SEEK_SET, SEEK_CUR, SEEK_END
	
	//pedir dados ao utilizador
	pedirDados(&passageiro);
	
	//escrever os dados da estrutura para o ficheiro
	if( fwrite(&passageiro, sizeof(PASSAGEIRO), 1, fp) == 1)
	{
		puts("Registo adicionado com sucesso no Ficheiro");
	}
	
	// fechar o ficheiro
	fclose( fp );
}


void mostrarPassageiro(PASSAGEIRO passageiro)
{
	printf("\tID: %d\n", passageiro.id);
	
	printf("\tNome: %s\n", passageiro.nome);
		
	printf("\tBilhete de Identidade: %s\n", passageiro.bi);

	printf("\tGenero: %s\n", passageiro.genero);
	
	printf("\tTelefone: %d\n", passageiro.telefone);
	
	printf("\tData de Nascimento: %d/%d/%d\n", 
		passageiro.dataNascimento.dia, 
		passageiro.dataNascimento.mes, 
		passageiro.dataNascimento.ano);	
	
}


void listarPassageiro()
{
	FILE *fp;
	PASSAGEIRO passageiro;
	
	//abrir ou criar o ficheiro 
	fp = fopen("PASSAGEIROS.DAT", "rb");
	
	//movimentar o File Pointer
	fseek(fp, 0L, SEEK_SET);	
		
	system("cls");
	
	puts("\n\t\tLISTAGEM DE PASSAGEIROS");
	
	//escrever os dados da estrutura para o ficheiro
	while( fread(&passageiro, sizeof(PASSAGEIRO), 1, fp) == 1)
	{		
		printf("****************************************\n");
		mostrarPassageiro(passageiro);		
	}
		
	fclose( fp );
}


void pesquisarPassageiroPorNome()
{
	FILE *fp;
	PASSAGEIRO passageiro;
	char nomeProcurado[50];
	
	//abrir ou criar o ficheiro 
	fp = fopen("PASSAGEIROS.DAT", "rb");
	
	//colocar o File Pointer no principio do ficheiro
	rewind(fp);
	
	system("cls");
	
	printf("\n\tPESQUISA POR NOME\n");
	printf("\t------------------------------------------------\n");
	printf("\n\tDigite o Nome Procurado: ");
	getchar();
	gets(nomeProcurado);
		
	//escrever os dados da estrutura para o ficheiro
	while( fread(&passageiro, sizeof(PASSAGEIRO), 1, fp) == 1)
	{	
		
		if ( strcmp(passageiro.nome, nomeProcurado) == 0)
		{	
			system("cls");
						
			printf("\n\tPassageiro ENCONTRADO!\n");
			printf("\t------------------------------------------------\n");
			mostrarPassageiro(passageiro);
			
			fclose(fp);
			return;
		}
	}
	
	printf("\n\tPassageiro nao Encontrado\n");
		
	fclose( fp );
}
