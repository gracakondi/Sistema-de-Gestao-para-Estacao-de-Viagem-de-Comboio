#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "estruturas.h"

float calculoPreco();
int id_paraComboio;

// FUNCOES DA VIAGEM

int getNextViagemAutoID()
{
	FILE *fp;
	VIAGEM viagem;
	int nextID = 1;

	fp = fopen("VIAGEM.DAT", "rb");

	rewind(fp);
	
	while( fread(&viagem, sizeof(VIAGEM), 1, fp) == 1)
	{	
		nextID++;
	}
		
	fclose( fp );
	
	return nextID;
}

void comboioID()
{
	FILE *fp;
	COMBOIO comboio;
	int encontrado = 0;
	
	do 
	{
		
	//abrir o ficheiro 
	fp = fopen("COMBOIO.DAT", "rb");
	
	//colocar o File Pointer no principio do ficheiro
	rewind(fp);
	
	printf("\t\tDigite o ID do Comboio: ");
	scanf("%d", &id_paraComboio);
	
	//escrever os dados da estrutura para o ficheiro
	while( fread(&comboio, sizeof(COMBOIO), 1, fp) == 1)
	{	
		if (id_paraComboio == comboio.id)
		{	
			printf("\t\tComboio %s selecionado", comboio.nomeComboio);
			encontrado = 1;
			fclose(fp);
			return;
		}
	}	
	fclose( fp );
	
	if (encontrado == 0) {
            printf("\n\tComboio nao Encontrado. Tente novamente!\n\n");
        }
	
	} while (!encontrado);
}

float calculoPreco(VIAGEM *viagem) {
    float precoFinal = 1000;

    // Verifica se o tipo foi realmente definido
    if (strcmp(viagem->tipo, "Interprovincial") == 0) {
        precoFinal += precoFinal * 12.5;
    } else if (strcmp(viagem->tipo, "Intermunicipal") == 0) {
        precoFinal -= precoFinal * 0.50; 
    } else {
        printf("Tipo de viagem inválido!\n");
    }

    return precoFinal;
}

void pedirDadosViagem(VIAGEM *viagem)
{
	
	system("cls");
	 
	printf("\n\t\t PREENCHA OS CAMPOS DA VIAGEM\n");
	printf("\t------------------------------------------------\n");
	
	viagem -> id = getNextViagemAutoID();
	
	fflush(stdin);
	
	printf("\t\tAdicione o nome da Viagem [Partida-Destino]:  ");
	gets(viagem->rota);
	
	fflush(stdin);
		
	comboioID();
	viagem->idComboio = id_paraComboio;
	
	fflush(stdin);
	
	printf("\n\t\tAdicione o Tipo de Viagem: ");
	gets(viagem->tipo);
	
	fflush(stdin);
	
	printf("\t\tAdicione as Paragens durante a Viagem:  ");
	gets(viagem->paragens);
	
	fflush(stdin);
	
	printf("\t\tAdicione a Data de Viagem [DD-MM-AAAA]: ");
	scanf("%d%d%d", &viagem->dataViagem.dia, 
		&viagem->dataViagem.mes, &viagem->dataViagem.ano);
	
	fflush(stdin);
	
	printf("\t\tAdicione a Hora Da Viagen[Hr Min]: ");
	scanf("%d%d", &viagem->horario.hora, 
		&viagem->horario.minuto);
	
	fflush(stdin);
	viagem->preco = calculoPreco(viagem);
	printf("\t------------------------------------------------\n");
	printf("\t\tPreco Final: %d Kz\n", viagem->preco);
	getchar();
	
	fflush(stdin);
}



void apagarViagem() {
    FILE *fp, *fpTemp2;
    VIAGEM viagem;
    int idApagar, encontrado = 0;

    // Abrir o arquivo original para leitura
    fp = fopen("VIAGEM.DAT", "rb");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo original.\n");
        return;
    }

    // Criar um arquivo temporário para escrita
    fpTemp2 = fopen("temp2.dat", "wb");
    if (fpTemp2 == NULL) {
        printf("Erro ao criar o arquivo temporário.\n");
        fclose(fp);
        return;
    }

    // Pedir o ID do registro a ser apagado
    printf("Digite o ID do registro que deseja apagar: ");
    scanf("%d", &idApagar);

    // Ler todos os registros do arquivo original
    while (fread(&viagem, sizeof(VIAGEM), 1, fp) == 1) {
        if (viagem.id == idApagar) {
            encontrado = 1; // Registro encontrado
            printf("Registro apagado: ID = %d, Rota = %s\n", viagem.id, viagem.rota);
        } else {
            // Copiar o registro para o arquivo temporário (exceto o que será apagado)
            fwrite(&viagem, sizeof(VIAGEM), 1, fpTemp2);
        }
    }

    // Fechar os arquivos
    fclose(fp);
    fclose(fpTemp2);

    // Verificar se o registro foi encontrado e apagado
    if (!encontrado) {
        printf("Registro com ID %d não encontrado.\n", idApagar);
        remove("temp2.dat"); // Excluir o arquivo temporário, pois não houve alterações
    } else {
        // Substituir o arquivo original pelo temporário
        remove("VIAGEM.DAT");               // Excluir o arquivo original
        rename("temp2.dat", "VIAGEM.DAT");   // Renomear o arquivo temporário
        printf("Registro apagado com sucesso!\n");
    }
}


