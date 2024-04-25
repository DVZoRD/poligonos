#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Estrutura para representar um ponto no plano 2D
typedef struct {
    float X;
    float Y;
} Ponto;

// Função para calcular a área de um triângulo dados três vértices
float AreaTriangulo(Ponto A, Ponto B, Ponto C) {
    float Det = A.X * (B.Y - C.Y) + B.X * (C.Y - A.Y) + C.X * (A.Y - B.Y);
    return fabs(Det) / 2.0;
}

// Função para calcular a área de um polígono com a fórmula de Shoelace
float AreaPoligono(Ponto* pontos, int num_pontos) {
    if (num_pontos < 3) {
        printf("Nao e possível calcular a area para menos de 3 pontos.\n");
        return 0.0;
    }
    
    float area = 0.0;
    for (int i = 0; i < num_pontos; i++) {
        int j = (i + 1) % num_pontos;  
        area += pontos[i].X * pontos[j].Y;
        area -= pontos[i].Y * pontos[j].X;
    }
    area = fabs(area) / 2.0;
    return area;
}

int main() {
    // Lê o arquivo de entrada com os vértices do polígono
    FILE* file = fopen("poligono.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    int num_pontos;
    if (fscanf(file, "%d", &num_pontos) != 1) {  // Verifica se a leitura foi bem-sucedida
        printf("Erro ao ler o número de vertices.\n");
        fclose(file);
        return 1;
    }

    if (num_pontos < 3) {  // Checa se o número de vértices é suficiente para um polígono
        printf("Numero insuficiente de vertices para um poligono.\n");
        fclose(file);
        return 1;
    }

    // Aloca memória para os pontos do polígono
    Ponto* pontos = (Ponto*)malloc(sizeof(Ponto) * num_pontos);
    if (pontos == NULL) {
        printf("Erro ao alocar memoria para os pontos.\n");
        fclose(file);
        return 1;
    }

    // Lê as coordenadas dos vértices
    for (int i = 0; i < num_pontos; i++) {
        if (fscanf(file, "%f %f", &pontos[i].X, &pontos[i].Y) != 2) {  // Verifica se a leitura foi bem-sucedida
            printf("Erro ao ler as coordenadas dos vertices.\n");
            free(pontos);
            fclose(file);
            return 1;
        }
    }

    fclose(file);

    // Calcula a área do polígono usando a fórmula de Shoelace
    float area = AreaPoligono(pontos, num_pontos);

    printf("A area do poligono e %.2f\n", area);

    free(pontos);

    return 0;
}
