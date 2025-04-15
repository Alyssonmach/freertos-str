// Disciplina: Sistemas em Tempo Real - Engenharia Elétrica
// Aluno: Alysson Machado
// Matrícula: 119110236
// Universidade Federal de Campina Grande (UFCG)

#include <FreeRTOS.h>
//#include <pthread.h>
#include <semphr.h>
#include <stdio.h>

#define TEMPO_OPERACAO_ROBO 100
#define TEMPO_MOVIMENTO_R1_R2_R4 500
#define TEMPO_MOVIMENTO_R3 800
#define TEMPO_PRODUCAO_M1_M2 1500
#define TEMPO_PRODUCAO_M3 3000

SemaphoreHandle_t xTemEntradaCelIn;
SemaphoreHandle_t xTemSaidaCelIn;

SemaphoreHandle_t xTemEntradaM1;
SemaphoreHandle_t xItemProntoM1;
SemaphoreHandle_t xTemSaidaM1;

//pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int vezM1 = 1;

SemaphoreHandle_t xTemEntradaM2;
SemaphoreHandle_t xItemProntoM2;
SemaphoreHandle_t xTemSaidaM2;

SemaphoreHandle_t xTemEntradaM3;
SemaphoreHandle_t xItemProntoM3;
SemaphoreHandle_t xTemSaidaM3;

int vezM4 = 1;

SemaphoreHandle_t xTemEntradaCelOut;
SemaphoreHandle_t xItemProntoCelOut;

void vMaquinaCelin(void *pvParameters);
void vRoboR1(void *pvParameters);
void vMaquinaM1(void *pvParameters);
void vRoboR2(void *pvParameters);
void vMaquinaM2(void *pvParameters);
void vRoboR3(void *pvParameters);
void vMaquinaM3(void *pvParameters);
void vRoboR4(void *pvParameters);
void vMaquinaCelOut(void *pvParameters);

int main() {

    xTemEntradaCelIn = xSemaphoreCreateBinary();
    xTemSaidaCelIn = xSemaphoreCreateBinary();

    xTemEntradaM1 = xSemaphoreCreateBinary();
    xItemProntoM1 = xSemaphoreCreateBinary();
    xTemSaidaM1 = xSemaphoreCreateBinary();

    xTemEntradaM2 = xSemaphoreCreateBinary();
    xItemProntoM2 = xSemaphoreCreateBinary();
    xTemSaidaM2 = xSemaphoreCreateBinary();

    xTemEntradaM3 = xSemaphoreCreateBinary();
    xItemProntoM3 = xSemaphoreCreateBinary();
    xTemSaidaM3 = xSemaphoreCreateBinary();

    xTemEntradaCelOut = xSemaphoreCreateBinary();
    xItemProntoCelOut = xSemaphoreCreateBinary();

    xSemaphoreGive(xTemEntradaCelIn);
    xSemaphoreGive(xTemEntradaM1);
    xSemaphoreGive(xTemEntradaM2);
    xSemaphoreGive(xTemEntradaM3);
    xSemaphoreGive(xTemEntradaCelOut);

    xTaskCreate(vMaquinaCelin, "Célula de Entrada", 128, NULL, 1, NULL);
    xTaskCreate(vRoboR1, "Robo R1", 128, NULL, 1, NULL);
    xTaskCreate(vMaquinaM1, "Máquina M1", 128, NULL, 1, NULL);
    xTaskCreate(vRoboR2, "Robo R2", 128, NULL, 1, NULL);
    xTaskCreate(vMaquinaM2, "Máquina M2", 128, NULL, 1, NULL);
    xTaskCreate(vRoboR3, "Robo R3", 128, NULL, 1, NULL);
    xTaskCreate(vMaquinaM3, "Máquina M3", 128, NULL, 1, NULL);
    xTaskCreate(vRoboR4, "Robo R4", 128, NULL, 1, NULL);
    xTaskCreate(vMaquinaCelOut, "Célula de Saída", 128, NULL, 1, NULL);

    vTaskStartScheduler();

    return 0;
}

