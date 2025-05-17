typedef struct
{
	int dia, mes, ano;
}DATE;

typedef struct
{
	int hora, minuto;
}TIME;

typedef struct
{
		int id, telefone;
	 	char nome [50], bi[15], genero[10];
	 	DATE dataNascimento;
}PASSAGEIRO;

typedef struct
{
		int id, capacidadeTotal, lugaresDisponiveis;
		char nomeComboio [20], diocese[50], paroquia[50];			
}COMBOIO;


typedef struct
{
		int id, idComboio, preco;
		char rota [50], tipo [30], paragens [100];
		DATE dataViagem;
		TIME horario;
}VIAGEM;

typedef struct
{
		int id, idPassageiro, idViagem, assentoComprado;
		char funcionario [50], classe [10];
		DATE dataReserva;
			
}RESERVA;
