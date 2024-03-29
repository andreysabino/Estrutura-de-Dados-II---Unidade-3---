#ifndef ESTRUTURAS_CPP
#define ESTRUTURAS_CPP
#define SIZE 159
#define MAX 5570
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef float latitude;
typedef float longitude;

struct cidade {
    unsigned int id;
    char *estado;
    char *cidade;
    int vizinhos;
};

struct gps {
    unsigned int id;
    latitude la;
    longitude lo;
};

struct dataItem {
    int key;
    cidade city;
    gps GPS;
    float km;
    int vizinhos;
};

cidade *getCidades(char *arquivo) {
    FILE *f = fopen(arquivo, "r");
    cidade *cidades = (cidade *)malloc(MAX * sizeof(cidade));
    if (!f) {
        perror("Arquivo não existe");
        return NULL;
    }
    fscanf(f, "CODIGO MUNICIPIO;UF;NOME MUNICIPIO");
    unsigned int cod;
    char *uf;
    char *cid;
    int i = 0;
    int j = 0;
    while (!feof(f)) {
        uf = (char *)malloc(2 * sizeof(char));
        cid = (char *)malloc(40 * sizeof(char));
        fscanf(f, "%d %s ", &cod, uf);
        fgets(cid, 40 * sizeof(char), f);
       // printf("%d %s %s", cod, uf, cid);
    
        cidades[j].id = cod;
        cidades[j].estado = uf;
        cidades[j].cidade = cid;
        j = j + 1;
       
        i = i + 1;
    }
    return cidades;
}

gps *getGps(char *localizacoes) {
    FILE *f = fopen(localizacoes, "r");
    gps *local = (gps *)malloc(MAX * sizeof(gps));
    if (!f) {
        perror("Arquivo não existe");
        return NULL;
    }
    fscanf(f, "CODIGO MUNICIPIO;LATITUDE;LONGITUDE");
    unsigned int cod;
    latitude la;
    longitude lo;
    int i = 0, j = 0;
    while (!feof(f)) {
        
        fscanf(f, "%u;%f;%f", &cod, &la, &lo);
            local[i].id = cod;
            local[i].la = la;
            local[i].lo = -1*lo;
            i = i + 1; 
        
    }
    return local;
}

dataItem *getItens(cidade *cities, gps *local) {
    dataItem *dados = (dataItem *)malloc(MAX * sizeof(dataItem));
    int k = 0;
    for (size_t i = 0; i < MAX; i++) {
        dados[k].key = cities[i].id;
        for (size_t j = 0; j < MAX; j++) {
            if (cities[i].id == local[j].id) {
                dados[k].city = cities[i];
                dados[k].GPS = local[j];
                k++;
            }
        }
    }
    return dados;
}

struct vizinhanca{
    int pos;
    int posvoid;
    int qntvizinhos;
};

float dist(dataItem A, dataItem B){
    float d = 0;
    d = sqrt(pow((A.GPS.la - B.GPS.la),2)+pow((A.GPS.lo - B.GPS.lo),2));
 
    return d;

}

dataItem *criando_grafo(char *arquivo1, char *arquivo2){
    dataItem *d = (dataItem*)malloc(sizeof(dataItem));

    int i = 0;
    cidade *cidades = getCidades(arquivo1);
    gps *local = getGps(arquivo2);
    d = getItens(cidades,local);
    int k = 0;
    dataItem *cidadesRN = (dataItem*)malloc(167*sizeof(dataItem));
    
    for(int i = 0; i < 5570; i++){
        if(strcmp(d[i].city.estado,"RN") == 0){
            cidadesRN[k] = d[i];
            k++;
        }
    }

    return cidadesRN;
}

vizinhanca matriz_grafo(dataItem *G, float D){
    int j, i;
float g[167][167], V;
    for(i = 0; i < 167; i++){
       j = 0; 
        while(j < 167){

           V = dist(G[i],G[j]); 

                if(V < D){
                            
                g[i][j] = V;
                g[j][i] = V;

                } else {
                    g[i][j] = 0;
                    g[i][j] = 0;
                }
                            
            j++;
        }    
    }

    int aux = 0;
    vizinhanca vizinhos;
    vizinhos.qntvizinhos = 0;
    vizinhos.pos = 0; 
    vizinhos.posvoid = -1;

    for(i = 0; i < 167; i++){
        j = 0;
        while(j < 167){
            if (g[i][j] > 0){
                aux++;
            }
            j++;
        }

        if (aux > vizinhos.qntvizinhos){
            vizinhos.qntvizinhos = aux;
            vizinhos.pos = i;          
            aux = 0;
        } else if(aux == 0){
            vizinhos.posvoid = i;
        }
    }

    return vizinhos;
}

#endif
