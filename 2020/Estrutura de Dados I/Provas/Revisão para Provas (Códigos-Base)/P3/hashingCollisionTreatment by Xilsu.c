#include <math.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_M 150
#define MAX_DIGITS 15


/*----- Auxiliary functions implementations -----*/
int countDigits(long long int numbers){
    int digits;
    
    digits = 0;

    while(numbers > 0){
        numbers /= 10;

        digits++;
    }

    return digits;
}
/*----------------------------------------------*/


/*----- Hashing functions implementations -----*/
int divisionHashing(long long int key, int M){
	return key % M;
}

int midSquareHashing(long long int key, int M, int tableDigits){
    long long int keySquare;
    char stringHash[MAX_DIGITS];
    int keySquareDigits;

    keySquare = key * key;
    sprintf(stringHash, "%lld", keySquare);
    keySquareDigits = strlen(stringHash);
    
    int mid, bottomLimit, topLimit;
    
    mid = keySquareDigits / 2;
    bottomLimit = mid - tableDigits / 2;
    topLimit = mid + tableDigits / 2;

    if(bottomLimit < 0){
       bottomLimit = 0;
    }

    if(topLimit >= keySquareDigits){
        topLimit = keySquareDigits - 1;
    }

    long long int midSquareHash, power;
    int i;

    midSquareHash = 0;
    power = pow(10, tableDigits - 1);    

    for(i = bottomLimit; i <= topLimit && power > 0; i++, power /= 10){
        midSquareHash += (stringHash[i] - '0') * power;
    }

    return divisionHashing(midSquareHash, M);
}

int radixTransformationHashing(long long int key, int M, int base){
    char stringHash[MAX_DIGITS];
    int i;

    i = -1;

    while(key > 0){
        stringHash[++i] = (key % base) + '0';
        key /= base;
    }

    long long int radixTransformationHash, power;

    radixTransformationHash = 0;
    power = pow(10, i);

    for(i = i; i >= 0; i--, power /= 10){
        radixTransformationHash += (stringHash[i] - '0') * power;
    }
    
    return divisionHashing(radixTransformationHash, M);
}

int digitExtractionHashing(long long int key, int M, int tableDigits){
    char stringHash[MAX_DIGITS];
    int keyDigits;

    sprintf(stringHash, "%lld", key);
    keyDigits = strlen(stringHash);

    if(tableDigits > keyDigits){
        tableDigits = keyDigits;
    }

    long long int digitExtractionHash, power;
    int bottomPosition;

    digitExtractionHash = 0;
    power = pow(10, tableDigits - 1);
    bottomPosition = -1;

    while(power > 1){
        digitExtractionHash += (stringHash[++bottomPosition] - '0') * power;

        power /= 10;
    }

    digitExtractionHash += (stringHash[keyDigits - 1] - '0') * power;
   
    return divisionHashing(digitExtractionHash, M);
}

int deslocatedEnlaceHashing(long long int key, int M, int tableDigits){
    char stringHash[MAX_DIGITS];
    int keyDigits;

    sprintf(stringHash, "%lld", key);
    keyDigits = strlen(stringHash);

    if(tableDigits > keyDigits){
        tableDigits = keyDigits;
    }

    long long int deslocatedEnlaceHash, aux, power;
    int maxHashDigits, i;
    
    deslocatedEnlaceHash = 0;
    aux = 0;
    power = pow(10, tableDigits - 1);
    maxHashDigits = (ceil((float) keyDigits / tableDigits)) * tableDigits;

    for(i = 0; i < maxHashDigits; i++){
        if(i < keyDigits){
            aux += (stringHash[i] - '0') * power;
            
            power /= 10;
        }
        
        if((i + 1) % tableDigits == 0){
            deslocatedEnlaceHash += aux;
            
            aux = 0;
            power = pow(10, tableDigits - 1);
        } 
    }

    return divisionHashing(deslocatedEnlaceHash, M);
}

