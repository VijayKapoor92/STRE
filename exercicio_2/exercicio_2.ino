/*
  Programa: Blink com semáforos e threads
  Autor: Vijay Kapoor
  Data: 30/04/2021
*/

/* Inclui as bibliotecas necessarias */
#include <Arduino_FreeRTOS.h>
#include <semphr.h>

/* Define - LED PINS */
#define LED_PIN_BLUE 13
#define LED_PIN_RED 11

/* Define 2 tarefas */
void blink_blue( void *pvParameters );
void blink_red( void *pvParameters );

/* Semaforo utilizado */
SemaphoreHandle_t xSerial_semaphore;

/* A funcao setup eh chamada quando inicializa o sistema */
void setup() {
  
  /* Inicializa serial (baudrate 9600) */
  Serial.begin(9600);

  /* Inicializa e configura os LEDS */
  pinMode(LED_PIN_BLUE, OUTPUT);
  digitalWrite(LED_PIN_BLUE, LOW);
  pinMode(LED_PIN_RED, OUTPUT);
  digitalWrite(LED_PIN_RED, LOW);

  // Espera pro serial conectar.
  while (!Serial) {
    ;
  }

  /* Criação do semaforo */
  xSerial_semaphore = xSemaphoreCreateMutex();

  /* Sem semaforo o funcionamento esta comprometido. Nada mais deve ser feito. */
  if (xSerial_semaphore == NULL)
    {
        Serial.println("Erro: nao e possivel criar o semaforo");
        while(1);
    }
 
    /* Criação das tarefas */
    xTaskCreate( blink_blue /* Funcao a qual esta implementado o que a tarefa deve fazer */
               , "Blue" /* Nome (para fins de debug, se necessário) */
               , 128 /* Tamanho da stack (em words) reservada para essa tarefa */
               , NULL /* Parametros passados (nesse caso, não há) */
               , 3 /* Prioridade */
               , NULL ); /* Handle da tarefa, opcional (nesse caso, não há) */
 
    xTaskCreate( blink_red
               , "Red"
               , 128
               , NULL
               , 2
               , NULL );

  /* A partir deste momento, o scheduler de tarefas entra em ação e as tarefas executam */
}

void loop()
{
   /* Tudo é executado nas tarefas. Há nada a ser feito aqui. */
}

/* --------------------------------------------------*/
/* ---------------------- Tarefas -------------------*/
/* --------------------------------------------------*/
 
void blink_blue( void *pvParameters )
{
    (void) pvParameters;
    while(1)
    {
        /* ATENÇÃO: NUNCA USE A FUNÇÃO delay() QUANDO ESTIVER USANDO FREERTOS!
           em seu lugar, use a função vTaskDelay( tempo / portTICK_PERIOD_MS );, substituindo "tempo" pelo tempo de delay 
          (em ms) desejado.
        */
        digitalWrite(LED_PIN_BLUE, HIGH);
        vTaskDelay( 250 / portTICK_PERIOD_MS );
        digitalWrite(LED_PIN_BLUE, LOW);
        vTaskDelay( 250 / portTICK_PERIOD_MS );
 
        /* Para fins de teste de ocupação de stack, printa na serial o high water mark */
        xSemaphoreTake(xSerial_semaphore, portMAX_DELAY );
        xSemaphoreGive(xSerial_semaphore);
    }
}

void blink_red( void *pvParameters )
{
    (void) pvParameters;
    while(1)
    {
        /* ATENÇÃO: NUNCA USE A FUNÇÃO delay() QUANDO ESTIVER USANDO FREERTOS!
           em seu lugar, use a função vTaskDelay( tempo / portTICK_PERIOD_MS );, substituindo "tempo" pelo tempo de delay 
          (em ms) desejado.
        */
        digitalWrite(LED_PIN_RED, HIGH);
        vTaskDelay( 2500 / portTICK_PERIOD_MS );
        digitalWrite(LED_PIN_RED, LOW);
        vTaskDelay( 2500 / portTICK_PERIOD_MS );
 
        /* Para fins de teste de ocupação de stack, printa na serial o high water mark */
        xSemaphoreTake(xSerial_semaphore, portMAX_DELAY );
        xSemaphoreGive(xSerial_semaphore);
    }
}
