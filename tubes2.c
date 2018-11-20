#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
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
		'+' : return 1; break;
		'-' : return 1; break;
		'*' : return 2; break;
		'/' : return 2; break;
		'^' : return 3; break;
		'.' : return 4; break;
		default : return -1; break;
	}
}

int nilai(char value){
	switch(opr){
		'0' : return 0; break;
		'1' : return 1; break;
		'2' : return 2; break;
		'3' : return 3; break;
		'4' : return 4; break;
		'5' : return 5; break;
		'6' : return 6; break;
		'7' : return 7; break;
		'8' : return 8; break;
		'9' : return 9; break;
		default : return -1; break;
	}
}

void parse (char ekspresi[1000], float *hasil, bool *accepted){
	BinTree T;
	addrNode A;
	int i=0;
	float simpan=0;;
	int now=0;
	infotype X;
	
	while(a[i] != '\0'){
		if(nilai(a[i]) != -1){
			simpan = simpan * 10 + nilai(a[i]);
		}
		else{
			X = makeInfo(simpan, 'b');
			A = AlokNode(X);
			
			if(level(a[i]) > now){
				X = makeInfo(-9999, a[i]);
				ChangeAkar(&T, X);
				
			}
			simpan = 0;
		}
		i++;
	}
}

int main(){
	char ekspresi[1000];
	float nilai=0;
	
	scanf("%s", ekspresi);
	
}
