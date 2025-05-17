#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "estruturas.h"


 int id_passageiro;
 int id_paraViagem;
 //int idComboio;

// FUNCOES DA RESERVA
int getNextReservaAutoID()
{
	FILE *fp;
	RESERVA reserva;
	int nextID = 1;

	fp = fopen("RESERVA.DAT", "rb");

	rewind(fp);
	
	while( fread(&reserva, sizeof(RESERVA), 1, fp) == 1)
	{	
		nextID++;
	}
		
	fclose( fp );
	
	return nextID;
}

void passageiroID()
{
	FILE *fp;
	PASSAGEIRO passageiro;
	int encontrado = 0;
	
	do 
	{
		
	//abrir o ficheiro 
	fp = fopen("PASSAGEIROS.DAT", "rb");
	
	//colocar o File Pointer no principio do ficheiro
	rewind(fp);
	
	printf("\t\tDigite o ID do Cliente: ");
	scanf("%d", &id_passageiro);
	
	//escrever os dados da estrutura para o ficheiro
	while( fread(&passageiro, sizeof(PASSAGEIRO), 1, fp) == 1)
	{	
		if (id_passageiro == passageiro.id)
		{	

			printf("\n\t\tPassageiro %s selecionado!", passageiro.nome);
			encontrado = 1;
			fclose(fp);
			return;
		}
	}	
	fclose( fp );
	
	if (encontrado == 0) {
            printf("\n\tPassageiro nao Encontrado. Tente novamente!\n\n");
        }
	
	} while (!encontrado);
}


void viagemID()
{
	FILE *fp;
	VIAGEM viagem;
	int encontrado = 0;
	
	do 
	{
		
	//abrir o ficheiro 
	fp = fopen("VIAGEM.DAT", "rb");
	
	//colocar o File Pointer no principio do ficheiro
	rewind(fp);
	
	printf("\n\t\tDigite o ID da Viagem: ");
	scanf("%d", &id_paraViagem);
	
	//escrever os dados da estrutura para o ficheiro
	while( fread(&viagem, sizeof(VIAGEM), 1, fp) == 1)
	{	
		if (id_paraViagem == viagem.id)
		{	
			printf("\n\t\tViagem %s selecionada!", viagem.rota);
			encontrado = 1;
			fclose(fp);
			return;
		}
	}	
	fclose( fp );
	
	if (encontrado == 0) {
            printf("\n\tViagem nao Encontrado. Tente novamente!\n\n");
        }
	
	} while (!encontrado);
}


int atualizarLugares() {
    FILE *fp = fopen("COMBOIO.DAT", "r+b"); // Abre para leitura e escrita
    COMBOIO comboio;
    int idComboio, encontrado = 0;

    if (fp == NULL) {
        printf("Erro ao abrir o arquivo de comboios.\n");
        return 0;
    }

    printf("\t\tDigite o ID do comboio: ");
    scanf("%d", &idComboio);

    // Lê cada registro do arquivo
    while (fread(&comboio, sizeof(COMBOIO), 1, fp) == 1) {
        if (comboio.id == idComboio) {
            encontrado = 1;

            if (comboio.lugaresDisponiveis > 0) {
                comboio.lugaresDisponiveis--; // Reduz um lugar

                // Volta para a posição correta para reescrever o registro
                fseek(fp, -sizeof(COMBOIO), SEEK_CUR);

                // Reescreve o registro atualizado
                if (fwrite(&comboio, sizeof(COMBOIO), 1, fp) == 1) {
                    fclose(fp);
                    printf("Reserva confirmada! Lugares restantes: %d\n", comboio.lugaresDisponiveis);
                    return 1; // Reserva feita com sucesso
                } else {
                    fclose(fp);
                    printf("Erro ao atualizar o arquivo.\n");
                    return 0; // Erro ao escrever no arquivo
                }
            } else {
                fclose(fp);
                printf("O comboio está cheio! Reserva não pode ser feita.\n");
                return 0; // Comboio cheio, reserva não realizada
            }
        }
    }

    fclose(fp);

    if (!encontrado) {
        printf("Comboio não encontrado.\n");
    }

    return 0; // Comboio não encontrado
}


		
void pedirDadosReserva(RESERVA *reserva)
{	
	system("cls");
	
	printf("\n\t\t PREENCHA OS CAMPOS DA RESERVA\n");
	printf("\t------------------------------------------------\n");
	
	reserva -> id = getNextReservaAutoID();
	
	passageiroID();
	reserva->idPassageiro = id_passageiro;
	
	fflush(stdin);
	
	viagemID();
	reserva->idViagem = id_paraViagem;

	fflush(stdin);
	
	printf("\n\t\tAdicione o Assento Comprado: ");
	scanf("%d", &reserva->assentoComprado);
	
	fflush(stdin);
	
	printf("\t\tAdicione a Classe:  ");
	gets(reserva->classe);
	
	fflush(stdin);
	
	printf("\t\tAdicione a data da Reserva [DD-MM-AAAA]: ");
	scanf("%d%d%d", &reserva->dataReserva.dia, 
		&reserva->dataReserva.mes, &reserva->dataReserva.ano);	
	
	fflush(stdin);
	
	printf("\t\tNome do Funcionario:  ");
	gets(reserva->funcionario);
	
	fflush(stdin);

	 atualizarLugares();
}