void vMaquinaCelin(void *pvParameters) {
    (void) pvParameters;
    int item = 0;

    while (1) {
        if (xSemaphoreTake(xTemEntradaCelIn, portMAX_DELAY) == pdTRUE) {
            printf("CelulaIn: Item na Entrada, processando...\n");
            vTaskDelay(pdMS_TO_TICKS(TEMPO_PRODUCAO_M1_M2));
            printf("CelulaIn: Item pronto na saida\n");
            xSemaphoreGive(xTemSaidaCelIn);
        }
    }
}

void vRoboR1(void *pvParameters) {
    (void) pvParameters;
    int item;

    while (1) {
        if (xSemaphoreTake(xTemSaidaCelIn, portMAX_DELAY) == pdTRUE) {
            printf("R1: Movendo para CélulaIn\n");
            vTaskDelay(pdMS_TO_TICKS(TEMPO_MOVIMENTO_R1_R2_R4));
    
            printf("R1: Retirando da CélulaIn\n");
            vTaskDelay(pdMS_TO_TICKS(TEMPO_OPERACAO_ROBO));
            
            xSemaphoreGive(xTemEntradaCelIn);
            
            if (xSemaphoreTake(xTemEntradaM1, portMAX_DELAY) == pdTRUE) {
                printf("R1: Movendo para M1\n");
                vTaskDelay(pdMS_TO_TICKS(TEMPO_MOVIMENTO_R1_R2_R4));

                printf("R1: Depositando em M1\n");
                vTaskDelay(pdMS_TO_TICKS(TEMPO_OPERACAO_ROBO));

                xSemaphoreGive(xItemProntoM1);
            }
        }
    }
}

void vMaquinaM1(void *pvParameters) {
    (void) pvParameters;
    int item = 0;

    while (1) {
        if (xSemaphoreTake(xItemProntoM1, portMAX_DELAY) == pdTRUE) {
            printf("M1: Item na Entrada, processando...\n");
            vTaskDelay(pdMS_TO_TICKS(TEMPO_PRODUCAO_M1_M2));
            printf("M1: Item pronto na saida\n");
            xSemaphoreGive(xTemSaidaM1);
        }
    }
}

void vRoboR2(void *pvParameters) {
    (void) pvParameters;
    int item;

    while (1) {
        if (vezM1 == 1) {
            if (xSemaphoreTake(xTemSaidaM1, portMAX_DELAY) == pdTRUE) {
                printf("R2: Movendo para M1\n");
                vTaskDelay(pdMS_TO_TICKS(TEMPO_MOVIMENTO_R1_R2_R4));
        
                printf("R2: Retirando da M1\n");
                vTaskDelay(pdMS_TO_TICKS(TEMPO_OPERACAO_ROBO));
                
                xSemaphoreGive(xTemEntradaM1);
                vezM1 = 2;
                
                if (xSemaphoreTake(xTemEntradaM2, portMAX_DELAY) == pdTRUE) {
                    printf("R2: Movendo para M2\n");
                    vTaskDelay(pdMS_TO_TICKS(TEMPO_MOVIMENTO_R1_R2_R4));

                    printf("R2: Depositando em M2\n");
                    vTaskDelay(pdMS_TO_TICKS(TEMPO_OPERACAO_ROBO));

                    xSemaphoreGive(xItemProntoM2);
                }
            }
        }
    }
}

void vMaquinaM2(void *pvParameters) {
    (void) pvParameters;
    int item = 0;

    while (1) {
        if (xSemaphoreTake(xItemProntoM2, portMAX_DELAY) == pdTRUE) {
            printf("M2: Item na Entrada, processando...\n");
            vTaskDelay(pdMS_TO_TICKS(TEMPO_PRODUCAO_M1_M2));
            printf("M2: Item pronto na saida\n");
            xSemaphoreGive(xTemSaidaM2);
        }
    }
}