void editarViagem() {
    FILE *fp;
	VIAGEM viagem;
	
	//abrir ou criar o ficheiro 
	fp = fopen("VIAGEM.DAT", "r+b");
    int idEditar, encontrado = 0;


	system("cls");
	printf("\n\t\t EDITE OS CAMPOS DA VIAGEM\n");
	printf("\t------------------------------------------------\n");
    printf("\n\t\tDigite o ID da Viagem que deseja editar: ");
    scanf("%d", &idEditar);

    while (fread(&viagem, sizeof(VIAGEM), 1, fp)) {
        if (viagem.id == idEditar) {
            encontrado = 1;

            printf("Passageiro %s encontrado!\n", viagem.rota);

            printf("\t\tDigite a nova rota: ");
            fflush(stdin);
            gets(viagem.rota);
            
            fflush(stdin);
		
			comboioID();
			viagem.idComboio = id_paraComboio;
	
			fflush(stdin);
	
			printf("n\t\tAdicione as Paragens durante a Viagem:  ");
			gets(viagem.paragens);
	
			fflush(stdin);

            fseek(fp, -sizeof(PASSAGEIRO), SEEK_CUR); // Volta para sobrescrever
            fwrite(&viagem, sizeof(VIAGEM), 1, fp);

            printf("\t\tPassageiro atualizado com sucesso!\n");
            break;
        }
    }

    if (!encontrado) {
        printf("\t\tPassageiro não encontrado ou já excluído!\n");
    }

    fclose(fp);
}



void salvarViagem()
{
	FILE *fp;
	VIAGEM viagem;
	
	//abrir ou criar o ficheiro 
	fp = fopen("VIAGEM.DAT", "ab");
	
	//movimentar o File Pointer
	fseek(fp, 0L, SEEK_END);	//SEEK_SET, SEEK_CUR, SEEK_END
	
	//pedir dados ao utilizador
	pedirDadosViagem(&viagem);
	
	//escrever os dados da estrutura para o ficheiro
	if( fwrite(&viagem, sizeof(VIAGEM), 1, fp) == 1)
	{
		system("cls");
		puts("Registo adicionado com sucesso no Ficheiro");
	}
	
	// fechar o ficheiro
	fclose( fp );
}


void mostrarViagem(VIAGEM viagem)
{

	printf("\tID: %d\n", viagem.id);
	
	printf("\tComboio [ID]: %d\n", viagem.idComboio);
	
	printf("\tNome [Partida-Destino]: %s\n", viagem.rota);
	
	printf("\tParagens: %s\n", viagem.paragens);
	
	printf("\tTipo: %s\n", viagem.tipo);
	
	printf("\tPreco: %d\n", viagem.preco);
	
	printf("\tData da Viagem: %d-%d-%d\n", 
		viagem.dataViagem.dia, 
		viagem.dataViagem.mes, 
		viagem.dataViagem.ano);	
		
	printf("\tHorario: %dh:%dmin\n", 
		viagem.horario.hora, 
		viagem.horario.minuto);
}


void listarViagem()
{
	FILE *fp;
	VIAGEM viagem;
	
	//abrir ou criar o ficheiro 
	fp = fopen("VIAGEM.DAT", "rb");
	
	//movimentar o File Pointer
	fseek(fp, 0L, SEEK_SET);	
		
	system("cls");
	
	puts("\n\t\tLISTA DE VIAGENS");
	
	//escrever os dados da estrutura para o ficheiro
	while( fread(&viagem, sizeof(VIAGEM), 1, fp) == 1)
	{		
		printf("****************************************\n");
		mostrarViagem(viagem);		
	}
		
	fclose( fp );
}


void pesquisarViagemPorNome()
{
	FILE *fp;
	VIAGEM viagem;
	char nomeProcurado[50];
	
	//abrir ou criar o ficheiro 
	fp = fopen("VIAGEM.DAT", "rb");
	
	//colocar o File Pointer no principio do ficheiro
	rewind(fp);
	
	system("cls");
	printf("\n\tPESQUISA POR NOME\n");
	printf("\t------------------------------------------------\n");
	printf("\n\tDigite o Nome da Viagem Procurado: ");
	getchar();
	gets(nomeProcurado);
	
	//escrever os dados da estrutura para o ficheiro
	while( fread(&viagem, sizeof(VIAGEM), 1, fp) == 1)
	{	
		printf("Nome = %s\n", nomeProcurado);
		
		if ( strcmp(viagem.rota, nomeProcurado) == 0)
		{	
			system("cls");
			printf("\n\tVIAGEM ENCONTRADA!\n");
			printf("\t------------------------------------------------\n");
			mostrarViagem(viagem);
			
			fclose(fp);
			return;
		}
	}
	
	printf("%s nao Encontrado!...\n", nomeProcurado);
		
	fclose( fp );
}