void apagarReserva() {
    FILE *fp, *fpTemp3;
   	RESERVA reserva;
    int idApagar, encontrado = 0;

    // Abrir o arquivo original para leitura
    fp = fopen("RESERVA.DAT", "rb");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo original.\n");
        return;
    }

    // Criar um arquivo temporário para escrita
    fpTemp3 = fopen("temp3.dat", "wb");
    if (fpTemp3 == NULL) {
        printf("Erro ao criar o arquivo temporário.\n");
        fclose(fp);
        return;
    }

    // Pedir o ID do registro a ser apagado
    printf("Digite o ID do registro que deseja apagar: ");
    scanf("%d", &idApagar);

    // Ler todos os registros do arquivo original
    while (fread(&reserva, sizeof(RESERVA), 1, fp) == 1) {
        if (reserva.id == idApagar) {
            encontrado = 1; // Registro encontrado
            printf("Registro apagado: ID = %d\n", reserva.id);
        } else {
            // Copiar o registro para o arquivo temporário (exceto o que será apagado)
            fwrite(&reserva, sizeof(RESERVA), 1, fpTemp3);
        }
    }

    fclose(fp);
    fclose(fpTemp3);

    // Verificar se o registro foi encontrado e apagado
    if (!encontrado) {
        printf("Registro com ID %d não encontrado.\n", idApagar);
        remove("temp3.dat"); // Excluir o arquivo temporário, pois não houve alterações
    } else {
        // Substituir o arquivo original pelo temporário
        remove("RESERVA.DAT");               // Excluir o arquivo original
        rename("temp3.dat", "RESERVA.DAT");   // Renomear o arquivo temporário
        printf("Registro apagado com sucesso!\n");
    }
}


void editarReserva() {
    FILE *fp;
	RESERVA reserva;
	
	//abrir ou criar o ficheiro 
	fp = fopen("RESERVA.DAT", "r+b");
    int idEditar, encontrado = 0;


	system("cls");
	printf("\n\t\t EDITE OS CAMPOS DO PASSAGEIRO\n");
	printf("\t------------------------------------------------\n");
    printf("\n\t\tDigite o ID da reserva que deseja editar: ");
    scanf("%d", &idEditar);

    while (fread(&reserva, sizeof(RESERVA), 1, fp)) {
        if (reserva.id == idEditar) {
            encontrado = 1;

            printf("Passageiro %d encontrado!\n", reserva.id);

        //    printf("Digite o ID do Passageiro: ");
        //    fflush(stdin);
        //    scanf("%d", &reserva.id);
            
            passageiroID();
			reserva.idPassageiro = id_passageiro;
	
			fflush(stdin);
	
			viagemID();
			reserva.idViagem = id_paraViagem;

			fflush(stdin);
	
			printf("\n\t\tAdicione o Assento Comprado: ");
			scanf("%d", &reserva.assentoComprado);
	
			fflush(stdin);
	
			printf("\t\tAdicione a Classe:  ");
			gets(reserva.classe);
	
			fflush(stdin);
	
			printf("\t\tAdicione a data da Reserva [DD-MM-AAAA]: ");
			scanf("%d%d%d", &reserva.dataReserva.dia, 
			&reserva.dataReserva.mes, &reserva.dataReserva.ano);

            fseek(fp, -sizeof(RESERVA), SEEK_CUR); // Volta para sobrescrever
            fwrite(&reserva, sizeof(RESERVA), 1, fp);

            printf("\t\tPassageiro atualizado com sucesso!\n");
            break;
        }
    }

    if (!encontrado) {
        printf("\t\tPassageiro não encontrado ou já excluído!\n");
    }

    fclose(fp);
}