long long int reverseHash(long long int hashPartition){
    char stringHash[MAX_DIGITS];

    sprintf(stringHash, "%lld", hashPartition);
    strrev(stringHash);

    sscanf(stringHash, "%lld", &hashPartition);

    return hashPartition;
}

int limitEnlaceHashing(long long int key, int M, int tableDigits){
    char stringHash[MAX_DIGITS];
    int keyDigits;

    sprintf(stringHash, "%lld", key);
    keyDigits = strlen(stringHash);

    if(tableDigits > keyDigits){
        tableDigits = keyDigits;
    }

    long long int limitEnlaceHash, aux, power;
    int maxHashDigits, inverte, i;

    limitEnlaceHash = 0;
    aux = 0;
    power = pow(10, tableDigits - 1);
    maxHashDigits = (ceil((float) keyDigits / tableDigits)) * tableDigits;
    inverte = 0;

    for(i = 0; i < maxHashDigits; i++){
        if(i < keyDigits){
            aux += (stringHash[i] - '0') * power;

            power /= 10;
        }
        
        if((i + 1) % tableDigits == 0){
            if(inverte){
                aux = reverseHash(aux);

                inverte = 0;
            }
            else{
                inverte = 1;
            }

            limitEnlaceHash += aux;
            
            aux = 0;
            power = pow(10, tableDigits - 1);
        }
    }

    return divisionHashing(limitEnlaceHash, M); 
}

long long int fold(long long int foldHash, long long int aux, int tableDigits, int inverte){
    char fold1[MAX_DIGITS], fold2[MAX_DIGITS];
    int fold1Digits, fold2Digits;

    sprintf(fold1, "%lld", foldHash);
    sprintf(fold2, "%lld", aux);

    if(inverte){
        strrev(fold2);
    }

    fold1Digits = strlen(fold1);
    fold2Digits = strlen(fold2);

    if(fold2Digits < tableDigits){
        int i;

        for(i = fold2Digits - 1; i < tableDigits; i++){
            fold2[i] = 0;
        }

        fold2[i] = '\0';

        strrev(fold2);
    }

    long long int newHash, power;
    int i;

    newHash = 0;
    power = pow(10, tableDigits - 1);

    for(i = 0; i < tableDigits; i++, power /= 10){
        int fold;

        fold = 0;

        if(i < fold1Digits){
            fold += fold1[i] - '0';
        }

        if(i < fold2Digits){
            fold += fold2[i] - '0';
        }

        if(fold >= 10){
            fold %= 10;
        }

        newHash += fold * power;
    }

    return newHash;
}

int foldHashing(long long int key, int M, int tableDigits){
    char stringHash[MAX_DIGITS];
    int keyDigits;

    sprintf(stringHash, "%lld", key);
    keyDigits = strlen(stringHash);

    if(tableDigits > keyDigits){
        tableDigits = keyDigits;
    }

    long long int foldHash, aux, power;
    int maxHashDigits, inverte, i;

    foldHash = 0;
    aux = 0;
    power = pow(10, tableDigits - 1);
    maxHashDigits = (ceil((float) keyDigits / tableDigits)) * tableDigits;
    inverte = 0;

    for(i = 0; i < maxHashDigits; i++){
        if(i < keyDigits){
            aux += (stringHash[i] - '0') * power;

            power /= 10;
        }
        
        if((i + 1) % tableDigits == 0){
            foldHash = fold(foldHash, aux, tableDigits, inverte);
            
            if(!inverte){
                inverte = 1;
            }

            aux = 0;
            power = pow(10, tableDigits - 1);
        }
    }

    return divisionHashing(foldHash, M); 
}
/*---------------------------------------------*/


