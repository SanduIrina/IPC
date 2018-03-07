#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int mask_transf(int mask, int print){
	int aux = 0;
	if(mask>=24){
		mask = mask-24;
		while(mask >= 1){
			aux = aux + pow(2,8-mask);
			mask--;
		}
		
		if(print) printf("255.255.255.%d\n", aux);
		return aux*10+4;
	}

	if(mask<24 && mask>=16){
		mask = mask-16;
		while(mask >= 1){
			aux = aux + pow(2,8-mask);
			mask--;
		}
		if(print) printf("255.255.%d.0\n", aux);
		return aux*10+3;
	}
	
	if(mask<16 && mask>=8){
		mask = mask-8;
		while(mask >= 1){
			aux = aux + pow(2,8-mask);
			mask--;
		}
		if(print) printf("255.%d.0.0\n", aux);
		return aux*10+2;
	}

	if(mask<8){
		while(mask >= 1){
			aux = aux + pow(2,8-mask);
			mask--;
		}
		if(print) printf("%d.0.0.0\n", aux);
		return aux*10+1;
	}
}

void base32(int n){
	int lead;
	lead = 0;
	while(n>=32){
		n = n-32;
		lead++;
	}
	if(n<10){
		if(lead) 
			printf("%d%d",lead,n);
		else printf("%d",n);
	}
	else{
		char a;
		a = 55 + n;
		if(lead)
			printf("%d%c",lead,a);
		else 
			printf("%c",a);
	} 
}

int* mask_bytes(int comp){
	int *maskuse = malloc(4*sizeof(int));
	if(comp%10 == 1){
		comp = comp/10;
		maskuse[0] = comp;
		maskuse[1] = maskuse[2] = maskuse[3] = 0;
	}
	else if(comp%10 == 2){
		comp = comp/10;
		maskuse[1] = comp;
		maskuse[0] = 255;
		maskuse[2] = maskuse[3] = 0;
	}
	else if(comp%10 == 3){
		comp = comp/10;
		maskuse[2] = comp;
		maskuse[0] = maskuse[1] = 255;
		maskuse[3] = 0;
	}
	else if(comp%10 == 4){
		comp = comp/10;
		maskuse[3] = comp;
		maskuse[0] = maskuse[1] = maskuse[2] = 255;
	}
	return maskuse;
}

void base16(int *ip1){
	int j,k,max = 7;
	int bin[8];
	for(j=0; j<4; j++){
		max = 7;
		while(max >= 0){
			if(ip1[j] >= pow(2,max)){
				ip1[j] -= pow(2,max);
				bin[max] = 1;
				max--;
			}		
			else {
				bin[max] = 0;
				max--;
			}
		}
		for(k = 7; k>= 0; k--)
			printf("%d",bin[k]);
		if(j!=3)
			printf(".");
	}		
}

int main(){
	int set_nr,i,comp;
	scanf("%d",&set_nr);
	for(i=1;i<=set_nr;i++){
		int nr, j, ip_tmp[4], maskuse_out[4],k;
		int *maskuse = malloc(4*sizeof(int));
		int *ip1 = malloc(sizeof(int)*4);
		int *ip2 = malloc(sizeof(int)*4);
		int mask1, mask_tmp;
		printf("%d\n", i);
		scanf("%d.%d.%d.%d/%d", &ip1[0],&ip1[1],&ip1[2],&ip1[3],&mask1);
		scanf("%d.%d.%d.%d", &ip2[0],&ip2[1],&ip2[2],&ip2[3]);
		scanf("%d", &nr);
	
		//TASK 0

		printf("-0 ");
		printf("%d.%d.%d.%d\n", ip1[0],ip1[1],ip1[2],ip1[3]);

		//TASK 1
		
		printf("-1 ");
		comp = mask_transf(mask1,1);	

		//TASK 2

		maskuse = mask_bytes(comp);

		int ok = 1;
		for(j=0;j<4;j++){
			maskuse_out[j] = ip1[j] & maskuse[j];
			if(maskuse_out[j] != (ip2[j] & maskuse[j])) 
				ok = 0;
		}

		printf("-2 ");
		printf("%d.%d.%d.%d\n", maskuse_out[0],maskuse_out[1],maskuse_out[2],maskuse_out[3]);

		//TASK 3

		for(j=0;j<4;j++){
			maskuse_out[j] = ip1[j] | (255-maskuse[j]);
		}

		printf("-3 ");
		printf("%d.%d.%d.%d\n", maskuse_out[0],maskuse_out[1],maskuse_out[2],maskuse_out[3]);

		//TASK 4

		printf("-4 ");

		if(ok) 
			printf("da\n");
		else 
			printf("nu\n");

		//TASK 5

		printf("-5 %X.%X.%X.%X %o.%o.%o.%o\n", ip1[0],ip1[1],ip1[2],ip1[3],ip2[0],ip2[1],ip2[2],ip2[3]);

		//TASK 6

		printf("-6 ");
		if(ok){
			printf("0\n");
			for(j=0;j<nr;j++){
				scanf("%d.%d.%d.%d/%d", &ip_tmp[0],&ip_tmp[1],&ip_tmp[2],&ip_tmp[3],&mask_tmp);
			}
		}	

		else {
			for(j=0;j<nr;j++){
				scanf("%d.%d.%d.%d/%d", &ip_tmp[0],&ip_tmp[1],&ip_tmp[2],&ip_tmp[3],&mask_tmp);
				int comp1 = mask_transf(mask_tmp,0);
				int *mbyte = malloc(4*sizeof(int));
				int *maskuse_out1 = malloc(4*sizeof(int));
				mbyte = mask_bytes(comp1);
				int ok1 = 1;
				for(k=0;k<4;k++){
					maskuse_out1[k] = ip_tmp[k] & mbyte[k];
					if(maskuse_out1[k] != (ip2[k] & mbyte[k]))
						ok1 = 0;
				}
				if(ok1)
					printf("%d ",j+1);
			}
		}
		
		printf("\n");
		
		//TASK 7

		int ip1a[4],ip2a[4];

		for(j=0; j<4 ;j++){
			ip1a[j] = ip1[j];
			ip2a[j] = ip2[j];
		}

		printf("-7 ");

		base16(ip1);
		printf(" ");

		base16(ip2);
		printf("\n");

		//TASK 8

		printf("-8 ");
		for(k=0; k<4; k++){
			base32(ip1a[k]);
			if(k!=3) 
				printf(".");
		}
		printf(" ");

		for(j=0; j<4; j++){
			base32(ip2a[j]);
			if(j!=3) 
				printf(".");
		}
		printf("\n");
	}
}