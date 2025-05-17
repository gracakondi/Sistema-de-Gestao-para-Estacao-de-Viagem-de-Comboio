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

	fp = fopen("COMBOIO.DAT", "rb");

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
	
	fflush(stdin);
	
	//DADOS DA DEFESA
	
	printf("\t\tAdicione a Diocese:  ");
	gets(comboio->diocese);
	
	fflush(stdin);
	
	printf("\t\tAdicione a Paroquia:  ");
	gets(comboio->paroquia);
	
	
	comboio->lugaresDisponiveis = comboio->capacidadeTotal;
}


void apagarComboio() {
    FILE *fp, *fpTemp1;
    COMBOIO comboio;
    int idApagar, encontrado = 0;

    // Abrir o arquivo original para leitura
    fp = fopen("COMBOIO.DAT", "rb");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo original.\n");
        return;
    }

    // Criar um arquivo temporário para escrita
    fpTemp1 = fopen("temp1.dat", "wb");
    if (fpTemp1 == NULL) {
        printf("Erro ao criar o arquivo temporário.\n");
        fclose(fp);
        return;
    }

   	system("cls");
	printf("\n\t\t ELIMINAR REGISTRO DE PASSAGEIRO\n");
	printf("\t------------------------------------------------\n");
    printf("\t\tDigite o ID do Comboio que deseja apagar: ");
    scanf("%d", &idApagar);

    // Ler todos os registros do arquivo original
    while (fread(&comboio, sizeof(COMBOIO), 1, fp) == 1) {
        if (comboio.id == idApagar) {
            encontrado = 1; // Registro encontrado
            printf("\t\tRegistro apagado: ID = %d, Nome = %s\n", comboio.id, comboio.nomeComboio);
        } else {
            // Copiar o registro para o arquivo temporário (exceto o que será apagado)
            fwrite(&comboio, sizeof(COMBOIO), 1, fpTemp1);
        }
    }


    fclose(fp);
    fclose(fpTemp1);

    // Verificar se o registro foi encontrado e apagado
    if (!encontrado) {
        printf("Registro com ID %d não encontrado.\n", idApagar);
        remove("temp1.dat"); // Excluir o arquivo temporário, pois não houve alterações
    } else {
        // Substituir o arquivo original pelo temporário
        remove("COMBOIO.DAT");               
        rename("temp1.dat", "COMBOIO.DAT");   
        printf("Registro apagado com sucesso!\n");
    }
}


void editarComboio() {
    FILE *fp;
	COMBOIO comboio;
	
	//abrir ou criar o ficheiro 
	fp = fopen("COMBOIO.DAT", "r+b");
    int idEditar, encontrado = 0;


	system("cls");
	printf("\n\t\t EDITE OS CAMPOS DO PASSAGEIRO\n");
	printf("\t------------------------------------------------\n");
    printf("\n\t\tDigite o ID do passageiro que deseja editar: ");
    scanf("%d", &idEditar);

    while (fread(&comboio, sizeof(COMBOIO), 1, fp)) {
        if (comboio.id == idEditar) {
            encontrado = 1;

            printf("comboio %s encontrado!\n", comboio.nomeComboio);

            printf("Digite o novo nome: ");
            fflush(stdin);
            gets(comboio.nomeComboio);
            printf("Digite a nova Capacidade: ");
            scanf("%d", &comboio.capacidadeTotal);

            fseek(fp, -sizeof(COMBOIO), SEEK_CUR); // Volta para sobrescrever
            fwrite(&comboio, sizeof(COMBOIO), 1, fp);

            printf("\t\tPassageiro atualizado com sucesso!\n");
            break;
        }
    }

    if (!encontrado) {
        printf("\t\tPassageiro não encontrado ou já excluído!\n");
    }

    fclose(fp);
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
	
	printf("\tDIOCESE: %s\n", comboio.diocese);
	
	printf("\tPAROQUIA: %s\n", comboio.paroquia);
	
	
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



void pesquisarComboioPor2Nome()
{
	FILE *fp;
	COMBOIO comboio;
	char nomeProcurado0[50];
	char nomeProcurado2[50];
	
	//abrir ou criar o ficheiro 
	fp = fopen("COMBOIO.DAT", "rb");
	
	//colocar o File Pointer no principio do ficheiro
	rewind(fp);
		
	system("cls");
	printf("\n\tPESQUISA DEFESA\n");
	printf("\t------------------------------------------------\n");
	printf("\n\tDigite a Diocese Procurada: ");
	getchar();
	gets(nomeProcurado0);
	
	printf("\n\tDigite a Paroquia Procurada: ");
	getchar();
	gets(nomeProcurado2);
		
	//escrever os dados da estrutura para o ficheiro
	while( fread(&comboio, sizeof(COMBOIO), 1, fp) == 1)
	{	
		
		if ( strcmp(comboio.diocese, nomeProcurado0) == 0)// &&   strcmp(comboio.paroquia, nomeProcurado2) == 0 )
		{	
			system("cls");
			
			if( strcmp(comboio.paroquia, nomeProcurado2) == 0)
			 
						
			printf("\n\tCAMPOS ENCONTRADOS!\n");
			printf("\t------------------------------------------------\n");
			mostrarComboio(comboio);
			
			fclose(fp);
			return;
		}
	}
	
	printf("REGISTRO COM DUAS ENTIDADES N ENCONTRADO\n");
		
	fclose( fp );
}
