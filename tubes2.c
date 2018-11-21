#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "pohoncalc.h"

#define VAL_UNDEF -9999

infotype makeInfo(float Value, char Opr){
	infotype tempInfo;

	tempInfo.value = Value;
	tempInfo.operand = Opr;

	return tempInfo;
}

int level(char opr){
	switch(opr){
		case '+' : return 1; break;
		case '-' : return 1; break;
		case '*' : return 2; break;
		case '/' : return 2; break;
		case '^' : return 3; break;
		case '.' : return 4; break;
		default : return 99; break;
	}
}

int nilai(char value){
	switch(value){
		case '0' : return 0; break;
		case '1' : return 1; break;
		case '2' : return 2; break;
		case '3' : return 3; break;
		case '4' : return 4; break;
		case '5' : return 5; break;
		case '6' : return 6; break;
		case '7' : return 7; break;
		case '8' : return 8; break;
		case '9' : return 9; break;
		case '(' : return -2; break;
		default : return -1; break;
	}
}

void calc(BinTree T, float *hasil, bool *acc){
	if(*acc){
		float hasilkiri=0, hasilkanan=0;
		bool acc2=true;
		
		if((Akar(T)).operand == 'b'){
			*hasil = (Akar(T)).value;
		}
		else if((Akar(T)).operand == '+'){
			calc(Left(T),&hasilkiri,&acc2);
			calc(Right(T),&hasilkanan,&acc2);
			
			*hasil = hasilkiri+hasilkanan;
		}
		else if((Akar(T)).operand == '-'){
			calc(Left(T),&hasilkiri,&acc2);
			calc(Right(T),&hasilkanan,&acc2);
			
			*hasil = hasilkiri-hasilkanan;
		}
		else if((Akar(T)).operand == '*'){
			calc(Left(T),&hasilkiri,&acc2);
			calc(Right(T),&hasilkanan,&acc2);
			
			*hasil = hasilkiri*hasilkanan;
		}
		else if((Akar(T)).operand == '/'){
			calc(Left(T),&hasilkiri,&acc2);
			calc(Right(T),&hasilkanan,&acc2);
			
			if(hasilkanan != 0){
				*hasil = (hasilkiri / hasilkanan);
			}
			else{
				*acc = false;
			}
		}
		else if((Akar(T)).operand == '^'){
			calc(Left(T),&hasilkiri,&acc2);
			calc(Right(T),&hasilkanan,&acc2);
			
			if((hasilkiri <0) && ((hasilkanan) > (-1)) && (hasilkiri < 1)){
				*acc = false;
			}
			else{
				*hasil = pow(hasilkiri,hasilkanan);
			}
		}
		else if((Akar(T)).operand == '.'){
			calc(Left(T),&hasilkiri,&acc2);
			calc(Right(T),&hasilkanan,&acc2);
			
			while((hasilkanan > 1) || (hasilkanan < -1)){
				hasilkanan /= 10;
			}
			
			*hasil = hasilkiri+hasilkanan;
		}
	}
	
}

bool hitungkurung(char *ekspresi){
	int kurungkiri=0,kurungkanan=0;
	
	while(*ekspresi != '\0'){
		if(*ekspresi == '('){
			kurungkiri++;
		}
		else if(*ekspresi == ')'){
			kurungkanan++;
		}
		
		ekspresi++;
	}
	
	printf("%d %d\n", kurungkiri, kurungkanan);
	
	return (kurungkiri == kurungkanan);
}

void cleaning(BinTree T){

	if(IsUnerLeft(T)){
		cleaning(Left(T));
	}

	if(IsUnerRight(T)){
		cleaning(Right(T));
	}

	DealokNode(T);
}

void parse (char *ekspresi, float *hasil, bool *accepted){
	BinTree T;
	addrNode tempNode, lastNode;
	float tempRec;
	int currentLevel;
	infotype tempInfo;
	bool statusopr=false;

	*accepted = true;
	
		// inisialisasi akar
		tempInfo = makeInfo(0, 'b');
		T = Tree(tempInfo, Nil, Nil, Nil);
		lastNode = T;
		currentLevel = 99;
		
		// skip whitespaces
		while (*ekspresi == ' ') { ekspresi++; }
	
		while(*ekspresi != '\0' && *ekspresi != ')' && *accepted){
			if(nilai(*ekspresi) == -2){ // karakter '('
				ekspresi++;
				parse(ekspresi, &tempRec, accepted);
				
				// skip to after parenthesis
				while (*ekspresi != ')') { ekspresi++; }
	
				if (*accepted) {
					// add daun
					tempInfo = makeInfo(tempRec, 'b');
					AddDaun(&lastNode, tempInfo, false);
					lastNode = Right(lastNode);
				}
			}
			else if(nilai(*ekspresi) != -1){ // merupakan angka
				if (Akar(lastNode).value != VAL_UNDEF) {
					Akar(lastNode).value = Akar(lastNode).value * 10 + nilai(*ekspresi);
				}
				else {
					// add daun
					tempInfo = makeInfo(nilai(*ekspresi), 'b');
					AddDaun(&lastNode, tempInfo, false);
					lastNode = Right(lastNode);
				}
				
				statusopr = false;
			}
			else{ // merupakan operand
				tempInfo = makeInfo(VAL_UNDEF, *ekspresi);
				if(!statusopr){ //sebelumnya bukan operand
					if(level(*ekspresi) <= currentLevel){
						ChangeAkar(&T, tempInfo, true);
						lastNode = T;
					}
					else{
						ChangeAkar(&lastNode, tempInfo, true);
					}
	
					currentLevel = level(*ekspresi);
					statusopr = true;
				}
				else{
					*accepted = false;
				}
			}
	
			// skip whitespaces
			while (*ekspresi == ' ') { ekspresi++; }
	
			ekspresi++;
		}
		
		//PrintTree(T);
	
	
	if(*accepted){
		calc(T, hasil, accepted);
		
		if(*accepted){
			printf("hasil=%.2f\n", *hasil);
		}
		else{
			printf("MATH ERROR\n");
		}
	}
	else{
		printf("SYNTAX ERROR\n");
	}
	
	cleaning(T);
}

int main(){
	char input[512];
	float hasil=0;
	bool acc;

	scanf("%s", input);
	
	acc = hitungkurung(input);
	
	if(acc){
		parse(input, &hasil, &acc);
	}
	else{
		printf("SYNTAX ERROR\n");
	}

	//printf("%.2f\n", hasil);
}