/*----- Collision treatment implementations -----*/
int oneRegionInteriorChaining(int hashTable[], int chainingTable[], long long int key, int index, int M){
    if(hashTable[index] == -1){
        hashTable[index] = key;

        return index;
    }
    
    int hashLength, chainedIndex, auxIndex;

    hashLength = M - 1;
    chainedIndex = index;
    auxIndex = chainingTable[index];

    while(hashLength >= 0){
        if(hashTable[hashLength] == -1){
            hashTable[hashLength] = key;

            while(auxIndex != -1){
                chainedIndex = auxIndex;
                auxIndex = chainingTable[auxIndex];
            }

            chainingTable[chainedIndex] = hashLength;

            return hashLength;
        }

        hashLength--;
    }

    return -1;
}

int twoRegionInteriorChaining(int hashTable[], int chainingTable[], long long int key, int index, int M, int N){
    if(hashTable[index] == -1){
        hashTable[index] = key;

        return index;
    }
    
    int reservedLength, chainedIndex, auxIndex;

    reservedLength = N - M;
    chainedIndex = index;
    auxIndex = chainingTable[index];

    while(reservedLength < N){
        if(hashTable[reservedLength] == -1){
            hashTable[reservedLength] = key;

            while(auxIndex != -1){
                chainedIndex = auxIndex;
                auxIndex = chainingTable[auxIndex];
            }

            chainingTable[chainedIndex] = reservedLength;

            return reservedLength;
        }

        reservedLength++;
    }
    
    return -1;
}

int linearProbingOpenAdressing(int hashTable[], long long int key, int index, int M){
    if(hashTable[index] == -1){
        hashTable[index] = key;

        return index;
    }

    int auxIndex, k;
    
    for(k = 1; k < M; k++){
        auxIndex = (index + k) % M;

        if(hashTable[auxIndex] == -1){
            hashTable[auxIndex] = key;

            return auxIndex;
        }
    }
    
    return -1;
}

int quadraticProbingOpenAdressing(int hashTable[], long long int key, int index, int M){
    if(hashTable[index] == -1){
        hashTable[index] = key;

        return index;
    }

    int auxIndex, k;
    
    for(k = 1; k < M; k++){
        auxIndex = (index + 3 * k * k + 7 * k) % M;

        if(hashTable[auxIndex] == -1){
            hashTable[auxIndex] = key;

            return auxIndex;
        }
    }
    
    return -1;
}

int doubleDispersionOpenAdressing(int hashTable[], long long int key, int index, int M){
    if(hashTable[index] == -1){
        hashTable[index] = key;

        return index;
    }

    int auxIndex, k;
    
    for(k = 1; k < M; k++){
        auxIndex = (index + 3 * (key % 7)) % M;

        if(hashTable[auxIndex] == -1){
            hashTable[auxIndex] = key;

            return auxIndex;
        }
    }
    
    return -1;
}
/*-----------------------------------------------*/


