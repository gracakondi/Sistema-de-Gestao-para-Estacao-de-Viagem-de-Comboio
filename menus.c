#include <stdio.h>
#include <stdlib.h>
#include "menus.h"

#define MENU_PASSAGEIRO 1
#define MENU_VIAGEM 2
#define MENU_RESERVA 3
#define MENU_COMBOIO 4
#define MENU_DEFESA 6
#define SAIR_DA_APLICACAO 5

#define NOVO_PASSAGEIRO 1
#define EDITAR_PASSAGEIRO 2
#define ELIMINAR_PASSAGEIRO 3
#define LISTAR_PASSAGEIRO 4
#define PESQUISAR_PASSAGEIRO 5
#define VOLTAR_PASSAGEIRO 6

#define NOVA_VIAGEM 1
#define EDITAR_VIAGEM 2
#define ELIMINAR_VIAGEM 3
#define LISTAR_VIAGEM 4
#define PESQUISAR_VIAGEM 5
#define VOLTAR_VIAGEM 6

#define NOVA_RESERVA 1
#define EDITAR_RESERVA 2
#define ELIMINAR_RESERVA 3
#define LISTAR_RESERVA 4
#define PESQUISAR_RESERVA 5
#define VOLTAR_RESERVA 6

#define NOVO_COMBOIO 1
#define EDITAR_COMBOIO 2
#define ELIMINAR_COMBOIO 3
#define LISTAR_COMBOIO 4
#define PESQUISAR_COMBOIO 5
#define VOLTAR_COMBOIO 6

//DADOS DA DEFESA
#define CADASTRAR_DEFESA 1
#define PESQUISAR_DEFESA 2
#define VOLTAR_DEFESA 3


	
void apresentacao()
{
	char opcao;
	
	printf("\n");
	printf("\tUNIVERSIDADE CATOLICA DE ANGOLA\n");
	printf("\tFACULDADE DE ENGENHARIA\n");
	printf("\tPROJECTO DE FUNDAMENTOS DE PROG. I ANO 24-25\n");
	printf("\tAUTOR: GILDO KONDI, N. 33049\n");
	printf("\t------------------------------------------------\n");
	printf("\tTEMA: GESTAO DE UMA AGENCIA DE VIAGENS DE COMBOIO\n");
	printf("\tDOCENTE: ENG. OSVALDO RAMOS\n");
	printf("\tOBS: USO EXCLUSIVO DENTRO DA UCAN\n");
	printf("\t------------------------------------------------\n");
	printf("\n");
	printf("\tSE CONCORDA COM OS TERMOS DE USO DIGITE S, N CASO CONTRARIO\n");
	
	scanf(" %c", &opcao);	
	
	if (opcao == 'S' || opcao == 's')
	fazerLogin();
//	menuPrincipal();
	else
	{
		printf("ate a proxima!\n");
		return;
	}
}


void menuPrincipal()
{
	int opcao;
	
	do
	{
		
	system("cls");

	printf("\n\t\tMENU PRINCIPAL\n");
	printf("\t------------------------------------------------\n");
	printf("\t\t1 - MENU PASSAGEIRO\n");
	printf("\t\t2 - MENU VIAGEM\n");
	printf("\t\t3 - MENU RERSERVA\n");
	printf("\t\t4 - MENU COMBOIO\n");
	printf("\t\t5 - SAIR DA APLICACAO\n");
	printf("\t------------------------------------------------\n");
	printf("\t\t6 - MENU DEFESA\n");
	printf("\n");
	printf("\t\tEscolha uma Opcao\n");
	scanf("%d", &opcao);
	
	switch(opcao)
	{
		case MENU_PASSAGEIRO:
			menuPassageiro();
		break;
		
		case MENU_VIAGEM:
			menuViagem();
		break;
		
		case MENU_RESERVA:
			menuReserva();
		break;
		
		case MENU_COMBOIO:
			menuComboio();
		break;
		
		case SAIR_DA_APLICACAO:
			return;
		break;
		
		case MENU_DEFESA:
			menuDefesa();
		break;
		
		default:
			printf("Opcao Invalida!\n");
	}
}while (opcao != SAIR_DA_APLICACAO);
}


void menuPassageiro()
{
	int opcao;
	
	do
	{

	
	system("cls");
	
	printf("\n\t\tMENU PASSAGEIRO\n");
	printf("\t------------------------------------------------\n");
	printf("\t\t1 - NOVO PASSAGEIRO\n");
	printf("\t\t2 - EDITAR DADOS DO PASSAGEIRO\n");
	printf("\t\t3 - ELIMINAR PASSAGEIRO\n");
	printf("\t\t4 - LISTAR TODOS PASSAGEIROS\n");
	printf("\t\t5 - PESQUISAR PASSAGEIRO\n");
	printf("\t\t6 - VOLTAR\n");
	printf("\n");
	printf("\t------------------------------------------------\n");
	printf("\t\tEscolha uma opcao\n");
	scanf("%d", &opcao);
	
	switch (opcao)
	{
		case NOVO_PASSAGEIRO:
			salvarDadosPassageiro();
			system("pause");			
		break;
		
		case EDITAR_PASSAGEIRO:
			 editarPassageiro();
		break;
		
		case ELIMINAR_PASSAGEIRO:
			 apagarPassageiro();
		break;
	
		case LISTAR_PASSAGEIRO:
			listarPassageiro();
			system("pause");
		break;
		
		case PESQUISAR_PASSAGEIRO:
			pesquisarPassageiroPorNome();
			system("pause");
		break;
			
		case VOLTAR_PASSAGEIRO:
			return;
		break;
		
		default:
			printf("Opcao Invalida\n");
	}	
	
	}	while (opcao != VOLTAR_PASSAGEIRO);
	
}


