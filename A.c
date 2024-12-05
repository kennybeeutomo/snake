#include <stdio.h>

int main(){
	
	int lahan;
	scanf("%d", &lahan);
	
	double sum = 0;
	
	for (int i = 0; i < lahan; i++){
		int panjang, lebar;
		scanf("%d %d", &panjang, &lebar);
		
		sum += panjang * lebar;
	}
	
	int teman;
	scanf("%d", &teman);
	
	sum = sum / teman;
	
	printf("%.2lf\n", sum);
	
	return 0;
}