/*----- Main function -----*/
int main(){
    int M, tableDigits;
	
    printf("\n\nEntre com o tamanho da tabela (M <= 20): ");
	
    do{ 
        scanf("%d", &M);
	}while(M < 0 || M > MAX_M);

    tableDigits = countDigits(M - 1);

    long long int key;
    int hashTable[MAX_M], chainingTable[MAX_M];
    int optionHashFunction, optionTreatment, base, index, N, a1, a2, i;

    for(i = 0; i < MAX_M; i++){
        hashTable[i] = -1;
        chainingTable[i] = -1;
    }

	do{
		printf("\nQual funcao hash vai usar?\n");
        printf("[1] Divisao Inteira\n");
		printf("[2] Meio Quadrado\n");
		printf("[3] Transformacao de Raiz\n");
		printf("[4] Extracao\n");
		printf("[5] Enlace Deslocado\n");
		printf("[6] Enlace Limite\n");
		printf("[7] Dobra\n");
		printf("Opcao: ");
		
        scanf("%d", &optionHashFunction);
	}while(optionHashFunction < 1 || optionHashFunction > 7);

    do{
		printf("\nQual armazenamento vai usar?\n");
		printf("[1] Encadeamento Interior de Uma Regiao\n");
		printf("[2] Encadeamento Interior de Duas Regioes\n");
		printf("[3] Encadeamento Exterior\n");
		printf("[4] Enderecamento Aberto por Tentativa Linear\n");
		printf("[5] Enderecamento Aberto por Tentativa Quadratica\n");
		printf("[6] Enderecamento Aberto por Dispersao Dupla\n");
		printf("Opcao: ");

		scanf("%d", &optionTreatment);
	}while(optionTreatment < 1 || optionTreatment > 6);

    if(optionTreatment == 2){
        printf("\nEntre com N (tamanho da tabela + posicoes para chaves sinonimas): ");

        do{
            scanf("%d", &N);
        }while(N < M || N > MAX_M);
    }

    printf("\nEntre com as chaves. Digite -1 como valor da chave para encerrar...");
	
    do{
		printf("\nEntre com a chave: ");
		scanf("%lld", &key);

		switch(optionHashFunction) {
            case 1:
                index = divisionHashing(key, M);

                printf("Indice: %d", index);
                
                break;
            case 2:
                index = midSquareHashing(key, M, tableDigits);
                
                break;
            case 3:
                printf("\nEntre com a base: ");
		        scanf("%d", &base);

                index = radixTransformationHashing(key, M, base);
                
                break;
            case 4:
                index = digitExtractionHashing(key, M, tableDigits);
                
                break;
            case 5:
                index = deslocatedEnlaceHashing(key, M, tableDigits);
                
                break;
            case 6:
               index = limitEnlaceHashing(key, M, tableDigits);
                
                break;
            case 7:
                index = foldHashing(key, M, tableDigits);
                
                break;
        }

        switch(optionTreatment){
            case 1:
                N = M;

                index = oneRegionInteriorChaining(hashTable, chainingTable, key, index, M);

                if(index != -1){
                    printf("\nInseriu chave %d na tabela de tamanho %d no indice %d.", key, M, index);
                }
                else{
                    printf("\nNao foi inserido, pois faltou espaco para insercao.");
                }

                break;
            case 2:
                index = twoRegionInteriorChaining(hashTable, chainingTable, key, index, M, N);

                if(index != -1){
                    printf("\nInseriu chave %d na tabela de tamanho %d no indice %d.", key, M, index);
                }
                else{
                    printf("\nNao foi inserido, pois faltou espaco para insercao.");
                }

                break;
            case 4:
                index = linearProbingOpenAdressing(hashTable, key, index, M);

                if(index != -1){
                    printf("\nInseriu chave %d na tabela de tamanho %d no indice %d.", key, M, index);
                }
                else{
                    printf("\nNao foi inserido, pois faltou espaco para insercao.");
                }

                break;
            case 5:
                index = quadraticProbingOpenAdressing(hashTable, key, index, M);

                if(index != -1){
                    printf("\nInseriu chave %d na tabela de tamanho %d no indice %d.", key, M, index);
                }
                else{
                    printf("\nNao foi inserido, pois faltou espaco para insercao.");
                }

                break;
            case 6:
                index = doubleDispersionOpenAdressing(hashTable, key, index, M);

                if(index != -1){
                    printf("\nInseriu chave %d na tabela de tamanho %d no indice %d.", key, M, index);
                }
                else{
                    printf("\nNao foi inserido, pois faltou espaco para insercao.");
                }

                break;
            default:
                printf("Nao implementado.");
        }

        printf("\nTabela Hash: ");

        for(int i = 0; i < M; i++){
            printf("\t%d", hashTable[i]);
        }

        if(optionTreatment == 1 || optionTreatment == 2){
            printf("\nEncadeamento:");
    
            for(int i = 0; i < N; i++){
                printf("\t%d", chainingTable[i]);
            }
        }
        
        printf("\n");
	}while(key != -1);
}
/*------------------------*/