void menuViagem()
{
	int opcao;
	
	do 
	{

	system("cls");
	
	printf("\n\t\tMENU VIAGENS\n");
	printf("\t------------------------------------------------\n");
	printf("\t\t1 - NOVA VIAGEM\n");
	printf("\t\t2 - EDITAR VIAGEM\n");
	printf("\t\t3 - ELIMINAR VIAGEM\n");
	printf("\t\t4 - LISTAR TODAS AS VIAGENS\n");
	printf("\t\t5 - PESQUISAR VIAGEM\n");
	printf("\t\t6 - VOLTAR\n");
	printf("\n");
	printf("\t------------------------------------------------\n");
	printf("\t\tEscolha uma opcao\n");
	scanf("%d", &opcao);
	
	switch (opcao)
	{
		case NOVA_VIAGEM:
			salvarViagem();	
			system("pause");		
		break;
		
		case EDITAR_VIAGEM:
			editarViagem();
		break;
		
		case ELIMINAR_VIAGEM:
			apagarViagem();
		break;
	
		case LISTAR_VIAGEM:
			listarViagem();
			system("pause");
		break;
		
		case PESQUISAR_VIAGEM:
			pesquisarViagemPorNome();
			system("pause");
		break;
			
		case VOLTAR_VIAGEM:
			return;
		break;
		
		default:
			printf("Opcao Invalida\n");
	}
}while (opcao != SAIR_DA_APLICACAO);
}

void menuReserva()
{
	int opcao;
	
	do 
	{
	
	system("cls");
	
	printf("\n\t\tMENU RESERVA\n");
	printf("\t------------------------------------------------\n");
	printf("\t\t1 - ADICIONAR NOVA RESERVA\n");
	printf("\t\t2 - EDITAR UMA RESERVA\n");
	printf("\t\t3 - ELIMINAR RESERVA\n");
	printf("\t\t4 - LISTAR RESERVA\n");
	printf("\t\t5 - PESQUISAR RESERVA\n");
	printf("\t\t6 - VOLTAR\n");
	printf("\n");
	printf("\t------------------------------------------------\n");
	printf("\t\tEscolha uma opcao\n");
	scanf("%d", &opcao);
	
	
	switch (opcao)
	{
		case NOVA_RESERVA:
			salvarReserva();	
			system("pause");		
		break;
		
		case EDITAR_RESERVA:
			editarReserva();
		break;
		
		case ELIMINAR_RESERVA:
			apagarReserva();
		break;
	
		case LISTAR_RESERVA:
			listarReserva();
			system("pause");
		break;
		
		case PESQUISAR_RESERVA:
			pesquisarReservaPorID();
			system("pause");
		break;
			
		case VOLTAR_RESERVA:
			return;
		break;
		
		default:
			printf("Opcao Invalida\n");
	}
	
}while (opcao != SAIR_DA_APLICACAO);
}

void menuComboio()
{
	int opcao;
	
	do
	{
	
	system("cls");
	
	printf("\n\t\tMENU COMBOIO\n");
	printf("\t------------------------------------------------\n");
	printf("\t\t1 - ADICIONAR NOVO COMBOIO\n");
	printf("\t\t2 - EDITAR COMBOIO\n");
	printf("\t\t3 - ELIMINAR COMBOIO\n");
	printf("\t\t4 - LISTAR TODOS OS COMBOIOS\n");
	printf("\t\t5 - PESQUISAR COMBOIO\n");
	printf("\t\t6 - VOLTAR\n");
	printf("\n");
	printf("\t------------------------------------------------\n");
	printf("\t\tEscolha uma opcao\n");
	scanf("%d", &opcao);
	
	switch (opcao)
	{
		case NOVO_COMBOIO:
			salvarComboio();			
		break;
		
		case EDITAR_COMBOIO:
			editarComboio();
		break;
		
		case ELIMINAR_COMBOIO:
			apagarComboio();
		break;
	
		case LISTAR_COMBOIO:
			listarComboio();
			system("pause");
		break;
		
		case PESQUISAR_COMBOIO:
			pesquisarComboioPorNome();
			system("pause");
		break;
			
		case VOLTAR_COMBOIO:
			return;
		break;
		
		default:
			printf("Opcao Invalida\n");
	}
	
	}while (opcao != SAIR_DA_APLICACAO);
}


void menuDefesa()
{
	int opcao;
	
	do
	{

	
	system("cls");
	
	printf("\n\t\tMENU DEFESA\n");
	printf("\t------------------------------------------------\n");
	printf("\t\t1 - CADASTRAR DEFESA\n");
	printf("\t\t2 - PESQUISAR DEFESA\n");
	printf("\t\t3 - VOLTAR\n");
	printf("\n");
	printf("\t------------------------------------------------\n");
	printf("\t\tEscolha uma opcao\n");
	scanf("%d", &opcao);
	

	switch (opcao)
	{
		case CADASTRAR_DEFESA:
			salvarComboio();
			system("pause");			
		break;
		
		case PESQUISAR_DEFESA:
			pesquisarComboioPor2Nome();
			system("pause");
		break;
			
		case VOLTAR_DEFESA:
			return;
		break;
		
		default:
			printf("Opcao Invalida\n");
	}	
	
	}	while (opcao != VOLTAR_DEFESA);
	
}