void vRoboR3(void *pvParameters) {
    (void) pvParameters;
    int item;

    while (1) {
        if (vezM1 == 2) {
            if (xSemaphoreTake(xTemSaidaM1, portMAX_DELAY) == pdTRUE) {
                printf("R3: Movendo para M1\n");
                vTaskDelay(pdMS_TO_TICKS(TEMPO_MOVIMENTO_R1_R2_R4));
        
                printf("R3: Retirando da M1\n");
                vTaskDelay(pdMS_TO_TICKS(TEMPO_OPERACAO_ROBO));
                
                xSemaphoreGive(xTemEntradaM1);
                vezM1 = 1;
                
                if (xSemaphoreTake(xTemEntradaM3, portMAX_DELAY) == pdTRUE) {
                    printf("R3: Movendo para M3\n");
                    vTaskDelay(pdMS_TO_TICKS(TEMPO_MOVIMENTO_R3));

                    printf("R3: Depositando em M3\n");
                    vTaskDelay(pdMS_TO_TICKS(TEMPO_OPERACAO_ROBO));

                    xSemaphoreGive(xItemProntoM3);
                }
            }
        }
    }
}

void vMaquinaM3(void *pvParameters) {
    (void) pvParameters;
    int item = 0;

    while (1) {
        if (xSemaphoreTake(xItemProntoM3, portMAX_DELAY) == pdTRUE) {
            printf("M3: Item na Entrada, processando...\n");
            vTaskDelay(pdMS_TO_TICKS(TEMPO_PRODUCAO_M1_M2));
            printf("M3: Item pronto na saida\n");
            xSemaphoreGive(xTemSaidaM3);
        }
    }
}

void vRoboR4(void *pvParameters) {
    (void) pvParameters;
    int item;

    while (1) {
        if (vezM4 == 1) {
            if (xSemaphoreTake(xTemSaidaM2, portMAX_DELAY) == pdTRUE) {
                printf("R4: Movendo para M2\n");
                vTaskDelay(pdMS_TO_TICKS(TEMPO_MOVIMENTO_R1_R2_R4));
        
                printf("R4: Retirando da M2\n");
                vTaskDelay(pdMS_TO_TICKS(TEMPO_OPERACAO_ROBO));
                
                xSemaphoreGive(xTemEntradaM2);
                vezM4 = 2;
            }
        }
        else {
            if (xSemaphoreTake(xTemSaidaM3, portMAX_DELAY) == pdTRUE) {
                printf("R4: Movendo para M3\n");
                vTaskDelay(pdMS_TO_TICKS(TEMPO_MOVIMENTO_R1_R2_R4));
        
                printf("R4: Retirando da M3\n");
                vTaskDelay(pdMS_TO_TICKS(TEMPO_OPERACAO_ROBO));
                
                xSemaphoreGive(xTemEntradaM3);
                vezM4 = 1;
            }
        }

        if (xSemaphoreTake(xTemEntradaCelOut, portMAX_DELAY) == pdTRUE) {
            printf("R4: Movendo para CelOut\n");
            vTaskDelay(pdMS_TO_TICKS(TEMPO_MOVIMENTO_R3));

            printf("R4: Depositando em CelOut\n");
            vTaskDelay(pdMS_TO_TICKS(TEMPO_OPERACAO_ROBO));

            xSemaphoreGive(xItemProntoCelOut);
        }
    }
}

void vMaquinaCelOut(void *pvParameters) {
    (void) pvParameters;
    int item = 0;

    while (1) {
        if (xSemaphoreTake(xItemProntoCelOut, portMAX_DELAY) == pdTRUE) {
            printf("CelOut: Item na Entrada, processando...\n");
            vTaskDelay(pdMS_TO_TICKS(TEMPO_PRODUCAO_M1_M2));
            printf("CelOut: Item Entregue!\n");
            xSemaphoreGive(xTemEntradaCelOut);
        }
    }
}