void salvarReserva()
{
	FILE *fp;
	RESERVA reserva;
	
	//abrir ou criar o ficheiro 
	fp = fopen("RESERVA.DAT", "ab");
	
	//movimentar o File Pointer
	fseek(fp, 0L, SEEK_END);	//SEEK_SET, SEEK_CUR, SEEK_END
	
	//pedir dados ao utilizador
	pedirDadosReserva(&reserva);
	
	//escrever os dados da estrutura para o ficheiro
	if( fwrite(&reserva, sizeof(RESERVA), 1, fp) == 1)
	{
		system("cls");
		puts("Registo adicionado com sucesso no Ficheiro");
	}
	
	// fechar o ficheiro
	fclose( fp );
}


void mostrarReserva(RESERVA reserva)
{
	printf("\tID: %d\n", reserva.id);
	
	printf("\tPassageiro [ID]: %d\n", reserva.idPassageiro);
	
	printf("\tViagem [ID]: %d\n", reserva.idViagem);
	
	printf("\tAssento Comprado: %d\n", reserva.assentoComprado);

	printf("\tClasse: %s\n", reserva.classe);
		
	printf("\tData de Nascimento: %d/%d/%d\n", 
		reserva.dataReserva.dia, 
		reserva.dataReserva.mes, 
		reserva.dataReserva.ano);	
		
	printf("\tFuncionario: %s\n", reserva.funcionario);
	
}


void listarReserva()
{
	FILE *fp;
	RESERVA reserva;
	
	//abrir ou criar o ficheiro 
	fp = fopen("RESERVA.DAT", "rb");
	
	//movimentar o File Pointer
	fseek(fp, 0L, SEEK_SET);	
//	rewind(fp);
		
	system("cls");
	
	puts("\n\t\tLISTAGEM DE RESERVA");
	
	//escrever os dados da estrutura para o ficheiro
	while( fread(&reserva, sizeof(RESERVA), 1, fp) == 1)
	{		
		printf("****************************************\n");
		mostrarReserva(reserva);		
	}
		
	fclose( fp );
}


void pesquisarReservaPorID()
{
	FILE *fp;
	RESERVA reserva;
	int idProcurado;
	
	//abrir ou criar o ficheiro 
	fp = fopen("RESERVA.DAT", "rb");
	
	//colocar o File Pointer no principio do ficheiro
	rewind(fp);
	
		system("cls");
						
	printf("\n\tPESQUISA POR ID\n");
	printf("\t------------------------------------------------\n");
	printf("\t\tDigite o ID da reserva Procurado: ");
	scanf("%d", &idProcurado);
	
	//escrever os dados da estrutura para o ficheiro
	while( fread(&reserva, sizeof(RESERVA), 1, fp) == 1)
	{	
		
		if (reserva.id == idProcurado)
		{	
			system("cls");
						
			printf("\n\tRESERVA ENCONTRADA!\n");
			printf("\t------------------------------------------------\n");
			mostrarReserva(reserva);
			
			fclose(fp);
			return;
		}
	}
	
	printf("%Reserva nao Encontrado!...\n");
		
	fclose( fp );
}
