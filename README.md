# Simulação de Célula de Manufatura com FreeRTOS

## Descrição do Projeto

Este projeto implementa a simulação de uma célula de manufatura utilizando FreeRTOS. O sistema é composto por uma célula de entrada, máquinas de processamento e robôs que transportam os itens entre os diferentes pontos do processo de fabricação.

* [Código Principal do Projeto](src/main.c).
* [Link do Vídeo de Apresentação](https://www.youtube.com/watch?v=ljetrFXy6fc)

## Estrutura do Sistema

O sistema é composto pelos seguintes elementos:
- **Célula de Entrada**: Responsável por receber os pacotes e disponibilizá-los para processamento.
- **Máquinas de Processamento**:
  - **M1**: Primeira etapa do processamento.
  - **M2 e M3**: Segunda etapa do processamento (máquinas em paralelo).
  - **M4**: Etapa final do processamento.
- **Robôs**:
  - **R1**: Transporta pacotes da Célula de Entrada para a M1.
  - **R2 e R3**: Transporta pacotes da M1 para a M2 e M3, respectivamente.
  - **R4**: Transporta pacotes da M2 ou M3 para a M4.

Cada robô e máquina possui um tempo de operação definido conforme as regras do projeto.

## Como Rodar o Projeto

### Pré-requisitos

- **Versão do FreeRTOS:** `FreeRTOSv202210.01-LTS`  
- **Site Oficial:** [FreeRTOS.org](https://freertos.org/)
- **Linux Distro:** Ubuntu 24.04 LTS

### Instalando FreeRTOS

1. **Baixando FreeRTOS LTS**

   Baixe a versão estável do FreeRTOS a partir do site oficial: [FreeRTOSv202210.01-LTS](https://freertos.org/)

   Desse modo, extraia o arquivo e deixe em um local acessível, por exemplo:

   ```bash
   unzip FreeRTOSv202210.01-LTS
   ```

2. **Defina a Variável de Ambiente**

   Adicione o seguinte recurso ao `.profile`, `.bashrc`, ou `.zshrc`:

   ```bash
   export FREERTOS_PATH=~/FreeRTOSv202210.01-LTS/FreeRTOS-LTS
   ```

   Depois, reinicie a máquina ou atualize as variáveis no terminal com:

   ```bash
   source ~/.profile
   ```

3. **Outras Dependências**

   Instale as seguintes dependências no seu WSL Debian:

   ```bash
   sudo apt update
   sudo apt install build-essential
   ```

## Autor(es)
Projeto desenvolvido para a disciplina **STR 2024.2 - Sistemas de Automação para Monitoramento Inteligente**.
Professor: `KYLLER COSTA GORGONIO`

