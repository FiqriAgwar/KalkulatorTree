#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "pohoncalc.h"
/*
bool cekKurung(char check[1000]){
	int countleft=0;
	int countright=0;
	
	for(int i=0;i<strlen(check);i++){
		if(check[i] == '('){
			countleft++;
		}
		
		if(check[i] == ')'){
			countright++;
		}
	}
	
	return(countleft == countright);
}

bool cekDoubleOp(char check[1000]){
	bool valid = true;
	
	for(int i=1;i<strlen(check);i++){
		// check +-*/ /*dengan karakter sebelumnya sebelumnya.
		//contoh tidak valid = ++ )+ (+ ^+
		if((((check[i]) == '+') || ((check[i]) == '-') || ((check[i]) == '*') || ((check[i]) == '/') && (((check[i-1]) == '+') || ((check[i-1]) == '-') || ((check[i-1]) == '*') || ((check[i-1]) == '/') || ((check[i-1]) == '(')  || ((check[i-1]) == '^')){
			valid = false;
		} 
*/		
		//check ) dengan sebelumnya
		//seluruh operator kecuali kurung, tepat sebelum ) tidak valid
/*		if(((check[i]) == ')') && (((check[i-1]) == '+') || ((check[i-1]) == '-') || ((check[i-1]) == '*') || ((check[i-1]) == '/') || ((check[i-1]) == '^'))){
			valid = false;
		}
*/		
		//check ^ dengan sebelumnya
		// contoh tidak valid : +^ (^
/*		if(((check[i]) == '^') && (((check[i-1]) == '+') || ((check[i-1]) == '-') || ((check[i-1]) == '*') || ((check[i-1]) == '/') || ((check[i-1]) == '^') || ((check[i-1]) == '('))){
			valid = false;
		}
	}
	
	return valid;
}
*/
infotype makeInfo(int Value, char Opr){
	infotype X;
	
	X.value = Value;
	X.operand = Opr;
	
	return X;
}

int level(char opr){
	switch(opr){
		case '+' : return 1; break;
		case '-' : return 1; break;
		case '*' : return 2; break;
		case '/' : return 2; break;
		case '^' : return 3; break;
		case '.' : return 4; break;
		default : return -1; break;
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

float calc(BinTree T){
	if((Akar(T)).operand == 'b'){
		return (Akar(T)).value;
	} 
	else{
		if((Akar(T)).operand == '+'){
			return  (calc(Left(T)) + calc(Right(T)));
		}
		else if((Akar(T)).operand == '-'){
			return  (calc(Left(T)) - calc(Right(T)));
		}
		else if((Akar(T)).operand == '*'){
			return  (calc(Left(T)) * calc(Right(T)));
		}
		else if((Akar(T)).operand == '/'){
			return  (calc(Left(T)) / calc(Right(T)));
		}
		else if((Akar(T)).operand == '^'){
			return  pow(calc(Left(T)), calc(Right(T)));
		}
		else if((Akar(T)).operand == '.'){
			//gak tahu
		}
	}
}

void parse (char a[1000], float *hasil, bool *accepted){
	BinTree T;
	addrNode A, last=Nil;
	int i=0;
	float simpan=0;;
	int now=0;
	infotype X;
	
	while(a[i] != Nil){
		if(nilai(a[i]) != -1){
			simpan = simpan * 10 + nilai(a[i]);
		}
		else if(nilai(a[i]) == -2){
			
			//debug yang ini pls
			X = makeInfo(0, 'b');
			A = AlokNode(X);
			Parent(A) = last;
		}
		else{
			//sama ini
			X = makeInfo(simpan, 'b');
			A = AlokNode(X);
			
			if(level(a[i]) > now){
				X = makeInfo(-9999, a[i]);
				ChangeAkar(&T, X);
				Parent(A) = T;
				Left(T) = A;
				last = Right(A);
			}
			else{
				AddDaun(&T,X,false);
			}
			simpan = 0;
			now = level(a[i]);
		}
		i++;
	}
	
	*hasil = calc(T);
}



void cleaning(BinTree T){
	
	while(!IsTreeEmpty(T)){
		if(IsTreeOneElmt(T)){
			DealokNode(T);
		}
		else{
			if(IsUnerLeft(T)){
				cleaning(Left(T));
			}
			else if(IsUnerRight(T)){
				cleaning(Right(T));
			}
			else{
				cleaning(Left(T));
				cleaning(Right(T));
			}
		}
	}
}

int main(){
	char ekspresi[1000];
	float hasil=0;
	bool acc=true;
	
	scanf("%s", &ekspresi);
	parse(ekspresi, &hasil, &acc);
	
	printf("%f\n", hasil);
}
