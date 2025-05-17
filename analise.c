/*************************
FileName: Annalise.c
Tema: Gestão de Agência de Viagens de Comboio
Nome: Gildo Graça Kondi
N. 33049
Data do Ficheiro: 13/01/2024
**************************


1. Descricao:
	Implementar um sistema capaz de registar dados de passageiros, viagens, 
	comboios e  reservas de uma agencia de viagem de comboio.

2. Menus do Projecto:
	2.1- MENU PRINCIPAL 
	2.2 - MENU PASSAGEIRO
	2.3 - MENU VIAGEM
	2.4 - MENU RESERVA
	2.5 - MENU COMBOIO
	
		2.2.1 - MENU PASSAGEIRO
			1 - NOVO PASSAGEIRO
			2 - EDITAR PASSAGEIRO
			3 - ELIMINAR PASSAGEIRO
			4 - LISTAR PASSAGEIRO
			5 - PESQUISAR PASSAGEIRO
			6 - VOLTAR
			
		2.3.1 - MENU VIAGEM
			1 - NOVO VIAGEM
			2 - EDITAR VIAGEM
			3 - ELIMINAR VIAGEM
			4 - LISTAR VIAGEM
			5 - PESQUISAR VIAGEM
			6 - VOLTAR 
			
		2.4.1 - MENU RESERVA
			1 - NOVO RESERVA
			2 - EDITAR RESERVA
			3 - ELIMINAR RESERVA
			4 - LISTAR RESERVA
			5 - PESQUISAR RESERVA
			6 - VOLTAR
			
		2.5.1 - MENU COMBOIO
			1 - NOVO COMBOIO
			2 - EDITAR COMBOIO
			3 - ELIMINAR COMBOIO
			4 - LISTAR COMBOIO
			5 - PESQUISAR COMBOIO
			6 - VOLTAR


3. Entidades
	3.0 DATE
		int dia, mes, ano;
		
	3.0.1
		TIME 
		int hora, minuto;
		
	3.1 PASSAGEIRO	
			int id;	
			int telefone;
	 		char nome [50];
	 		char bi[15]; 
			char genero[10];
	 		DATE dataNascimento;
		
	3.2 VIAGEM 
			int id;
			int idComboio;
			char rota [50];
	 		int preco;
		  	char paragens [100];
		  	char tipo [15];
			TIME horario;
	 		DATE dataViagem;
		
	3.3 RESERVA
			int id;
			int idPassageiro;
			int idViagem;
			DATE dataReserva;
			int assentoComprado;
			char funcionario [50];
			char classe [10];
	
	3.4 COMBOIO
			int id;
			char nomeComboio [20];
			int capacidadeTotal;
			int lugaresReservados;
	
4. Ficheiros de Dados
	PASSAGEIROS.DAT
	VIAGEM.DAT
	RESERVA.DAT
	COMBOIO.DAT
	
5. Implementacao
Linguagem C, no IDE: Dev-C++
*/
