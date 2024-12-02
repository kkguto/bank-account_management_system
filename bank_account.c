//Bank Account Management System

#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <time.h>

//Declarando Funções para a verificação do CPF
int todos_iguais(char[]);
int verificador_cpf(char[]);

struct Conta{
	char nome[50];
	char senha[15];
	char cpf[15];
	float dinheiro;
};

//Função para criar uma Conta
int criar_conta(struct Conta *contas, int *count, int max){
	
	if(*count >= max){
		printf("Limite maximo atingido\n");
		return 0;
	}
	
	struct Conta nova_conta;

	printf("Nome: ");
	scanf(" %[^\n]s", nova_conta.nome);
	
	printf("CPF (formato XXX.XXX.XXX-YY): ");
	scanf("%14s", nova_conta.cpf);
	
	if(verificador_cpf(nova_conta.cpf) == 0){
	    printf("\nCPF Inválido\n");
	    return 0;
	}
	
	printf("Senha: ");
	scanf("%15s", nova_conta.senha);
	printf("Deposito Inicial: ");
	scanf("%f", &nova_conta.dinheiro);
	
	contas[*count] = nova_conta;//Copia os dados da nova conta para posição correta
	
	(*count)++; //incrementando +1 no contador;
	return 1;
}

//Função para exibir as Contas
void exibir_contas(struct Conta *contas, int count){
	int i; 
	for(i = 0; i<count; i++){
		printf("Conta %d: ", i+1);
		printf("Nome: %s, CPF: %s\n", contas[i].nome, contas[i].cpf);
	}
}

//Função para buscar uma conta a partir do CPF
int buscar_conta(struct Conta *conta, int count){
	int i;
	char cpf_buscar[15];
	int encontrado = -1;
	printf("Digite o CPF da conta(formato XXX.XXX.XXX-YY): ");
	scanf("%14s", cpf_buscar);
	for(i = 0; i < count; i++){
		if(strcmp(cpf_buscar, conta[i].cpf) == 0){
			printf("\nConta Encontrada:\n");
			printf("Nome: %s, CPF: %s\n", conta[i].nome, conta[i].cpf);
			encontrado = i; // Armazena o indice da conta na variavel
			break;
		}
	}
	
	if(encontrado == -1){
		printf("Nenhuma conta encontrada com o CPF fornecido.\n");
	}
	
	return encontrado;
}

//Função para a validação de senha
int validacao(struct Conta *conta, int count){
	
	int indice = buscar_conta(conta, count);
	if (!indice){
		return 0; //Retorna 0 para conta não encontrada 
	}
	
	char senha_valida[15];
	
	printf("Digite a senha da conta %s", conta[indice].cpf);
	scanf("%14s", senha_valida);
		
	if(strcmp(senha_valida, conta[indice].senha) == 0){
		printf("Acesso válidado.");
		return 1;
	}else{
		printf("Senha Incorreta\n");
		return -1;
	}
}

//Função para depositar
int depositar(struct Conta *conta, int count){
	float valor_deposito;
	
	int indice = validacao(conta, count);
	
	if(indice < 0){
		return; //A validaçao não deu certo, entao encerra a função
	}
	
	printf("Digite o valor a ser depositado: ");
	scanf("%f", &valor_deposito);
	
	if(valor_deposito <= 0){
		printf("Valor inválido para depósito.\n");
        return;
	}
	
	conta[indice].dinheiro += valor_deposito;
	printf("Depósito realizado com sucesso! Saldo atual: R$%.2f\n", conta[indice].dinheiro);
}

//Função de saque
int sacar(struct Conta *conta, int count){
	float valor_sacar;
	int indice = validacao(conta, count);
	
	if(indice < 0){
		return; //A validaçao não deu certo, entao encerra a função
	}
	
	printf("Digite o valor a ser Sacado: ");
	scanf("%f", &valor_sacar);
	
	if(valor_sacar > conta[indice].dinheiro || valor_sacar <= 0){
		printf("Valor inválido para saque. Verifique seu Saldo\n");
        return;
	}
	
	conta[indice].dinheiro -= valor_sacar;
	printf("Saque realizado com sucesso! Saldo atual: R$%.2f\n", conta[indice].dinheiro);
}

int main(){
	setlocale(LC_ALL, "");
	int max = 5;
	struct Conta contas[max];
	int count = 0;
	int escolha;
	
	while(1){
		
		printf("\n\tMenu Principal\n");
		printf("[1] Criar Conta\n[2] Mostrar Todas as Contas\n[3] Buscar Conta\n[4] Depostar Dinheiro\n[5] Sacar Dinheiro\n[0] Sair\n");
		printf("------------------------------\n");
		printf("Sua escolha é: ");
		scanf("%d", &escolha);
		
		if(escolha == 0){
			printf("\nEncerrado");
			break;
		}
		
		if(escolha == 1){
			criar_conta(contas, &count, max);
		}else if(escolha == 2){
			exibir_contas(contas, count);
		}else if(escolha == 3){
			printf("\nBuscando...\n");
			sleep(2);
			buscar_conta(contas, count);
		}else if(escolha == 4){
			depositar(contas, count);
		}else if(escolha == 5){
			sacar(contas, count);
		}else{
			printf("\n**Opção Inválida**\n");
		}
	}
	
	return 0;
} 

//funçoes para a verificação de cpf
int todos_iguais(char cpf[]) {
	int i;
    for (i = 1; i < 11; i++) {
        if (cpf[i] != cpf[0]) {
            return 0; // Retorna falso se encontrar algum caractere diferente
        }
    }
    return 1; // Retorna verdadeiro se todos forem iguais
}

int verificador_cpf(char cpf[]){
	char numeros[12];
	
	int i, j = 0;
	int soma = 0, soma2 = 0;
	
	//Guardando os numeros do cpf no vetor numeros[] usando isdigit()
	for(i = 0; i < strlen(cpf); i++){
		if(isdigit(cpf[i])){
			numeros[j] = cpf[i];
			j++;
		}
	}
	
	numeros[j] = '\0';
	
	if(strlen(numeros) != 11){
		printf("Cpf Invalido: Quantidade de Digitos Incorreta");
		return 0; // Retorna 0 para CPF inválido
	}
	
	if(todos_iguais(numeros)){
		printf("Cpf Invalido: contém todos os dígitos iguais.\n");
		return 0; // Retorna 0 para CPF inválido
	}
	
	//Validação do Primeiro digito
	for(i = 0; i<9; i++){
		soma += (numeros[i] - '0') * (10 - i); 
	}
	
	int digito1 = (soma * 10) % 11;
	
	if(digito1 == 10){
		digito1 = 0;
	}
	
	////Validação do Segundo digito
	for(i = 0; i<10; i++){
		soma2 += (numeros[i] - '0') * (11 - i); 
	}
	
	int digito2 = (soma2 * 10) % 11;
	
	if(digito2 == 10){
		digito2 = 0;
	}
	
	if(digito1 == (numeros[9] - '0') && digito2 == (numeros[10] - '0')){
		return 1; // Retorna 1 para CPF Valido
	}
	
	return 0; // Retorna 0 para CPF inválido
}
