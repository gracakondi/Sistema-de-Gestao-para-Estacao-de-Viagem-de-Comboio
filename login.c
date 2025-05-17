#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include "menus.h"

// Credenciais fixas
#define USERNAME "admin"
#define PASSWORD "33049"

void fazerLogin() {
    char username[50], password[50];
    
	system("cls");
	
	printf("\n\t\t TELA DE LOGIN\n");
	printf("\t----------------------------------------\n");
	
    printf("\t\tDigite o nome de usuario: ");
    scanf("%s", username);

    printf("\t\tDigite a senha: ");
    scanf("%s", password);

	printf("\n\t\tANALISANDO... ");
	Sleep(2000);
	
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        printf("\n\t\tLogin bem-sucedido! Bem-vindo, %s.\n", USERNAME);
        	Sleep(1000);
        	menuPrincipal();
    } else {
         printf("\n\tERROR: VOCE ERROU NAS CREDENCIAIS\n");
        return;
    }
}
