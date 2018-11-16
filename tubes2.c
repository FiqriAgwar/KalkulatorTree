#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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
		// check +-*/ dengan karakter sebelumnya sebelumnya.
		//contoh tidak valid = ++ )+ (+ ^+
		if((((check[i]) == '+') || ((check[i]) == '-') || ((check[i]) == '*') || ((check[i]) == '/') && (((check[i-1]) == '+') || ((check[i-1]) == '-') || ((check[i-1]) == '*') || ((check[i-1]) == '/') || ((check[i-1]) == '(') || ((check[i-1]) == ')') || ((check[i-1]) == '^')){
			valid = false;
		} 
		
		//check ) dengan sebelumnya
		//seluruh operator kecuali kurung, tepat sebelum ) tidak valid
		if(((check[i]) == ')') && (((check[i-1]) == '+') || ((check[i-1]) == '-') || ((check[i-1]) == '*') || ((check[i-1]) == '/') || ((check[i-1]) == '^'))){
			valid = false;
		}
		
		//check ^ dengan sebelumnya
		// contoh tidak valid : +^ (^
		if(((check[i]) == '^') && (((check[i-1]) == '+') || ((check[i-1]) == '-') || ((check[i-1]) == '*') || ((check[i-1]) == '/') || ((check[i-1]) == '^') || ((check[i-1]) == '('))){
			valid = false;
		}
	}
}

int main(){
	
}
